#include "commonvalidators.h"

namespace ComputerWorkshop {

QValidator* ValidatorsFactory::nullable(QValidator* base) {
    return new NullValidator(base);
}

QValidator* ValidatorsFactory::email() {
    return new QRegExpValidator(QRegExp("\\w+@\\w+\\.\\w+"));
}

QValidator* ValidatorsFactory::working_hours() {
    return new QRegExpValidator(QRegExp("[0-2][0-9]:[0-5][0-9] - [0-2][0-9]:[0-5][0-9]"));
}

QValidator* ValidatorsFactory::phone() {
    return new QRegExpValidator(QRegExp("\\+7 \\d{3} \\d{3} \\d{2} \\d{2}"));
}

QValidator* ValidatorsFactory::date(const QString& format) {
    return new DateTimeValidator(format);
}

QValidator* ValidatorsFactory::uuid() {
    QRegExpValidator* res = new QRegExpValidator();

    QRegExp reg;
    reg.setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
    reg.setPattern("([a-z]|\\d){8}-([a-z]|\\d){4}-([a-z]|\\d){4}-([a-z]|\\d){4}-([a-z]|\\d){12}");

    res->setRegExp(reg);

    return res;
}

QValidator* ValidatorsFactory::string_pattern(const QString& pattern) {
    return new QRegExpValidator(QRegExp(pattern));
}

QValidator* ValidatorsFactory::string_size(
    std::optional<quint32> min,
    std::optional<quint32> max
) {
    QString base = ".{%1,%2}";

    base = min.has_value() ? base.arg(min.value()) : base.arg("");
    base = max.has_value() ? base.arg(max.value()) : base.arg("");

    return new QRegExpValidator(QRegExp(base));
}

QValidator* ValidatorsFactory::int_range(
    std::optional<quint32> min,
    std::optional<quint32> max
) {
    QIntValidator* res = new QIntValidator();

    if (min.has_value()) res->setBottom(min.value());
    if (max.has_value()) res->setTop(max.value());

    return res;
}

QValidator* ValidatorsFactory::real_range(
    std::optional<qreal> min,
    std::optional<qreal> max,
    std::optional<quint32> decimals
) {
    QDoubleValidator* res = new QDoubleValidator();
    res->setNotation(QDoubleValidator::StandardNotation);

    if (min.has_value())        res->setBottom(min.value());
    if (max.has_value())        res->setTop(max.value());
    if (decimals.has_value())   res->setDecimals(decimals.value());

    return res;
}

} // namespace ComputerWorkshop