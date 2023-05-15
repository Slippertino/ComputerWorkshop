#include "selectquerybuilder.h"

namespace ComputerWorkshop {

SelectQueryBuilder& SelectQueryBuilder::table(const QString& name) {
	table_ = name;

	return *this;
}

SelectQueryBuilder& SelectQueryBuilder::column(const QString& column) {
	columns_.push_back(column);

	return *this;
}

QString SelectQueryBuilder::build() {
	auto query = QString("SELECT ");

	for (auto i = 0; i < columns_.size(); ++i) {
		query += columns_[i] % " ";

		if (i != columns_.size() - 1) {
			query += ", ";
		}
		else {
			query += "FROM " % table_ % " ";
		}
	}

	add_filters(query);

	return query;
}

} // namespace ComputerWorkshop