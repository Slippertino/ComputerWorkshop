#pragma once

#include "config/config.h"
#include "views/authform.h"
#include "views/mainwindow.h"
#include "model/appdata.h"
#include "presenters/presenters.h"

namespace ComputerWorkshop {

class Shop : public QObject {

    Q_OBJECT

public:
    Shop();

    void setup(const Config& cfg);
    void run();

    ~Shop();

private slots:
    void on_auth_completed();

private:
    template<class TEntityPresenter>
    void add_entity() {
        auto view = new EntityEditorForm(main_view_);
        view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        auto presenter = new TEntityPresenter(view);
        main_view_->add_section(presenter->get_entity_display_name(), view);
        presenters_.append(presenter);
    }

private:
    AppData& data_;
    AuthForm* auth_view_;
    MainWindow* main_view_;
    QList<QObject*> presenters_;
};

} // namespace ComputerWorkshop


