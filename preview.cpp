#include "preview.h"
#include "ui_preview.h"
#include <qdebug.h>
#include <QStringListModel>

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

void Preview::synchronizing(QModelIndexList index)
{
    qDebug() << "12";
    ui->listViewWill->setCurrentIndex(index.first());
}

void Preview::on_buttonBox_accepted()
{
    emit successRaname();
}


void Preview::showInfo(QString info) {

    QStringList now = QStringList();
    QStringList will = QStringList();

    QStringList items = info.split( "\n" );
    for ( const auto& item : items )
    {
        if (item == "") {
            break;
        }
        QStringList items = item.split( "->" );
        if (items.size() == 2) {
            now.append("\n" + items[0].trimmed() + "\n");
            will.append("\n" + items[1].trimmed() + "\n");
        }
    }

    ui->listViewNow->setModel(new QStringListModel(now));
    ui->listViewWill->setModel(new QStringListModel(will));
}
