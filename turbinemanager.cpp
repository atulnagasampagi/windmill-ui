#include "turbinemanager.h"

TurbineManager::TurbineManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << Q_FUNC_INFO;
}

TurbineManager::~TurbineManager()
{
    qDebug() << Q_FUNC_INFO;
    foreach(TurbineInfo* turbine, m_turbineNameToTurbineObjMap.values()) {
        delete turbine;
    }
    m_turbineNameToTurbineObjMap.clear();
}

void TurbineManager::addNewTurbine(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer)
{
    TurbineInfo* l_turbineInfo = new TurbineInfo();
    l_turbineInfo->setCountry(a_countryName);
    l_turbineInfo->setSiteName(a_siteName);
    l_turbineInfo->setTurbineName(a_turbineName);
    l_turbineInfo->setManufacturer(a_manufacturer);

    if(!m_turbineNameToTurbineObjMap.contains(a_turbineName)){
        m_turbineNameToTurbineObjMap.insert(a_turbineName,l_turbineInfo);
    }else{
        qDebug() << "Turbine Already Exists";
    }
}

void TurbineManager::addTurbine(TurbineInfo *a_turbineInfo)
{

    static int tcount = 1;
    qDebug() << Q_FUNC_INFO << tcount;
    tcount++;

    if(!m_turbineNameToTurbineObjMap.contains(a_turbineInfo->turbineName())){
        m_turbineNameToTurbineObjMap.insert(a_turbineInfo->turbineName(),a_turbineInfo);

        emit addTurbineSuccess();
    }else{
        qDebug() << "Turbine Already Exists";
        emit addTurbineFailure();
    }
}

bool TurbineManager::checkTurbine(QString a_turbineName)
{
    qDebug()<<Q_FUNC_INFO;
    if(m_turbineNameToTurbineObjMap.contains(a_turbineName)){
        return true;
    }
    else{
        return false;
    }
}

QMap<TURBINENAME, TurbineInfo *> TurbineManager::getTurbineNameToTurbineObjMap() const
{
    return m_turbineNameToTurbineObjMap;
}
