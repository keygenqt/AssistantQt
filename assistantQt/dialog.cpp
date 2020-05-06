#include "dialog.h"
#include "ui_dialog.h"
#include <qdebug.h>
#include <QStringListModel>
#include <QtWidgets>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showLines(QString params)
{
    QStringList list = QStringList();
    QStringList items = params.split( "------------", QString::SkipEmptyParts);
    for ( const auto& item : items ) {
        QString tr = item.trimmed();
        if (tr == "") {
            continue;
        }
        list.append("\n" + tr + "\n");
    }
    QStringListModel *model = new QStringListModel(list);
    ui->listView->setModel(model);
    ui->listView->scrollToBottom();
    ui->listView->setCurrentIndex(model->index(model->rowCount()-1));
    ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    this->show();
}
