#include "usersession.h"
#include <model/appdata.h>
#include <model/services/entitycontext/entitycontext.h>

namespace ComputerWorkshop {

void UserSession::setup(const User& usr) {
    user_.sys_user = usr;

    auto id = user_.sys_user.get(User::field_employee_id);

    if (id.isNull()) {
        return;
    }

    QList<Employee> empls;
    EntityOperationError error;
    auto res = AppData::inst().get_service<EntityContext>()->read_object_by_sys<Employee>(
        { Employee::field_full_name, Employee::field_phone },
        { ColumnFilter().column(Employee::pk).equal(id) },
        empls,
        error
    );

    if (!empls.isEmpty()) {
        auto& empl = empls.first();
        user_.name = empl.get(Employee::field_full_name).toString();
        user_.phone = empl.get(Employee::field_phone).toString();
    }
}

const UserData& UserSession::get_user() const {
    return user_;
}

} // namespace ComputerWorkshop