#include "packagemanager.h"

#include <QProcess>
#include <QDebug>

#define PACKAGEMANAGER_UNDEFINED 0

PackageManager::PackageManager(const QJsonObject &json){
    id = json.value("id").toInt(0);
    title = json.value("title").toString("");
    cmd = json.value("cmd").toString("");
    cmdParam = json.value("param").toString("");
    installAtEnd = json.value("instAtEnd").toBool(false);
    mustPrefixWithSudo = json.value("sudo").toBool(true);
    managerAvailable = isPackageManagerAny()? -1 : PACKAGEMANAGER_UNDEFINED;
    isManagerAvailable();
}

QString PackageManager::getInstallCommand(QString arg) const{
    return QString("%1%2 %3 %4").arg(mustPrefixWithSudo? "sudo " : "",cmd,cmdParam,arg);
}

QString PackageManager::toString() const{
    return QString("[%1] %2: %3 %4").arg(QString::number(id),title,cmd, managerAvailable>0?"[Available]":"");
}

bool PackageManager::isPackageManagerAny() const{
    return this->id == PACKAGEMANAGER_ANY;
}

bool PackageManager::isManagerAvailable(){
    // Check if process is callable
    if(managerAvailable == PACKAGEMANAGER_UNDEFINED){
        QProcess process;
        process.start(QString("which %1").arg(cmd));
        process.waitForFinished(-1);
        QString stdout = process.readAllStandardOutput();
        managerAvailable = stdout.length() > 0 ? 1 : 0;
    }

    return managerAvailable == 1;
}

//
// Getter & Setter
//
int PackageManager::getId() const{ return id; }
QString PackageManager::getTitle() const{ return title; }
QString PackageManager::getCmd() const { return cmd; }
QString PackageManager::getCmdParam() const{ return cmdParam; }
bool PackageManager::getMustPrefixWithSudo() const { return mustPrefixWithSudo; }
bool PackageManager::isInstallAtEnd() const{ return installAtEnd; }
void PackageManager::setInstallAtEnd(bool value){ installAtEnd = value; }
