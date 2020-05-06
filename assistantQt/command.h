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
    QString renameFiles(QString, QString, QString, QString, QString, QString, QString);
    QString extension(QString, QString, QString, QString, QString, QString);
    QString statistic(QString, QString, QString, QString);
    QString lines(QString, QString, QString, QString, QString);
    QString getSort(QString);

public:
    QString argExtensionUp = "--extension-up";
    QString argExtensionLower = "--extension-lower";

private:
    QProcess *p;

    QString command = "java -jar /home/keygenqt/Documents/Other/applications/assistant/build/libs/assistant.jar";
//    QString command = "java -jar /snap/kg-assistantqt/current/jar/assistant.jar"; // snap

    QString argDir = "--dir";
    QString argTemplate = "--template";
    QString argSearch = "--search";
    QString argExclude = "--exclude";
    QString argExcludeLines = "--exclude-lines=500";
    QString argZeros = "--zeros";
    QString argSort = "--sort";
    QString argVersion = "--version";
    QString argStatistic = "--statistic";
    QString argLines = "--lines";
    QString argLinesSearch = "--lines-search";

signals:

};

#endif // COMMAND_H
