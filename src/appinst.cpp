#include <QCoreApplication>

#include "appinst.h"
#include "util/helpers.h"
#include "model/packagemanager.h"
#include "model/packages.h"
#include "model/category.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDateTime>
#include <QDebug>
#include <iostream>

AppInst::AppInst(const QCoreApplication &app) : app(app){
    saveFilepath = "/tmp/appInst.sh";
    sourceFilepath = "../appInst.json";

    // Check some default paths
    const QString moreDefaultPaths[] = {
        QString("../appinst.json"),
        QString("appInst.json"),
        QDir::homePath() + "/.dotDesktop/appInst/appInst.json"
    };

    for (const QString& defaultPath : moreDefaultPaths){
        if(Helper::fileExists(defaultPath)){
            sourceFilepath=defaultPath;
            break;
        }
    }
}

// Run AppInst
int AppInst::run(){
    // Check if exists
    std::cout << "Trying to open \"" << sourceFilepath.toStdString() << "\"\n";
    if (!Helper::fileExists(sourceFilepath)){
        std::cerr << "Error: File not found: " << sourceFilepath.toStdString() << "\n";
        exit(-1);
    }

    QJsonObject root = Helper::loadJsonFile(sourceFilepath);
    initScript(root.size());

    // Parse Package Managers
    std::cout << "Package managers:\n";
    QMap<int,PackageManager*> pkgManagers;
    for(auto o : root.value("packageManager").toArray()){
        PackageManager* pkgManager = new PackageManager(o.toObject());
        std::cout << Helper::getIndentPrefix(2).toStdString()
            << QString("%1\n").arg(pkgManager->toString()).toStdString();
        if (pkgManager->isManagerAvailable()){
            pkgManagers.insert(pkgManager->getId(), pkgManager);
        }
    }

    // Parse package categories
    std::cout << "\nPackage categories:\n";
    QList<Category*> pkgCategories;
    for(auto o : root.value("categories").toArray()){
        Category *category = new Category(o.toObject());
        if (category->isEnabled()){
            pkgCategories.append(category);
            std::cout << "\n" << pkgCategories.last()->toString(2).toStdString();
        }
    }

    // Load all packages
    for (auto pkgCategory: pkgCategories){
        scriptText.append(QString("\n# Category: %1\n").arg(pkgCategory->getTitle()));
        QMap<int,QString> pkgInstallMaps;
        for (auto pkgs: pkgCategory->getPackages()){
            // Process one package
            for (auto pkgSources : pkgs->getSources()){
                int id = pkgSources->getPackageManagerId();
                if (id == PackageManager::PACKAGEMANAGER_ANY){
                    id = pkgManagers.first()->getId();
                }
                if(pkgManagers.contains(id)){
                    QString concated = QString("%1 %2").arg(pkgInstallMaps[id], pkgSources->getPackage());
                    pkgInstallMaps.insert(id, concated);
                }
            }
        }

        for (auto id : pkgInstallMaps.keys()){
            auto pkgManager = pkgManagers[id];
            if(!pkgManager->isInstallAtEnd()){
                scriptText += pkgManager->getInstallCommand(pkgInstallMaps[id]) + "\n";
            } else {
                scriptTextEnd += pkgManager->getInstallCommand(pkgInstallMaps[id]) + "\n";
            }
        }
    }

    return finishScript();
}

// Init the script file
void AppInst::initScript(int estSize){
    scriptText.reserve(estSize);
    scriptTextEnd.reserve((int)estSize/2);
    scriptTextEnd = "\n# Install at end\n";
    scriptText  = QString("#!/bin/bash") \
                  + "\n# Generated at " + QDateTime::currentDateTime().toString() + "\n" \
                  + "startsudo() { sudo -v; ( while true; do sudo -v; sleep 50; done; ) &   SUDO_PID=\"$!\" ; trap stopsudo SIGINT SIGTERM ; }\n" \
                  + "stopsudo() { disown \"$SUDO_PID\" 2>/dev/null ;kill \"$SUDO_PID\" 2>/dev/null ; trap - SIGINT SIGTERM ; sudo -k ; }\n" \
                  + "##########################################\n" \
                  + "startsudo";
}

// Append finishing text to script and write to file
bool AppInst::finishScript() {
    scriptTextEnd += QString("\nstopsudo\n")
        + "echo -e '\e[1;31m###############################\e[0m'\n"
        + "echo -e '\e[1;31m# \e[0;32mAppInst finished :)\e[0m\n'";

    scriptTextEnd.squeeze();
    scriptText += scriptTextEnd;
    scriptText.squeeze();

    std::cout << scriptText.toUtf8().constData();
    Helper::deleteFile(saveFilepath);
    return Helper::saveTextFile(saveFilepath, scriptText);
}


//
// Getter & Setter
//
QString AppInst::getSourceFilepath() const { return sourceFilepath; }
void AppInst::setSourceFilepath(const QString &value) { sourceFilepath = value; }
QString AppInst::getSaveFilepath() const{ return saveFilepath; }
void AppInst::setSaveFilepath(const QString &value) { saveFilepath = value; }
