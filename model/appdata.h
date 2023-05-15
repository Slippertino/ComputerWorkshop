#pragma once

#include <QHash>
#include <QString>
#include <unordered_map>
#include <QVector>
#include <memory>
#include <any>
#include <config/config.h>

namespace ComputerWorkshop {

class AppData
{
public:
    static AppData& inst();

    void setup(const Config& cfg);

    template<class TService>
    TService* get_service() {
        auto& packed_serv = services_.at(typeid(TService).name());
        return std::any_cast<TService>(&packed_serv);
    }

private:
    AppData() = default;

private:
    static std::unordered_map<QString, std::any> services_;
};

} // namespace ComputerWorkshop
