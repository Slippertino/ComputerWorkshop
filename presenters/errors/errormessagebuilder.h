#pragma once

#include <QHash>
#include <QString>
#include <model/services/entitycontext/entityoperationerror.h>
#include "../lookups/operationrightnameslookup.h"
#include "../entitypresenterbase.h"

namespace ComputerWorkshop {

class ErrorMessageBuilder {
public:
	static QString build(const EntityOperationError& error) {
		return error_builders_.value(error.code)(error);
	}

private:
	static QString build_by_access_viloated(const EntityOperationError& error) {
		return QString("Нет доступа по причине недостаточности прав \"%1\" для совершения операции \"%2\" над таблицей \"%3\"")
			.arg(OperationRightNamesLookup().get_alias_by_source(QString::number(error.user_right)))
			.arg(OperationRightNamesLookup().get_alias_by_source(QString::number(error.required_right)))
			.arg(IEntityPresenter::get_entity_presenters().value(error.entity_name)->get_entity_display_name());
	}

	static QString build_by_unique_rule_violated(const EntityOperationError& error) {
		auto presenter = IEntityPresenter::get_entity_presenters().value(error.entity_name);

		QStringList names;
		for (const auto& uf : error.ext_names) {
			names << QString("\"%1\"").arg(presenter->get_name(uf));
		}

		return QString("Уникальное(-ые) значение(-я) поля(-ей) (%1) таблицы \"%2\" уже существуют.")
			.arg(names.join(','))
			.arg(IEntityPresenter::get_entity_presenters().value(error.entity_name)->get_entity_display_name());
	}

	static QString build_by_unexisting_foreign_record(const EntityOperationError& error) {
		auto presenter = IEntityPresenter::get_entity_presenters().value(error.entity_name);

		return QString("Записи, на которую ссылается поле \"%1\" таблицы \"%2\", не существует в базе данных.")
			.arg(presenter->get_name(error.ext_names.first()))
			.arg(presenter->get_entity_display_name());
	}

	static QString build_by_forbidden_delete_rule(const EntityOperationError& error) {
		auto presenter		= IEntityPresenter::get_entity_presenters().value(error.entity_name);
		auto dep_presenter	= IEntityPresenter::get_entity_presenters().value(error.ext_names[0]);

		return QString("Невозможно удалить запись таблицы \"%1\", пока поле \"%2\" таблицы \"%3\" ссылается на нее.")
			.arg(presenter->get_entity_display_name())
			.arg(dep_presenter->get_name(error.ext_names[1]))
			.arg(dep_presenter->get_entity_display_name());
	}

	static QString build_by_unexpected(const EntityOperationError& error) {
		return error.messages.join('\n');
	}

private:
	inline static const QHash<EntityOperationErrorCode, std::function<QString(const EntityOperationError&)>> error_builders_ = {
		{ 
			EntityOperationErrorCode::ACCESS_RIGHTS_VIOLATED_ERROR,
			&ErrorMessageBuilder::build_by_access_viloated		
		},
		{ 
			EntityOperationErrorCode::UNIQUE_RULE_VIOLATED_ERROR,
			&ErrorMessageBuilder::build_by_unique_rule_violated	
		},
		{ 
			EntityOperationErrorCode::UNEXISTING_FOREIGN_RECORD_ERROR,
			&ErrorMessageBuilder::build_by_unexisting_foreign_record 
		},
		{
			EntityOperationErrorCode::FK_DELETE_RULE_FORBIDDEN,
			&ErrorMessageBuilder::build_by_forbidden_delete_rule
		},
		{ 
			EntityOperationErrorCode::UNEXPECTED_DBMS_ERROR,
			&ErrorMessageBuilder::build_by_unexpected				
		},
	};
};

} // namespace ComputerWorkshop