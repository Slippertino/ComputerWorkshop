#pragma once

#include <QWidget>
#include <QFileDialog>
#include <QStandardItemModel>
#include "entityobjecteditform.h"
#include "columnseditdialog.h"
#include "types.h"

namespace Ui {
    class EntityEditorForm;
}

namespace ComputerWorkshop {


class EntityEditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit EntityEditorForm(QWidget* parent = nullptr);
    ~EntityEditorForm();

    void setup(
        const QString& name,
        const QList<HeaderData>& headers,
        QList<QVariantMap>* data
    );

    void notify_error(const QString& msg);

    void update();

signals:
    void object_added(const QList<QString>& columns, QVariantMap data);
    void object_updated(const QList<QString>& columns, int number, QVariantMap data, QList<QString> updated);
    void object_deleted(const QList<QString>& columns, int number);
    void reloaded(const QList<QString>& columns);
    void report_requested(const QString& filename, const QList<QString>& columns);

protected:
    virtual void showEvent(QShowEvent* event) override;

private slots:
    void on_reload_button_clicked();
    void on_add_button_clicked();
    void on_edit_button_clicked();
    void on_remove_button_clicked();

    void on_configure_button_clicked();

    void on_report_button_clicked();

private:
    void update_view_structure();

    int get_selected_row() const;

private:
    Ui::EntityEditorForm* ui;

    QStandardItemModel* model_ = nullptr;
    QList<QVariantMap>* data_;
    QList<QString> headers_;
    QList<QString> included_headers_;

    EntityObjectEditForm* object_editor_ = nullptr;
    ColumnsEditDialog* columns_editor_;
};

} // namespace ComputerWorkshop
