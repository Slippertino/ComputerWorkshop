#pragma once

#include <QtSql>
#include <QString>
#include <QVector>
#include "query_args_storable.h"

namespace ComputerWorkshop {

class InsertQueryBuilder : public QueryArgsStorable {
public:
	InsertQueryBuilder& table(const QString& name);
	InsertQueryBuilder& inserting_column(const QString& column, const QVariant& value);

	QString build();

private:
	QString table_;
	QVector<QPair<QString, QVariant>> columns_;
};

} // namespace ComputerWorkshop