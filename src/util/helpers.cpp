#include "helpers.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>
#include <iostream>
#include <QFileInfo>

// Convert a JSON-Array to a QStringList
QStringList Helper::jsonArrayToStringList(QJsonArray array){
    QStringList result;
    for(const QJsonValue& location : array){
        result.append(location.toString());
    }
    result.sort(Qt::CaseInsensitive);
    return result;
}

// Get the default AppData Folder for this application
QString Helper::getAppDataFolder(){
    return QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0) + QDir::separator();
}

// Convert filesize to "Human readable format"
QString Helper::getHumanReadableFileSize(double filesize) {
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(filesize >= 1024.0 && i.hasNext()){
        unit = i.next();
        filesize /= 1024.0;
    }
    return QString().setNum(filesize,'f',2)+" "+unit;
}

// cout a line with linefeed
void Helper::coutLine(QString msg){
    std::cout << msg.toStdString() << std::endl;
}

// Returns an indented prefix (e.g. -->)
QString Helper::getIndentPrefix(unsigned int indent){
    QString ret;
    if(indent > 0){
        for(unsigned int i=0; i < indent; i++){
            ret += (i == (indent-1) ? ">":"-");
        }
    }
    return ret;
}

//
//      File stuff
//

// Delete file
bool Helper::deleteFile(QString filepath){
    QFile file(filepath);
    if(file.exists() && file.isWritable()){
        return file.remove();
    }
    return false;
}

// Write text to given filepath
bool Helper::saveTextFile(QString filepath, QString text){
    createParentFolders(filepath);
    QFile file(filepath);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << text;
        file.close();
        return true;
    }
    return false;
}

// Load text from a file
QJsonObject Helper::loadJsonFile(const QString& filepath){
    QFile file(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file.readAll();
    file.close();
    return QJsonDocument::fromJson(str.toUtf8()).object();
}

// Save a QJsonObject to a file
bool Helper::saveJsonFile(QJsonObject json, QString file){
    return saveTextFile(file, QString(QJsonDocument(json).toJson()));
}

// Get absolute directory from file
QString Helper::getDirectory(QString filePath){
    QFileInfo info(filePath);
    return info.absolutePath();
}

// Check if the string filepath exists and is a file
bool Helper::fileExists(QString filepath) {
    QFileInfo file(filepath);
    return file.exists() && file.isFile();
}

// Create parent folders of file
bool Helper::createParentFolders(QString filepath){
    QFileInfo info(filepath);
    QDir dir;
    return dir.mkpath(info.absolutePath());
}

// Get filename including extension
QString Helper::getFilenameWithExtension(QString filePath){
    QFileInfo info(filePath);
    return info.fileName();
}



//
//  Test, deprecated and deleted stuff
//
QString Helper::resolveApplicationInPath(QString appName){
    QProcess resolveProcess;
    QStringList arguments;
#ifdef __linux
    arguments.append(appName);
    resolveProcess.setArguments(arguments);
    resolveProcess.start("which",arguments);
    resolveProcess.waitForFinished();
    QString which = QString(resolveProcess.readAll());
    if(which.startsWith(QDir::separator())){
        which = which.replace("\n","");
        return which;
    }
#endif
    return QString("");
}
