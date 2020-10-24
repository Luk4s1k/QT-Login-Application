#ifndef LOGIN_H
#define LOGIN_H

#include <QMessageAuthenticationCode>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMainWindow>
#include <QCryptographicHash>
#include "registration.h"


namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    
private slots:
    void on_signUpButton_clicked();
    void on_checkBox_toggled(bool checked);
    void on_signInButton_clicked();

private:
    Ui::Login *ui;
    Registration *RegWin;


};

#endif // LOGIN_H
