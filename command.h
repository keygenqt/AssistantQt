#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QProcess>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);
    QString getVersion();

private:
    QProcess *p;

    QString command = "java -jar /home/keygenqt/Documents/Other/gitlub/assistant/build/libs/assistant-0.0.1.jar";

    QString argDir = "--dir";
    QString argTemplate = "--template";
    QString argSearch = "--search";
    QString argZeros = "--zeros";
    QString argSort = "--sort";
    QString argVersion = "--version";

signals:

};

#endif // COMMAND_H
