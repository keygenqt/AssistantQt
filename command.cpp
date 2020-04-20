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

QString Command::renameFiles(
        QString answer,
        QString dir,
        QString tmpl,
        QString search,
        QString zeros,
        QString sort)
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
        if (sort == "Standart by name") {
            command += " " + argSort + "=default";
        }
        else if (sort == "Natural by name") {
            command += " " + argSort + "=natural";
        }
        else if (sort == "Last modification") {
            command += " " + argSort + "=mod";
        }
    }

    qDebug() << command;

    p->start(command);
    p->write(answer.toUtf8() + "\n");
    p->waitForFinished();
    return p->readAllStandardOutput();
}
