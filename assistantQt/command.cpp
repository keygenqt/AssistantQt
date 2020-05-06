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
        QString exclude,
        QString sort)
{
    QString command = this->command + " " + arg;

    if (!dir.isEmpty()) {
        command += " " + argDir + "=" + dir;
    }
    if (!search.isEmpty()) {
        command += " " + argSearch + "=" + search;
    }
    if (!exclude.isEmpty()) {
        command += " " + argExclude + "=" + exclude + " " + argExcludeLines;
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
        QString exclude,
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
    if (!exclude.isEmpty()) {
        command += " " + argExclude + "=" + exclude + " " + argExcludeLines;
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

QString Command::statistic(
        QString dir,
        QString search,
        QString exclude,
        QString sort)
{
    QString command = this->command + " " + this->argStatistic;

    if (!dir.isEmpty()) {
        command += " " + argDir + "=" + dir;
    }
    if (!search.isEmpty()) {
        command += " " + argSearch + "=" + search;
    }
    if (!exclude.isEmpty()) {
        command += " " + argExclude + "=" + exclude + " " + argExcludeLines;
    }

    QString typeSort = getSort(sort);

    if (!typeSort.isEmpty()) {
        command += " " + argSort + "=" + typeSort;
    }

    qDebug() << command;

    p->start(command);
    p->waitForFinished();
    return p->readAllStandardOutput();
}

QString Command::lines(
        QString dir,
        QString linesSearch,
        QString search,
        QString exclude,
        QString sort)
{
    QString command = this->command + " " + this->argLines;

    if (!dir.isEmpty()) {
        command += " " + argDir + "=" + dir;
    }
    if (!linesSearch.isEmpty()) {
        command += " " + argLinesSearch + "=" + linesSearch;
    } else {
        command += " " + argLinesSearch + "=.*";
    }
    if (!search.isEmpty()) {
        command += " " + argSearch + "=" + search;
    }
    if (!exclude.isEmpty()) {
        command += " " + argExclude + "=" + exclude + " " + argExcludeLines;
    }

    QString typeSort = getSort(sort);

    if (!typeSort.isEmpty()) {
        command += " " + argSort + "=" + typeSort;
    }

    qDebug() << command;

    p->start(command);
    p->waitForFinished();
    return p->readAllStandardOutput();
}
