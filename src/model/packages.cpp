#include "packages.h"
#include "../util/helpers.h"
#include <QDebug>

Packages::Packages(const QJsonObject& json){
    packageManagerId = json.value("type").toInt(0);
    title = json.value("title").toString("");
    enabled = json.contains("enabled") ? json.value("enabled").toBool(true) : true;
    if(title.contains("#")){
        int sharpIndex = title.indexOf("#");
        title = title.remove(sharpIndex, title.length()-sharpIndex);
    }
}

QString Packages::toString(unsigned int indent){
    return Helper::getIndentPrefix(indent)+ QString("[%1] %2").arg(QString::number(packageManagerId),title);
}


//
// Getter & Setter
//
QString Packages::getPackage() const { return title; }
int Packages::getPackageManagerId() const { return packageManagerId; }
bool Packages::isEnabled() const { return enabled; }
void Packages::setEnabled(bool value) { enabled = value; }
