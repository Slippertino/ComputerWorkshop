#pragma once

#include <QString>
#include <QList>
#include <QStringList>
#include "operationrighttype.h"
#include "entityoperationerrorcode.h"

namespace ComputerWorkshop {

struct EntityOperationError {
	OperationRightType user_right = OperationRightType::NONE;
	OperationRightType required_right = OperationRightType::NONE;
	EntityOperationErrorCode code;
	QString entity_name;
	QStringList ext_names;
	QStringList messages;
};

} // namespace ComputerWorkshop