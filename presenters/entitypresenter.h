#pragma once

#include <QList>
#include <QVariantMap>
#include "../views/entityeditorform.h"
#include "views/types.h"
#include <model/services/entitycontext/entitycontext.h>
#include "entitypresenterbase.h"
#include "lookups/lookups.h"
#include "views/datainputs/datainputs.h"
#include "errors/errormessagebuilder.h"
#include "commoneditplaceholders.h"
#include "model/reporter.h"

namespace ComputerWorkshop {

#define DECLARE_ENTITY_PRESENTER_BEGIN(presenter, entity) \
	class presenter final : public EntityPresenter<presenter, entity> { \
	public: \
		presenter() = delete; \
		presenter(EntityEditorForm* form) : EntityPresenter(form) \
		{ }

#define DECLARE_ENTITY_PRESENTER_END() };

#define DECLARE_EP_FIELDS_DATA_BEGIN() \
	public: QList<EntityPresenter::FieldData> get_own_fields_data() const override { return {
#define EP_FIELD_DATA(name, display_name, data_input) { #name, #display_name, data_input },
#define DECLARE_EP_FIELDS_DATA_END() };}

#define ENTITY_DISPLAY_NAME(name) \
public: QString get_entity_display_name() const override { return #name; }

#define ENTITY_ALIAS_ARG_1(arg)	#arg
#define ENTITY_ALIAS_ARG_2(arg1, arg2) #arg1, ENTITY_ALIAS_ARG_1(arg2)
#define ENTITY_ALIAS_ARG_3(arg1, arg2, arg3) #arg1, ENTITY_ALIAS_ARG_2(arg2, arg3)
#define ENTITY_ALIAS_ARG_N(_1, _2, _3, N, ...) N 
#define ENTITY_CONVERT(args) ENTITY_ALIAS_ARG_N args
#define ENTITY_ALIAS_CHOOSE_FROM_ARG_COUNT(...) \
        ENTITY_CONVERT((__VA_ARGS__, ENTITY_ALIAS_ARG##_3, ENTITY_ALIAS_ARG##_2, ENTITY_ALIAS_ARG##_1))
#define ENTITY_ALIAS(...) ENTITY_ALIAS_CHOOSE_FROM_ARG_COUNT(__VA_ARGS__)(__VA_ARGS__)

#define ENTITY_ALIASES(...) \
public: \
	const QList<QString>& get_alias_names() const override { \
		static const QList<QString> aliases = { ENTITY_ALIAS(__VA_ARGS__) }; \
		return aliases; \
	} \

template<class TPresenter, class TEntity>
class EntityPresenter : public IEntityPresenter {
protected:
	struct FieldData {
		QString name;
		QString display_name;
		IDataInput* input;
	};

public:
	EntityPresenter() = delete;
	EntityPresenter(EntityEditorForm* editor) : IEntityPresenter(TEntity::table_name()), editor_(editor) {
		connect(editor_, &EntityEditorForm::object_added, this, &EntityPresenter<TPresenter, TEntity>::on_object_added);
		connect(editor_, &EntityEditorForm::object_updated, this, &EntityPresenter<TPresenter, TEntity>::on_object_updated);
		connect(editor_, &EntityEditorForm::object_deleted, this, &EntityPresenter<TPresenter, TEntity>::on_object_deleted);
		connect(editor_, &EntityEditorForm::reloaded, this, &EntityPresenter<TPresenter, TEntity>::on_reloaded);
		connect(editor_, &EntityEditorForm::report_requested, this, &EntityPresenter<TPresenter, TEntity>::on_report_requested);
	}

	void setup() override {
		IEntityPresenter::setup();
		TEntity::setup();

		auto entity_name = TEntity::table_name();
		auto entity_display_name = get_entity_display_name();

		names_.insert(entity_name, entity_display_name);
		names_.insert(entity_display_name, entity_name);

		const auto& fields = get_fields_data();

		QList<HeaderData> view_data;

		foreach(const FieldData& fld, fields) {
			names_.insert(fld.name, fld.display_name);
			names_.insert(fld.display_name , fld.name);

			inputs_.insert(fld.display_name, fld.input);

			switch (fld.input->get_type())
			{
			case DataInputType::EDIT_INPUT: {
				auto edit = qobject_cast<QLineEdit*>(fld.input->get_widget());
				edit->setReadOnly(TEntity::readonly(fld.name));

				auto vld = TEntity::validator(fld.name);
				if (vld.has_value()) {
					edit->setValidator(vld.value());
				}

				break;
			}
			case DataInputType::LOOKUP_INPUT: {
				static_cast<LookupInput*>(fld.input)->get_lookup()->setup();

				break;
			}
			default:
				break;
			}

			view_data.append({
				fld.display_name,
				fld.input
			});
		}

		editor_->setup(get_entity_display_name(), view_data, &data_);
	}

	QString get_name(const QString& name) const override {
		return names_.value(name);
	}

	virtual QString get_entity_display_name() const = 0;
	virtual const QList<QString>& get_alias_names() const = 0;
	virtual QList<FieldData> get_own_fields_data() const = 0;

	virtual ~EntityPresenter() {
		foreach(auto input, inputs_) {
			delete input;
		}
	}

public:
	void on_object_added(const QList<QString>& columns, QVariantMap data) {
		process_from_view(data);
		auto ent = TEntity::from_map(data);

        EntityOperationError error;
        if (!AppData::inst().get_service<EntityContext>()->create_object_by_user(ent, error)) {
            editor_->notify_error(ErrorMessageBuilder::build(error));
        }

		on_reloaded(columns);
	}

	void on_object_updated(const QList<QString>& columns, int number, QVariantMap data, QList<QString> updated) {
		data[pk_display_name] = data_[number][pk_display_name];
		process_from_view(data);
		auto ent = TEntity::from_map(data);

		for (auto& upd : updated) {
			upd = names_.value(upd);
		}

		EntityOperationError error;
        if (!AppData::inst().get_service<EntityContext>()->update_object_by_user(ent, updated, error)) {
            editor_->notify_error(ErrorMessageBuilder::build(error));
        }

		on_reloaded(columns);
	}

	void on_object_deleted(const QList<QString>& columns, int number) {
		auto data = data_[number];
		process_from_view(data);

		auto ent = TEntity::from_map(data);

		EntityOperationError error;
        if (!AppData::inst().get_service<EntityContext>()->delete_object_by_user(ent, error)) {
            editor_->notify_error(ErrorMessageBuilder::build(error));
        }

		on_reloaded(columns);
	}

	void on_reloaded(const QList<QString>& columns) {
		QList<TEntity> data;

		QList<QString> fields = { TEntity::pk };
		std::transform(columns.begin(), columns.end(), std::back_inserter(fields), [&](const QString& s) {
			return get_name(s);
		});

		if (fields.indexOf(TEntity::pk) == -1) {
			fields.push_front(TEntity::pk);
		}

		EntityOperationError error;
		if (!AppData::inst().get_service<EntityContext>()->read_object_by_user(fields, {}, data, error)) {
            editor_->notify_error(ErrorMessageBuilder::build(error));
            return;
        }

		data_.clear();
		for (auto& ent : data) {
			auto cur = ent.to_map(fields);
			process_from_model(cur);
			data_.append(cur);
		}

        editor_->update();
	}

	void on_report_requested(const QString& filename, const QList<QString>& columns) {
		auto user = AppData::inst().get_service<UserSession>()->get_user();
		Reporter::make_report(
			filename,
			user,
			QDateTime::currentDateTime(),
			get_entity_display_name(),
			columns,
			data_
		);
	}

private:
	void process_from_view(QVariantMap& data) {
		for (const auto& display_name : data.keys()) {
			auto name = names_.value(display_name);
			auto val = data.value(display_name);
			auto input = inputs_.value(display_name);

			QVariant new_val = val;

			if (input->get_type() == DataInputType::LOOKUP_INPUT) {
				auto lookup = static_cast<LookupInput*>(input)->get_lookup();

				lookup->update();
				new_val = lookup->get_source_by_alias(val.toString());
			}

			data.insert(name, new_val);
			data.remove(display_name);
		}
	}

	void process_from_model(QVariantMap& data) {
		for (const auto& name : data.keys()) {
			auto display_name = names_.value(name);
			auto val = data.value(name);
			auto input = inputs_.value(display_name);

			QVariant new_val = val;

			if (input->get_type() == DataInputType::LOOKUP_INPUT) {
				auto lookup = static_cast<LookupInput*>(input)->get_lookup();

				lookup->update();
				new_val = lookup->get_alias_by_source(val.toString());
			}

			data.insert(display_name, new_val);
			data.remove(name);
		}
	}

	QList<FieldData> get_fields_data() {
		QList<FieldData> res = {
			{ TEntity::pk, pk_display_name, new EditInput }
		};

		res.append(get_derived()->get_own_fields_data());

		return res;
	}

	TPresenter* get_derived() const {
		return static_cast<TPresenter*>(const_cast<EntityPresenter<TPresenter, TEntity>*>(this));
	}

private:
	QHash<QString, IDataInput*> inputs_;
	QHash<QString, QString> names_;
	EntityEditorForm* editor_;
	QList<QVariantMap> data_;
};

} // namespace ComputerWorkshop
