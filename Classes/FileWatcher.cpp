#include "FileWatcher.h"
#include <QVector>
#include <Classes/FileState.h>

void FileWatcher::addNewFile(const FileState &fileState) {
    watchedFiles.push_back(fileState);
}

void FileWatcher::changeFileState(int position, const FileState &fileState) {
    watchedFiles[position] = fileState;
}

bool FileWatcher::checkExistChangesByPosition(int position) {
    FileState savedState = watchedFiles.takeAt(position);
    FileState currentState = savedState.getFilePath();
    bool isChanged = (savedState.isExists() == currentState.isExists());
    if (isChanged)
        changeFileState(position, currentState);
    return isChanged;
}

bool FileWatcher::checkSizeChangesByPosition(int position) {
    FileState savedState = watchedFiles.takeAt(position);
    FileState currentState = savedState.getFilePath();
    bool isChanged = (savedState.getFileSize() == currentState.getFileSize());
    if (isChanged)
        changeFileState(position, currentState);
    return isChanged;
}

QVector<FileState> FileWatcher::checkExistChanges() {
    QVector<FileState> changedStates;
    for (int i=0; i<watchedFiles.count; i++) {
        if (this->checkExistChangesByPosition(i)) {
            changedStates.push_back(watchedFiles.takeAt(i));
        }
    }
    return changedStates;
}

QVector<FileState> FileWatcher::checkSizeChanges() {
    QVector<FileState> changedStates;
    for (int i = 0; i < watchedFiles.count; i++) {
        if (this->checkSizeChangesByPosition(i)) {
            changedStates.push_back(watchedFiles.takeAt(i));
        }
    }
    return changedStates;
}

void runWatching() {

    auto loopBody = [this]() {
            QVector<FileState> existChange = checkExistChanges();
            QVector<FileState> sizeChange = checkSizeChanges();
            if (!existChange.isEmpty()) {
                for (int i = 0 ; i < existChange.count; i++) {
                    existChanged(existChange[i].getFilePath(), existChange[i].isExists());
                }
            }
            if (!sizeChange.isEmpty()) {
                for (int i = 0; i < existChange.count; i++) {
                    existChanged(existChange[i].getFilePath(), existChange[i].getFileSize());
                }
            }
    };
    while () {
        loopBody();
    }
}
