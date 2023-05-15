#pragma once

#include <QHash>
#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include "entityeditorform.h"
#include "userinfodialog.h"
#include "aboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace ComputerWorkshop {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_section(const QString& title, EntityEditorForm* section_form);
    void set_user_info(const UserData& usr);

private slots:
    void on_data_action_triggered();

private:
    void turn_section(QWidget* sect, bool flag);

private:
    QMenuBar* menu_bar_;
    QMenu* main_menu_;

    UserInfoDialog* user_view_;
    QHash<QString, EntityEditorForm*> sections_;
    Ui::MainWindow *ui;
};

} // namespace ComputerWorkshop
