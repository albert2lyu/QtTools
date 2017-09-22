#ifndef FILEUTILS_H
#define FILEUTILS_H
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>

class FileUtils
{
public:
    FileUtils();
    //递归返回目录下所有文件（不包括快捷方式）
    static QFileInfoList getAllFiles(QDir dir);
    //比较文件内容是否相等
    static bool fileSame(QFileInfo info1, QFileInfo info2);

};

#endif // FILEUTILS_H
