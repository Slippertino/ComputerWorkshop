#pragma once

#include <QString>
#include <QDialog>
#include <QCheckBox>

namespace Ui {
class ColumnsEditDialog;
}

namespace ComputerWorkshop {

class ColumnsEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColumnsEditDialog(
        const QList<QString>& headers,
        QList<QString>* data,
        QWidget *parent = nullptr
    );

    ~ColumnsEditDialog();

public slots:
    void accept() override;

private:
    inline static const qint32 height_for_box_px = 75;

    QList<QString>* headers_;
    QList<QCheckBox*> boxes_;

private:
    Ui::ColumnsEditDialog *ui;
};

} // namespace ComputerWorkshop
