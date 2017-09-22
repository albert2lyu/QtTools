#include "fileUtils.h"
#include <QFile>
#include <QDataStream>

FileUtils::FileUtils(){}
QFileInfoList FileUtils::getAllFiles(QDir dir){
    QFileInfoList dirList_this = dir.entryInfoList(QDir::AllDirs | QDir::NoSymLinks | QDir::Hidden | QDir::NoDotAndDotDot);
    QFileInfoList fileList_this = dir.entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::Hidden);
    if(dirList_this.size() == 0){
        return fileList_this;
    }else{
        QFileInfoList res;
        res.append(fileList_this);
        for(int i=0; i<dirList_this.size(); i++){
            QFileInfoList fileList_sub = getAllFiles(QDir(dirList_this.at(i).absoluteFilePath()));
            res.append(fileList_sub);
        }
        return res;
    }
}

bool FileUtils::fileSame(QFileInfo info1, QFileInfo info2){
    if(info1.size() != info2.size()){
        return false;
    }else{
        QFile f1(info1.absoluteFilePath());
        QFile f2(info2.absoluteFilePath());
        f1.open(QIODevice::ReadOnly);
        f2.open(QIODevice::ReadOnly);
        QDataStream out1(&f1);
        QDataStream out2(&f2);

        int len1 = -1, len2 = -1;
        int cacheLen = 1024;
        char *c1 = new char[cacheLen];
        char *c2 = new char[cacheLen];
        bool res = true;
        while(len1 != 0){
            len1 = out1.readRawData(c1, cacheLen);
            len2 = out2.readRawData(c2, cacheLen);
            if(len1 != len2){
                res = false;
                break;
            }else{
                for(int i=0; i<len1; i++){
                    if(*(c1+i) != *(c2+i)){
                        res = false;
                        break;
                    }
                }
                if(!res){
                    break;
                }
            }
        } //while end
        delete c1;
        delete c2;
        return res;
    }//else end
}//fileSame end
