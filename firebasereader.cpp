#include "firebasereader.h"

FireBaseReader::FireBaseReader(QObject *parent)
    : QObject{parent}
{

    qDebug()<<Q_FUNC_INFO;

    timer1=new QElapsedTimer;
    timer2=new QElapsedTimer;
    timer3=new QElapsedTimer;
    timer4=new QElapsedTimer;
}

FireBaseReader::~FireBaseReader()
{
    qDebug()<<Q_FUNC_INFO;
}

void FireBaseReader::retrieveDatafromFireBase()
{
    qDebug()<<Q_FUNC_INFO;
    qDebug()<<"---------------------------------------------------";
    QUrl url("https://windmillproject-4a20b-default-rtdb.firebaseio.com/.json");

    timer1->start();
    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &FireBaseReader::networkReplyFromDatabase);
    manager->get(request);
}

void FireBaseReader::networkReplyFromDatabase(QNetworkReply* a_networkReply)
{
    qint64 connectionestablishment = timer1->elapsed();

    qDebug()<<Q_FUNC_INFO;
    if(a_networkReply->error()!=QNetworkReply::NoError) {
        qDebug() << "Error:" << a_networkReply->errorString();
        return;
    }

    timer2->start();
    QByteArray data = a_networkReply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    qint64 jsonParsingTime = timer2->elapsed();

    if(doc.isNull()){
        qDebug()<<"parsing error "<<a_networkReply->errorString();
        return;
    }
    qDebug()<<"dddddddd  --> "<<doc;

    timer4->start();
    QJsonObject  turbineObj=doc.object();
    for(auto countryKey:turbineObj.keys()){
        timer3->start();
        QJsonObject countryobj=turbineObj.value(countryKey).toObject();
        for(auto powerPlantKey:countryobj.keys()){
            QJsonObject powerPlantobj=countryobj.value(powerPlantKey).toObject();
            for(auto turbineKey:powerPlantobj.keys()){
                QJsonObject turbineData=powerPlantobj.value(turbineKey).toObject();
                m_turbineData=new TurbineData;
                m_turbineData->setTurbineName(turbineKey);
                m_turbineData->setTurbineID(turbineData.value("TurbineID").toString());
                m_turbineData->setWindSpeed((turbineData.value("WindSpeed").toString()).toDouble());
                m_turbineData->setWindDirection((turbineData.value("WindDirection").toString()).toDouble());
                m_turbineData->setPowerOutput((turbineData.value("SystemPowerGenerated").toString()).toDouble());
                m_turbineData->setTemperature((turbineData.value("AirTemperature").toString()).toDouble());
                m_turbineData->setPressure((turbineData.value("Pressure").toString()).toDouble());
                m_turbineData->setPitchAngle(turbineData.value("PitchAngle").toString().toDouble());
                m_turbineData->setBladeAngle(turbineData.value("BladeAngle").toString().toDouble());
                m_turbineData->setYawDirection(turbineData.value("YawDirection").toString().toDouble());

                m_turbineData->setCountry(countryKey);
                m_turbineData->setPowerplant(powerPlantKey);
                emit sendTurbinetoDataManger(m_turbineData);
                qint64 dataprocessingoneobject = timer3->elapsed();
                qDebug() << "Time taken for processing data one object:" << dataprocessingoneobject<< "ms";
            }
        }
    }
    qint64 dataprocessing = timer4->elapsed();
    a_networkReply->deleteLater();

    qDebug() << "Time taken for network request:" << connectionestablishment << "ms";
    qDebug() << "Time taken for parsing JSON:" << jsonParsingTime<< "ms";
    qDebug() << "Time taken for json processing data:" <<dataprocessing<< "ms";
}
