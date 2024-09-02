/* 
 * File:   DBConn.h
 * Author: batista
 *
 * Created on 20 de Fevereiro de 2013, 12:08
 */

#ifndef DBCONN_H
#define	DBCONN_H

#include <QObject>
#include <QString>

class DBConn {
public:
    DBConn();
    //DBConn() = default;
    DBConn(const DBConn&) = default;
    //
    ~DBConn();
    //


    QString getHostname() const;
    void setHostname(const QString &newHostname);
    QString getDatabase() const;
    void setDatabase(const QString &newDatabase);
    QString getPort() const;
    void setPort(const QString &newPort);
    QString getUsername() const;
    void setUsername(const QString &newUsername);
    QString getPassword() const;
    void setPassword(const QString &newPassword);

private:
    QString hostname;
    QString database;
    QString port;
    QString username;
    QString password;
};

#endif	/* DBCONN_H */

