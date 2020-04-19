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
