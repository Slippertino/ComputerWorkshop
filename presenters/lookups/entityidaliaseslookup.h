#pragma once

#include <QHash>
#include <model/entities/entity.h>
#include <model/services/entitycontext/entitycontext.h>
#include "../entitypresenterbase.h"
#include "lookupbase.h"

namespace ComputerWorkshop {

template<class TEntity>
class EntityIdAliasesLookup : public ILookup {
public:
	EntityIdAliasesLookup() = default;

	void setup() override {
		auto target_table = TEntity::table_name();

		auto tpres = IEntityPresenter::get_entity_presenters().value(target_table);

		primary_field_ = tpres->get_name(IEntityPresenter::pk_display_name);

		for (const auto& alias : tpres->get_alias_names()) {
			alias_fields_.append(tpres->get_name(alias));
		}
	}
	
	QList<QString> get_alias_values() const override {
		return forward_data_.keys();
	}

	QString get_source_by_alias(const QString& alias) override {
		return forward_data_.value(alias);
	}

	QString get_alias_by_source(const QString& src) override {
		return reversed_data_.value(src);
	}

	void update() override {
		forward_data_.clear();
		reversed_data_.clear();

		QList<TEntity> data;
		EntityOperationError error;
		if (!AppData::inst().get_service<EntityContext>()->read_object_by_sys<TEntity>(
			alias_fields_ + QList<QString>{ primary_field_ }, 
			{ },
			data, 
			error
		)) {
			return;
		}

		foreach(const auto& ent, data) {
			auto pf = ent.get(primary_field_).toString();

			QString alias;
			for (auto i = 0; i < alias_fields_.size(); ++i) {
				alias += ent.get(alias_fields_[i]).toString();

				if (i + 1 != alias_fields_.size()) {
					alias += alias_separator_;
				}
			}

			forward_data_.insert(alias, pf);
			reversed_data_.insert(pf, alias);
		}
	}

private:
	inline static const QString alias_separator_ = ", ";

	QString primary_field_;
	QList<QString> alias_fields_;

	QHash<QString, QString> forward_data_;
	QHash<QString, QString> reversed_data_;
};

} // namespace ComputerWorkshop