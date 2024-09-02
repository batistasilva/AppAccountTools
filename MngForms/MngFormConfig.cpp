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
    ui_cfg(new Ui::MngFormConfig(this))
{
    ui_cfg->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    //
    connect(ui_cfg->TButtonTestConn, SIGNAL(clicked()), this, SLOT(runTestConf()));
    connect(TButtonConfigDbSave, SIGNAL(clicked()), this, SLOT(runSaveConf()));
    connect(TButtonConfigDbExit, SIGNAL(clicked()), this, SLOT(runClose()));

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
    if (ConfigLEDbName->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), tr("Preencha o Campo (Nome do Banco)!!"));
        return false;
    }
    //
    if (ConfigLEDbHost->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), QString::fromUtf8("Preencha o Campo (Endereço do Banco)!!"));
        return false;
    }
    //
    if (ConfigLEDbPort->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), tr("Preencha o Campo (Porta do Banco)!!"));
        return false;
    }
    //
    if (ConfigLEDbUser->text().isEmpty()) {
        QMessageBox::warning(this, tr("Mensagem!"), QString::fromUtf8("Preencha o Campo (Usuário do Banco)!!"));
        return false;
    }
    //
    if (ConfigLEDbPass->text().isEmpty()) {
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
   // DBConn m_dbc;

    if (VlFillForm() == true) {
        /**
         * seta os dados para o objeto, para que
         * sejam salvos para o arquivo xml
         */
        m_dbc->setDatabase(ConfigLEDbName->text());
        m_dbc->setHostname(ConfigLEDbHost->text());
        m_dbc->setPort(ConfigLEDbPort->text());
        m_dbc->setUsername(ConfigLEDbUser->text());
        m_dbc->setPassword(ConfigLEDbPass->text());
        //
        dbconn->setDbconn(m_dbc);
        bool st_db = dbconn->writeFile("Xml/ConfigXml.xml");

        if (st_db) {
            ConfigLEDbTestResult->setStyleSheet(QString("QLineEdit { color: blue }"));
            ConfigLEDbTestResult->setText("Arquivo gerado com sucesso!!");
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
        m_dbc->setDatabase(ConfigLEDbName->text());
        m_dbc->setHostname(ConfigLEDbHost->text());
        m_dbc->setPort(ConfigLEDbPort->text());
        m_dbc->setUsername(ConfigLEDbUser->text());
        m_dbc->setPassword(ConfigLEDbPass->text());
        //
        dbconn->setDbconn(m_dbc);
        //
        if(dbconn->openConnInPGree()){
           ConfigLEDbTestResult->setStyleSheet(QString("QLineEdit { color: green }")); 
           ConfigLEDbTestResult->setText(QString::fromUtf8("Conexão feita com sucesso!!")); 
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

