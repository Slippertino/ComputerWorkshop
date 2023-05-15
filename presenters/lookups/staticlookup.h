#pragma once

#include <QHash>
#include <QString>
#include <QList>
#include "lookupbase.h"

namespace ComputerWorkshop {

template<class TLookup>
class IStaticLookup : public ILookup {
public:
	void setup() override final {
		if (!is_setup) {
			setup_once();
			is_setup = true;
		}
	}

	void update() override final { }

	virtual QList<QString> get_alias_values() const = 0;
	virtual QString get_source_by_alias(const QString& alias) = 0;
	virtual QString get_alias_by_source(const QString& src) = 0;

protected:
	virtual void setup_once() = 0;

private:
	inline static bool is_setup = false;
};

} // namespace ComputerWorkshop