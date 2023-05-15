#pragma once

#include <QtSql>
#include <QList>
#include <QDebug>
#include <config/config.h>

namespace ComputerWorkshop {

class Database
{
public:
    using TransactionFunc = std::function<bool()>;

public:
    Database() = default;
    Database(const Database&) = default;

    void setup(const Config& cfg);

    bool make_transaction(const TransactionFunc& op);

    bool execute_query(
        const QString& query_text,
        QSqlQuery& query,
        const QList<QVariant>& args = {}
    );

    ~Database();

private:
    void init_database(const Config& cfg);
    void connect_db(const Config& cfg, const QString& db);

private:
    static const QList<QString> initial_script_;

    QSqlDatabase db_;
};

} // namespace ComputerWorkshop
