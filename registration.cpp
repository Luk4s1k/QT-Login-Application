#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_signUpButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("mainbase");

    QString username = ui->usernameField->text();
    QString password = ui->passwordField->text();
    QString email = ui->emailField->text();
 // add dynamic salt addition here
     QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
     QString encodedPass = encryption.getEncodedText(password);

    QVariant v,a;
    QSqlQuery query(db);

    /*-----------------    Check for empty Fields     --------------*/

    if(username==""){
        QMessageBox::critical(0,"No Username", "Please Enter the username");
        return;
    }
    if(password==""){
        QMessageBox::critical(0,"No Password", "Please Enter the password");
        return;
    }
    if(email==""){
        QMessageBox::critical(0,"No email", "Please Enter the email");
      return;
    }

/*-------------------    Check For Username in Database   ---------------------------------------------------*/

    query.prepare(QString("SELECT `Username` FROM `users` WHERE `Username` =  :user_name"));
    query.bindValue(":user_name" , username);

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return;
     }

    query.first();
    v = query.value(0);
    if (v.toString()!=""){
        QMessageBox::critical(0,"Error","The username " + v.toString()  + " is already used");
        return;
    }
    /*------------------------    Check For Email in Database   ---------------------------------------------*/

    query.prepare(QString("SELECT `Email` FROM `users`  WHERE `Email` = :email"));
    query.bindValue(":email", email);
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return;
    }
    query.first();
    v = query.value(0);
    a = query.value(1);
    if(v.toString()!=""){
        QMessageBox::critical(0,"Error","The email " + v.toString()  + " is already used" + a.toString());
        return;
    }




        //-----------------------------------------
        query.prepare(" INSERT INTO `users` VALUES (?, ?, ?)");
        // add dynamic salt storing here
        query.bindValue(0, username);
        query.bindValue(1, encodedPass);
        query.bindValue(2, email);

        if (!query.exec()) {
            qDebug() << query.lastError().text();
            QMessageBox::critical(0,"Error","Due to an error your registration could not be completed");
            return;
        }else{
            QMessageBox::information(0,"Registration sucessfull","Your registration has been sucessfull");
        }


}

void Registration::on_cancelButton_clicked()
{
    close();
}

