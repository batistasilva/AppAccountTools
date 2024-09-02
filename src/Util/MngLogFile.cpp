#include "MngLogFile.h"

MngLogFile::MngLogFile(QObject *parent)
    : QObject{parent}
{}

QString MngLogFile::getFile_name() const
{
    return file_name;
}

void MngLogFile::setFile_name(const QString &newFile_name)
{
    file_name = newFile_name;
}
