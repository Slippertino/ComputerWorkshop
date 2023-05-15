#pragma once

#include <QString>
#include <QVariant>
#include <QTextDocument>
#include <QDateTime>
#include <QTextTableCell>
#include <QPrinter>
#include "entities/userdata.h"

namespace ComputerWorkshop {

class Reporter {
public:
	static void make_report(
		const QString& file,
		const UserData& user,
		QDateTime date,
		const QString& entity,
		const QList<QString> columns,
		QList<QVariantMap> data
	);
};

} // namespace ComputerWorkshop
