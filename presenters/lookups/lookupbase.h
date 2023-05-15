#pragma once

#include <QString>
#include <QList>

namespace ComputerWorkshop {

class ILookup {
public:
	virtual void setup() = 0;
	virtual QList<QString> get_alias_values() const = 0;
	virtual QString get_source_by_alias(const QString& alias) = 0;
	virtual QString get_alias_by_source(const QString& src) = 0;
	virtual void update() = 0;
};

} // namespace ComputerWorkshop