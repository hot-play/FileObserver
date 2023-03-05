#ifndef CHANGENOTIFIER_H
#define CHANGENOTIFIER_H

#include <QString>

class ChangeNotifier : public QObject
{
public:
    ChangeNotifier() = default;
public slots:
    void logExistChanges(QString fileName, bool isExist);
    void logSizeChanges(QString fileName, qint64 size);
};

#endif // CHANGENOTIFIER_H
