#pragma once

#include <memory>
#include <vector>
#include <QtSql>
#include <QString>
#include <QVector>
#include "filteredquery.h"

namespace ComputerWorkshop {

class DeleteQueryBuilder : public FilteredQuery<DeleteQueryBuilder> {
public:
	DeleteQueryBuilder& table(const QString& name);
	QString build();

private:
	QString table_;
};

} // namespace ComputerWorkshop