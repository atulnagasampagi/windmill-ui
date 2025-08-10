#include "configurationmanagement.h"

ConfigurationManagement::ConfigurationManagement(QObject *parent)
    : QObject{parent}
{
    qDebug() << Q_FUNC_INFO;
    m_countryManager = new CountryManager;
    m_csvProcessor = new CsvProcessor;
    connect(m_countryManager,&CountryManager::addCountrySuccess,this,&ConfigurationManagement::addCountrySuccess);
    connect(m_countryManager,&CountryManager::addCountryFailure,this,&ConfigurationManagement::addCountryFailure);

    connect(m_countryManager,&CountryManager::removeCountrySuccess,this,&ConfigurationManagement::removeCountrySuccess);
    connect(m_countryManager,&CountryManager::removeCountryFailure,this,&ConfigurationManagement::removeCountryFailure);

    connect(m_countryManager,&CountryManager::removeSiteSuccess,this,&ConfigurationManagement::removeSiteSuccess);
    connect(m_countryManager,&CountryManager::removeSiteFailure,this,&ConfigurationManagement::removeSiteFailure);
    connect(m_csvProcessor,&CsvProcessor::sendCountrytoCountryManager,m_countryManager,&CountryManager::addCountryInCountryManager);
    connect(m_csvProcessor,&CsvProcessor::sendSitetoCountryManager,m_countryManager,&CountryManager::addSiteInCountryManager);
    connect(m_csvProcessor,&CsvProcessor::sendturbinetoCountryManager,m_countryManager,&CountryManager::addTurbineInCountryManager);

    m_csvProcessor->readCountryInfoFile();
    m_csvProcessor->readSiteInfofile();
    m_csvProcessor->readTurbineInfoFile();
    m_countryManager->display();
}

ConfigurationManagement::~ConfigurationManagement()
{
    qDebug()<<Q_FUNC_INFO;
    delete m_countryManager;
    delete m_csvProcessor;
}

CountryManager *ConfigurationManagement::getCountryManager() const
{
    qDebug()<<Q_FUNC_INFO;
    return m_countryManager;
}

void ConfigurationManagement::addCountryToCountryManager(QString a_countryName)
{
    qDebug()<<Q_FUNC_INFO;
    m_countryManager->addNewCountryInCountryManager(a_countryName);
}

void ConfigurationManagement::addSiteToCountryManager(QString a_countryName, QString a_state, QString a_site, QString a_location, QString a_phno)
{
    qDebug()<<Q_FUNC_INFO;
    m_countryManager->addNewSiteInCountryManager(a_countryName,a_state,a_site,a_location,a_phno);
}

void ConfigurationManagement::addTurbineToCountryManager(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer)
{
    qDebug()<<Q_FUNC_INFO;
    m_countryManager->addNewTurbineInCountryManager(a_countryName,a_siteName,a_turbineName,a_manufacturer);
}

bool ConfigurationManagement::checkParameters(QString a_countryName, QString a_siteName, QString a_turbineName)
{
    qDebug()<<Q_FUNC_INFO;
    if(m_countryManager->checkCountry(a_countryName,a_siteName,a_turbineName)){
        qDebug()<<Q_FUNC_INFO<<"set true";
        emit settrue();
        return true;
    }
    else{
        qDebug()<<Q_FUNC_INFO<<"set false";
        emit setfalse();
        return false;
    }
}

void ConfigurationManagement::removeCountry(QString a_countryName)
{
    m_countryManager->removeCountry(a_countryName);
}

void ConfigurationManagement::removeSite(QString a_countryName, QString a_siteName)
{
    m_countryManager->removeSite(a_countryName,a_siteName);
}
