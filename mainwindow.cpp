#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QMessageBox>
#include <QStyle>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QProcess>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->command = new Command(parent);
    QString version = command->getVersion();

    ui->setupUi(this);
    ui->statusbar->showMessage("AssistantQt v0.0.2; Assistant v" + version);

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

    if (version == "") {
        this->hide();
        QMessageBox::information(this, tr("Screener"), "Screener not found. Install screener app.");
        this->close();
    } else {
        this->show();
    }
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

void MainWindow::on_pushButton_2_clicked()
{

}
