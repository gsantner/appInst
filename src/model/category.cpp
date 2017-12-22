#include "category.h"
#include "../util/helpers.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

Category::Category(const QJsonObject& json){
    title = json.value("category").toString();
    enabled = json.contains("enabled") ? json.value("enabled").toBool(true) : true;

    for(auto o : json.value("subcategories").toArray()){
        SubCategory *subCat = new SubCategory(o.toObject());
        if (subCat->isEnabled()){
            packages.append(subCat);
        }
    }
}

QString Category::toString(unsigned int indent) const{
    QString ret;
    for(auto package : packages){
        ret += package->toString(indent+2) + "\n";
    }
    return Helper::getIndentPrefix(indent)+ title + "\n" + ret;
}

//
// Getter & Setter
//
QString Category::getTitle() const { return title; }
QList<SubCategory*> Category::getPackages() const { return packages; }
bool Category::isEnabled() const { return enabled; }
void Category::setEnabled(bool value) { enabled = value; }
