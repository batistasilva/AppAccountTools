/*
 * File:   ConfigXml.h
 * Author: batista
 *
 * Created on 20 de Fevereiro de 2013, 08:52
 */

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


class ConfigXml : public QObject {
    Q_OBJECT
public:
    explicit ConfigXml(QObject *parent = nullptr);
    virtual ~ConfigXml();
    //
    bool readFile(const QString &fileName);
    //
    bool writeFile(const QString &fileName);

private:
    DBConn * m_dbconn;
    ShowMsg * m_msg;

    void readMainContentElement(); //ler mãe
    void readChildContentElement(); //ler filhos
    QXmlStreamReader reader;
};

#endif	/* CONFIGXML_H */

