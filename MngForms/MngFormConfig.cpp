/* 
 * File:   MngFormConfig.cpp
 * Author: batista
 * 
 * Created on 21 de Fevereiro de 2013, 09:06
 */

#include "MngFormConfig.h"

MngFormConfig::MngFormConfig(QWidget *parent): QDialog(parent),
    m_dao(new DBUtil()),
    m_cfx(new ConfigXml()),
    m_dbc(new DBConn()),
    mfcg(new Ui_FormConfig)
{
    mfcg->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    //
    connect(mfcg->TButtonTestConn, SIGNAL(clicked()), this, SLOT(runTestConf()));
    connect(mfcg->TButtonConfigDbSave, SIGNAL(clicked()), this, SLOT(runSaveConf()));
    connect(mfcg->TButtonConfigDbExit, SIGNAL(clicked()), this, SLOT(runClose()));

}

MngFormConfig::~MngFormConfig() {
  //  runClose();
}

/**
 * Metodo responsavel por validar 
 * preenchimento do formulário.
 * @return 
 */
bool MngFormConfig::VlFillForm() {
    if (mfcg->ConfigLEDbName->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), tr("Preencha o Campo (Nome do Banco)!!"));
        return false;
    }
    //
    if (mfcg->ConfigLEDbHost->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), QString::fromUtf8("Preencha o Campo (Endereço do Banco)!!"));
        return false;
    }
    //
    if (mfcg->ConfigLEDbPort->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), tr("Preencha o Campo (Porta do Banco)!!"));
        return false;
    }
    //
    if (mfcg->ConfigLEDbUser->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), QString::fromUtf8("Preencha o Campo (Usuário do Banco)!!"));
        return false;
    }
    //
    if (mfcg->ConfigLEDbPass->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), tr("Preencha o Campo (Senha do Banco)!!"));
        return false;
    }
    //
    return true;
}

/**
 * Metodo responsavel por chamar metodo
 * de gravação dos dados do formulário.
 */
void MngFormConfig::runSaveConf() {  

    if (VlFillForm() == true) {
        /**
         * seta os dados para o objeto, para que
         * sejam salvos para o arquivo xml
         */
        m_dbc->setDatabase(mfcg->ConfigLEDbName->text());
        m_dbc->setHostname(mfcg->ConfigLEDbHost->text());
        m_dbc->setPort(mfcg->ConfigLEDbPort->text());
        m_dbc->setUsername(mfcg->ConfigLEDbUser->text());
        m_dbc->setPassword(mfcg->ConfigLEDbPass->text());
        //
        m_dao->setDbc(m_dbc);

        bool st_db = m_cfx->writeFile("Xml/ConfigXml.xml");

        if (st_db) {
            mfcg->ConfigLEDbTestResult->setStyleSheet(QString("QLineEdit { color: blue }"));
            mfcg->ConfigLEDbTestResult->setText("Arquivo gerado com sucesso!!");
        }
    }

}

/**
 * Metodo responsavel por chamar metodo
 * de teste para os dados informados
 * no formulário.
 */
void MngFormConfig::runTestConf() {
    //
    if (VlFillForm() == true) {
        m_dbc->setDatabase(mfcg->ConfigLEDbName->text());
        m_dbc->setHostname(mfcg->ConfigLEDbHost->text());
        m_dbc->setPort(mfcg->ConfigLEDbPort->text());
        m_dbc->setUsername(mfcg->ConfigLEDbUser->text());
        m_dbc->setPassword(mfcg->ConfigLEDbPass->text());
        //
        m_dao->setDbc(m_dbc);
        //
        if(m_dao->openConnInPGree()){
           mfcg->ConfigLEDbTestResult->setStyleSheet(QString("QLineEdit { color: green }"));
           mfcg->ConfigLEDbTestResult->setText(QString::fromUtf8("Conexão feita com sucesso!!"));
        }
    }
    //
}

/**
 * Metodo responsavel por fechar janela
 * de formulário aberta
 */
void MngFormConfig::runClose() {
       // qApp->quit();
//   qobject_cast<QMdiSubWindow*>(parent())->close();
    //this->accept();
   //this->close();
}

