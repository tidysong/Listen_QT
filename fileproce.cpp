#include "fileproce.h"

fileproce::fileproce()
{

}
void fileproce::copyPath(QString p, QString pchange){            //复制粘贴文件内容
    QDir dir(p);
    if (! dir.exists())
        return;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString pchange_path = pchange + QDir::separator() + d;
        dir.mkpath(pchange_path);
        copyPath(p+ QDir::separator() + d, pchange_path);//use recursion
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(p + QDir::separator() + f, pchange + QDir::separator() + f);
    }

}

void fileproce::DeleteFileOrFolder(const QString &strPath)//要删除的文件夹或文件的路径
{
    if (strPath.isEmpty() || !QDir().exists(strPath))//是否传入了空的路径||路径是否存在
        return;

    QFileInfo FileInfo(strPath);

    if (FileInfo.isFile())//如果是文件
        QFile::remove(strPath);
    else if (FileInfo.isDir())//如果是文件夹
    {
        QDir qDir(strPath);
        qDir.removeRecursively();
    }
}



bool fileproce::renameFile(QString oldnamePath, QString newnamePath){
        if (oldnamePath == newnamePath){
            return true;
        }
        if (!QFile::exists(oldnamePath)){
            return false;
        }
        QDir *createfile     = new QDir;
        bool exist = createfile->exists(newnamePath);
        if (exist){
            createfile->remove(newnamePath);
        }//end if

        if(!QFile::copy(oldnamePath, newnamePath))
        {
            return false;
        }

        createfile->remove(oldnamePath);
        return true;
}

QStringList fileproce::getlist(QString path){

    QDir dir(path);
    QStringList files = dir.entryList( QDir::Files|QDir::Readable, QDir::Name);
    //qDebug()<<files;

    return files;
}
