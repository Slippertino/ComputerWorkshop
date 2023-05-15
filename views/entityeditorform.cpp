#include "entityeditorform.h"
#include "ui_entityeditorform.h"

namespace ComputerWorkshop {

EntityEditorForm::EntityEditorForm(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::EntityEditorForm)
{
    ui->setupUi(this);

    model_ = new QStandardItemModel(this);
    ui->tableView->setModel(model_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void EntityEditorForm::setup(
    const QString& name,
    const QList<HeaderData>& headers,
    QList<QVariantMap>* data
) {
    ui->entity_name_label->setText(name);
    data_ = data;

    for(auto i = 0; i < headers.size(); ++i) {
        headers_.append(headers[i].name);
        included_headers_.append(headers[i].name);
    }

    object_editor_  = new EntityObjectEditForm(headers, this);
    columns_editor_ = new ColumnsEditDialog(headers_, &included_headers_, this);

    update_view_structure();
}

void EntityEditorForm::notify_error(const QString& msg) {
    QMessageBox::critical(this, "Ошибка при работе с базой данных", msg);
}

void EntityEditorForm::update() {
    model_->removeRows(0, model_->rowCount());

    for (auto& el : *data_) {
        QList<QStandardItem*> items;

        for (auto i = 0; i < model_->columnCount(); ++i) {
            auto name = model_->headerData(i, Qt::Orientation::Horizontal).toString();

            auto item = new QStandardItem(el.value(name).toString());
            item->setEditable(false);
            item->setTextAlignment(Qt::AlignCenter);

            items.append(item);
        }

        model_->appendRow(items);
    }
}

void EntityEditorForm::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    data_->clear();
    update_view_structure();
    emit reloaded(included_headers_);
}

EntityEditorForm::~EntityEditorForm() {
    if (model_)         delete model_;
    if (object_editor_) delete object_editor_;

    delete ui;
}

void EntityEditorForm::update_view_structure() {
    model_->removeRows(0, model_->rowCount());
    model_->removeColumns(0, model_->columnCount());

    model_->setColumnCount(included_headers_.size());
    for(auto i = 0; i < included_headers_.size(); ++i) {
        model_->setHeaderData(i, Qt::Orientation::Horizontal, included_headers_[i], Qt::DisplayRole);
    }
}

int EntityEditorForm::get_selected_row() const {
    auto indexes = ui->tableView->selectionModel()->selectedIndexes();

    return !indexes.empty()
            ? indexes.first().row()
            : -1;
}

void EntityEditorForm::on_reload_button_clicked() {
    emit reloaded(included_headers_);
}

void EntityEditorForm::on_add_button_clicked() {
    object_editor_->set_window_title(
        QString("Объект %1 : добавление").arg(ui->entity_name_label->text())
    );

    object_editor_->show_blocks(headers_);

    if (object_editor_->exec() == QDialog::Accepted) {
        emit object_added(included_headers_, object_editor_->get_inputs_data());
    }
}

void EntityEditorForm::on_edit_button_clicked() {
    auto row_id = get_selected_row();

    if (row_id == -1) {
        return;
    }

    auto data = data_->value(row_id);
    for(auto& key : included_headers_) {
        object_editor_->set_input_data(key, data[key].toString());
    }

    object_editor_->set_window_title(
        QString("Объект %1 : изменение").arg(ui->entity_name_label->text())
    );

    object_editor_->show_blocks(included_headers_);

    if (object_editor_->exec() == QDialog::Accepted) {
        QList<QString> updated;
        auto new_data = object_editor_->get_inputs_data();

        for(auto& key : included_headers_) {
            if (data[key] != new_data[key]) {
                updated.append(key);
            }
        }

        emit object_updated(included_headers_, row_id, new_data, updated);
    }
}

void EntityEditorForm::on_remove_button_clicked() {
    auto row_id = get_selected_row();

    if (row_id == -1) {
        return;
    }

    emit object_deleted(included_headers_, row_id);
}

void EntityEditorForm::on_configure_button_clicked() {
    if (columns_editor_->exec() == QDialog::Accepted) {
        update_view_structure();
        emit reloaded(included_headers_);
    }
}

void EntityEditorForm::on_report_button_clicked() {
    auto file_name = QFileDialog::getSaveFileName(this, "Report File", "", "Text files (*.pdf)");
    emit report_requested(file_name, included_headers_);
}

} // namespace ComputerWorkshop
