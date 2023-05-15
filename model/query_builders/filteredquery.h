#pragma once

#include <QVector>
#include "query_args_storable.h"
#include "columnfilter.h"

namespace ComputerWorkshop {

template<class TQueryBuilder>
class FilteredQuery : public QueryArgsStorable {
public:
	TQueryBuilder& filter(const ColumnFilter& fltr) {
		filters_.append(fltr);
		return get_query_builder();
	}

protected:
	void add_filters(QString& target) {
		if (filters_.size()) {
			target += "WHERE ";
		}

		for (auto i = 0; i < filters_.size(); ++i) {
			target += "(" % filters_[i].get_filter() % ") ";
			add_range(filters_[i].args());

			if (i != filters_.size() - 1) {
				target += "AND ";
			}
		}
	}

private:
	TQueryBuilder& get_query_builder() {
		return *static_cast<TQueryBuilder*>(this);
	}

private:
	QVector<ColumnFilter> filters_;
};

} // namespace ComputerWorkshop