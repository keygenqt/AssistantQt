/*
 * This file is part of AssistantQt.
 *
 * AssistantQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AssistantQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AssistantQt.  If not, see <https://www.gnu.org/licenses/>.
 */

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
    this->preview = new Preview(this);
    this->preview->setModal(true);

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
        QMessageBox::information(this, tr("AssistantQt"), "AssistantQt not found<br><br>Install AssistantQt app:<br><b>sudo snap install kg-assistant</b>");
        this->close();
    } else {
        this->show();
    }

    this->setFixedSize(680, 330);
    this->statusBar()->setSizeGripEnabled(false);

    connect(this->preview, SIGNAL(success()), this, SLOT(success()));
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
    this->typeSuccess = "rename";

    QString dir = ui->input_dir->text();
    if (dir.isEmpty()) {
        QMessageBox::information(this, tr("AssistantQt"), "Select folder pls.");
    } else {
        QString params = command->renameFiles("no", dir,
                             ui->input_template->text(),
                             ui->input_search->text(),
                             QString::number(ui->spinBox_zeros->value()),
                             ui->comboBox_sort->itemText(ui->comboBox_sort->currentIndex()));

        if (params.contains("->")) {
            this->preview->showInfo(params);
            this->preview->show();
        } else {
            QMessageBox::information(this, tr("AssistantQt"), "Files not found.");
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    this->typeSuccess = "ext";

    QString dir = ui->input_dir->text();
    if (dir.isEmpty()) {
        QMessageBox::information(this, tr("AssistantQt"), "Select folder pls.");
    } else {
        QString type = command->argExtensionLower;
        if (ui->radioButton->isChecked()) {
            type = command->argExtensionUp;
        }
        QString params = command->extension(type, "no", dir,
                             ui->input_search->text(),
                             ui->comboBox_sort->itemText(ui->comboBox_sort->currentIndex()));

        if (params.contains("->")) {
            this->preview->showInfo(params);
            this->preview->show();
        } else {
            QMessageBox::information(this, tr("AssistantQt"), "Files not found.");
        }
    }
}

void MainWindow::success() {
    if (this->typeSuccess == "rename") {
        command->renameFiles("yes",
                             ui->input_dir->text(),
                             ui->input_template->text(),
                             ui->input_search->text(),
                             QString::number(ui->spinBox_zeros->value()),
                             ui->comboBox_sort->itemData(ui->comboBox_sort->currentIndex()).toString());
        QMessageBox::information(this, tr("AssistantQt"), "Success rename files");
    }
    else if (this->typeSuccess == "ext") {
        QString type = command->argExtensionLower;
        if (ui->radioButton->isChecked()) {
            type = command->argExtensionUp;
        }
        QString params = command->extension(type, "yes",
                             ui->input_dir->text(),
                             ui->input_search->text(),
                             ui->comboBox_sort->itemText(ui->comboBox_sort->currentIndex()));
        QMessageBox::information(this, tr("AssistantQt"), "Success update files extensions");
    }
}
