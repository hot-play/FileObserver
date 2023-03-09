#ifndef FILESTATE_H
#define FILESTATE_H


#include <QFileInfo>
#include <QString>

class FileState {
    // Путь до файла, в конструкторах используется абсолютный путь
    QString filePath;
    // Размер файла в байтах
    qint64 fileSize;
    // Состояние файла: 1 - сщуествует, 0 - не существует
    bool fileExistence;
public:
    FileState() = default;
    FileState(const QString &file);
    FileState(QString path, qint64 size, bool existence);
    void setExists(bool existence);
    void setFilePath(QString path);
    void setFileSize(qint64 size);
    bool isExists();
    QString getFilePath();
    qint64 getFileSize();
};


#endif // FILESTATE_H
