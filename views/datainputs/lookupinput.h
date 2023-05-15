#pragma once

#include <QString>
#include <QWidget>
#include <QComboBox>
#include "datainputbase.h"
#include "presenters/lookups/lookupbase.h"

namespace ComputerWorkshop {

class LookupBox : public QComboBox {

	Q_OBJECT

signals:
	void refreshed();

protected:
	void mousePressEvent(QMouseEvent* e) override {
		emit refreshed();

		QComboBox::mousePressEvent(e);
	}
};

class LookupInput : public QObject, public IDataInput {

	Q_OBJECT

public:
	LookupInput() : IDataInput(DataInputType::LOOKUP_INPUT)  {
		input_->setEditable(true);
		input_->lineEdit()->setReadOnly(true);
		input_->lineEdit()->setAlignment(Qt::AlignCenter);
		connect(input_, SIGNAL(refreshed()), this, SLOT(on_box_refreshed()));
	}

	LookupInput(ILookup* lookup) : LookupInput() {
		set_lookup(lookup);
	}

	ILookup* get_lookup() const {
		return lookup_;
	}

	void set_lookup(ILookup* lookup) {
		lookup_ = lookup;
	}

	QString get_data() const override {
		return input_->currentText();
	}

	void set_data(const QString& text) override {
		input_->setCurrentText(text);
	}

	void clear() override {
		input_->clearEditText();
	}

	QWidget* get_widget() const override {
		return input_;
	}

	~LookupInput() {
		delete input_;
	}

private slots:
	void on_box_refreshed() {
		lookup_->update();
		input_->clear();
		input_->addItems(lookup_->get_alias_values());
	}

private:
	LookupBox* input_ = new LookupBox;
	ILookup* lookup_ = nullptr;
};

} // namespace ComputerWorkshop