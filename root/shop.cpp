#include "shop.h"

namespace ComputerWorkshop {

Shop::Shop() : data_(AppData::inst()) {
    auth_view_ = new AuthForm();
    auto auth_presenter = new AuthPresenter(auth_view_);
    presenters_.append(auth_presenter);
    connect(auth_view_, SIGNAL(auth_completed()), this, SLOT(on_auth_completed()));

    main_view_ = new MainWindow();

    add_entity<BranchesPresenter>();
    add_entity<EmployeesPresenter>();
    add_entity<ClientsPresenter>();
    add_entity<EmbeddedServicesPresenter>();
    add_entity<ContractsPresenter>();
    add_entity<ContractAnnexesPresenter>();
    add_entity<AnnexEmbeddedServicesPresenter>();
    add_entity<AnnexOrderedSparePartsPresenter>();
    add_entity<UsersPresenter>();
    add_entity<RightsPresenter>();
}

void Shop::setup(const Config& cfg) {
    data_.setup(cfg);

    foreach(auto p, presenters_) {
        if (auto ep = qobject_cast<IEntityPresenter*>(p)) {
            ep->setup();
        }
    }
}

void Shop::run() {
    auth_view_->show();
}

void Shop::on_auth_completed() {
    auth_view_->close();
    auto usr = data_.get_service<UserSession>()->get_user();
    main_view_->set_user_info(usr);
    main_view_->show();
}

Shop::~Shop() {
    foreach(auto p, presenters_) {
        delete p;
    }

    delete auth_view_;
    delete main_view_;
}

} // namespace ComputerWorkshop
