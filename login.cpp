#include "login.h"
#include "ui_login.h"



Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
// make ssh connection HERE!
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","mainbase");
    qDebug() << db.lastError();
    db.setHostName("156.17.224.165"); //set host ip where db locates
    db.setPort(8889); // port which will be listened by server
    db.setDatabaseName("loginapp_db");
    db.setUserName("luka");
    db.setPassword("1234");

    if (!db.open()) {
        QMessageBox::critical(0,"Connection error","Could not connect to the database");
     }
    else { QMessageBox::information(0,"Connection","Connected");}
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


    //QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
     //encoded pass must be with static salt and dynamic salt stored in db
     // add dynamic salt in db
     //add dynamic  salt generator
     //QString encodedPass = encryption.getEncodedText(password);
     QByteArray message =  QByteArray::fromHex(password.toUtf8());
     QByteArray key = "key";
     QMessageAuthenticationCode encodePass(QCryptographicHash::Sha256);
           encodePass.setKey(key);
           encodePass.addData(message);

     QString encryptedPass(encodePass.result().toHex());



   if(userName==""){
        QMessageBox::critical(0, "No username provided","Username Field is empty");
        return;     }
    if(password==""){
     QMessageBox::critical(0, "No password provided","Password Field is empty");
     return;
    }




    QSqlQuery query(db);
    query.prepare("SELECT `Passwords` FROM `users1` WHERE `Username` = :user_name");
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
    QVariant v = query.value(0);
    if(encryptedPass == v.toString()){ //changed to encoded Pass
        QMessageBox::information(0,"Login Sucessfull","Login Sucessfull");
        // next app window open here

    }else{
        QMessageBox::critical(0, "Invalid credentials","Login or Password does not match");
        return;
    }


}





void Login::on_checkBox_toggled(bool checked)
{
//    int currentState = ui->checkBox->checkState();
    if (checked == false){
        ui->passwordField->setEchoMode(QLineEdit::Password);
    }else{
        ui->passwordField->setEchoMode(QLineEdit::Normal);
    }

}

void Login::on_signUpButton_clicked()
{

RegWin = new Registration(this);
RegWin->setWindowTitle("Registration");
RegWin->show();

}
