#pragma once

#include "model/entities/userdata.h"
#include "../views/authform.h"
#include "../model/services/auth/auth.h"
#include "../model/services/auth/autherrorcode.h"

namespace ComputerWorkshop {

class AuthPresenter : public QObject {

	Q_OBJECT

public:
	AuthPresenter() = delete;
	AuthPresenter(AuthForm* auth_form) : auth_form_(auth_form) {
		connect(
			auth_form_, SIGNAL(authed(const UserData&, const QString&)), 
			this,		SLOT(on_authed(const UserData&, const QString&))
		);

		connect(
			auth_form_, SIGNAL(registered(const UserData&, const QString&)),
			this,		SLOT(on_registered(const UserData&, const QString&))
		);
	}
	
private slots:
	void on_authed(const UserData& usr, const QString& pass) {
		auto code = AppData::inst().get_service<Auth>()->try_authorize_user(usr, pass);

		if (code == AuthStatusCode::SUCCESS) {
			auth_form_->notify_auth_success();
		}
		else {
			auth_form_->notify_auth_error(error_interpreter_.value(code));
		}
	}

	void on_registered(const UserData& usr, const QString& pass) {
		auto code = AppData::inst().get_service<Auth>()->try_register_user(usr, pass);

		if (code == AuthStatusCode::SUCCESS) {
			auth_form_->notify_register_success();
		}
		else {
			auth_form_->notify_register_error(error_interpreter_.value(code));
		}
	}

private:
	inline static const QHash<AuthStatusCode, QString> error_interpreter_ = {
		{ AuthStatusCode::UNEXISTING_EMPLOYEE_ERROR,		"Такого работника не существует"								},
		{ AuthStatusCode::EXISTING_USER_ERROR,				"Работник с такими данными уже зарегистрирован в системе"		},
		{ AuthStatusCode::REGISTRATION_ERROR,				"Не удалось зарегистрироваться в системе. Попробуйте еще раз"	},
		{ AuthStatusCode::WRONG_LOGIN_OR_PASSWORD_ERROR,	"Неверный логин или пароль. Попробуйте еще раз"					},
	};

private:
	AuthForm* auth_form_;
};

} // namespace ComputerWorkshop