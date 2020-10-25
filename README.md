# Login Application QT

Login application can be used in mostly every project written in QT. 

## Database connection:
It has to be connected to the database, I personally was using Remote Routing on the Rassberry Pi 
where my database is stored, but if you have your own host you can enter IP, port as well as login and password to
your database. I was using QMYSQL plugin, if you have problems installing the driver, just go through the instruction in
**Driver_Installation.txt** file in this repository because I personally spent a lot of time trying to find the right answer.
### Database structure:
| Username        | Password                 | Salt           |  Email          |
| -------------   |:-------------:           | :-------------:|-----:           |
| user            | 06454cb860514c5108b194   | plcjAttdWZLE   | user@email.com  |


## Encryption:
SHA-256 is used as hashing algorythm to store passwords safely in the database. Salts were added, static salt is a part of a program, 
you can change it in **registration.cpp** file. 
```C++
 QString staticSalt = "my-static-salt";
```
Dynamic salt is generated for each new user completing the registratin, and is stored in the database.

## Here enter your host info:
```C++
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","mainbase");
    db.setHostName("192.168.0.1"); // Host IP 
    db.setPort(0000); // Port
    db.setDatabaseName("myDatabase"); //Database name 
    db.setUserName("admin"); // Database username
    db.setPassword("admin"); //Database Password
```

## Login Window:
![alt text](https://github.com/Luk4s1k/Login_Application_QT/blob/master/loginWindow.png)

## Registration Window:
![alt text](https://github.com/Luk4s1k/Login_Application_QT/blob/master/registrtionWindow.png)

## Customization 

You can change the window style in **login.ui** file of **registration.ui file**. Encryption algorythm can be changed if you find SHA-256 not 
secure enought for your purposes. 
