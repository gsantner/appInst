#include <QCoreApplication>

#include "appinst.h"
#include "util/helpers.h"

#include <QCommandLineParser>
#include <QStringList>
#include <QDebug>
#include <QString>
#include <iostream>

int main(int argc, char *argv[]){
    // Init
    QCoreApplication app(argc, argv);
    app.setApplicationName("AppInst");
    app.setApplicationVersion("0.4.1");
    app.setOrganizationName("Gregor Santner");
    app.setOrganizationDomain("https://gsantner.github.io/");

    // Init cmd parser
    QCommandLineParser parser;
    parser.setApplicationDescription("AppInst");
    const QCommandLineOption optionHelp = parser.addHelpOption();
    const QCommandLineOption optionVersion = parser.addVersionOption();
    parser.addPositionalArgument("src", "Source filepath to load in AppInst.");
    parser.addPositionalArgument("tar", "Target bash filepath to save to.");

    // Init AppInst
    AppInst appInst(app);

    // Parse cmd options
    parser.process(app);
    if(parser.isSet(optionHelp)){
        std::cout << parser.helpText().toStdString();
        return 0;
    }
    const QStringList& posArgs = parser.positionalArguments();
    if(posArgs.size() > 0){
        appInst.setSourceFilepath(posArgs.at(0));
    }
    if(posArgs.size() > 1){
        appInst.setSaveFilepath(posArgs.at(1));
    }
    return appInst.run();
}

