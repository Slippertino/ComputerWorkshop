#pragma once

#include <QtGlobal>

namespace ComputerWorkshop {

enum class AuthStatusCode : quint16 {
	SUCCESS,
	UNEXISTING_EMPLOYEE_ERROR,
	EXISTING_USER_ERROR,
	WRONG_LOGIN_OR_PASSWORD_ERROR,
	REGISTRATION_ERROR,
};


inline uint qHash(AuthStatusCode key, uint seed) {
	return ::qHash(static_cast<quint16>(key), seed);
}

} // namespace ComputerWorkshop