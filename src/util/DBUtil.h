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
    bool runTestConnection();

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

protected:
    QSqlDatabase DbPGree;
    //

private:
    bool status_read = false;

    MngLogFile * m_mlf;
    ShowMsg * m_msg;

};


#endif	/* DBUTIL_H */

