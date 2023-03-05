#include <QCoreApplication>
#include <Classes/FileState.h>
#include <Classes/FileWatcher.h>
#include <QString>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    QCoreApplication a(argc, argv);
    FileWatcher watcher;
    watcher.addNewFile(FileState("D:/test1.txt"));
    watcher.addNewFile(FileState("D:/test2.txt"));
    watcher.addNewFile(FileState("D:/test3.txt"));
    watcher.addNewFile(FileState("D:/test4.txt"));
    watcher.addNewFile(FileState("D:/test5.txt"));
    watcher.runWatching();
    return a.exec();
}
