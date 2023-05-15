#pragma once

#include <QtGlobal>

namespace ComputerWorkshop {

enum class EntityOperationErrorCode : quint16 {
	UNIQUE_RULE_VIOLATED_ERROR,
	UNEXISTING_FOREIGN_RECORD_ERROR,
	ACCESS_RIGHTS_VIOLATED_ERROR,
	FK_DELETE_RULE_FORBIDDEN,
	UNEXPECTED_DBMS_ERROR
};

inline uint qHash(EntityOperationErrorCode key, uint seed) {
	return ::qHash(static_cast<quint16>(key), seed);
}

} // namespace ComputerWorkshop