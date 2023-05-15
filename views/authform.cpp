#include "authform.h"
#include "ui_authform.h"
#include <QThread>

namespace ComputerWorkshop {

AuthForm::AuthForm(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::AuthForm)
{
    ui->setupUi(this);
}

void AuthForm::notify_auth_error(const QString& msg) {
    ui->auth_message_label->setStyleSheet("color: red;");
    ui->auth_message_label->setText(msg);
}

void AuthForm::notify_register_error(const QString& msg) {
    ui->register_message_label->setStyleSheet("color: red");
    ui->register_message_label->setText(msg);
}

void AuthForm::notify_auth_success() {
    ui->auth_message_label->setStyleSheet("color: green");
    ui->auth_message_label->setText(QString("Успешно"));
    ui->auth_message_label->repaint();
    QThread::sleep(1);

    emit auth_completed();
}

void AuthForm::notify_register_success() {
    ui->register_message_label->setStyleSheet("color: green;");
    ui->register_message_label->setText("Успешно");
}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::on_commit_auth_button_clicked() {
    UserData usr;
    usr.sys_user.set(User::field_login, ui->auth_login_edit->text());

    emit authed(
        usr,
        ui->auth_password_edit->text()
    );
}

void AuthForm::on_commit_register_button_clicked() {
    auto password = ui->register_password_edit->text();

    if (password != ui->commit_register_password_edit->text()) {
        notify_register_error("Введенные пароли не совпадают");
        return;
    }

    UserData usr;
    usr.sys_user.set(User::field_login, ui->register_login_edit->text());
    usr.name = ui->register_name_edit->text();
    usr.phone = ui->register_phone_edit->text();

    emit registered(
        usr,
        password
    );
}

} // namespace ComputerWorkshop

