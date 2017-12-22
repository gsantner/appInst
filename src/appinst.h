#pragma once

#include <QObject>
#include <QCoreApplication>
#include <QString>

class AppInst{
	public:
		AppInst (const QCoreApplication & app);
		int run ();

		QString getSaveFilepath () const;
		void setSaveFilepath (const QString & value);
		QString getSourceFilepath () const;
		void setSourceFilepath (const QString & value);

    private:
        void initScript (int estSize);
		bool finishScript ();

		const QCoreApplication & app;
		QString scriptText;
		QString scriptTextEnd;
		QString saveFilepath;
		QString sourceFilepath;
};
