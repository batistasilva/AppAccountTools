#ifndef MNGLOGFILE_H
#define MNGLOGFILE_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QString>
#include "ShowMsg.h"

class MngLogFile : public QObject
{
    Q_OBJECT
public:
    explicit MngLogFile(QObject *parent = nullptr);

    void CreateLogFile(QString filename, QString message);


signals:

private:
    QString system_path;
    //
    ShowMsg  * m_msg;
};

#endif // MNGLOGFILE_H
