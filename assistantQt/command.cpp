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

QString Command::extension(
        QString arg,
        QString answer,
        QString dir,
        QString search,
        QString sort)
{
    QString command = this->command + " " + arg;

    if (!dir.isEmpty()) {
        command += " " + argDir + "=" + dir;
    }
    if (!search.isEmpty()) {
        command += " " + argSearch + "=" + search;
    }

    QString typeSort = getSort(sort);

    if (!typeSort.isEmpty()) {
        command += " " + argSort + "=" + typeSort;
    }

    qDebug() << command;

    p->start(command);
    p->write(answer.toUtf8() + "\n");
    p->waitForFinished();
    return p->readAllStandardOutput();
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
    if (!search.isEmpty()) {
        command += " " + argSearch + "=" + search;
    }
    if (!tmpl.isEmpty()) {
        command += " " + argTemplate + "=\"" + tmpl + "\"";
    }
    if (!zeros.isEmpty() && zeros != "0") {
        command += " " + argZeros + "=" + zeros;
    }

    QString typeSort = getSort(sort);

    if (!typeSort.isEmpty()) {
        command += " " + argSort + "=" + typeSort;
    }

    qDebug() << command;

    p->start(command);
    p->write(answer.toUtf8() + "\n");
    p->waitForFinished();
    return p->readAllStandardOutput();
}

QString Command::getSort(QString sort)
{
    if (sort == "Standart by name") {
        return "default";
    }
    else if (sort == "Natural by name") {
        return "natural";
    }
    else if (sort == "Last modification") {
        return "mod";
    }
    return "";
}
