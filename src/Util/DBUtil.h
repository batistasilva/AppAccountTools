/* 
 * File:   DBUtil.h
 * Author: batista
 *
 * Created on 20 de Fevereiro de 2013, 08:38
 */

#ifndef DBUTIL_H
#define	DBUTIL_H

#include <QObject>
#include <QtSql/qtsqlglobal.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QVector>
#include "ShowMsg.h"
#include "MngLogFile.h"
#include "DBConn.h"
#include "ConfigXml.h"

;
class DBUtil : public ConfigXml {

public:
    DBUtil();
    //
    //QSqlQuery query;

    QSqlDatabase getDbPGree() const {
        return DbPGree;
    }

    void setDbPGree(QSqlDatabase DbPGree) {
        this->DbPGree = DbPGree;
    }


    /**
     * Abre uma conexao com
     * o banco PostgreSql
     * @return true or false
     */
    bool openConnInPGree();

    /**
     * Fecha uma conexão 
     * aberta com o banco 
     * PostgreSql
     * @return 
     */
    void closeConnPGree();



    /**
     * Verifica se ha uma
     * conexao aberta com
     * o banco PostgreSql
     * @return true or false
     */
    bool isOpenConnPGree();

    DBConn *dbc() const;
    void setDbc(DBConn *newDbc);

protected:
    QSqlDatabase DbPGree;
    //

private:
    bool status_read;

    MngLogFile * m_mlf;
    ShowMsg * m_msg;
    DBConn * m_dbc;

};


#endif	/* DBUTIL_H */

