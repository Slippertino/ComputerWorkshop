#include "insertquerybuilder.h"

namespace ComputerWorkshop {

InsertQueryBuilder& InsertQueryBuilder::table(const QString& name) {
	table_ = name;

	return *this;
}

InsertQueryBuilder& InsertQueryBuilder::inserting_column(const QString& column, const QVariant& value) {
	columns_.push_back({ column, value });

	return *this;
}

QString InsertQueryBuilder::build() {
	QString query = "INSERT INTO " % table_ % "(";

	for (auto i = 0; i < columns_.size(); ++i) {
		query += columns_[i].first % " ";

		if (i != columns_.size() - 1) {
			query += ", ";
		}
		else {
			query += ") VALUES (";
		}
	}

	for (auto i = 0; i < columns_.size(); ++i) {
		query += "?";

		add(columns_[i].second);

		if (i != columns_.size() - 1) {
			query += ", ";
		}
		else {
			query += ")";
		}
	}

	return query;
}

} // namespace ComputerWorkshop