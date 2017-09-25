#include "widget.h"
#include "fileUtils.h"
#include "ui_widget.h"
#include <QDebug>
#include <worker.h>
#include <QRegExp>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Worker *worker = new Worker();
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &Worker::deleteLater);
    connect(this, &Widget::calSameFiles, worker, &Worker::calSameFiles);
    connect(this, &Widget::calSameFiles1, worker, &Worker::calSameFiles1);
    connect(worker, &Worker::calSameFilesDone, this, &Widget::calSameFilesDone);
    workerThread.start();
}

Widget::~Widget()
{
    delete ui;
    workerThread.quit();
    workerThread.terminate();
}

void Widget::on_one_clicked()
{
    const QString resShowed = ui->info_show->toPlainText();
    QString files_path = ui->edit_files->text();
    QStringList file_path_list = files_path.split(QRegExp("\\s*;\\s*"), QString::SkipEmptyParts);
    if(file_path_list.size() == 0){
        const QString NoInputInfo = tr("请输入有效文件夹路径...");
        if(resShowed.contains(NoInputInfo)){
            ui->info_show->append(NoInputInfo);
        }else{
            ui->info_show->setText(NoInputInfo);
        }
        return;
    }

    QString base_dir_path = file_path_list.value(0).append('/');
    QDir dir(base_dir_path);
    if(!dir.exists()){
        const QString NotExistsInfo = tr("指定文件夹不存在...");
        if(resShowed.contains(NotExistsInfo)){
            ui->info_show->append(NotExistsInfo);
        }else{
            ui->info_show->setText(NotExistsInfo);
        }
        return;
    }

    ui->one->setEnabled(false);
    ui->info_show->clear();
    ui->info_show->setText(tr("正在计算，请稍等……"));
    emit calSameFiles(base_dir_path, resShowed);
}

void Widget::on_multi_clicked()
{
    const QString resShowed = ui->info_show->toPlainText();
    QString files_path = ui->edit_files->text();
    QStringList file_path_list = files_path.split(QRegExp("\\s*;\\s*"), QString::SkipEmptyParts);
    if(file_path_list.size() == 0){
        const QString NoInputInfo = tr("请输入有效文件夹路径...");
        if(resShowed.contains(NoInputInfo)){
            ui->info_show->append(NoInputInfo);
        }else{
            ui->info_show->setText(NoInputInfo);
        }
        return;
    }

    for(QString file_path : file_path_list){
        QDir dir(file_path);
        if(!dir.exists()){
            const QString NotExistsInfo = tr("指定文件夹不存在...") +  dir.absolutePath();
            if(resShowed.contains(NotExistsInfo)){
                ui->info_show->append(NotExistsInfo);
            }else{
                ui->info_show->setText(NotExistsInfo);
            }
            return;
        }
    }



    ui->multi->setEnabled(false);
    ui->info_show->clear();
    ui->info_show->setText(tr("正在计算，请稍等……"));

    emit calSameFiles1(file_path_list, resShowed);

}

void Widget::calSameFilesDone(QString resShow){
    ui->info_show->setText(resShow);
    ui->one->setEnabled(true);
    ui->multi->setEnabled(true);
}
