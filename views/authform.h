#pragma once

#include <QDialog>
#include <QTabWidget>
#include "../model/entities/userdata.h"

namespace Ui {
class AuthForm;
}

namespace ComputerWorkshop {

class AuthForm : public QTabWidget {
    Q_OBJECT

public:
    explicit AuthForm(QWidget *parent = nullptr);
    ~AuthForm();

    void notify_auth_error(const QString& msg);
    void notify_register_error(const QString& msg);

    void notify_auth_success();
    void notify_register_success();

signals:
    void authed(const UserData& usr, const QString& pass);
    void registered(const UserData& usr, const QString& pass);
    void auth_completed();

private slots:
    void on_commit_auth_button_clicked();
    void on_commit_register_button_clicked();

private:
    Ui::AuthForm *ui;
};

} // namespace ComputerWorkshop
