#pragma once

#include <optional>
#include <QRegExpValidator>
#include <QIntValidator>
#include "datetimevalidator.h"
#include "nullvalidator.h"

namespace ComputerWorkshop {

class ValidatorsFactory {
public:
    static QValidator* nullable(QValidator*);

    static QValidator* email();

    static QValidator* working_hours();

    static QValidator* phone();

    static QValidator* date(const QString& format);

    static QValidator* uuid();

    static QValidator* string_pattern(
        const QString& pattern
    );

    static QValidator* string_size(
        std::optional<quint32> min,
        std::optional<quint32> max
    );

    static QValidator* int_range(
        std::optional<quint32> min,
        std::optional<quint32> max
    );

    static QValidator* real_range(
        std::optional<qreal> min,
        std::optional<qreal> max,
        std::optional<quint32> decimals = 10
    );
};

} // namespace ComputerWorkshop
