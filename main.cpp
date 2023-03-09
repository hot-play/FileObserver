#include <QCoreApplication>
#include <Classes/FileState.h>
#include <Classes/FileWatcher.h>
#include <QString>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    QCoreApplication a(argc, argv);
    // Создалим наблюдатель за файлами
    FileWatcher watcher;
    // Воспользуемся конструктором FileState и созданные экземпляры занесем в наблюдатель
    watcher.addNewFile(FileState("D:/test/test1.txt"));
    watcher.addNewFile(FileState("D:/test/test2.txt"));
    watcher.addNewFile(FileState("D:/test/test3.txt"));
    watcher.addNewFile(FileState("D:/test/test4.txt"));
    watcher.addNewFile(FileState("D:/test/test5.txt"));
    watcher.runWatching();
    return a.exec();
}
