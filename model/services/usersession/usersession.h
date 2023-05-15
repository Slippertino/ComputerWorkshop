#pragma once

#include <QVariant>
#include <model/services/database/database.h>
#include <model/entities/userdata.h>
#include <model/entities/user.h>
#include <model/entities/employee.h>

namespace ComputerWorkshop {

class UserSession
{
public:
    void setup(const User& usr);

    const UserData& get_user() const;

private:
    UserData user_;
};

} // namespace ComputerWorkshop