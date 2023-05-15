#include "configparser.h"

namespace ComputerWorkshop {

ConfigParser::ConfigParser(Config& cfg) : cfg_(cfg)
{ }

bool ConfigParser::startElement(
    const QString& a1,
    const QString& a2,
    const QString& name,
    const QXmlAttributes& attrs
) {
    current_elements_.insert(name);

    return true;
}

bool ConfigParser::endElement(
    const QString& a1,
    const QString& a2,
    const QString& name
) {
    handle_db_info(name);
    current_elements_.remove(name);

    return true;
}

bool ConfigParser::characters(
    const QString& text
) {
    current_text_ = text;

    return true;
}


void ConfigParser::handle_db_info(const QString& name) const {
    if (current_elements_.contains("database") &&
        current_elements_.contains(name)) {
        field_handlers_[name](cfg_, current_text_);
    }
}

const QHash<QString, std::function<void(Config&, const QString&)>> ConfigParser::field_handlers_ =
{
    { "database", [](Config& cfg, const QString& text) {  } },
    { "driver",   [](Config& cfg, const QString& text) { cfg.db_settings_.driver = text;   } },
    { "host",     [](Config& cfg, const QString& text) { cfg.db_settings_.host = text;     } },
    { "name",     [](Config& cfg, const QString& text) { cfg.db_settings_.db_name = text;  } },
    { "user",     [](Config& cfg, const QString& text) { cfg.db_settings_.user = text;     } },
    { "password", [](Config& cfg, const QString& text) { cfg.db_settings_.password = text; } },
};

} // namespace ComputerWorkshop