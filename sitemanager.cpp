#include "sitemanager.h"

SiteManager::SiteManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << Q_FUNC_INFO;
}

SiteManager::~SiteManager()
{
    qDebug() << Q_FUNC_INFO;
    foreach(TurbineManager* manager, m_siteToTurbineMap.values()) {
        delete manager;
    }
    m_siteToTurbineMap.clear();

    foreach(SiteInfo* site, m_siteToSiteObjMap.values()) {
        delete site;
    }
    m_siteToSiteObjMap.clear();
}

void SiteManager::addSite(QString a_siteName,SiteInfo *a_siteInfo)
{
    qDebug()<<Q_FUNC_INFO;    m_siteToSiteObjMap.insert(a_siteName,a_siteInfo);
    SiteManager::addTurbineManager(a_siteName, new TurbineManager);
}

void SiteManager::disp()
{

}

void SiteManager::removeSite(QString a_siteName)
{
    if(m_siteToSiteObjMap.contains(a_siteName)){
        delete m_siteToSiteObjMap.value(a_siteName);
        m_siteToSiteObjMap.remove(a_siteName);
        if(m_siteToTurbineMap.contains(a_siteName)){
            delete m_siteToTurbineMap.value(a_siteName);
            m_siteToTurbineMap.remove(a_siteName);
            emit dataUpdated();
            emit removeSiteSuccess("Success","Site Removed Successfully");
        }else{
            emit removeSiteFailure("Failure","Site Not Removed");
        }
    }else{
        emit removeSiteFailure("Failure","Site Not Removed");
    }
}

void SiteManager::addNewSite(QString a_countryName, QString a_state, QString a_site, QString a_location, QString a_phno)
{
    SiteInfo* l_siteInfo = new SiteInfo();
    l_siteInfo->setCountry(a_countryName);
    l_siteInfo->setState(a_state);
    l_siteInfo->setSiteName(a_site);
    l_siteInfo->setLocation(a_location);
    l_siteInfo->setPhno(a_phno);

    if(!m_siteToSiteObjMap.contains(a_site)){
        m_siteToSiteObjMap.insert(a_site,l_siteInfo);
        SiteManager::addTurbineManager(a_site, new TurbineManager);
        emit dataUpdated();
        emit addSiteSuccess("Success","Site Added Successfully");
    }else{
        qDebug() << "Site Already Present";
        emit addSiteFailure("Failure","Site Already Exists");
    }
}

void SiteManager::addNewTurbineInSiteManager(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer)
{
    TurbineManager* l_turbineManager = nullptr;
    if(m_siteToTurbineMap.contains(a_siteName)){
        l_turbineManager = m_siteToTurbineMap.value(a_siteName);
        l_turbineManager->addNewTurbine(a_countryName,a_siteName,a_turbineName,a_manufacturer);
    }
}

void SiteManager::addTurbineManager(QString a_siteName, TurbineManager *a_turbineManager)
{
    m_siteToTurbineMap.insert(a_siteName,a_turbineManager);
}

void SiteManager::addTurbineinTurbineManager(TurbineInfo* a_turbineInfo)
{
    if(m_siteToTurbineMap.contains(a_turbineInfo->siteName())){
        TurbineManager* l_turbineManager = m_siteToTurbineMap.value(a_turbineInfo->siteName());
        l_turbineManager->addTurbine(a_turbineInfo);
    }
}

QMap<SITENAME, SiteInfo *> SiteManager::getSiteToSiteObjMap() const
{
    return m_siteToSiteObjMap;
}

bool SiteManager::checkSite(QString a_siteName, QString a_turbineName)
{
    qDebug()<<Q_FUNC_INFO;
    if(m_siteToTurbineMap.contains(a_siteName)){
        if(m_siteToTurbineMap.value(a_siteName)->checkTurbine(a_turbineName)){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }   
}
