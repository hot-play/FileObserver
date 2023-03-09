#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <Classes/FileState.h>

#include <QVector>
#include <QTime>

class FileWatcher : public QObject
{
    // Для реализации сигнал-слотовой работы наследуемся от QObject
    Q_OBJECT
    // Вектор с статистикой файлов
    QVector<FileState> watchedFiles;
public:
    FileWatcher() = default;
    FileWatcher(const FileState &fileState);
    void addNewFile(const FileState &fileState);
    void changeFileState(int position, const FileState &fileState);

    // Функции просмотра изменений по состоянию и размеру
    bool checkExistChangesByPosition(int position);
    bool checkSizeChangesByPosition(int position);

    // Функции проверки всех файлов по состоянию и размеру
    QVector<FileState> checkExistChanges();
    QVector<FileState> checkSizeChanges();

    // Функция слежения за всеми файлами
    void runWatching();

signals:
    void existChanged(QString fileName, bool isExist);
    void sizeChanged(QString fileName, qint64 size);
};

#endif // FILEWATCHER_H
