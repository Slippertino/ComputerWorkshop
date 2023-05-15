#include "nullvalidator.h"

namespace ComputerWorkshop {

NullValidator::NullValidator(QObject* parent) : QValidator(parent)
{ }

NullValidator::NullValidator(QValidator* base, QObject* parent) : NullValidator(parent) {
    base_ = base;
}

void NullValidator::set_base(QValidator* base) {
    base_ = base;
}

QValidator::State NullValidator::validate(QString& input, int& pos) const {
    if (null_validator_->validate(input, pos) == State::Acceptable) {
        return State::Acceptable;
    }

    if (base_) {
        return base_->validate(input, pos);
    }

    return State::Invalid;
}

} // namespace ComputerWorkshop