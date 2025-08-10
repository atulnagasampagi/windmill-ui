#ifndef COUNTRYPROXYMODEL_H
#define COUNTRYPROXYMODEL_H

#include <QObject>
#include <configurationmanagement.h>
#include <countrymanager.h>
#include <countryviewmodel.h>
#include <csvprocessor.h>
#include <markerviewmodel.h>
#include <turbineviewmodel.h>
#include <turbineinfoviewmodel.h>
#include <datamanager.h>
#include <siteviewmodel.h>
#include <turbinedatamodel.h>
#include <csvprocessor.h>
#include <turbineinfoviewmodel.h>
#include <logincredentials.h>

class CountryProxyModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CountryViewModel *mycountryViewModel READ countryViewModel WRITE setCountryViewModel NOTIFY countryViewModelChanged FINAL)
    Q_PROPERTY(SiteViewModel *mysiteViewModel READ siteViewModel WRITE setSiteViewModel NOTIFY siteViewModelChanged FINAL)
    Q_PROPERTY(MarkerViewModel *mymarkerViewModel READ markerViewModel WRITE setMarkerViewModel NOTIFY markerViewModelChanged FINAL)
    Q_PROPERTY(TurbineViewModel *myturbineViewModel READ turbineViewModel WRITE setTurbineViewModel NOTIFY turbineViewModelChanged FINAL)
    Q_PROPERTY(TurbineInfoViewModel *myturbineInfoViewModel READ turbineInfoViewModel WRITE setTurbineInfoViewModel NOTIFY turbineInfoViewModelChanged FINAL)
    Q_PROPERTY(LoginCredentials *myLoginCredentials READ getLoginCredentials WRITE setLoginCredentials NOTIFY loginCredentialsChanged FINAL)
public:

    explicit CountryProxyModel(QObject *parent = nullptr);
    ~CountryProxyModel();

    CountryViewModel *countryViewModel() const;
    void setCountryViewModel(CountryViewModel *newCountryViewModel);

    SiteViewModel *siteViewModel() const;
    void setSiteViewModel(SiteViewModel *newSiteViewModel);

    MarkerViewModel *markerViewModel() const;
    void setMarkerViewModel(MarkerViewModel *newMarkerViewModel);

    TurbineViewModel *turbineViewModel() const;
    void setTurbineViewModel(TurbineViewModel *newTurbineViewModel);

    TurbineInfoViewModel *turbineInfoViewModel() const;
    void setTurbineInfoViewModel(TurbineInfoViewModel *newTurbineInfoViewModel);

    LoginCredentials *getLoginCredentials() const;
    void setLoginCredentials(LoginCredentials *a_loginCredentials);

public slots:

    void setSiteManager(QString a_countryName);
    void addCountryToConfig(QString a_countryName);
    void addSiteToConfig(QString a_countryName, QString a_state, QString a_site, QString a_location, QString a_phno);
    void addTurbineToConfig(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer);
    void verfiyLoginDetails(QString a_username,QString a_password);
    void addNewUserToApplication(QString a_username,QString a_email,QString a_password,QString a_confirmPassword);

    void sendTurbineListToViewModel(QString a_sitename);

    void removeCountry(QString a_countryName);
    void removeSite(QString a_countryName,QString a_siteName);

signals:
    void addCountrySuccess(QString a_label,QString a_text);
    void addCountryFailure(QString a_label,QString a_text);

    void removeCountrySuccess(QString a_label,QString a_text);
    void removeCountryFailure(QString a_label,QString a_text);

    void addSiteSuccess(QString a_label,QString a_text);
    void addSiteFailure(QString a_label,QString a_text);

    void removeSiteSuccess(QString a_label,QString a_text);
    void removeSiteFailure(QString a_label,QString a_text);

    void addTurbineSuccess();
    void addTurbineFailure();

    void countryViewModelChanged();
    void siteViewModelChanged();
    void markerViewModelChanged();

    void turbineViewModelChanged();
    void turbineInfoViewModelChanged();
    void loginCredentialsChanged();

    void loginSuccess(QString a_title,QString a_text);
    void loginFailure(QString a_title,QString a_text);

    void registrationSuccess(QString a_title,QString a_text);
    void registrationFailure(QString a_title,QString a_text);

private:

    ConfigurationManagement* m_configurationManagment = nullptr;
    CountryViewModel* m_countryViewModel = nullptr;
    SiteViewModel* m_siteViewModel = nullptr;
    TurbineViewModel* m_turbineViewModel = nullptr;
    MarkerViewModel* m_markerViewModel = nullptr;
    DataManager *m_datamanager = nullptr;
    TurbineDataModel* m_turbineDataModel = nullptr;
    TurbineInfoViewModel* m_turbineInfoViewModel = nullptr;
    CsvProcessor* m_csvProcessor = nullptr;
    LoginCredentials* m_loginCredentials = nullptr;
};

#endif // COUNTRYPROXYMODEL_H
