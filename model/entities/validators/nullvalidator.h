#pragma once

#include <optional>
#include <QRegExpValidator>
#include <QIntValidator>

namespace ComputerWorkshop {

class NullValidator final : public QValidator {
public:
    NullValidator(QObject* parent = nullptr);

    NullValidator(QValidator* base, QObject* parent = nullptr);

    void set_base(QValidator* base);

    QValidator::State validate(QString& input, int& pos) const override final;

private:
    inline static const QRegExpValidator* null_validator_ = new QRegExpValidator(QRegExp(""));
    QValidator* base_ = nullptr;
};

} // namespace ComputerWorkshop
