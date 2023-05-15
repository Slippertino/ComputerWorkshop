#pragma once

#include <memory>
#include <vector>
#include <QtSql>
#include <QString>
#include <QVector>
#include "query_args_storable.h"
#include "filteredquery.h"

namespace ComputerWorkshop {

class UpdateQueryBuilder : public FilteredQuery<UpdateQueryBuilder> {
public:
	UpdateQueryBuilder& table(const QString& name);
	UpdateQueryBuilder& changed_column(const QString& column, const QVariant& value);

	QString build();

private:
	QString table_;
	QVector<QPair<QString, QVariant>> columns_;
};

} // namespace ComputerWorkshop