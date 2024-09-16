/* 
 * File:   MngFormConfig.h
 * Author: batista
 *
 * Created on 21 de Fevereiro de 2013, 09:06
 */

#ifndef CTRLCONFIG_H
#define	CTRLCONFIG_H
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
#include <QMdiSubWindow>
#include "ConfigXml.h"
#include "DBUtil.h"
#include "DBConn.h"

#include "ui_FormConfig.h"


// namespace Ui
// {
//     class Ui_FormConfig;
// }

class QWidget;


class CtrlConfig : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(CtrlConfig)
public:
    explicit CtrlConfig(QWidget *parent = 0);
    virtual ~CtrlConfig();

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

#endif	/* CTRLCONFIG_H */

