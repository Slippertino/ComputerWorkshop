#pragma once

#include "reporter.h"

namespace ComputerWorkshop {

void Reporter::make_report(
	const QString& file,
	const UserData& user,
	QDateTime date,
	const QString& entity,
	const QList<QString> columns,
	QList<QVariantMap> data
) {
	QTextDocument* doc = new QTextDocument;
	doc->setDocumentMargin(10);
	QTextCursor cursor(doc);

	QString html = QString(
		"<h1> Report </h1>"
		"<h3> User: %1 </h3>"
		"<h3> Date: %2 </h3>"
		"<h3> Table: %3 </h3>")
		.arg(user.sys_user.login.value)
		.arg(date.toString(Field<QDateTime>::format))
		.arg(entity);

	cursor.insertHtml(html);

	cursor.movePosition(QTextCursor::EndOfBlock);

	QTextTableFormat table_format;
	table_format.setAlignment(Qt::AlignCenter);
	table_format.setCellSpacing(5);
	table_format.setBorder(1);
	table_format.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);

	QTextCharFormat data_char_format;
	data_char_format.setFont(QFont("Calibri", 9, QFont::Weight::Normal));

	QTextCharFormat header_char_format;
	header_char_format.setFont(QFont("Calibri", 12, QFont::Weight::Bold));

	QTextTable* table = cursor.insertTable(data.size() + 1, columns.size(), table_format);

	for (auto i = 0; i < columns.size(); ++i) {
		QTextTableCell headerCell = table->cellAt(0, i);
		QTextCursor headerCellCursor = headerCell.firstCursorPosition();
		headerCellCursor.insertText(columns[i], header_char_format);
	}

	for (int i = 0; i < data.size(); i++) {
		for (auto j = 0; j < columns.size(); ++j) {
			QTextTableCell cell = table->cellAt(i + 1, j);
			QTextCursor cellCursor = cell.firstCursorPosition();
			cellCursor.insertText(data[i][columns[j]].toString(), data_char_format);
		}
	}

	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock();

	QPrinter printer(QPrinter::HighResolution);
	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setOutputFileName(file);
	doc->print(&printer);
}

} // namespace ComputerWorkshop
