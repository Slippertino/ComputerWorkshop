#pragma once

#include <functional>
#include <QHash>
#include <model/services/database/database.h>
#include "fields.h"
#include "validators/nullvalidator.h"
#include "validators/commonvalidators.h"

namespace ComputerWorkshop {

#define DECLARE_ENTITY_BEGIN(cls_name) class cls_name : public Entity<cls_name> {
#define ENTITY_NAME(name) public: QString get_table_name() const override { return #name; }
#define ENTITY_FIELD(type, name) public: inline static QString field_##name = #name; Field<type> name;
#define ENTITY_FIELD_DATA_BEGIN(cls_name)	QHash<QString, FieldData<cls_name>> get_fields_data() const override { return {
#define ENTITY_FIELD_DATA(cls_name, name, validator, readonly) { #name, { [](cls_name* target) { return &target->name; }, validator, readonly }, },
#define ENTITY_FIELD_DATA_END() };}
#define DECLARE_ENTITY_END() };

enum class FkModifyRuleType {
	CASCADE,
	NO_ACTION,
	SET_NULL,
	SET_DEFAULT
};
Q_DECLARE_METATYPE(FkModifyRuleType)

struct DepEntityData {
	QString dep_entity;
	QString fk;
	FkModifyRuleType on_update;
	FkModifyRuleType on_delete;
};

template<class T>
class Entity {
protected:
	template<class T>
	struct FieldData {
		std::function<IField* (T*)> accessor;
		std::optional<QValidator*> validator = std::nullopt;
		bool readonly = false;
	};

public:
	inline static const QString pk = "id";
	Field<QUuid> id;

public:
	static void setup() {
		QSqlQuery query;
		auto db = AppData::inst().get_service<Database>();

		auto tname = table_name();

		db->execute_query(
			"SELECT Tab.CONSTRAINT_NAME, Col.COLUMN_NAME FROM "
			"INFORMATION_SCHEMA.TABLE_CONSTRAINTS Tab, "
			"INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE Col "
			"WHERE "
			"Col.CONSTRAINT_NAME = Tab.CONSTRAINT_NAME AND "
			"Col.TABLE_NAME = Tab.TABLE_NAME AND "
			"Col.TABLE_NAME = ? AND "
			"Tab.CONSTRAINT_TYPE = 'UNIQUE' ",
			query,
			{ tname }
		);

		QHash<QString, QList<QString>> data;

		while (query.next()) {
			auto cname = query.value("CONSTRAINT_NAME").toString();
			auto tname = query.value("COLUMN_NAME").toString();

			data[cname].append(tname);
		}

		for (const auto& uks : data) {
			unique_keys_.append(uks);
		}

		db->execute_query(
			"EXEC sp_fkeys @fktable_name = ?",
			query,
			{ tname }
		);

		while (query.next()) {
			auto fk_field = query.value("FKCOLUMN_NAME").toString();
			auto pk_table = query.value("PKTABLE_NAME").toString();

			foreign_keys_.insert(fk_field, pk_table);
		}

		db->execute_query(
			"EXEC sp_fkeys @pktable_name = ?",
			query,
			{ T::table_name() }
		);

		while (query.next()) {
			DepEntityData data;

			data.dep_entity = query.value("FKTABLE_NAME").toString();
			data.fk = query.value("FKCOLUMN_NAME").toString();
			data.on_update = query.value("UPDATE_RULE").value<FkModifyRuleType>();
			data.on_delete = query.value("DELETE_RULE").value<FkModifyRuleType>();
			
			dependents_.append(data);
		}
	}

	static QString table_name() {
		return T().get_table_name();
	}

	static bool readonly(const QString& field) {
		return T().get_fields_data_base().value(field).readonly;
	}

	static std::optional<QValidator*> validator(const QString& field) {
		return T().get_fields_data_base().value(field).validator;
	}

	static QList<QString> fields() {
		return T().get_fields_data_base().keys();
	}

	static const QList<QList<QString>>& ukeys() {
		return unique_keys_;
	}

	static const QHash<QString, QString>& fkeys() {
		return foreign_keys_;
	}

	static const QList<DepEntityData>& deps() {
		return dependents_;
	}

	static T from_map(const QVariantMap& mp) {
		T res;

		for (const auto& kmp : mp.keys()) {
			res.set(kmp, mp.value(kmp));
		}

		return res;
	}

	void generate_id(
		const std::function<bool(const QString&)> pred = 
		[](const QString&) { return true; }
	) {
		do {
			id.value = QUuid::createUuid();
		} while (!pred(id.get().toString()));
	}
	
	QVariant get(const QString& field) const {
		return get_fields_data_base().value(field).accessor(get_derived())->get();
	}

	void set(const QString& field, const QVariant& val) {
		get_fields_data_base().value(field).accessor(get_derived())->set(val);
	}

	QVariantMap to_map(const QList<QString>& fields) const {
		QVariantMap res;

		for (const auto& fld : fields) {
			res.insert(fld, get(fld));
		}

		return res;
	}

	virtual QString get_table_name() const = 0;
	virtual QHash<QString, FieldData<T>> get_fields_data() const = 0;

	virtual ~Entity() = default;

protected:
	const QHash<QString, FieldData<T>>& get_fields_data_base() const {
		static const QHash<QString, FieldData<T>> fields = init_fields_data(get_derived());

		return fields;
	}

	static QHash<QString, FieldData<T>> init_fields_data(T* obj) {
		QHash<QString, FieldData<T>> res = {
			{
				pk,
				{
					[](T* target) { return &target->id; },
					std::nullopt,
					true
				},
			},
		};

		res.insert(obj->get_fields_data());
		
		return res;
	}

private:
	T* get_derived() const {
		return static_cast<T*>(const_cast<Entity<T>*>(this));
	}

protected:
	inline static QList<QList<QString>> unique_keys_;
	inline static QHash<QString, QString> foreign_keys_;
	inline static QList<DepEntityData> dependents_;
};

} // namespace ComputerWorkshop