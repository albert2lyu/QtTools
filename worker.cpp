#include "worker.h"
#include "fileUtils.h"
#include <QThread>
#include <QDebug>

Worker::Worker(QObject *parent) : QObject(parent){}

void Worker::calSameFiles(QString base_dir_path, QString resShowed){
    QDir dir(base_dir_path);
    QString resShow;
    QString resShow1;
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
    emit calSameFilesDone(resShow);
}

void Worker::calSameFiles1(QStringList file_path_list, QString resShowed){
    QFileInfoList files;
    for(QString file_path : file_path_list){
        QDir dir(file_path);
        files.append(FileUtils::getAllFiles(dir));
    }


    QString resShow;
    resShow = tr("普通文件数目：%1\n\n").arg(files.size());

    for(int i=0; i<files.length(); i++){
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
            }
            resShow += "\n";
        }
    }

    if(resShow == resShowed){
        resShow = tr("计算完成! ") + resShow;
    }
    emit calSameFilesDone(resShow);
}
