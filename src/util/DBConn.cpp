/* 
 * File:   DBConn.cpp
 * Author: batista
 * 
 * Created on 20 de Fevereiro de 2013, 12:08
 */


#include "DBConn.h"


DBConn::DBConn()
{

}


DBConn::~DBConn() {
}

QString DBConn::getHostname() const
{
    return hostname;
}

void DBConn::setHostname(const QString &newHostname)
{
    hostname = newHostname;
}

QString DBConn::getDatabase() const
{
    return database;
}

void DBConn::setDatabase(const QString &newDatabase)
{
    database = newDatabase;
}

QString DBConn::getPort() const
{
    return port;
}

void DBConn::setPort(const QString &newPort)
{
    port = newPort;
}

QString DBConn::getUsername() const
{
    return username;
}

void DBConn::setUsername(const QString &newUsername)
{
    username = newUsername;
}

QString DBConn::getPassword() const
{
    return password;
}

void DBConn::setPassword(const QString &newPassword)
{
    password = newPassword;
}






