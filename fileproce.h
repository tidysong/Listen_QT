#ifndef FILEPROCE_H
#define FILEPROCE_H
#include <QFile>
#include <QDir>

class fileproce
{
public:
    fileproce();
private:
    QString p;
    QString pchange;

    void copyPath(QString p,QString pchange);      //复制粘贴文件
    void DeleteFileOrFolder(const QString &strPath);        //删除文件
    bool renameFile(QString oldnamePath, QString newname);       //修改文件名
    QStringList getlist(QString path);                          //本地文件列表
};

#endif // FILEPROCE_H
