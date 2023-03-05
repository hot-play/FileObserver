#include <QCoreApplication>
#include <Classes/FileState.h>
#include <Classes/FileWatcher.h>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString path = "D:\test.txt";
    FileState file1(path,0,1);
    FileWatcher watch1(file1);
    watch1.runWatching();
    return a.exec();
}
