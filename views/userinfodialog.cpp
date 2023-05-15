#include "userinfodialog.h"
#include "ui_userinfodialog.h"

namespace ComputerWorkshop {

UserInfoDialog::UserInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInfoDialog) {
    ui->setupUi(this);

    connect(ui->close_button, SIGNAL(clicked()), this, SLOT(accept()));
}

void UserInfoDialog::set_data(const UserData& usr) {
    ui->login_field->setText(usr.sys_user.login.value);

    if (usr.name.has_value())  ui->name_field->setText(usr.name.value());
    if (usr.phone.has_value()) ui->number_field->setText(usr.phone.value());
}

UserInfoDialog::~UserInfoDialog() {
    delete ui;
}

} // namespace ComputerWorkshop
