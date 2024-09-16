// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtWidgets>

#include "mainwindow.h"
#include "mdichild.h"

class MdiArea : public QMdiArea
{
public:
    MdiArea(QWidget *parent = 0)
        :
        QMdiArea(parent)
        ,
        m_pixmap(QPixmap(":/images/logo.png"))

       // m_pixmap("/home/system/WorkSpace/QtProjects/QtTestHowTo/QtMdiExample/forms/images/logo.png")

    {
    }
protected:
    void paintEvent(QPaintEvent *event)
    {
        QMdiArea::paintEvent(event);

        QPainter painter(viewport());

        int x = (geometry().width() - m_pixmap.width() ) /2;
        int y = (geometry().height() - m_pixmap.height() ) /2;
        painter.drawPixmap(x,y,m_pixmap);  // draw the pixmap in center, or whatever location u want

       // m_pixmap.load(":/images/logo.png");

       // painter.drawPixmap(x,y,m_pixmap);  // draw the pixmap in center, or whatever location u want


        // QPixmap pixmapTarget = QPixmap(":/images/PNG/logo-194x42.png");
        // pixmapTarget = pixmapTarget.scaled(x, y, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // painter.drawPixmap(x,y,pixmapTarget);  // draw the pixmap in center, or whatever location u want

        // // Calculate the logo position - the bottom right corner of the mdi area.
        // int x = m_pixmap.width();//width() - m_pixmap.width();
        // int y = m_pixmap.height();//height() - m_pixmap.height();
        // painter.drawPixmap(x, y, m_pixmap);
    }
private:
    // Store the logo image.
    QPixmap m_pixmap;
};

MainWindow::MainWindow()
    : mdiArea(new MdiArea),
    m_msg(new ShowMsg())
{
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QResource::registerResource("/home/system/WorkSpace/QtProjects/QtTestHowTo/QtMdiExample/forms/images.qrc");

    // connect(mdiArea, &QMdiArea::subWindowActivated,
    //         this, &MainWindow::updateMenus);


    createActions();
    createStatusBar();
    readSettings();

   //QPixmap m_pixm("/home/system/WorkSpace/QtProjects/QtTestHowTo/QtMdiExample/forms/images/logo.png");

    // QPixmap m_pixm("images/logo.png");

    // m_pixm = m_pixm.scaled(this->size(), Qt::IgnoreAspectRatio);
    // QPalette m_pal;
    // m_pal.setBrush(QPalette::Window, m_pixm);
    // this->setPalette(m_pal);

    setCentralWidget(mdiArea);
    setWindowIcon(QIcon(":images/PNG/49x49/stoq-49x49.png"));
    setWindowTitle(tr("AppAccountTools"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        writeSettings();
        event->accept();
    }
}

void MainWindow::configDatabase()
{
    //m_msg->ShowGuiMessage("info","Config Database","Config Database!!!","");
    CtrlConfig * m_ctrlcf = createMdiConfig();

    //Setting the window size to
    m_ctrlcf->setFixedSize(510, 420);

    //Show Window Maximized
    m_ctrlcf->showMaximized();

    m_ctrlcf->setAttribute(Qt::WA_DeleteOnClose);

    m_ctrlcf->show();

}



void MainWindow::about()
{
   QMessageBox::about(this, tr("About MDI"),
            tr("The <b>MDI</b> example demonstrates how to write multiple "
               "document interface applications using Qt."));
}



CtrlConfig *MainWindow::createMdiConfig()
{
    CtrlConfig * m_ctrl_cf = new CtrlConfig;
    mdiArea->addSubWindow(m_ctrl_cf);

    return m_ctrl_cf;
}

void MainWindow::createActions()
{
    //File Edit Window Help

    //---------
    //Menu File
    //---------
    QMenu *fileMenu = menuBar()->addMenu(tr("&Menu"));
    QToolBar *fileToolBar = addToolBar(tr("Menu"));

    const QIcon newIcon = QIcon::fromTheme("menu-new", QIcon(":/images/new.png"));
    // newAct = new QAction(newIcon, tr("&New"), this);
    // newAct->setShortcuts(QKeySequence::New);
    // newAct->setStatusTip(tr("Create a new file"));
    // connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    // fileMenu->addAction(newAct);
    // fileToolBar->addAction(newAct);

    fileMenu->addAction(tr("Switch layout direction"), this, &MainWindow::switchLayoutDirection);

    fileMenu->addSeparator();

//! [0]
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), qApp, &QApplication::quit);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    fileMenu->addAction(exitAct);
//! [0]



//Start

    //---------
    //Menu Tools
    //---------
    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    QToolBar *toolsToolBar = addToolBar(tr("Tools"));

    const QIcon configIcon = QIcon::fromTheme("config-icon", QIcon(":/images/PNG/128x128/advancedsettings.png"));
    configAct = new QAction(configIcon, tr("&Config DB"), this);
    configAct->setShortcuts(QKeySequence::New);
    configAct->setStatusTip(tr("Create a Database Connection."));
    connect(configAct, &QAction::triggered, this, &MainWindow::configDatabase);
    toolsMenu->addAction(configAct);
    toolsToolBar->addAction(configAct);

    // //! [qaction setup]
    // const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    // QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    // openAct->setShortcuts(QKeySequence::Open);
    // openAct->setStatusTip(tr("Open an existing file"));
    // connect(openAct, &QAction::triggered, this, &MainWindow::open);
    // fileMenu->addAction(openAct);
    // fileToolBar->addAction(openAct);
    // //! [qaction setup]

    // const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    // saveAct = new QAction(saveIcon, tr("&Save"), this);
    // saveAct->setShortcuts(QKeySequence::Save);
    // saveAct->setStatusTip(tr("Save the document to disk"));
    // connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    // fileToolBar->addAction(saveAct);

    // const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    // saveAsAct = new QAction(saveAsIcon, tr("Save &As..."), this);
    // saveAsAct->setShortcuts(QKeySequence::SaveAs);
    // saveAsAct->setStatusTip(tr("Save the document under a new name"));
    // connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);
    // fileMenu->addAction(saveAsAct);

    // fileMenu->addSeparator();

    // QMenu *recentMenu = fileMenu->addMenu(tr("Recent..."));
    // connect(recentMenu, &QMenu::aboutToShow, this, &MainWindow::updateRecentFileActions);
    // recentFileSubMenuAct = recentMenu->menuAction();

    // for (int i = 0; i < MaxRecentFiles; ++i) {
    //     recentFileActs[i] = recentMenu->addAction(QString(), this, &MainWindow::openRecentFile);
    //     recentFileActs[i]->setVisible(false);
    // }

    // recentFileSeparator = fileMenu->addSeparator();

    // setRecentFilesVisible(MainWindow::hasRecentFiles());

    // fileMenu->addAction(tr("Switch layout direction"), this, &MainWindow::switchLayoutDirection);

    // fileMenu->addSeparator();

    // //! [0]
    // const QIcon exitIcon = QIcon::fromTheme("application-exit");
    // QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), qApp, &QApplication::quit);
    // exitAct->setShortcuts(QKeySequence::Quit);
    // exitAct->setStatusTip(tr("Exit the application"));
    // fileMenu->addAction(exitAct);
    // //! [0]


//End


    //---------
    //Menu Edit
    //---------


    //---------
    //Menu Window
    //---------

    //---------
    //Menu Help
    //---------
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}


void MainWindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        QGuiApplication::setLayoutDirection(Qt::RightToLeft);
    else
        QGuiApplication::setLayoutDirection(Qt::LeftToRight);
}
