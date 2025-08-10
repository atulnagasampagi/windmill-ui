#include "countryproxymodel.h"

CountryProxyModel::CountryProxyModel(QObject *parent)
    : QObject{parent}
{
    qDebug()<<Q_FUNC_INFO;
    Q_UNUSED(parent)
    m_countryViewModel = new CountryViewModel();
    m_configurationManagment = new ConfigurationManagement();
    m_markerViewModel = new MarkerViewModel();
    m_datamanager = new DataManager();
    m_siteViewModel = new SiteViewModel();
    m_turbineViewModel = new TurbineViewModel();
    m_turbineInfoViewModel = new TurbineInfoViewModel();
    m_turbineDataModel = new TurbineDataModel();
    m_csvProcessor = new CsvProcessor();
    m_loginCredentials = new LoginCredentials();
    connect(m_csvProcessor,&CsvProcessor::sendturbinetoCountryManager,m_turbineDataModel,&TurbineDataModel::addTurbine);
    //for Login Data
    connect(m_csvProcessor,&CsvProcessor::sendlogintoCountryProxy,m_loginCredentials,&LoginCredentials::insertLoginData);
    connect(m_loginCredentials,&LoginCredentials::sendRegistrationData,m_csvProcessor,&CsvProcessor::writeRegisterDataToCsv);

    m_csvProcessor->readTurbineInfoFile();
    m_csvProcessor->readRegisterData();

    //for Add Country
    connect(m_configurationManagment,&ConfigurationManagement::addCountrySuccess,this,&CountryProxyModel::addCountrySuccess);
    connect(m_configurationManagment,&ConfigurationManagement::addCountryFailure,this,&CountryProxyModel::addCountryFailure);

    //for Remove Country
    connect(m_configurationManagment,&ConfigurationManagement::removeCountrySuccess,this,&CountryProxyModel::removeCountrySuccess);
    connect(m_configurationManagment,&ConfigurationManagement::removeCountryFailure,this,&CountryProxyModel::removeCountryFailure);

    //for Remove Site
    connect(m_siteViewModel,&SiteViewModel::removeSiteSucess,this,&CountryProxyModel::removeSiteSuccess);
    connect(m_siteViewModel,&SiteViewModel::removeSiteFailure,this,&CountryProxyModel::removeSiteFailure);

    //for Add Site
    connect(m_siteViewModel,&SiteViewModel::addSiteSucess,this,&CountryProxyModel::addSiteSuccess);
    connect(m_siteViewModel,&SiteViewModel::addSiteFailure,this,&CountryProxyModel::addSiteFailure);

    //for login verification
    connect(m_loginCredentials,&LoginCredentials::loginSucess,this,&CountryProxyModel::loginSuccess);
    connect(m_loginCredentials,&LoginCredentials::loginFailure,this,&CountryProxyModel::loginFailure);

    //for registration verification
    connect(m_loginCredentials,&LoginCredentials::registrationSuccess,this,&CountryProxyModel::registrationSuccess);
    connect(m_loginCredentials,&LoginCredentials::registrationFailure,this,&CountryProxyModel::registrationFailure);

    // connect(m_datamanager,&DataManager::dataChanged,m_turbineViewModel,&TurbineViewModel::changeToView);

    connect(m_datamanager,&DataManager::sendParameters,m_configurationManagment,&ConfigurationManagement::checkParameters);
    connect(m_configurationManagment,&ConfigurationManagement::settrue,m_datamanager,&DataManager::callTurbineDataobj);
    connect(m_configurationManagment,&ConfigurationManagement::setfalse,m_datamanager,&DataManager::checkstatus);

    m_countryViewModel->setDataModel(m_configurationManagment->getCountryManager());
    m_turbineInfoViewModel->setTurbineDataModel(m_turbineDataModel);


}

CountryProxyModel::~CountryProxyModel()
{
    qDebug()<<Q_FUNC_INFO;
    delete m_configurationManagment;
    delete m_countryViewModel;
    delete m_csvProcessor;
    delete m_datamanager;
    delete m_markerViewModel;
    delete m_siteViewModel;
    delete m_turbineDataModel;
    delete m_turbineInfoViewModel;
    delete m_turbineViewModel;
    delete m_loginCredentials;
}

CountryViewModel *CountryProxyModel::countryViewModel() const
{
    qDebug()<<Q_FUNC_INFO;
    return m_countryViewModel;
}

void CountryProxyModel::setCountryViewModel(CountryViewModel *newCountryViewModel)
{
    qDebug()<<Q_FUNC_INFO;
    if (m_countryViewModel == newCountryViewModel)
        return;
    m_countryViewModel = newCountryViewModel;
    emit countryViewModelChanged();
}

SiteViewModel *CountryProxyModel::siteViewModel() const
{
    qDebug()<<Q_FUNC_INFO;
    return m_siteViewModel;
}

void CountryProxyModel::setSiteViewModel(SiteViewModel *a_SiteViewModel)
{
    qDebug()<<Q_FUNC_INFO;
    if (m_siteViewModel == a_SiteViewModel)
        return;
    m_siteViewModel = a_SiteViewModel;
    emit siteViewModelChanged();
}

void CountryProxyModel::setSiteManager(QString a_countryName)
{
    qDebug()<<Q_FUNC_INFO;
    qDebug() << Q_FUNC_INFO;
    SiteManager* l_siteManager = m_configurationManagment->getCountryManager()->getSiteManager(a_countryName);

    m_siteViewModel->setSiteManager(l_siteManager);
}

void CountryProxyModel::addCountryToConfig(QString a_countryName)
{
    qDebug()<<Q_FUNC_INFO;
    m_configurationManagment->addCountryToCountryManager(a_countryName);
}

void CountryProxyModel::addSiteToConfig(QString a_countryName, QString a_state, QString a_site, QString a_location, QString a_phno)
{
    qDebug()<<Q_FUNC_INFO;
    m_configurationManagment->addSiteToCountryManager(a_countryName,a_state,a_site,a_location,a_phno);
}

void CountryProxyModel::addTurbineToConfig(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer)
{
    qDebug()<<Q_FUNC_INFO;
    m_configurationManagment->addTurbineToCountryManager(a_countryName,a_siteName,a_turbineName,a_manufacturer);
}

void CountryProxyModel::verfiyLoginDetails(QString a_username, QString a_password)
{
    m_loginCredentials->verifyLoginCredentials(a_username,a_password);
}

void CountryProxyModel::addNewUserToApplication(QString a_username, QString a_email, QString a_password, QString a_confirmPassword)
{
    m_loginCredentials->addNewUser(a_username,a_email,a_password,a_confirmPassword);
}


void CountryProxyModel::sendTurbineListToViewModel(QString a_sitename)
{
    qDebug()<<Q_FUNC_INFO;
    m_turbineViewModel->setTurbineData(m_datamanager->getTurbineList(a_sitename));
}

void CountryProxyModel::removeCountry(QString a_countryName)
{
    m_configurationManagment->removeCountry(a_countryName);
}

void CountryProxyModel::removeSite(QString a_countryName, QString a_siteName)
{
    m_configurationManagment->removeSite(a_countryName,a_siteName);
}

TurbineInfoViewModel *CountryProxyModel::turbineInfoViewModel() const
{
    return m_turbineInfoViewModel;
}

void CountryProxyModel::setTurbineInfoViewModel(TurbineInfoViewModel *newTurbineInfoViewModel)
{
    if (m_turbineInfoViewModel == newTurbineInfoViewModel)
        return;
    m_turbineInfoViewModel = newTurbineInfoViewModel;
    emit turbineInfoViewModelChanged();
}

LoginCredentials *CountryProxyModel::getLoginCredentials() const
{
    return m_loginCredentials;
}

void CountryProxyModel::setLoginCredentials(LoginCredentials *a_loginCredentials)
{
    if (m_loginCredentials == a_loginCredentials){
        return;
    }
    m_loginCredentials = a_loginCredentials;
    emit loginCredentialsChanged();
}

TurbineViewModel *CountryProxyModel::turbineViewModel() const
{
    return m_turbineViewModel;
}

void CountryProxyModel::setTurbineViewModel(TurbineViewModel *a_TurbineViewModel)
{
    if (m_turbineViewModel == a_TurbineViewModel)
        return;
    m_turbineViewModel = a_TurbineViewModel;
    emit turbineViewModelChanged();
}

MarkerViewModel *CountryProxyModel::markerViewModel() const
{
    qDebug()<<Q_FUNC_INFO;
    return m_markerViewModel;
}

void CountryProxyModel::setMarkerViewModel(MarkerViewModel *a_MarkerViewModel)
{
    qDebug()<<Q_FUNC_INFO;
    if (m_markerViewModel == a_MarkerViewModel)
        return;
    m_markerViewModel = a_MarkerViewModel;
    emit markerViewModelChanged();
}
