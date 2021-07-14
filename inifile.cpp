#include "inifile.h"
Inifile::Inifile()
{
    configIni = new QSettings("cloud.ini", QSettings::IniFormat);
}
Inifile::~Inifile(){

    delete configIni;
}

void Inifile::Saveusername(QString username){
    configIni->setValue( "YY/username" ,username);
}
void Inifile::Savepassword(QString password){
    configIni->setValue( "YY/password" ,password);
}
void Inifile::Savelogintime(QString logintime){
    configIni->setValue( "YY/logintime" ,logintime);
}
void Inifile::Saveplaymode(QString playmode){
    configIni->setValue( "CC/playmode" ,playmode);
}
void Inifile::Saveother(QString other){
    configIni->setValue( "AA/on" ,other);
}
QString Inifile::Readusername(){
    return configIni->value("YY/username").toString();
}
QString Inifile::Readpassword(){
    return configIni->value("YY/password").toString();
}
QString Inifile::Readlogintime(){
    return configIni->value("YY/logintime").toString();
}
QString Inifile::Readplaymode(){
    return configIni->value("CC/playmode").toString();
}
QString Inifile::Readother(){
    return configIni->value("AA/on").toString();
}
