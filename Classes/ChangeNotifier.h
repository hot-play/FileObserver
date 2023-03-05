#ifndef CHANGENOTIFIER_H
#define CHANGENOTIFIER_H

#include <QString>
#include <QObject>

class ChangeNotifier : public QObject
{
    // Для реализации сигнал-слотовой работы наследуемся от QObject
public:
    ChangeNotifier() = default;
public slots:
    // Функции статичны для возможности вызова их без создания экзепляра класса
    static void logExistChanges(QString fileName, bool isExist);
    static void logSizeChanges(QString fileName, qint64 size);
};

#endif // CHANGENOTIFIER_H
