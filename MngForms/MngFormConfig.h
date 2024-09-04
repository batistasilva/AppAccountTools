/* 
 * File:   MngFormConfig.h
 * Author: batista
 *
 * Created on 21 de Fevereiro de 2013, 09:06
 */

#ifndef MNGFORMCONFIG_H
#define	MNGFORMCONFIG_H
#include <QDebug>
#include <QKeyEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QtCore/QTimer>
#include <QObject>
#include <QStringListModel>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "ConfigXml.h"
#include "DBUtil.h"
#include "DBConn.h"
#include "ui_MngFormConfig.h"


using namespace std;
using std::string;

// namespace Ui
// {
//     class Ui_FormConfig;
// }

class QWidget;
class QTimer;
class MngFormConfig : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(MngFormConfig)
public:
    explicit MngFormConfig(QWidget *parent = 0);
    virtual ~MngFormConfig();

protected:
    //void keyPressEvent(QKeyEvent * event);

protected:
    //void closeEvent(QCloseEvent *event);

private slots:   
    void runSaveConf();
    void runTestConf();
    void runClose();

private:
    ConfigXml * m_cfx;
    DBUtil * m_dao;
    // DBConn * m_dbc;
    Ui_FormConfig * mfcg;

    bool VlFillForm();
};

#endif	/* MNGFORMCONFIG_H */

