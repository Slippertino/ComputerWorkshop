#pragma once

#include <QDialog>
#include "../model/entities/userdata.h"

namespace Ui {
class UserInfoDialog;
}

namespace ComputerWorkshop {

class UserInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserInfoDialog(QWidget *parent = nullptr);
    ~UserInfoDialog();

    void set_data(const UserData& usr);

private:
    Ui::UserInfoDialog *ui;
};

} // namespace ComputerWorkshop
