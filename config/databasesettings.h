#pragma once

#include <QString>

namespace ComputerWorkshop {

struct DatabaseSettings {
    QString driver;
    QString host;
    QString db_name;
    QString user;
    QString password;
};

} // namespace ComputerWorkshop
