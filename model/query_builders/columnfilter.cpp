#pragma once

#include "columnfilter.h"

namespace ComputerWorkshop {

ColumnFilter& ColumnFilter::column(const QString& name) {
	current_column_ = name;

	return *this;
}

ColumnFilter& ColumnFilter::open_block() {
	filter_.append("(");
	return *this;
}

ColumnFilter& ColumnFilter::close_block() {
	filter_.append(")");
	return *this;
}

ColumnFilter& ColumnFilter::equal(const QVariant& val) {
	return add_comparison_expr("=", val);
}

ColumnFilter& ColumnFilter::greater_equal(const QVariant& val) {
	return add_comparison_expr(">=", val);
}

ColumnFilter& ColumnFilter::less_equal(const QVariant& val) {
	return add_comparison_expr("<=", val);
}

ColumnFilter& ColumnFilter::greater(const QVariant& val) {
	return add_comparison_expr(">", val);
}

ColumnFilter& ColumnFilter::less(const QVariant& val) {
	return add_comparison_expr("<", val);
}

ColumnFilter& ColumnFilter::like(const QString& val) {
	return add_comparison_expr("LIKE", val);
}

ColumnFilter& ColumnFilter::null() {
	filter_.append(QString("%1 IS NULL").arg(current_column_));
	return *this;
}

ColumnFilter& ColumnFilter::not_null() {
	filter_.append(QString("%1 IS NOT NULL").arg(current_column_));
	return *this;
}

ColumnFilter& ColumnFilter::and() {
	return add_operation("AND");
}

ColumnFilter& ColumnFilter::or() {
	return add_operation("OR");
}

QString ColumnFilter::get_filter() const {
	return filter_;
}

ColumnFilter& ColumnFilter::add_comparison_expr(const QString& op, const QVariant& val) {
	filter_.append(QString("%1 %2 ?").arg(current_column_).arg(op));
	add(val);

	return *this;
}

ColumnFilter& ColumnFilter::add_operation(const QString& op) {
	filter_.append(QString(" %1 ").arg(op));
	return *this;
}

} // namespace ComputerWorkshop