#include "preview.h"
#include "ui_preview.h"
#include <qdebug.h>

Preview::Preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);
}

Preview::~Preview()
{
    delete ui;
}

void Preview::on_buttonBox_clicked(QAbstractButton *button)
{

}

void Preview::on_buttonBox_accepted()
{
    emit successRaname();
}


void Preview::showInfo(QString info) {
    qDebug() << info;
}
