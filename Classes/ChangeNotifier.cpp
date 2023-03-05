#include "ChangeNotifier.h"

using namespace std;

void logExistChanges(QString fileName,bool isExist) {
    if (isExist) {
        cout << "Файл: " << fileName << " - существует"<< endl;
    }
    cout << "Файл: " << fileName << " - не существует"<< endl;
}
void logSizeChanges(QString fileName,qint64 size) {
    cout << "Файл: " << fileName << " имеет размер: "<< size<< " байт"<< endl;
}
