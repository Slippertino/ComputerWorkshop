#pragma once

#include <memory>
#include <vector>
#include <QtSql>
#include <QString>
#include <QVector>
#include "filteredquery.h"

namespace ComputerWorkshop {

class SelectQueryBuilder : public FilteredQuery<SelectQueryBuilder> {
public:
	SelectQueryBuilder& table(const QString& name);
	SelectQueryBuilder& column(const QString& column);

	QString build();

private:
	QString table_;
	QVector<QString> columns_;
};

} // namespace ComputerWorkshop