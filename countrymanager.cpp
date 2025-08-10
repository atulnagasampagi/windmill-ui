#include "countrymanager.h"

CountryManager::CountryManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << Q_FUNC_INFO;
}

CountryManager::~CountryManager()
{
    qDebug() << Q_FUNC_INFO;
    foreach(SiteManager* manager, m_countryToSiteMap.values()) {
        delete manager;
    }
    m_countryToSiteMap.clear();

    foreach(CountryInfo* country, m_countryToCountryObj.values()) {
        delete country;
    }
    m_countryToCountryObj.clear();

}

void CountryManager::display()
{
    qDebug()<<Q_FUNC_INFO;
    foreach(CountryInfo* countryInfo, m_countryToCountryObj) {
        if (countryInfo != nullptr) {
            qDebug() << "country name : " << countryInfo->CountryName();
            qDebug() << "country flag : " << countryInfo->CountryFlag();
        }
    }
}

void CountryManager::addCountryInCountryManager(QString a_countryName,CountryInfo *a_countryInfo)
{
    qDebug()<<Q_FUNC_INFO;
    qDebug() << "Country Name : " << a_countryInfo->CountryName();
    if(!m_countryToCountryObj.contains(a_countryName)){
        m_countryToCountryObj.insert(a_countryName,a_countryInfo);
        CountryManager::addSiteManager(a_countryName, new SiteManager());
    }
}

void CountryManager::addSiteInCountryManager(QString a_country,QString a_site,SiteInfo* a_siteInfo)
{
    qDebug()<<Q_FUNC_INFO;
    SiteManager* l_siteManager = nullptr;
    if(m_countryToSiteMap.contains(a_country)){
        l_siteManager = m_countryToSiteMap.value(a_country);
        l_siteManager->addSite(a_site,a_siteInfo);
    }
}

void CountryManager::addTurbineInCountryManager(TurbineInfo* a_TurbineInfo)
{
    qDebug()<<Q_FUNC_INFO;
    SiteManager* l_siteManager = nullptr;
    if(m_countryToSiteMap.contains(a_TurbineInfo->country())){
        l_siteManager = m_countryToSiteMap.value(a_TurbineInfo->country());
        l_siteManager->addTurbineinTurbineManager(a_TurbineInfo);
    }
}

void CountryManager::addSiteManager(QString a_countryName, SiteManager *a_siteManager)
{
    qDebug()<<Q_FUNC_INFO;
    if(!m_countryToSiteMap.contains(a_countryName)){
        m_countryToSiteMap.insert(a_countryName,a_siteManager);
    }
}

bool CountryManager::checkCountry(QString a_countryName, QString a_siteName, QString a_turbineName)
{
    qDebug()<<Q_FUNC_INFO;
    if(m_countryToSiteMap.contains(a_countryName)){
        if(m_countryToSiteMap.value(a_countryName)->checkSite(a_siteName,a_turbineName)){
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
void CountryManager::removeCountry(QString a_countryName)
{
    if(m_countryToCountryObj.contains(a_countryName)){
        delete m_countryToCountryObj.value(a_countryName);
        m_countryToCountryObj.remove(a_countryName);
        if(m_countryToSiteMap.contains(a_countryName)){
            delete m_countryToSiteMap.value(a_countryName);
            m_countryToSiteMap.remove(a_countryName);
            emit dataUpdated();
            emit removeCountrySuccess("Success","Country Removed Successfully");
        }else{
            emit removeCountryFailure("Failure","Country Not Removed");
        }
    }else{
        emit removeCountryFailure("Failure","Country Not Removed");
    }
}

void CountryManager::removeSite(QString a_countryName, QString a_siteName)
{
    if(m_countryToSiteMap.contains(a_countryName)){
        m_countryToSiteMap.value(a_countryName)->removeSite(a_siteName);
        connect(m_countryToSiteMap.value(a_countryName),&SiteManager::removeSiteSuccess,this,&CountryManager::removeSiteSuccess,Qt::UniqueConnection);
        connect(m_countryToSiteMap.value(a_countryName),&SiteManager::removeSiteFailure,this,&CountryManager::removeSiteFailure,Qt::UniqueConnection);
    }else{
        emit removeSiteFailure("Failure","Country Doesn't Exists");
    }
}

QMap<COUNTRYNAME, CountryInfo *> CountryManager::getCountryToCountryObj() const
{
    qDebug()<<Q_FUNC_INFO;
    return m_countryToCountryObj;
}

SiteManager *CountryManager::getSiteManager(QString a_country)
{
    qDebug()<<Q_FUNC_INFO;
    SiteManager* l_siteManager = nullptr;
    if(m_countryToSiteMap.contains(a_country)){
        l_siteManager = m_countryToSiteMap.value(a_country);
        return l_siteManager;
    }

    return nullptr;
}

void CountryManager::addNewCountryInCountryManager(QString a_countryName)
{
    qDebug()<<Q_FUNC_INFO;
    CountryInfo* l_countryInfo = new CountryInfo();
    l_countryInfo->setCountryName(a_countryName);

    QString filePath = "CountryList.csv";

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(",");

        if (parts.size() == 2) {
            if(a_countryName == parts[0]){
                CountryInfo* l_countryInfo = new CountryInfo();

                l_countryInfo->setCountryName(a_countryName);
                l_countryInfo->setCountryFlag(parts[1]);
                if(!m_countryToCountryObj.contains(a_countryName)){
                    m_countryToCountryObj.insert(a_countryName,l_countryInfo);
                    CountryManager::addSiteManager(a_countryName, new SiteManager());
                    emit addCountrySuccess("Success","Country Added Successfully");
                }else{
                    qDebug() << "Country Already Exists";
                    emit addCountryFailure("Failure","Country Already Exists");
                }
            }
        } else {
            qDebug() << "Invalid line:" << line;
        }
    }

    file.close();
}

void CountryManager::addNewSiteInCountryManager(QString a_countryName, QString a_state, QString a_site, QString a_location, QString a_phno)
{
    qDebug()<<Q_FUNC_INFO;
    SiteManager* l_siteManager = nullptr;
    if(m_countryToSiteMap.contains(a_countryName)){
        l_siteManager = m_countryToSiteMap.value(a_countryName);
        l_siteManager->addNewSite(a_countryName,a_state,a_site,a_location,a_phno);
    }
}

void CountryManager::addNewTurbineInCountryManager(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer)
{
    qDebug()<<Q_FUNC_INFO;
    SiteManager* l_siteManager = nullptr;
    if(m_countryToSiteMap.contains(a_countryName)){
        l_siteManager = m_countryToSiteMap.value(a_countryName);
        l_siteManager->addNewTurbineInSiteManager(a_countryName,a_siteName,a_turbineName,a_manufacturer);
    }
}
