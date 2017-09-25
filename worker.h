#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QFileInfoList>

namespace Ui {
class Widget;
}

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:
    void calSameFilesDone(QString resShow);
public slots:
    void calSameFiles(QString base_dir_path, QString resShowed);
    void calSameFiles1(QStringList file_path_list, QString resShowed);
};

#endif // WORKER_H
