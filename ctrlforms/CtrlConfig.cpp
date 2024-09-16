/* 
 * File:   MngFormConfig.cpp
 * Author: batista
 * 
 * Created on 21 de Fevereiro de 2013, 09:06
 */

#include "CtrlConfig.h"

CtrlConfig::CtrlConfig(QWidget *parent): QDialog(parent),
    m_dao(new DBUtil()),
    m_cfx(new ConfigXml()),
    mfcg(new Ui_FormConfig)
{
    mfcg->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    //
    connect(mfcg->TButtonTestConn, SIGNAL(clicked()), this, SLOT(runTestConf()));
    connect(mfcg->TButtonConfigDbSave, SIGNAL(clicked()), this, SLOT(runSaveConf()));
    connect(mfcg->TButtonConfigDbExit, SIGNAL(clicked()), this, SLOT(runClose()));

}

CtrlConfig::~CtrlConfig() {
   runClose();
}

/**
 * Method to validate the form connection.
 * @return
 */
bool CtrlConfig::VlFillForm() {
    if (mfcg->ConfigLEDbName->text().isEmpty()) {
        QMessageBox::warning(this, tr("Message!"), tr("Enter the database name!"));
        return false;
    }
    //
    if (mfcg->ConfigLEDbHost->text().isEmpty()) {
        QMessageBox::warning(this, tr("Message!"), tr("Enter the database address!"));
        return false;
    }
    //
    if (mfcg->ConfigLEDbPort->text().isEmpty()) {
        QMessageBox::warning(this, tr("Message!"), tr("Enter the database port!"));
        return false;
    }
    //
    if (mfcg->ConfigLEDbUser->text().isEmpty()) {
        QMessageBox::warning(this, tr("Message!"), tr("Enter the database user!"));
        return false;
    }
    //
    if (mfcg->ConfigLEDbPass->text().isEmpty()) {
        QMessageBox::warning(this, tr("Message!"), tr("Enter the database password!"));
        return false;
    }
    //
    return true;
}

/**
 * Method to save database connection that works fine..
 */
void CtrlConfig::runSaveConf() {

    if (VlFillForm() == true) {
        /**
         * seta os dados para o objeto, para que
         * sejam salvos para o arquivo xml
         */
        m_cfx->setDatabase(mfcg->ConfigLEDbName->text());
        m_cfx->setHostname(mfcg->ConfigLEDbHost->text());
        m_cfx->setPort(mfcg->ConfigLEDbPort->text());
        m_cfx->setUsername(mfcg->ConfigLEDbUser->text());
        m_cfx->setPassword(mfcg->ConfigLEDbPass->text());
        //

        bool st_db = m_cfx->writeFile("ConfigXml.xml");

        if (st_db) {
            mfcg->ConfigLEDbTestResult->setStyleSheet(QString("QLineEdit { color: blue }"));
            mfcg->ConfigLEDbTestResult->setText(tr("File generated successfully!"));
        }
    }

}

/**
 * Method to test database connection.
 */
void CtrlConfig::runTestConf() {
    //
    if (VlFillForm() == true) {
        m_dao->setDatabase(mfcg->ConfigLEDbName->text());
        m_dao->setHostname(mfcg->ConfigLEDbHost->text());
        m_dao->setPort(mfcg->ConfigLEDbPort->text());
        m_dao->setUsername(mfcg->ConfigLEDbUser->text());
        m_dao->setPassword(mfcg->ConfigLEDbPass->text());
        //

        if(m_dao->runTestConnection()){
           mfcg->ConfigLEDbTestResult->setStyleSheet(QString("QLineEdit { color: green }"));
           mfcg->ConfigLEDbTestResult->setText(tr("Connection made successfully!"));
           mfcg->TButtonConfigDbSave->setEnabled(true);
        }else{
            mfcg->ConfigLEDbTestResult->setStyleSheet(QString("QLineEdit { color: red }"));
            mfcg->ConfigLEDbTestResult->setText(tr("Connection Error!"));
            mfcg->TButtonConfigDbSave->setEnabled(false);
        }
    }
    //
}

/**
 * Method to close subwindow.
 */
void CtrlConfig::runClose() {
   //Works for App, not for subwindow
   //qApp->quit();

   //Works for subwindow the right way
   qobject_cast<QMdiSubWindow*>(parent())->close();

   //Works for subwindow, but does not close the entire process
   //this->accept();

   //Works for subwindow, but does not close the entire process
   //this->close();
}

