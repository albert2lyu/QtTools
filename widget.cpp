#include "widget.h"
#include "fileUtils.h"
#include "ui_widget.h"
#include <QFileSystemModel>
#include <QDir>
#include <QTreeView>
#include <QDirModel>
#include <QVBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //    QStringList strList;
    //    strList << "a" << "b";
    //    QDirModel *model = new QDirModel(strList, QDir::Files, QDir::NoSort, this);
    //    QTreeView *tree = new QTreeView(this);
    //    tree->setModel(model);
    //    tree->setGeometry(10,10,500,500);

    //    QFileSystemModel *model = new QFileSystemModel;
    //    model->setRootPath(QDir::currentPath());
    //    QTreeView *tree = new QTreeView(this);
    //    tree->setModel(model);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_one_clicked()
{
    const QString resShowed = ui->info_show->toPlainText();
//    qDebug()<<resShowed << " " << resShowed.length();
    QString files_path = ui->edit_files->text();
    QStringList file_path_list = files_path.split(';', QString::SkipEmptyParts);
    if(file_path_list.size() == 0){
        const QString NoInputInfo = tr("请输入有效文件夹路径...");
        if(resShowed.contains(NoInputInfo)){
            ui->info_show->append(NoInputInfo);
        }else{
            ui->info_show->setText(NoInputInfo);
        }
        return;
    }

    QString resShow;
    QString resShow1;
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

    ui->info_show->clear();
    ui->info_show->setText(tr("正在计算，请稍等……"));
    QFileInfoList files = FileUtils::getAllFiles(dir);
    resShow += tr("普通文件数目：%1\n\n").arg(files.size());
    resShow1 += tr("普通文件数目：%1\n\n").arg(files.size());

    for(int i=0; i<files.size(); i++){
        QFileInfo f1 = files.at(i);
        QFileInfoList sameFileList;
        sameFileList.append(f1);
        for(int j=i+1; j<files.size(); j++){
            QFileInfo f2 = files.at(j);
            if(FileUtils::fileSame(f1, f2)){
                sameFileList.append(files.takeAt(j));
            }
        }
        if(sameFileList.size() > 1){
            for(int g=0; g<sameFileList.size(); g++){
                resShow += sameFileList.at(g).absoluteFilePath() + "\n";
                resShow1 += sameFileList.at(g).absoluteFilePath().mid(base_dir_path.length()) + "\n";
            }
            resShow += "\n";
            resShow1 += "\n";
        }
    }
    bool showRelativePathFlag = false;
    if(showRelativePathFlag){
        resShow = resShow1;
    }
    if(resShow == resShowed){
        resShow.append("计算完成!");
    }
    ui->info_show->setText(resShow);
}

void Widget::on_multi_clicked()
{
    QString files_path = "a:/b/c/d.txt";
    QString t = "a:/b/c/";
    qDebug()<<files_path.mid(t.length());
}
