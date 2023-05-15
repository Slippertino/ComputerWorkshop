#include "updatequerybuilder.h"

namespace ComputerWorkshop {

UpdateQueryBuilder& UpdateQueryBuilder::table(const QString& name) {
	table_ = name;

	return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::changed_column(const QString& column, const QVariant& value) {
	columns_.push_back({ column, value });

	return *this;
}

QString UpdateQueryBuilder::build() {
	QString query = "UPDATE " % table_ % " SET ";

	for (auto i = 0; i < columns_.size(); ++i) {
		query += columns_[i].first % " = ? ";
		
		add(columns_[i].second);

		if (i != columns_.size() - 1) {
			query += ", ";
		}
	}

	add_filters(query);

	return query;
}

} // namespace ComputerWorkshop