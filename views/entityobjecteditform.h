#pragma once

#include <optional>
#include <QVariantMap>
#include <QList>
#include <QString>
#include <QMap>
#include <QGridLayout>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "types.h"

namespace ComputerWorkshop {

class EntityObjectEditForm : public QDialog {

    Q_OBJECT

private:
    struct DataBlock {
        QLabel* label;
        IDataInput* input;
    };

public:
    EntityObjectEditForm(
        QList<HeaderData> inputs_data,
        QWidget* parent = 0
    );

    void set_window_title(const QString& title);

    QVariantMap get_inputs_data();
    void set_input_data(const QString& name, const QString& value);

    void show_blocks(const QList<QString>& headers);

    ~EntityObjectEditForm();

public:
    void accept() override;
    void reject() override;

private:
    bool is_block_available(const QString& name) const;
    void hide_all_blocks();
    static qint32 get_max_input_size(const QFont& font);

private:
    QMap<QString, DataBlock> data_blocks_;
};

} // namespace ComputerWorkshop
