#include "logincredentials.h"

LoginCredentials::LoginCredentials(QObject *parent)
    : QObject{parent}
{

}

LoginCredentials::~LoginCredentials()
{
    m_usernameToPasswordMap.clear();
}

bool LoginCredentials::addNewUser(QString a_userName, QString a_email, QString a_password, QString a_confirmPassword)
{
    if(a_userName == "" || a_email == "" || a_password == "" || a_confirmPassword == ""){
        emit registrationFailure("Invalid","Please Provide all data");
        return false;
    }else{
        if(m_usernameToPasswordMap.contains(a_userName)){
            emit registrationFailure("Invalid","Account already exists with this username");
            return false;
        }else{
            if(a_password != a_confirmPassword){
                emit registrationFailure("Failure","Password and Confirm password doesn't match");
                return false;
            }else{
                m_usernameToPasswordMap.insert(a_userName,a_password);
                emit registrationSuccess("Success","Registration Success now you can Login");
                emit sendRegistrationData(a_userName,a_email,a_password,a_confirmPassword);
                return true;
            }
        }
    }
}

bool LoginCredentials::verifyLoginCredentials(QString a_userName, QString a_password)
{
    qDebug() << Q_FUNC_INFO;

    if(a_userName == "" || a_password == ""){
        emit loginFailure("Empty Data","Please Enter Valid Data");
        // emit loginSucess("Success","You have now Logged in");
        return false;
    }else{
        if(m_usernameToPasswordMap.contains(a_userName)){
            if(a_password == m_usernameToPasswordMap.value(a_userName)){
                m_currentUser = a_userName;
                emit userNameChanged();
                emit loginSucess("Success","You have now Logged in");
                return true;
            }else{
                emit loginFailure("Retry","Incorrect Password");
                return false;
            }
        }else{
            emit loginFailure("Failure","Username Not Found, Please Register");
            return false;
        }
    }
    return false;
}

QString LoginCredentials::getUserName() const
{
    return m_currentUser;
}

void LoginCredentials::setUserName(QString a_userName)
{
    if(m_currentUser == a_userName){
        return;
    }
    m_currentUser = a_userName;
    emit userNameChanged();
}

void LoginCredentials::insertLoginData(QString a_username, QString a_password)
{
    m_usernameToPasswordMap.insert(a_username,a_password);
}
