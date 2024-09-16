// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qglobal.h"
#include "ShowMsg.h"
#include "CtrlConfig.h"

class ShowMsg;
class CtrlConfig;
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    bool openFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void configDatabase();


#ifndef QT_NO_CLIPBOARD

#endif
    void about();
    CtrlConfig * createMdiConfig();
    void switchLayoutDirection();

private:
    enum { MaxRecentFiles = 5 };

    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();


    QMdiArea *mdiArea;
    QMenu *windowMenu;
    QMenu *configMenu;
#ifndef QT_NO_CLIPBOARD

#endif
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *windowMenuSeparatorAct;
    QAction *configAct;
    //
    ShowMsg * m_msg;

};

#endif
