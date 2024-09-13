
#include "ConfigXml.h"
#include <QtSql/QSqlDatabase>



ConfigXml::ConfigXml():
    m_msg(new ShowMsg())
{
    system_path = "/home/system/WorkSpace/QtProjects/AppAccountTools/";
    folder_write = system_path + "settings/";

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

    QDir mDir(folder_write);
    m_msg->ShowMessage("Directory: " + mDir.dirName(), COLOR_GREEN, COLOR_PINK);

    QString file_path = mDir.filePath(fileName);
    m_msg->ShowMessage("Path: " + file_path, COLOR_GREEN, COLOR_PINK);

    mDir.setPath(folder_write);

    /**
     * Abre o arquivo para gravacao. Caso ele exista
     * gera um novo arquivo.
     */
    QFile file(file_path);

    m_msg->ShowMessage("GRAVANDO PARA PASTA: " + file_path, COLOR_CIANO, COLOR_PINK);


    if (!mDir.exists()) {
        m_msg->ShowMessage("ConfigXml::readFile(), ERRO PASTA NAO ENCONTRADA..." + folder_write, COLOR_CIANO, COLOR_RED);

        if (!mDir.mkdir(folder_write))
            m_msg->ShowMessage("ConfigXml::readFile(), ERRO, NAO FOI POSSIVEL CRIAR A PASTA: " + folder_write, COLOR_CIANO, COLOR_RED);
    }

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QString erro_msg = QString::fromUtf8("Não foi possível abrir arquivo\n")
                           + QString(qPrintable(fileName)) + ": "
                           + QString(qPrintable(file.errorString()));
        m_msg->ShowMessage(erro_msg + file_path, COLOR_CIANO, COLOR_RED);
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
            if (reader.name() == QString("ConfigConn")) {
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
                //qDebug() << "readBook Database: " << reader.name().toString();
                //qDebug() << "Valor de reader: " << reader.attributes().value("term").toQString();
                readChildContentElement(); //seta dados lido
            } else if (reader.name() == QString("User")) {//se for igual a entry, entra
                //qDebug() << "readBook User: " << reader.name().toString();
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
                QString m_Database = reader.readElementText();
                setDatabase(m_Database);
                qDebug() << "\nName.....:" << m_Database;
                //
                if (reader.isEndElement()) reader.readNext();
            } else if (reader.name() == QString("hostname")) {
                //
                QString m_HostName = reader.readElementText();
                setHostname(m_HostName);
                qDebug() << "Host.....:" << m_HostName;
                //
                if (reader.isEndElement()) reader.readNext();
            } else if (reader.name() == QString("port")) {
                //
                QString m_Port = reader.readElementText();
                setPort(m_Port);
                qDebug() << "Port.....:" << m_Port;
                //
                if (reader.isEndElement()) reader.readNext();
            } else if (reader.name() == QString("username")) {
                //
                QString m_UserName = reader.readElementText();
                setUsername(m_UserName);
                qDebug() << "User.....:" << m_UserName;
                //
                if (reader.isEndElement()) reader.readNext();
            } else if (reader.name() == QString("password")) {
                //
                QString m_Password = reader.readElementText();
                setPassword(m_Password);
                qDebug() << "Pass.....:" << m_Password;
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
    QDir mDir(folder_write);
    m_msg->ShowMessage("Directory: " + mDir.dirName(), COLOR_GREEN, COLOR_PINK);

    QString file_path = mDir.filePath(fileName);
    m_msg->ShowMessage("Path: " + file_path, COLOR_GREEN, COLOR_PINK);

    mDir.setPath(folder_write);

    /**
     * Abre o arquivo para gravacao. Caso ele exista
     * gera um novo arquivo.
     */
    QFile file(file_path);

    m_msg->ShowMessage("GRAVANDO PARA PASTA: " + file_path, COLOR_CIANO, COLOR_PINK);


    if (!mDir.exists()) {
        m_msg->ShowMessage("ConfigXml::writeFile(), ERRO PASTA NAO ENCONTRADA..." + folder_write, COLOR_CIANO, COLOR_RED);

        if (!mDir.mkdir(folder_write))
            m_msg->ShowMessage("ConfigXml::writeFile(), ERRO, NAO FOI POSSIVEL CRIAR A PASTA: " + folder_write, COLOR_CIANO, COLOR_RED);
    }

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
    xmlWriter.writeStartElement("ConfigConn");

    xmlWriter.writeStartElement("Database");
    
    xmlWriter.writeTextElement("name", getDatabase());
    xmlWriter.writeTextElement("hostname", getHostname());
    xmlWriter.writeTextElement("port", getPort());
    //
    xmlWriter.writeEndElement();
    //
    xmlWriter.writeStartElement("User");
   
    xmlWriter.writeTextElement("username", getUsername());
    xmlWriter.writeTextElement("password", getPassword());
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





