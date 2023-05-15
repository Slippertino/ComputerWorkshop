#pragma once

#include <functional>
#include <QtSql>
#include <QString>
#include <QList>
#include "query_args_storable.h"

namespace ComputerWorkshop {

class ColumnFilter : public QueryArgsStorable {
public:
	ColumnFilter& column(const QString& name);

	ColumnFilter& open_block();
	ColumnFilter& close_block();

	ColumnFilter& equal(const QVariant& val);
	ColumnFilter& greater_equal(const QVariant& val);
	ColumnFilter& less_equal(const QVariant& val);
	ColumnFilter& greater(const QVariant& val);
	ColumnFilter& less(const QVariant& val);

	ColumnFilter& like(const QString& val);

	ColumnFilter& null();
	ColumnFilter& not_null();

	ColumnFilter& and();
	ColumnFilter& or();

	QString get_filter() const;

private:
	ColumnFilter& add_comparison_expr(const QString& op, const QVariant& val);
	ColumnFilter& add_operation(const QString& op);

private:
	QString filter_;
	QString current_column_;
};

} // namespace ComputerWorkshop