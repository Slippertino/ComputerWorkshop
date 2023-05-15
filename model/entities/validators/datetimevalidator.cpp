#include "datetimevalidator.h"

namespace ComputerWorkshop {

DateTimeValidator::DateTimeValidator(QObject* parent) : QValidator(parent)
{ }

DateTimeValidator::DateTimeValidator(const QString& format, QObject* parent) : DateTimeValidator(parent) {
    format_ = format;
}

QValidator::State DateTimeValidator::validate(QString& input, int& pos) const {
    auto base_res = base_date_validator_->validate(input, pos);

    if (base_res == State::Invalid) {
        return base_res;
    }

    if (base_res == State::Acceptable) {
        return QDateTime::fromString(input, format_).isValid() 
            ? State::Acceptable 
            : State::Invalid;
    }

    return base_res;
}

} // namespace ComputerWorkshop