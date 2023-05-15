#include "database.h"

namespace ComputerWorkshop {

void Database::setup(const Config& cfg) {
    init_database(cfg);
    connect_db(cfg, cfg.get_db_settings().db_name);
}

bool Database::make_transaction(const TransactionFunc& op) {
    bool res;

    auto trans_start = db_.transaction();

    if (!trans_start) {
        qDebug() << "Transaction error: " << db_.lastError().text() << "\n";
        return false;
    }

    res = op();
 
    auto trans_act_res = res
        ? db_.commit()
        : db_.rollback();

    if (!trans_act_res) {
        qDebug() << "Transaction error: " << db_.lastError().text() << "\n";
    }

    return res;
}

bool Database::execute_query(
    const QString& query_text,
    QSqlQuery& query,
    const QList<QVariant>& args
) {
    query.finish();

    query = QSqlQuery{ db_ };
    query.prepare(query_text);
    for (const auto& arg : args) {
        query.addBindValue(arg);
    }
    auto res = query.exec();

    qDebug() << "Query executed: " << query.executedQuery() << "\n";

    return res;
}

Database::~Database() {
    db_.close();
}

void Database::init_database(const Config& cfg) {
    auto sets = cfg.get_db_settings();

    connect_db(cfg, "master");

    QSqlQuery query{ db_ };
    query.prepare(QString("SELECT DB_ID('%1') AS id").arg(sets.db_name));
    query.exec();

    query.next();
    if (!query.value("id").isNull()) {
        return;
    }

    foreach(auto qtext, initial_script_) {
        qtext = qtext.arg(sets.db_name);
        query.prepare(qtext);

        if (!query.exec()) {
            auto l = query.lastError().text();
            throw std::runtime_error("Ошибка при инициализации базы данных");
        }
    }

    db_.close();
}

void Database::connect_db(const Config& cfg, const QString& db) {
    auto sets = cfg.get_db_settings();

    QString connectionTemplate = "Driver={%1};Server=%2;Database=%3";
    QString connectionString = connectionTemplate
        .arg(sets.driver)
        .arg(sets.host)
        .arg(db);

    db_ = QSqlDatabase::addDatabase("QODBC");

    db_.setDatabaseName(connectionString);
    db_.setUserName(sets.user);
    db_.setPassword(sets.password);

    if (!db_.open()) {
        throw std::runtime_error("Невозможно подключиться к базе данных");
    }
}

} // namespace ComputerWorkshop