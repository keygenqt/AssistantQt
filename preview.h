#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>
#include <QAbstractButton>
#include <QModelIndexList>

namespace Ui {
class Preview;
}

class Preview : public QDialog
{
    Q_OBJECT

public:
    explicit Preview(QWidget *parent = nullptr);
    ~Preview();
    void showInfo(QString info);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_buttonBox_accepted();
    void synchronizing(QModelIndexList);

signals:
    void successRaname();

private:
    Ui::Preview *ui;
};

#endif // PREVIEW_H
