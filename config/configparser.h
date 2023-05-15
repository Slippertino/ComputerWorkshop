#pragma once

#include <QSet>
#include <QHash>
#include <QXmlDefaultHandler>
#include <functional>
#include "config.h"

namespace ComputerWorkshop {

class ConfigParser : public QXmlDefaultHandler {
public:
    ConfigParser() = delete;
    ConfigParser(Config& cfg);

    bool startElement(
        const QString&,
        const QString&,
        const QString& name,
        const QXmlAttributes& attrs
    ) override;

    bool endElement(
        const QString&,
        const QString&,
        const QString& name
    ) override;

    bool characters(
        const QString& text
    ) override;

private:
    void handle_db_info(const QString& name) const;

private:
    static const QHash<QString, std::function<void(Config&, const QString&)>> field_handlers_;

    Config& cfg_;
    QSet<QString> current_elements_;
    QString current_text_;
};

} // namespace ComputerWorkshop
