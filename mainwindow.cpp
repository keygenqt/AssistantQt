#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QMessageBox>
#include <QStyle>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("AssistantQt v0.0.2; Assistant v0.0.2");

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

    ui->comboBox_sort->addItem("Standart by name");
    ui->comboBox_sort->addItem("Natural by name");
    ui->comboBox_sort->addItem("Last modification");



//    QString command = "java -jar /home/keygenqt/Documents/Other/gitlub/assistant/build/libs/assistant-0.0.1.jar";

//    QStringList arguments;
//    arguments << "--version";

//    QProcess *p = new QProcess(parent);
//    p->setProcessChannelMode(QProcess::MergedChannels);
//    p->start(command, arguments);

//    if (p->waitForStarted()) {
//        if (!p->waitForReadyRead()) {
//            qDebug() << "waitForReadyRead() [false] : CODE: " << QVariant(p->error()).toString() << " | ERROR STRING: " << p->errorString();
//        }
//        if (!p->waitForFinished(1000)) {
//            qDebug() << p->readAll();
//            qDebug() << p->readAllStandardOutput();
//        }
//    } else {
//        qDebug() << "error: waitForStarted";
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 QDir::homePath(),
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->input_dir->setText(dir);
}
