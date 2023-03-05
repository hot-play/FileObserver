#include "ChangeNotifier.h"
#include <iostream>

using namespace std;

void ChangeNotifier::logExistChanges(QString fileName,bool isExist) {
    if (isExist) {
        wcout << L"Файл: " << fileName.toStdWString() << L" - существует"<< endl;
    } else {
        wcout << L"Файл: " << fileName.toStdWString() << L" - не существует"<< endl;
    }
}
void ChangeNotifier::logSizeChanges(QString fileName,qint64 size) {
    wcout << L"Файл: " << fileName.toStdWString() << L" имеет размер: "<< size << L" байт"<< endl;
}
