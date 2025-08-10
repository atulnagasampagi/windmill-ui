#ifndef LOGINCREDENTIALS_H
#define LOGINCREDENTIALS_H

#include <QObject>
#include <QMap>
#include <QDebug>

using USERNAME = QString;
using PASSWORD = QString;

class LoginCredentials : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString myUserName READ getUserName WRITE setUserName NOTIFY userNameChanged FINAL)
public:
    explicit LoginCredentials(QObject *parent = nullptr);
    ~LoginCredentials();


    bool addNewUser(QString a_userName, QString a_email, QString a_password, QString a_confirmPassword);
    bool verifyLoginCredentials(QString a_userName,QString a_password);
    QString getUserName() const;
    void setUserName(QString a_userName);

public slots:
    void insertLoginData(QString a_username,QString a_password);

signals:
    void loginSucess(QString,QString);
    void loginFailure(QString,QString);

    void registrationSuccess(QString,QString);
    void registrationFailure(QString,QString);
    void sendRegistrationData(QString,QString,QString,QString);
    void userNameChanged();

private:
    QString m_currentUser;
    QMap<USERNAME,PASSWORD> m_usernameToPasswordMap;
};

#endif // LOGINCREDENTIALS_H
