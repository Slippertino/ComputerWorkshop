#pragma once

#include <optional>
#include <QString>
#include <QRegExpValidator>
#include <QDateTime>

namespace ComputerWorkshop {

class DateTimeValidator final : public QValidator {
public:
    DateTimeValidator(QObject* parent = nullptr);

    DateTimeValidator(const QString& format, QObject* parent = nullptr);

    QValidator::State validate(QString& input, int& pos) const override final;

private:
    inline static const QRegExpValidator* base_date_validator_ = 
        new QRegExpValidator(QRegExp(
            "\\d{4}-(0{1}\\d{1}|10|11|12)-([0-2]{1}\\d|30|31) ([0-1]{1}\\d|20|21|22|23):([0-5]{1}\\d{1})"
    ));

    QString format_;
};

} // namespace ComputerWorkshop
