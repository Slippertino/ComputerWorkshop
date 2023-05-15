#pragma once

#include <QString>
#include <QWidget>
#include "datainputtype.h"

namespace ComputerWorkshop {

class IDataInput {
public:
	IDataInput() = delete;
	IDataInput(DataInputType type) : type_(type)
	{ }

	DataInputType get_type() const {
		return type_;
	}

	virtual QString get_data() const = 0;
	virtual void set_data(const QString& text) = 0;
	virtual void clear() = 0;

	virtual QWidget* get_widget() const = 0;

	virtual ~IDataInput() = default;

private:
	DataInputType type_;
};

} // namespace ComputerWorkshop