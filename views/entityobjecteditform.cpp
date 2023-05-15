#include "entityobjecteditform.h"

namespace ComputerWorkshop {

EntityObjectEditForm::EntityObjectEditForm(
    QList<HeaderData> inputs_data, 
    QWidget* parent
) : QDialog(parent) {
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/assets/pc_repair_60.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);

    QGridLayout* glayout = new QGridLayout;

    glayout->setHorizontalSpacing(35);
    glayout->setColumnStretch(0, 1);
    glayout->setColumnStretch(1, 7);
    glayout->setVerticalSpacing(50);

    QFont controls_font = QFont("Calibri", 14, QFont::Weight::Medium);
    auto max_input_size = get_max_input_size(controls_font);

    for (auto i = 0; i < inputs_data.size(); ++i) {
        const auto& input = inputs_data[i];

        QLabel* lbl = new QLabel;
        lbl->setText(input.name);
        lbl->setAlignment(Qt::AlignmentFlag::AlignLeft);
        lbl->setFont(controls_font);
        lbl->hide();

        auto wdgt = input.input->get_widget();
        wdgt->setFont(controls_font);
        wdgt->setMinimumWidth(max_input_size);
        wdgt->hide();

        data_blocks_.insert(input.name, { lbl, input.input });

        glayout->addWidget(lbl, i, 0);
        glayout->addWidget(wdgt, i, 1);
    }

    QBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->setSpacing(50);
    btns_layout->setContentsMargins(50, 0, 50, 0);

    QPushButton* ok = new QPushButton("Ок");
    ok->setFont(controls_font);
    connect(ok, SIGNAL(clicked()), SLOT(accept()));
    btns_layout->addWidget(ok);

    QPushButton* cancel = new QPushButton("Отмена");
    cancel->setFont(controls_font);
    connect(cancel, SIGNAL(clicked()), SLOT(reject()));
    btns_layout->addWidget(cancel);

    glayout->addLayout(btns_layout, inputs_data.size(), 0, 1, 2);

    setLayout(glayout);
}

void EntityObjectEditForm::set_window_title(const QString& title) {
    setWindowTitle(title);
}

QVariantMap EntityObjectEditForm::get_inputs_data() {
    QVariantMap res;

    for (const auto& inp_nm : data_blocks_.keys()) {
        auto inp = data_blocks_.value(inp_nm).input;

        if (is_block_available(inp_nm)) {
            res.insert(inp_nm, inp->get_data());
        }

        inp->clear();
    }

    hide_all_blocks();

    return res;
}

void EntityObjectEditForm::set_input_data(const QString& name, const QString& value) {
    data_blocks_.value(name).input->set_data(value);
}

void EntityObjectEditForm::show_blocks(const QList<QString>& headers) {
    foreach(const auto& hdr, headers) {
        auto& block = data_blocks_.value(hdr);
        block.label->show();
        block.input->get_widget()->show();
    }
}

void EntityObjectEditForm::hide_all_blocks() {
    foreach(const auto& block, data_blocks_) {
        block.label->hide();
        block.input->get_widget()->hide();
    }
}

bool EntityObjectEditForm::is_block_available(const QString& name) const {
    const auto& block = data_blocks_.value(name);

    return !block.input->get_widget()->isHidden();
}

EntityObjectEditForm::~EntityObjectEditForm() {
    QList<QWidget*> children;

    do
    {
       children = findChildren<QWidget*>();

       if (children.count() == 0) break;

       delete children.at( 0 );

    } while(true);
}

void EntityObjectEditForm::accept() {
    for(auto& name : data_blocks_.keys()) {
        if (!is_block_available(name)) {
            continue;
        }

        const auto& inp = data_blocks_.value(name).input;

        if (inp->get_type() != DataInputType::EDIT_INPUT) {
            continue;
        }

        auto edit = qobject_cast<QLineEdit*>(inp->get_widget());
        if (!edit->hasAcceptableInput()) {
            QMessageBox::warning(
                this,
                "Неверный формат данных",
                QString("Поле \"%1\" заполнено некорректно. \nПояснение: %2")
                    .arg(name)
                    .arg(edit->placeholderText())
            );

            return;
        }
    }

    QDialog::accept();
}

void EntityObjectEditForm::reject() {
    foreach(auto edit, data_blocks_) {
        edit.input->clear();
    }

    hide_all_blocks();

    QDialog::reject();
}

qint32 EntityObjectEditForm::get_max_input_size(const QFont& font) {
    QString max_input_str(50, 'm');
    QFontMetrics fm(font);
    return fm.horizontalAdvance(max_input_str);
}

} // namespace ComputerWorkshop
