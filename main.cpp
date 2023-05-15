#pragma once

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include "root/shop.h"

using namespace ComputerWorkshop;

const QString default_cfg_path = "computerworkshop.xml";

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString cfg_path = default_cfg_path;

    if (argc > 1) {
        cfg_path = QString::fromStdString(argv[1]);
    }

    try {
        auto config = Config::from_file(cfg_path);

        Shop shop;
        shop.setup(config);
        shop.run();

        return a.exec();

    } catch(const std::exception & ex) {
        QMessageBox::critical(nullptr, "Системная ошибка", ex.what());
    }

    return -1;
}

#include "main.moc"