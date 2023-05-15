#pragma once

#include <QVector>
#include <QVariant>

namespace ComputerWorkshop {

class QueryArgsStorable {
public:
	QList<QVariant> args() const {
		return args_;
	}

protected:
	void add(const QVariant& arg) {
		args_.push_back(arg);
	}

	void add_range(const QList<QVariant>& args) {
		args_.append(args);
	}

private:
	QList<QVariant> args_;
};

} // namespace ComputerWorkshop