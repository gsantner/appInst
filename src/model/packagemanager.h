#pragma once

#include <QString>
#include <QJsonObject>

class PackageManager{
    public:
        static const int PACKAGEMANAGER_ANY = 0;

        PackageManager (const QJsonObject& json);

        QString toString () const;
        bool isPackageManagerAny () const;
        bool isManagerAvailable ();
        QString getInstallCommand (QString arg = "") const;

        int getId () const;
        QString getTitle () const;
        QString getCmd () const;
        QString getCmdParam () const;
        bool getMustPrefixWithSudo () const;
        bool isInstallAtEnd () const;
        void setInstallAtEnd (bool value);

    private:
        int id;
        QString title;
        QString cmd;
        QString cmdParam;
        int managerAvailable;
        bool mustPrefixWithSudo;
        bool installAtEnd;
};
