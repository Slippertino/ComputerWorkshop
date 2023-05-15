#pragma once

#include <QUuid>
#include <QString>
#include <QDateTime>
#include <optional>
#include "user.h"

namespace ComputerWorkshop {

struct UserData {
    User sys_user;
    std::optional<QString> name = std::nullopt;
    std::optional<QString> phone = std::nullopt;
};

} // namespace ComputerWorkshop
