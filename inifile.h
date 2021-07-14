#ifndef INIFILE_H
#define INIFILE_H
#include <QSettings>

class Inifile
{
public:
    Inifile();
    ~Inifile();
    void Saveusername(QString username);
    void Savepassword(QString password);
    void Savelogintime(QString logintime);
    void Saveplaymode(QString playmode);
    void Saveother(QString other);
    QString Readusername();
    QString Readpassword();
    QString Readlogintime();
    QString Readplaymode();
    QString Readother();
private:
    QSettings *configIni;
};

#endif // INIFILE_H
