#pragma once

#include <QHash>
#include <QString>
#include "staticlookup.h"
#include <model/services/entitycontext/operationrighttype.h>

namespace ComputerWorkshop {

class OperationRightNamesLookup final : public IStaticLookup<OperationRightNamesLookup> {
public:
	QList<QString> get_alias_values() const override final {
		return ops_names_forward_.keys();
	}

	QString get_source_by_alias(const QString& alias) override final {
		return ops_names_forward_.value(alias);
	}

	QString get_alias_by_source(const QString& src) override final {
		return ops_names_reversed_.value(src);
	}

private:
	void setup_once() override final {
		for (const auto& name : ops_names_forward_.keys()) {
			ops_names_reversed_.insert(ops_names_forward_.value(name), name);
		}
	}

private:
	inline static QHash<QString, QString> ops_names_forward_ = {
		{ "Нет доступа",								QString::number(NONE)						},
		{ "Создание",									QString::number(CREATE)						},
		{ "Чтение",										QString::number(READ)						},
		{ "Редактирование",								QString::number(UPDATE)						},
		{ "Удаление",									QString::number(DELETE)						},
		{ "Создание, Чтение",							QString::number(CREATE_READ)				},
		{ "Создание, Редактирование",					QString::number(CREATE_UPDATE)				},
		{ "Создание, Удаление",							QString::number(CREATE_DELETE)				},
		{ "Чтение, Редактирование",						QString::number(READ_UPDATE)				},
		{ "Чтение, Удаление",							QString::number(READ_DELETE)				},
		{ "Редактирование, Удаление",					QString::number(UPDATE_DELETE)				},
		{ "Создание, Чтение, Редактирование",			QString::number(CREATE_READ_UPDATE)			},
		{ "Создание, Чтение, Удаление",					QString::number(CREATE_READ_DELETE)			},
		{ "Создание, Редактирование, Удаление",			QString::number(CREATE_UPDATE_DELETE)		},
		{ "Чтение, Редактирование, Удаление",			QString::number(READ_UPDATE_DELETE)			},
		{ "Создание, Чтение, Редактирование, Удаление", QString::number(CREATE_READ_UPDATE_DELETE)	},
	};

	inline static QHash<QString, QString> ops_names_reversed_;
};

} // namespace ComputerWorkshop