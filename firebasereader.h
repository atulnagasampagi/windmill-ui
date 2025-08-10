#ifndef FIREBASEREADER_H
#define FIREBASEREADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <turbinedata.h>
#include <QElapsedTimer>

class FireBaseReader : public QObject
{
    Q_OBJECT
public:
    explicit FireBaseReader(QObject *parent = nullptr);
    ~FireBaseReader();

public slots:
    void retrieveDatafromFireBase();
    void networkReplyFromDatabase(QNetworkReply *a_networkReply);
signals:

    void sendTurbinetoDataManger(TurbineData*);

private:
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_networkReply;

    TurbineData *m_turbineData;
    QElapsedTimer *timer1,*timer2,*timer3,*timer4;
};

#endif // FIREBASEREADER_H
