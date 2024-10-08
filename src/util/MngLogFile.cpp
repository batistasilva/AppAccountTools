#include "MngLogFile.h"


MngLogFile::MngLogFile(QObject *parent)
    : QObject(parent),
    m_msg(new ShowMsg())
{
    system_path = "/home/system/WorkSpace/QtProjects/AppAccountTools/";
}

void MngLogFile::CreateLogFile(QString filename, QString message)
{
    QDateTime dt_time(QDateTime::currentDateTime());
    QString format = "dd-MM-HH:mm:ss";
    QString date_to_file  = dt_time.toString(format);

    //seta o nome do arquivo
    QString name_file = filename +"-"+ date_to_file + ".TXT";

    m_msg->ShowMessage("GRAVANDO LOG, PARA: " + name_file, COLOR_BLUE, COLOR_PINK);

    QString folder_write = system_path + "Logs/";
    QDir directory(folder_write);
    m_msg->ShowMessage("Directory: " + directory.dirName(), COLOR_GREEN, COLOR_PINK);

    QString file_path = directory.filePath(name_file);
    m_msg->ShowMessage("Path: " + file_path, COLOR_GREEN, COLOR_PINK);

    directory.setPath(folder_write);

    /**
     * Abre o arquivo para gravacao. Caso ele exista
     * gera um novo arquivo.
     */
    QFile file(file_path);

    m_msg->ShowMessage("GRAVANDO PARA PASTA: " + file_path, COLOR_CIANO, COLOR_PINK);


    if (!directory.exists()) {
        m_msg->ShowMessage("CreateLogFile(), ERRO PASTA NAO ENCONTRADA..." + folder_write, COLOR_CIANO, COLOR_RED);

        if (!directory.mkdir(folder_write))
            m_msg->ShowMessage("MngLogFile::CreateLogFile(), ERRO, NAO FOI POSSIVEL CRIAR A PASTA: " + folder_write, COLOR_CIANO, COLOR_RED);
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << message.toStdString().c_str() << "\n";
        file.close();
    } else {
        m_msg->ShowMessage("MngLogFile::CreateLogFile(), ERRO NA GRAVACAO DO ARQUIVO" + name_file, COLOR_CIANO, COLOR_RED);
    }
}


