#pragma once

#define varname(x) #x

#include <QString>
#include <QFile>
#include <QStringList>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>


namespace Helper{
    QStringList jsonArrayToStringList (QJsonArray array);
    QJsonObject loadJsonFile (const QString& filepath);
    QString getAppDataFolder ();
    bool createParentFolders (QString filenameOrPath);
    bool saveJsonFile (QJsonObject json, QString file);
    void coutLine (QString msg);
    bool deleteFile (QString filename);
    bool saveTextFile (QString filename, QString text);
    bool fileExists (QString path);

    QString getHumanReadableFileSize (double filesize);
    QString getDirectory (QString filepath);
    QString getFilenameWithExtension (QString filePath);
    QString resolveApplicationInPath (QString appName);
    QString getIndentPrefix (unsigned int indent);
}
