#ifndef FILESTATE_H
#define FILESTATE_H


#include <QFileInfo>
#include <QString>

class FileState {
    QString filePath;
    qint64 fileSize;
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
