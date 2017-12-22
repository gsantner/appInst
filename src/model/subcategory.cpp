#include "subcategory.h"
#include "../util/helpers.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


SubCategory::SubCategory(const QJsonObject& json){
    title = json.value("title").toString();
    enabled = json.contains("enabled") ? json.value("enabled").toBool(true) : true;

    for(auto o : json.value("packages").toArray()){
        Packages *packages = new Packages(o.toObject());
        if (packages->isEnabled()){
            sources.append(packages);
        }
    }
}

QString SubCategory::toString(unsigned int indent){
    QString ret;
    for(auto source : sources){
        ret += source->toString(indent+2) + "\n";
    }
    return Helper::getIndentPrefix(indent)+ title + "\n" + ret;

}

//
// Getter & Setter
//
QString SubCategory::getTitle() const { return title; }
QList<Packages*> SubCategory::getSources() const { return sources; }
bool SubCategory::isEnabled() const { return enabled; }
void SubCategory::setEnabled(bool value) { enabled = value; }
