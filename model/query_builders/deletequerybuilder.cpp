#include "deletequerybuilder.h"

namespace ComputerWorkshop {

DeleteQueryBuilder& DeleteQueryBuilder::table(const QString& name) {
	table_ = name;

	return *this;
}

QString DeleteQueryBuilder::build() {
	QString query = "DELETE FROM " % table_ % " ";
	add_filters(query);

	return query;
}

} // namespace ComputerWorkshop