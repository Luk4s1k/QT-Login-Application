#include "login.h"
#include "ui_login.h"



Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","mainbase");
    qDebug() << db.lastError();
    db.setHostName("156.17.224.165");
    db.setPort(8889);
    db.setDatabaseName("loginapp_db");
    db.setUserName("luka");
    db.setPassword("1234");

    if (!db.open()) {
        QMessageBox::critical(0,"Connection error","Could not connect to the database");
     }
    else {
        QMessageBox::information(0,"Connection","Connected");}
}

Login::~Login(){
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("mainbase");
    db.close();
}


void Login::on_signInButton_clicked()
{

    QSqlDatabase db = QSqlDatabase::database("mainbase");



     QString password = ui->passwordField->text();
     QString userName = ui->usernameField->text();


   if(userName==""){
        QMessageBox::critical(0, "No username provided","Username Field is empty");
        return;     }
    if(password==""){
     QMessageBox::critical(0, "No password provided","Password Field is empty");
     return;
    }




    QSqlQuery query(db);
    query.prepare("SELECT `Password` ,`Salt` FROM `users1` WHERE `Username` = :user_name");
    query.bindValue(":user_name", userName);
    bool logcheck = true;
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        logcheck = false;
        return;
    }
    if(logcheck == false){
        return;
    }
    query.first();
    QVariant databasePass = query.value(0);
    QString staticSalt = "AxYh9huk#Md$";
    QString saltedPass = staticSalt + password + query.value(1).toString();
    QByteArray encryptedInputPass = QCryptographicHash::hash(saltedPass.toUtf8(), QCryptographicHash::Sha256);
    if(encryptedInputPass.toHex() == databasePass){
        QMessageBox::information(0,"Login Sucessfull","Login Sucessfull");
        // next app window open here

    }else{
        QMessageBox::critical(0, "Invalid credentials","Login or Password does not match");
        return;
    }


}

void Login::on_checkBox_toggled(bool checked)
{

    if (checked == false){
        ui->passwordField->setEchoMode(QLineEdit::Password);
    } else{
        ui->passwordField->setEchoMode(QLineEdit::Normal);
    }

}

void Login::on_signUpButton_clicked()
{

RegWin = new Registration(this);
RegWin->setWindowTitle("Registration");
RegWin->show();

}
