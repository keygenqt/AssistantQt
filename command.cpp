#include "command.h"
#include <qdebug.h>
#include <QProcess>
#include <QRegularExpression>

Command::Command(QObject *parent) : QObject(parent)
{
    this->p = new QProcess(this);
}

QString Command::getVersion()
{
    p->start(command + " " + argVersion);
    p->waitForFinished();

    return p->readAllStandardOutput().replace("Assistant Ver ", "").replace("\n", "");
}

void Command::renameFilesYes(QString dir, QString tmpl, QString search, QString zeros, QString sort)
{
    QString command = this->command;

    if (!dir.isEmpty()) {
        command += " " + argDir + "=" + dir;
    }
    if (!tmpl.isEmpty()) {
        command += " " + argTemplate + "=" + tmpl;
    }
    if (!search.isEmpty()) {
        command += " " + argSearch + "=" + search;
    }
    if (!zeros.isEmpty() && zeros != "0") {
        command += " " + argZeros + "=" + zeros;
    }
    if (!sort.isEmpty()) {
        command += " " + argSort + "=" + sort;
    }

    p->start(command);
    p->write("yes\n");
    p->waitForFinished();
    qDebug() << p->readAllStandardOutput();
}

QString Command::renameFilesNo(QString dir, QString tmpl, QString search, QString zeros, QString sort)
{
    QString command = this->command;

    if (!dir.isEmpty()) {
        command += " " + argDir + "=" + dir;
    }
    if (!tmpl.isEmpty()) {
        command += " " + argTemplate + "=" + tmpl;
    }
    if (!search.isEmpty()) {
        command += " " + argSearch + "=" + search;
    }
    if (!zeros.isEmpty() && zeros != "0") {
        command += " " + argZeros + "=" + zeros;
    }
    if (!sort.isEmpty()) {
        command += " " + argSort + "=" + sort;
    }

    p->start(command);
    p->write("no\n");
    p->waitForFinished();
    return  p->readAllStandardOutput();
}
