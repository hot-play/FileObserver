#include "FileState.h"
#include <iostream>

FileState::FileState(QString path, qint64 size, bool existence) :
    filePath(path),
    fileSize(size),
    fileExistence(existence) {}

FileState::FileState(const QString &file) {
    // Для инициализации статистики используем путь к файлу
    QFileInfo fileInfo(file);
    // Необходимую статистику записываем
    filePath = fileInfo.absoluteFilePath();
    fileExistence = fileInfo.exists();
    fileSize = fileInfo.size();
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


