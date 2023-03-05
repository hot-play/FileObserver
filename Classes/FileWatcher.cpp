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
    bool isChanged = (savedState.isExists() != currentState.isExists());
    if (isChanged)
        changeFileState(position, currentState);
    return isChanged;
}

bool FileWatcher::checkSizeChangesByPosition(int position) {
    FileState savedState = watchedFiles[position];
    FileState currentState(savedState.getFilePath());
    bool isChanged = (savedState.getFileSize() != currentState.getFileSize());
    if (isChanged)
        changeFileState(position, currentState);
    return isChanged;
}

QVector<FileState> FileWatcher::checkExistChanges() {
    QVector<FileState> changedStates;
    for (int i = 0; i < watchedFiles.count(); i++) {
        if (this->checkExistChangesByPosition(i)) {
            changedStates.push_back(watchedFiles[i]);
        }
    }
    return changedStates;
}

QVector<FileState> FileWatcher::checkSizeChanges() {
    QVector<FileState> changedStates;
    for (int i = 0; i < watchedFiles.count(); i++) {
        if (this->checkSizeChangesByPosition(i)) {
            changedStates.push_back(watchedFiles[i]);
        }
    }
    return changedStates;
}

void FileWatcher::runWatching() {
    connect(this, &FileWatcher::existChanged, &ChangeNotifier::logExistChanges);
    connect(this, &FileWatcher::sizeChanged, &ChangeNotifier::logSizeChanges);
    for (int i = 0 ; i < watchedFiles.count(); i++) {
        existChanged(watchedFiles[i].getFilePath(), watchedFiles[i].isExists());
        sizeChanged(watchedFiles[i].getFilePath(), watchedFiles[i].getFileSize());
    }
    while (1) {
        QVector<FileState> existChanges = checkExistChanges();
        QVector<FileState> sizeChanges = checkSizeChanges();
        if (!existChanges.isEmpty()) {
            for (int i = 0 ; i < existChanges.count(); i++) {
                existChanged(existChanges[i].getFilePath(), existChanges[i].isExists());
            }
        }
        if (!sizeChanges.isEmpty()) {
            for (int i = 0; i < sizeChanges.count(); i++) {
                sizeChanged(sizeChanges[i].getFilePath(), sizeChanges[i].getFileSize());
            }
        }
    }
}
