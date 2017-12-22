#pragma once

#include <QString>
#include <QJsonObject>

class Packages{
    public:
        Packages (const QJsonObject& json);

        QString toString (unsigned int indent = 2);

        QString getPackage () const;
        int getPackageManagerId () const;
        bool isEnabled() const;
        void setEnabled(bool value);

private:
        int packageManagerId;
        QString title;
        bool enabled;
};
