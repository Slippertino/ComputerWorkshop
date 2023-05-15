#pragma once

#include <QHash>
#include <QVector>
#include <QSet>
#include <QUuid>
#include <model/appdata.h>
#include <model/services/database/database.h>
#include <model/entities/user.h>
#include <model/entities/right.h>
#include <model/services/usersession/usersession.h>
#include <model/query_builders/query_builders.h>
#include <model/entities/entity.h>
#include "entityoperationerror.h"

namespace ComputerWorkshop {

class EntityContext {
public:
    template<class T>
    bool create_object_by_user(const T& obj, EntityOperationError& error) {
        if (!has_right(T::table_name(), CREATE, error)) {
            return false;
        }

        return EntityContext::create_object_by_sys<T>(obj, error);
    }

    template<class T>
    bool create_object_by_sys(const T& obj, EntityOperationError& error) {
        return AppData::inst().get_service<Database>()->make_transaction([&]() {
            return EntityContext::create_object<T>(obj, error);
        });
    }

    template<class T>
    bool read_object_by_user(
        const QList<QString>& columns, 
        const QList<ColumnFilter>& filters, 
        QList<T>& result, 
        EntityOperationError& error
    ) {
        if (!has_right(T::table_name(), READ, error)) {
            return false;
        }

        return EntityContext::read_object_by_sys<T>(columns, filters, result, error);
    }

    template<class T>
    bool read_object_by_sys(
        const QList<QString>& columns, 
        const QList<ColumnFilter>& filters, 
        QList<T>& result, 
        EntityOperationError& error
    ) {
        return AppData::inst().get_service<Database>()->make_transaction([&]() {
            return EntityContext::read_object<T>(columns, filters, result, error);
        });
    }

    template<class T>
    bool update_object_by_user(const T& obj, const QList<QString>& modified, EntityOperationError& error) {
        if (!has_right(T::table_name(), UPDATE, error)) {
            return false;
        }

        return EntityContext::update_object_by_sys<T>(obj, modified, error);
    }

    template<class T>
    bool update_object_by_sys(const T& obj, const QList<QString>& modified, EntityOperationError& error) {
        return AppData::inst().get_service<Database>()->make_transaction([&]() {
            return EntityContext::update_object<T>(obj, modified, error);
        });
    }

    template<class T>
    bool delete_object_by_user(const T& obj, EntityOperationError& error) {
        if (!has_right(T::table_name(), DELETE, error)) {
            return false;
        }

        return EntityContext::delete_object_by_sys<T>(obj, error);
    }

    template<class T>
    bool delete_object_by_sys(const T& obj, EntityOperationError& error) {
        return AppData::inst().get_service<Database>()->make_transaction([&]() {
            return EntityContext::delete_object<T>(obj, error);
        });
    }

private:
    template<class T>
    bool generate_pk(T& obj, EntityOperationError& error) {
        QSqlQuery query;
        auto db = AppData::inst().get_service<Database>();

        if (!db->execute_query(
            SelectQueryBuilder().table(T::table_name()).column(T::pk).build(), 
            query
        )) {
            error.code = EntityOperationErrorCode::UNEXPECTED_DBMS_ERROR;
            error.entity_name = T::table_name();
            error.messages << query.lastError().text();
            return false;
        }

        QSet<QString> existing_pk;
        while (query.next()) {
            existing_pk.insert(query.value(T::pk).toString());
        }

        obj.generate_id([&existing_pk](const QString& id) {
            return !existing_pk.contains(id);
        });

        return true;
    }

    template<class T>
    bool validate_ukeys(const T& obj, const QList<QString>& columns, EntityOperationError& error) {
        QSet<QString> cols{ columns.begin(), columns.end() };

        QSqlQuery query;
        auto db = AppData::inst().get_service<Database>();

        for (const auto& uks : T::ukeys()) {
            if (!QSet<QString>{ uks.begin(), uks.end() }.intersects(cols))
                continue;

            SelectQueryBuilder builder;
            builder
                .table(T::table_name())
                .column(T::pk);

            QVariantList args;
            for (auto i = 0; i < uks.size(); ++i) {
                const auto& uk = uks[i];

                QVariant val;
                if (!cols.contains(uk)) {
                    SelectQueryBuilder sel;

                    auto sel_text = sel
                        .table(T::table_name())
                        .column(uk)
                        .filter(ColumnFilter().column(T::pk).equal(obj.get(T::pk)))
                        .build();

                    db->execute_query(sel_text, query, sel.args());
                    query.next();
                    val = query.value(uk);
                }
                else {
                    val = obj.get(uk);
                }

                builder.filter(ColumnFilter().column(uks[i]).equal(val));
            }

            auto qtext = builder.build();

            if (!db->execute_query(qtext, query, builder.args())) {
                error.code = EntityOperationErrorCode::UNEXPECTED_DBMS_ERROR;
                error.entity_name = T::table_name();
                error.messages << query.lastError().text();
                return false;
            }

            if (query.next()) {
                error.code = EntityOperationErrorCode::UNIQUE_RULE_VIOLATED_ERROR;
                error.entity_name = T::table_name();
                error.ext_names << uks;
                return false;
            }
        }

        return true;
    }

    template<class T>
    bool validate_fkeys(const T& obj, const QList<QString>& columns, EntityOperationError& error) {
        QSet<QString> cols{ columns.begin(), columns.end() };

        QSqlQuery query;
        auto db = AppData::inst().get_service<Database>();

        for (const auto& fkey : T::fkeys().keys()) {
            if (!cols.contains(fkey))
                continue;

            auto val = obj.get(fkey);

            SelectQueryBuilder builder;
            auto qtext = builder
                .table(T::fkeys().value(fkey))
                .column(T::pk)
                .filter(ColumnFilter().column(T::pk).equal(obj.get(fkey)))
                .build();

            if (!db->execute_query(qtext, query, builder.args())) {
                error.code = EntityOperationErrorCode::UNEXPECTED_DBMS_ERROR;
                error.entity_name = T::table_name();
                error.messages << query.lastError().text();
                return false;
            }

            if (!query.next()) {
                error.code = EntityOperationErrorCode::UNEXISTING_FOREIGN_RECORD_ERROR;
                error.entity_name = T::table_name();
                error.ext_names << fkey;
                return false;
            }
        }

        return true;
    }

    template<class T>
    bool create_object(T obj, EntityOperationError& error) {
        QSqlQuery query;
        auto db = AppData::inst().get_service<Database>();

        if (!generate_pk(obj, error) || 
            !validate_ukeys(obj, T::fields(), error) || 
            !validate_fkeys(obj, T::fields(), error)
        ) {
            return false;
        }

        InsertQueryBuilder builder;
        builder.table(T::table_name());
        for (const auto& field : T::fields()) {
            builder.inserting_column(field, obj.get(field));
        }

        auto qtext = builder.build();

        if (!db->execute_query(qtext, query, builder.args())) {
            error.code = EntityOperationErrorCode::UNEXPECTED_DBMS_ERROR;
            error.entity_name = T::table_name();
            error.messages << query.lastError().text();
            return false;
        }

        return true;
    }

    template<class T>
    bool read_object(
        const QList<QString>& columns, 
        const QList<ColumnFilter> filters,
        QList<T>& result, 
        EntityOperationError& error
    ) {
        QSqlQuery query;
        auto db = AppData::inst().get_service<Database>();

        SelectQueryBuilder builder;
        builder.table(T::table_name());

        for (const auto& field : columns) {
            builder.column(field);
        }

        for (const auto& fltr : filters) {
            builder.filter(fltr);
        }

        auto qtext = builder.build();
        if (!db->execute_query(qtext, query, builder.args())) {
            error.code = EntityOperationErrorCode::UNEXPECTED_DBMS_ERROR;
            error.entity_name = T::table_name();
            error.messages << query.lastError().text();
            return false;
        }

        while (query.next()) {
            T obj;
            
            for (const auto& field : columns) {
                auto& val = query.value(field);
                obj.set(field, val);
            }

            result.append(obj);
        }

        return true;
    }

    template<class T>
    bool update_object(const T& obj, const QList<QString>& modified, EntityOperationError& error) {
        if (modified.isEmpty()) {
            return true;
        }

        if (!validate_ukeys(obj, modified, error) ||
            !validate_fkeys(obj, modified, error)
        ) {
            return false;
        }

        QSqlQuery query;
        auto db = AppData::inst().get_service<Database>();

        UpdateQueryBuilder builder;
        builder.table(T::table_name());

        for (const auto& mod : modified) {
            builder.changed_column(mod, obj.get(mod));
        }
        
        builder.filter(ColumnFilter().column(T::pk).equal(obj.get(T::pk)));

        auto qtext = builder.build();

        if (!db->execute_query(qtext, query, builder.args())) {
            error.code = EntityOperationErrorCode::UNEXPECTED_DBMS_ERROR;
            error.entity_name = T::table_name();
            error.messages << query.lastError().text();
            return false;
        }

        return true;
    }

    template<class T>
    bool delete_object(const T& obj, EntityOperationError& error) {
        QSqlQuery query;
        auto db = AppData::inst().get_service<Database>();

        foreach(const DepEntityData& dep, T::deps()) {
            if (dep.on_delete != FkModifyRuleType::NO_ACTION) {
                continue;
            }

            SelectQueryBuilder builder;
            auto qtext = builder
                .table(dep.dep_entity)
                .column(dep.fk)
                .filter(ColumnFilter().column(dep.fk).equal(obj.get(T::pk)))
                .build();

            db->execute_query(qtext, query, builder.args());

            if (query.next()) {
                error.code = EntityOperationErrorCode::FK_DELETE_RULE_FORBIDDEN;
                error.entity_name = T::table_name();
                error.ext_names << dep.dep_entity << dep.fk;
                return false;
            }
        }

        DeleteQueryBuilder builder;
        auto qtext = builder
            .table(T::table_name())
            .filter(ColumnFilter().column(T::pk).equal(obj.get(T::pk)))
            .build();

        if (!db->execute_query(qtext, query, builder.args())) {
            error.code = EntityOperationErrorCode::UNEXPECTED_DBMS_ERROR;
            error.entity_name = T::table_name();
            error.messages << query.lastError().text();
            return false;
        }

        return true;
    }

    bool has_right(const QString& table, OperationRightType required, EntityOperationError& error) {
        auto usr = AppData::inst().get_service<UserSession>()->get_user();
        
        QList<Right> sel;
        auto res = EntityContext::read_object_by_sys<Right>(
            { Right::field_op },
            {
                ColumnFilter()
                .column(Right::field_user_id).equal(usr.sys_user.get(User::pk)).and()
                .column(Right::field_entity).equal(table)
            },
            sel,
            error
        );

        if (!res) {
            return false;
        }

        OperationRightType usr_right = NONE;
        if (!sel.isEmpty()) {
            usr_right = static_cast<OperationRightType>(sel.first().get(Right::field_op).toInt());
        }

        if ((required & usr_right) != required) {
            error.code = EntityOperationErrorCode::ACCESS_RIGHTS_VIOLATED_ERROR;
            error.entity_name = table;
            error.required_right = required;
            error.user_right = usr_right;
            return false;
        }

        return true;
    }
};

} // namespace ComputerWorkshop