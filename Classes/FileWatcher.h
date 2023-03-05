#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <Classes/FileState.h>
#include <QVector>
#include <QTime>

class FileWatcher : public QObject
{
    QVector<FileState> watchedFiles;
public:
    FileWatcher() = default;
    FileWatcher(const FileState &fileState);
    void addNewFile(const FileState &fileState);
    void changeFileState(int position, const FileState &fileState);
    bool checkExistChangesByPosition(int position);
    bool checkSizeChangesByPosition(int position);
    QVector<FileState> checkExistChanges();
    QVector<FileState> checkSizeChanges();
    void runWatching();
signals:
    void existChanged(QString fileName, bool isExist);
    void sizeChanged(QString fileName, qint64 size);
};

#endif // FILEWATCHER_H
