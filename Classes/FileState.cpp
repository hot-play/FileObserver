#include "FileState.h"

FileState::FileState(QString path, qint64 size, bool existence) :
    filePath(path),
    fileSize(size),
    fileExistence(existence) {}

FileState FileState::initByPath(const QString &file) {
    QFileInfo fileInfo(file);
    FileState newFileState;
    newFileState.filePath = fileInfo.absoluteFilePath();
    newFileState.fileExistence = fileInfo.exists();
    newFileState.fileSize = fileInfo.size();
    return newFileState;
}

void FileState::setExists(bool existence) {
    fileExistence = existence;
}

void FileState::setFilePath(QString path) {
    filePath = path;
}

void FileState::setFileSize(qint64 size) {
    fileSize = size;
}

bool FileState::isExists() {
    return fileExistence;
}

QString FileState::getFilePath() {
    return filePath;
}

qint64 FileState::getFileSize() {
    return fileSize;
}


