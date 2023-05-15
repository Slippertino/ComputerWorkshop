#include "columnseditdialog.h"
#include "ui_columnseditdialog.h"

namespace ComputerWorkshop {

ColumnsEditDialog::ColumnsEditDialog(
    const QList<QString>& headers,
    QList<QString>* data,
    QWidget *parent
) :
    QDialog(parent),
    ui(new Ui::ColumnsEditDialog)
{
    ui->setupUi(this);

    resize(width(), height_for_box_px * headers.size());
    headers_ = data;

    ui->main_layout->removeItem(ui->buttons_layout);
    ui->main_layout->removeWidget(ui->ok_button);
    ui->main_layout->removeWidget(ui->cancel_button);

    for(auto i = 0; i < headers.size(); ++i) {
        auto box = new QCheckBox(this);
        box->setText(headers[i]);
        box->setChecked(true);

        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(box->sizePolicy().hasHeightForWidth());
        box->setSizePolicy(sizePolicy);

        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(true);

        box->setFont(font1);
        box->setTristate(false);

        ui->main_layout->addWidget(box);
        boxes_.append(box);
    }

    ui->main_layout->addLayout(ui->buttons_layout);
    ui->main_layout->addWidget(ui->ok_button);
    ui->main_layout->addWidget(ui->cancel_button);

    connect(ui->ok_button,      SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancel_button,  SIGNAL(clicked()), this, SLOT(reject()));
}

ColumnsEditDialog::~ColumnsEditDialog() {
    foreach(auto box, boxes_) {
        delete box;
    }

    delete ui;
}

void ColumnsEditDialog::accept() {
    headers_->clear();
    for(auto i = 0; i < boxes_.size(); ++i) {
        if (boxes_[i]->isChecked()) {
            headers_->append(boxes_[i]->text());
        }
    }

    QDialog::accept();
}

} // namespace ComputerWorkshop
