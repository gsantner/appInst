#pragma once

#include <QString>
#include <QList>
#include "subcategory.h"

class Category{
    public:
        Category (const QJsonObject& json);

        QString toString (unsigned int indent = 0) const;

        QString getTitle () const;
        QList <SubCategory*> getPackages () const;
        bool isEnabled() const;
        void setEnabled(bool value);

private:
        QString title;
        QList <SubCategory*> packages;
        bool enabled;
};
