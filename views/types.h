#pragma once

#include <optional>
#include <QString>
#include <QValidator>
#include "datainputs/datainputbase.h"

namespace ComputerWorkshop {

struct HeaderData {
    QString name;
    IDataInput* input;
};

} // namespace ComputerWorkshop