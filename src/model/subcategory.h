#pragma once

#include "packages.h"
#include <QString>
#include <QList>

class SubCategory{
    public:
        SubCategory (const QJsonObject& json);

        QString toString (unsigned int indent);

        QString getTitle () const;
        QList < Packages*>getSources () const;
        bool isEnabled() const;
        void setEnabled(bool value);

private:
        QString title;
        QList <Packages*>sources;
        bool enabled;
};
