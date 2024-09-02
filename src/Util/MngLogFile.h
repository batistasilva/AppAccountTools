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


    QString getFile_name() const;
    void setFile_name(const QString &newFile_name);

signals:

private:
    QString system_path;
    QString file_name;
    //
    ShowMsg  * m_msg;
};

#endif // MNGLOGFILE_H
