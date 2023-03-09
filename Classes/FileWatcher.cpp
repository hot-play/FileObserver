#include "FileWatcher.h"
#include <QVector>
#include <Classes/FileState.h>
#include <Classes/ChangeNotifier.h>

FileWatcher::FileWatcher(const FileState &fileState) {
    watchedFiles.push_back(fileState);
}

void FileWatcher::addNewFile(const FileState &fileState) {
    watchedFiles.push_back(fileState);
}

void FileWatcher::changeFileState(int position, const FileState &fileState) {
    watchedFiles[position] = fileState;
}

bool FileWatcher::checkExistChangesByPosition(int position) {
    FileState savedState = watchedFiles[position];
    FileState currentState(savedState.getFilePath());
    // Для проверки изменения сравним имеющийся экземпляр с вновь созданным по тому же пути
    bool isChanged = (savedState.isExists() != currentState.isExists());
    // Если файл изменен, то перезапишем его в вектор наблюдения
    if (isChanged)
        changeFileState(position, currentState);
    return isChanged;
}

bool FileWatcher::checkSizeChangesByPosition(int position) {
    FileState savedState = watchedFiles[position];
    FileState currentState(savedState.getFilePath());
    // Для проверки изменения сравним имеющийся экземпляр с вновь созданным по тому же пути
    bool isChanged = (savedState.getFileSize() != currentState.getFileSize());
    // Если файл изменен, то перезапишем его в вектор наблюдения
    if (isChanged)
        changeFileState(position, currentState);
    return isChanged;
}

QVector<FileState> FileWatcher::checkExistChanges() {
    //
    QVector<FileState> changedStates;
    for (int i = 0; i < watchedFiles.count(); i++) {
        if (this->checkExistChangesByPosition(i)) {
            changedStates.push_back(watchedFiles[i]);
        }
    }
    return changedStates;
}

QVector<FileState> FileWatcher::checkSizeChanges() {
    // Изменения решил сохранять в отдельном экзепляре, статистика которого, при наличии, потом будет выводится
    QVector<FileState> changedStates;
    for (int i = 0; i < watchedFiles.count(); i++) {
        if (this->checkSizeChangesByPosition(i)) {
            changedStates.push_back(watchedFiles[i]);
        }
    }
    return changedStates;
}

void FileWatcher::runWatching() {

    // Подключим сигналы изменения в слоты логирования
    connect(this, &FileWatcher::existChanged, &ChangeNotifier::logExistChanges);
    connect(this, &FileWatcher::sizeChanged, &ChangeNotifier::logSizeChanges);

    // Прологируем начальные состояния файлов
    for (int i = 0 ; i < watchedFiles.count(); i++) {
        existChanged(watchedFiles[i].getFilePath(), watchedFiles[i].isExists());
        sizeChanged(watchedFiles[i].getFilePath(), watchedFiles[i].getFileSize());
    }

    // Запустим цикл, который постоянно будет отслеживать изменения и логировать их в случае имеющихся изменений
    while (1) {
        // Вектор файлов, у которых изменилось состояние
        QVector<FileState> existChanges = checkExistChanges();
        // Вектор файлов, у которых изменился размер
        QVector<FileState> sizeChanges = checkSizeChanges();
        // Проход по вектору и логирование изменений существования файла
        if (!existChanges.isEmpty()) {
            for (int i = 0 ; i < existChanges.count(); i++) {
                existChanged(existChanges[i].getFilePath(), existChanges[i].isExists());
            }
        }
        // Проход по вектору и логирование изменений размера файла
        if (!sizeChanges.isEmpty()) {
            for (int i = 0; i < sizeChanges.count(); i++) {
                sizeChanged(sizeChanges[i].getFilePath(), sizeChanges[i].getFileSize());
            }
        }
    }
}
