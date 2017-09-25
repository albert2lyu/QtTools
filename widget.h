#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <QFileInfoList>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_one_clicked();

    void on_multi_clicked();

    void calSameFilesDone(QString resShow);

signals:
    void calSameFiles(QString base_dir_path, QString resShowed);
    void calSameFiles1(QStringList file_path_list, QString resShowed);

private:
    Ui::Widget *ui;
    QThread workerThread;
};

#endif // WIDGET_H
