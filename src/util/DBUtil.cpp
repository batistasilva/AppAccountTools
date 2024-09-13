/* 
 * File:   DBUtil.cpp
 * Author: batista
 * 
 * Created on 20 de Fevereiro de 2013, 08:38
 */

#include <QtSql/qtsqlglobal.h>
#include "DBUtil.h"

/**
 * Metodo construtor da aplicação
 */
DBUtil::DBUtil():
    m_mlf(new MngLogFile()),
    m_msg(new ShowMsg())
{
     m_msg->ShowMessage("Mensagem: Construtor Principal DBUtil()!!", COLOR_BLUE, COLOR_PINK);
    //
    //Abre banco Sqlite na memoria
    //openConnInSqLite();
}

bool DBUtil::runTestConnection()
{
    m_msg->ShowMessage("DBUtil::runTestConnection() ", COLOR_BLUE, COLOR_YELLOW);
    //
    DbPGree = QSqlDatabase::addDatabase("QPSQL");
    m_msg->ShowMessage(getHostname(), COLOR_BLUE, COLOR_PINK);
    m_msg->ShowMessage(getPort(), COLOR_BLUE, COLOR_PINK);
    m_msg->ShowMessage(getUsername(), COLOR_BLUE, COLOR_PINK);
    m_msg->ShowMessage(getPassword(), COLOR_BLUE, COLOR_PINK);

    //
    DbPGree.setHostName(getHostname());
    DbPGree.setDatabaseName(getDatabase());
    DbPGree.setPort(getPort().toInt());
    DbPGree.setUserName(getUsername());
    DbPGree.setPassword(getPassword());
    //

    //Valid if dbconnection found a valid driver
    if (!DbPGree.isValid()) {
        QString sqlerro = DbPGree.lastError().text();
        //
        QMessageBox::critical(0, QString::fromUtf8("Error: Invalid connection data!"), sqlerro);
        //
        sqlerro = "OpenConn(): Unable to open PostgreSql-> " + sqlerro;
        //
        m_msg->ShowMessage(sqlerro, COLOR_BLUE, COLOR_RED);
        //
        m_mlf->CreateLogFile("LOGPGSQL", sqlerro);
        //

        return false;
    }

    //Valid if database was opened corectly...
    if (!DbPGree.open()) {
        QString sqlerro = DbPGree.lastError().text();
        //
        QMessageBox::critical(0, QString::fromUtf8("Error: Connecting to the database!"), sqlerro);
        //
        sqlerro = "OpenConn(): Unable to open PostgreSql-> " + sqlerro;
        //
        m_msg->ShowMessage(sqlerro, COLOR_BLUE, COLOR_RED);
        //
        m_mlf->CreateLogFile("LOGPGSQL", sqlerro);
        //
        return false;
    }
    return true;
}


/**
 * Metodo responsavel por abrir uma conexao com o banco de dados
 * 
 * @return true ou false
 * -------------------------------------------------------------
 *          Driver     |    Database
 * -------------------------------------------------------------
 *       QDB2          |  IBM DB2 version 7.1and later
 *       QIBASE        |  Borland InterBase
 *       QMYSQL        |  MySQL
 *       QOCI          |  Oracle (Oracle Call Interface)
 *       QODBC         |  ODBC (includes Microsoft SQL Server)
 *       QPSQL         |  PostgreSQL 7.3 and later
 *       QSQLITE       |  SQLite version 3
 *       QSQLITE2      |  SQLite version 2
 *       QTDS          |  Sybase Adaptive Server
 * -------------------------------------------------------------
 */
bool DBUtil::openConnInPGree() {
    QString erro_log;
    status_read = readFile("ConfigXml.xml");
    //
    if(status_read){
        m_msg->ShowMessage("DBUtil::openConnInPGree() ", COLOR_BLUE, COLOR_YELLOW);
        //
        DbPGree = QSqlDatabase::addDatabase("QPSQL");
        m_msg->ShowMessage(getHostname(), COLOR_BLUE, COLOR_PINK);
        m_msg->ShowMessage(getPort(), COLOR_BLUE, COLOR_PINK);
        m_msg->ShowMessage(getUsername(), COLOR_BLUE, COLOR_PINK);
        m_msg->ShowMessage(getPassword(), COLOR_BLUE, COLOR_PINK);

        //
        DbPGree.setHostName(getHostname());
        DbPGree.setDatabaseName(getDatabase());
        DbPGree.setPort(getPort().toInt());
        DbPGree.setUserName(getUsername());
        DbPGree.setPassword(getPassword());
        //

        //Valid if dbconnection found a valid driver
        if (!DbPGree.isValid()) {
            QString sqlerro = DbPGree.lastError().text();
            //
            QMessageBox::critical(0, QString::fromUtf8("Error: Invalid connection data!"), sqlerro);
            //
            sqlerro = "OpenConn(): Unable to open PostgreSql-> " + sqlerro;
            //
            m_msg->ShowMessage(erro_log, COLOR_BLUE, COLOR_RED);
            //
            m_mlf->CreateLogFile("LOGPGSQL", sqlerro);
            //

            return false;
        }

        //Valid if database was opened corectly...
        if (!DbPGree.open()) {
            QString sqlerro = DbPGree.lastError().text();
            //
            QMessageBox::critical(0, QString::fromUtf8("Error: Connecting to the database!"), sqlerro);
            //
            erro_log = "OpenConn(): Unable to open PostgreSql-> " + sqlerro;
            //
            m_msg->ShowMessage(erro_log, COLOR_BLUE, COLOR_RED);
            //
            m_mlf->CreateLogFile("LOGPGSQL", erro_log);
            //        
            return false;
        }
    }

    //
    return true;
}


/**
 * Metodo responsavel por 
 * verficar se a conexao 
 * esta disponivel, ativa.
 * @return 
 */
bool DBUtil::isOpenConnPGree() {
    QString erro_log;
    //
    
    if (!DbPGree.isOpen()) {
        QString sqlerro = DbPGree.lastError().text();
        //
        erro_log = "OpenConn(): Nao foi possivel abri PostgreSql -> " + sqlerro;
        //
        m_msg->ShowMessage(erro_log, COLOR_BLUE, COLOR_RED);
        //
        m_mlf->CreateLogFile("LOGPGSQL", erro_log);
        //
        return false;
    }
    //
    return true;
}


void DBUtil::closeConnPGree(){
    /*Verifica se a conexao está aberta e a encerra*/
    if (DbPGree.isOpen()) {
        m_msg->ShowMessage("CloseConn() PGree, Conexao fechada com sucesso!!!", COLOR_BLUE, COLOR_RED);
        DbPGree.close();
    }    
}
