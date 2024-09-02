/*
 * File:   ConfigXml.cpp
 * Author: batista
 * 
 * Created on 20 de Fevereiro de 2013, 08:52
 */

#include "ConfigXml.h"
#include <QtSql/QSqlDatabase>



ConfigXml::ConfigXml(QObject *parent): QObject(parent),
    m_dbconn(new DBConn())
{
   qDebug() << "drivers: "<< QSqlDatabase::drivers();
}

ConfigXml::~ConfigXml() {
}

/**
 * Metodo responsavel por ler arquivo de configuração para 
 * a conexao com o banco de dados.
 * @param fileName
 * @return true or false
 */
bool ConfigXml::readFile(const QString& fileName) {
    //Ler arquivo de configuração setado
    qDebug() << "My Real File..." << fileName;

    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {

        qDebug() << "Erro: não foi possível abrir arquivo" << qPrintable(fileName)
                << ": " << qPrintable(file.errorString());
        QString erro_msg = QString::fromUtf8("Não foi possível abrir arquivo\n") + QString(qPrintable(fileName)) + ": " + QString(qPrintable(file.errorString()));
        QMessageBox::information(0, "Erro!", erro_msg);
 
        writeFile(fileName);
 
        return false;
    }

    reader.setDevice(&file);

    reader.readNext();

    while (!reader.atEnd()) {
        //
        if (reader.isStartElement()) {
            //
            if (reader.name() == QString("ConfigXml")) {
                readMainContentElement();
            } else {
                reader.raiseError(QObject::tr("Not a configconn file"));
            }
            //
        } else {
            reader.readNext();
        }
    }

    file.close();
    if (reader.hasError()) {
        qDebug() << "Erro: percorrendo arquivo XML" << qPrintable(fileName)
                << ": " << qPrintable(reader.errorString());

        QMessageBox::information(0, "Erro!", "Percorrendo arquivo XML\n" + QString(qPrintable(fileName)) +
                ": " + QString(qPrintable(reader.errorString())));

        return false;
    } else if (file.error() != QFile::NoError) {
        qDebug() << "Erro: não foi possível ler o arquivo" << qPrintable(fileName)
                << ": " << qPrintable(file.errorString());

        QMessageBox::information(0, "Erro!", QString::fromUtf8("Não foi possível ler o arquivo\n") + QString(qPrintable(fileName)) +
                ": " + QString(qPrintable(file.errorString())));
        
       
        return false;
    }
    return true;
}

/**
 * Metodo responsavel por ler o ELEMENT principal
 * do arquivo XML
 */
void ConfigXml::readMainContentElement() {
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {//se for o ultimo
            reader.readNext(); //ler o proximo
            break; //e finaliza
        }

        if (reader.isStartElement()) {//ser for inicio de elemento
            qDebug() << "Inicio Element em readBook Name: " << reader.name().toString();
            if (reader.name() == QString("Database")) {//se for igual a entry, entra
                qDebug() << "readBook Database: " << reader.name().toString();
                //qDebug() << "Valor de reader: " << reader.attributes().value("term").toQString();
                readChildContentElement(); //seta dados lido
            } else if (reader.name() == QString("User")) {//se for igual a entry, entra
                qDebug() << "readBook User: " << reader.name().toString();
                //qDebug() << "Valor de reader: " << reader.attributes().value("term").toQString();
                readChildContentElement(); //seta dados lido
            } else {
                //skipUnknownElement();
            }
        } else {//ser for inicio vai para o proximo
            reader.readNext();
        }
    }
}

/**
 * Metodo responsavel por ler os ELEMENTS CHILD 
 * do arquivo XML
 */
void ConfigXml::readChildContentElement() {

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {

            if (reader.name() == QString("name")) {
                //
                m_dbconn->setDatabase(reader.readElementText());
                qDebug() << "\nName.....:" << m_dbconn->getDatabase();
                //
                if (reader.isEndElement()) reader.readNext();
            } else if (reader.name() == QString("hostname")) {
                //
                m_dbconn->setHostname(reader.readElementText());
                qDebug() << "Host.....:" << m_dbconn->getHostname();
                //
                if (reader.isEndElement()) reader.readNext();
            } else if (reader.name() == QString("port")) {
                //
                m_dbconn->setPort(reader.readElementText());
                qDebug() << "Port.....:" << m_dbconn->getPort();
                //
                if (reader.isEndElement()) reader.readNext();
            } else if (reader.name() == QString("username")) {
                //
                m_dbconn->setUsername(reader.readElementText());
                qDebug() << "User.....:" << m_dbconn->getUsername();
                //
                if (reader.isEndElement()) reader.readNext();
            } else if (reader.name() == QString("password")) {
                //
                m_dbconn->setPassword(reader.readElementText());
                qDebug() << "Pass.....:" << m_dbconn->getPassword();
                //
                if (reader.isEndElement()) reader.readNext();
            } else {
                //skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

/**
 * Metodo responsavel por gravar o arquivo XML
 * para os dados de configuração de conexão com
 * a base de dados.
 * @param fileName
 * @return true=sucesso, false=erro de gravação
 */
bool ConfigXml::writeFile(const QString& fileName) {
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(0, "Erro!", QString::fromUtf8("Não foi possível gravar o arquivo\n") + QString(qPrintable(fileName)) +
                " : Erro..: " + QString(qPrintable(file.errorString())));
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    //
    //
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("ConfigXml");

    xmlWriter.writeStartElement("Database");
    
    xmlWriter.writeTextElement("name", m_dbconn->getDatabase());
    xmlWriter.writeTextElement("hostname", m_dbconn->getHostname());
    xmlWriter.writeTextElement("port", m_dbconn->getPort());
    //
    xmlWriter.writeEndElement();
    //
    xmlWriter.writeStartElement("User");
   
    xmlWriter.writeTextElement("username", m_dbconn->getUsername());
    xmlWriter.writeTextElement("password", m_dbconn->getPassword());
    //
    //
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    //
    file.close();
    if (file.error()) {
        QMessageBox::information(0, "Erro!", "Não foi possível gravar o arquivo\n" + QString(qPrintable(fileName)) +
                ": " + QString(qPrintable(file.errorString())));
        return false;
    }
    return true;
}



