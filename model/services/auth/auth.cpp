#include "auth.h"

namespace ComputerWorkshop {

AuthStatusCode Auth::try_register_user(const UserData& usr, const QString& password) {
	auto context = AppData::inst().get_service<EntityContext>();
	EntityOperationError error;

	QList<Employee> empls;
	context->read_object_by_sys<Employee>(
		{ Employee::pk },
		{
			ColumnFilter()
			.column(Employee::field_full_name).equal(usr.name.value()).and()
			.column(Employee::field_phone).equal(usr.phone.value())
		},
		empls,
		error
	);

	if (empls.isEmpty()) {
		return AuthStatusCode::UNEXISTING_EMPLOYEE_ERROR;
	}

	auto id = empls.first().get(Employee::pk);

	QList<User> usrs;
	context->read_object_by_sys<User>(
		{ User::field_login },
		{
			ColumnFilter()
			.column(User::field_login).equal(usr.sys_user.get(User::field_login)).or()
			.column(User::field_employee_id).equal(id)
		},
		usrs,
		error
	);

	if (!usrs.isEmpty()) {
		return AuthStatusCode::EXISTING_USER_ERROR;
	}

	User new_user = usr.sys_user;
	new_user.employee_id.set(id);
	new_user.password.set(get_password_hash(password));

	if (!AppData::inst().get_service<EntityContext>()->create_object_by_sys<User>(new_user, error)) {
		return AuthStatusCode::REGISTRATION_ERROR;
	}

	return AuthStatusCode::SUCCESS;
}

AuthStatusCode Auth::try_authorize_user(const UserData& usr, const QString& password) {
	auto context = AppData::inst().get_service<EntityContext>();

	QList<User> usrs;
	EntityOperationError error;

	context->read_object_by_sys<User>(
		{ User::pk, User::field_login, User::field_employee_id, User::field_password },
		{ 
			ColumnFilter()
			.column(User::field_login)
			.equal(usr.sys_user.get(User::field_login)) 
		},
		usrs,
		error
	);

	if (usrs.isEmpty()) {
		return AuthStatusCode::WRONG_LOGIN_OR_PASSWORD_ERROR;
	}

	auto& user = usrs.first();

	if (user.password.value != get_password_hash(password)) {
		return AuthStatusCode::WRONG_LOGIN_OR_PASSWORD_ERROR;
	}

	AppData::inst().get_service<UserSession>()->setup(user);

	return AuthStatusCode::SUCCESS;
}

QString Auth::get_password_hash(const QString& password) {
	return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

} // namespace ComputerWorkshop
