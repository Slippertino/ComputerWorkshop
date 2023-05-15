#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace ComputerWorkshop {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);

    user_view_ = new UserInfoDialog(this);

    menu_bar_ = new QMenuBar(this);
    setMenuBar(menu_bar_);

    main_menu_ = menu_bar_->addMenu("Таблицы");
    menu_bar_->addAction(main_menu_->menuAction());

    auto usr_action = menu_bar_->addAction("Пользователь");
    connect(usr_action, &QAction::triggered, this, [&](){ user_view_->exec();});

    auto about_action = menu_bar_->addAction("О программе");
    connect(about_action, &QAction::triggered, this, [&](){ (new AboutDialog(this))->exec(); });
}

MainWindow::~MainWindow() {
    delete main_menu_;
    delete menu_bar_;

    foreach(auto sect, sections_) {
        delete sect;
    }

    delete ui;
}

void MainWindow::add_section(const QString& title, EntityEditorForm* section_form) {
    sections_.insert(title, section_form);

    section_form->setParent(ui->current_section_->parentWidget());
    turn_section(section_form, false);

    QAction* act = new QAction(main_menu_);
    act->setText(title);
    act->setFont(QFont("Calibri", 14, QFont::Weight::Medium));

    connect(act, SIGNAL(triggered()), this, SLOT(on_data_action_triggered()));

    main_menu_->addAction(act);
}

void MainWindow::set_user_info(const UserData& usr) {
    user_view_->set_data(usr);
}

void MainWindow::on_data_action_triggered() {
    auto sender = qobject_cast<QAction*>(QObject::sender());

    ui->horizontalLayout->removeWidget(ui->current_section_);
    turn_section(ui->current_section_, false);

    ui->current_section_ = sections_.value(sender->text());
    ui->horizontalLayout->addWidget(ui->current_section_);
    ui->horizontalLayout->setStretch(0, 0);
    ui->horizontalLayout->setStretch(1, 1);
    turn_section(ui->current_section_, true);
}

void MainWindow::turn_section(QWidget* sect, bool flag) {
    sect->setEnabled(flag);
    sect->setVisible(flag);
}

} // namespace ComputerWorkshop

