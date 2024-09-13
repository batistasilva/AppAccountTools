#ifndef CONFIGXML_H
#define	CONFIGXML_H
#include <QtGui>
#include <QtXml/QtXml>
#include <QFile>
#include <QXmlStreamReader>
#include <QObject>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include "DBConn.h"
#include "ShowMsg.h"


class ConfigXml: public DBConn {
public:
    ConfigXml();
    virtual ~ConfigXml();
    //
    bool readFile(const QString &fileName);
    //
    bool writeFile(const QString &fileName);
    //


private:
    ShowMsg * m_msg;
    QString system_path;
    QString folder_write;

    void readMainContentElement();
    void readChildContentElement();
    QXmlStreamReader reader;
};

#endif	/* CONFIGXML_H */

