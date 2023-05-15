#include "appdata.h"
#include "services/database/database.h"
#include "services/auth/auth.h"
#include "services/usersession/usersession.h"
#include "services/entitycontext/entitycontext.h"
#include "entities/entities.h"

namespace ComputerWorkshop {

AppData& AppData::inst() {
    static AppData data;

    return data;
}

std::unordered_map<QString, std::any> AppData::services_ = {
    { typeid(Auth).name(),          std::make_any<Auth>()           },
    { typeid(Database).name(),      std::make_any<Database>()       },
    { typeid(UserSession).name(),   std::make_any<UserSession>()    },
    { typeid(EntityContext).name(), std::make_any<EntityContext>()  },
};

void AppData::setup(const Config& cfg) {
    get_service<Database>()->setup(cfg);
}

} // namespace ComputerWorkshop