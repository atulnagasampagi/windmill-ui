#include "datamanager.h"

DataManager::DataManager(QObject *parent)
    : QObject{parent}
{
    qDebug()<<Q_FUNC_INFO;
    m_firebase = new FireBaseReader;
    m_timer = new QTimer;

    connect(m_firebase,&FireBaseReader::sendTurbinetoDataManger,this,&DataManager::checkParameters);
    m_firebase->retrieveDatafromFireBase();
    connect(m_timer,&QTimer::timeout,m_firebase,&FireBaseReader::retrieveDatafromFireBase);
    m_timer->start(6000);
}

DataManager::~DataManager()
{
    qDebug()<<Q_FUNC_INFO;
}

void DataManager::checkParameters(TurbineData *a_turbineData)
{
    qDebug()<<Q_FUNC_INFO;

    m_TurbineData=a_turbineData;

    QString l_country = a_turbineData->country();
    QString l_site = a_turbineData->powerplant();
    QString l_turbine = a_turbineData->turbineName();

    emit sendParameters(l_country,l_site,l_turbine);
}

void DataManager::checkstatus()
{
    qDebug()<<Q_FUNC_INFO;
    qDebug()<<m_TurbineData->powerplant()<<" not exists";
}

QList<TurbineData*> DataManager::getTurbineList(QString a_sitename)
{
    qDebug()<<Q_FUNC_INFO << "SIZE IN GETTURBINELIST : " << m_TurbineDatamap.size();

    QList<QString> siteNames = m_TurbineDatamap.keys();

    for(QString& site : siteNames){
        qDebug() << "Available Site : " << site;
    }
    if(m_TurbineDatamap.contains(a_sitename)){
        return m_TurbineDatamap.value(a_sitename);
    }
    else{
        qDebug()<<a_sitename<<" not present";
        return m_TurbineDatamap.value(a_sitename);
    }
}

void DataManager::callTurbineDataobj()
{
    qDebug()<<Q_FUNC_INFO;
    DataManager::addTurbine(m_TurbineData);
}

void DataManager::addTurbine(TurbineData *a_turbineData)
{
    qDebug()<<Q_FUNC_INFO;

    int i=0;
    bool isTurbineAvailable=false;

    if(m_TurbineDatamap.contains(a_turbineData->powerplant())){
        qDebug() << "Inside IF in addTurbine";
        QList<TurbineData*>& turbineList = m_TurbineDatamap[a_turbineData->powerplant()];
        for(TurbineData* turbineobj : turbineList){
            if(turbineobj->turbineName() == a_turbineData->turbineName()){
                isTurbineAvailable =true;
                qDebug()<<"deleted turbine = "<<turbineobj->turbineName();
                if(turbineobj)
                    delete turbineobj;
                turbineList.removeAt(i);
                qDebug()<<"added turbine = "<<a_turbineData->turbineName();
                turbineList.insert(i,a_turbineData);
                emit dataChanged();
            }
            i++;
        }

        if(!isTurbineAvailable){
            qDebug()<<"added turbine = "<<a_turbineData->turbineName();
            if(m_TurbineDatamap.contains(a_turbineData->powerplant())){
                QList<TurbineData*>& turbineList = m_TurbineDatamap[a_turbineData->powerplant()];
                turbineList.append(a_turbineData);
                return;
            }
        }
    }
    else{
        QList<TurbineData*> turbineList;
        turbineList.append(a_turbineData);
        m_TurbineDatamap.insert(a_turbineData->powerplant(),turbineList);
        qDebug() << "INSERT Turbine Site Name : " << a_turbineData->powerplant();
    }
}
