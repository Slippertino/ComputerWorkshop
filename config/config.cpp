#include "config.h"
#include "configparser.h"

namespace ComputerWorkshop {

Config Config::from_file(QString file_path) {
    if (!QFileInfo::exists(file_path) || !QFileInfo(file_path).isFile()) {
        throw std::runtime_error("Неверный путь к конфигурационному файлу");
    }

    QFile file{ file_path };

    Config cfg;
    ConfigParser handler{cfg};

    try {
        QXmlInputSource source(&file);

        QXmlSimpleReader reader;

        reader.setContentHandler(&handler);

        reader.parse(source);

    } catch(...) {
        throw std::runtime_error("Конфигурационный файл не может быть обработан");
    }

    return cfg;
}

const DatabaseSettings& Config::get_db_settings() const {
    return db_settings_;
}

} // namespace ComputerWorkshop