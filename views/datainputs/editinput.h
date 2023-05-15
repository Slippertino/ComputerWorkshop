#pragma once

#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QValidator>
#include "datainputbase.h"

namespace ComputerWorkshop {

class EditInput : public IDataInput {
public:
	EditInput(const QString& ph = "") : IDataInput(DataInputType::EDIT_INPUT) {
		input_->setPlaceholderText(ph);
		input_->setAlignment(Qt::AlignCenter);
	}

	QString get_data() const override {
		return input_->text();
	}

	void set_data(const QString& text) override {
		input_->setText(text);
	}

	void clear() override {
		input_->clear();
	}

	QWidget* get_widget() const override {
		return input_;
	}

	~EditInput() {
		delete input_;
	}

private:
	QLineEdit* input_ = new QLineEdit;
};

} // namespace ComputerWorkshop