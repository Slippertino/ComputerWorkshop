#pragma once

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QFile>
#include <QFileInfo>
#include <stdexcept>
#include "databasesettings.h"

namespace ComputerWorkshop {

class Config
{
    friend class ConfigParser;

public:
    static Config from_file(QString file_path);

    const DatabaseSettings& get_db_settings() const;

private:
    DatabaseSettings db_settings_;
};

} // namespace ComputerWorkshop
