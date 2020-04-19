#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <preview.h>
#include <command.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void successRaname();

private:
    Ui::MainWindow *ui;
    Command *command;
    Preview *preview;
};
#endif // MAINWINDOW_H
