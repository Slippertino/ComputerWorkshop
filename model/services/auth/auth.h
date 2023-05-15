#pragma once

#include <QCryptoGraphicHash>
#include <model/appdata.h>
#include <model/entities/user.h>
#include <model/entities/employee.h>
#include <model/services/database/database.h>
#include <model/services/usersession/usersession.h>
#include <model/services/entitycontext/entitycontext.h>
#include "autherrorcode.h"

namespace ComputerWorkshop {

class Auth {
public:
    AuthStatusCode try_register_user(const UserData& usr, const QString& password);
    AuthStatusCode try_authorize_user(const UserData& usr, const QString& password);

private:
    QString get_password_hash(const QString& password);
};

} // namespace ComputerWorkshop
