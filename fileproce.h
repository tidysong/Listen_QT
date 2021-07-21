#ifndef FILEPROCE_H
#define FILEPROCE_H
#include <QFile>
#include <QDir>
#include <QFileInfo>

#include <qDebug>
class fileproce
{
public:
    fileproce();
    QString p;
    QString pchange;
    bool exist(QString filePath);
    void copyPath(QString p,QString pchange);      //复制粘贴文件
    void DeleteFileOrFolder(const QString &strPath);        //删除文件
    bool renameFile(QString oldnamePath, QString newname);       //修改文件名
    QStringList getlist(QString path);                          //本地文件列表
    void copy(QString reportpath,QString newreportpath);
};

#endif // FILEPROCE_H
