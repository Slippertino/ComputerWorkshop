#pragma once

#include <QDialog>

namespace Ui {
class AboutDialog;
}

namespace ComputerWorkshop {

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;
};

} // namespace ComputerWorkshop
