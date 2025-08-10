#ifndef COUNTRYMANAGER_H
#define COUNTRYMANAGER_H

#include <QObject>
#include <countryinfo.h>
#include <sitemanager.h>
#include <QFile>

using COUNTRYNAME = QString;

class CountryManager : public QObject
{
    Q_OBJECT
public:
    explicit CountryManager(QObject *parent = nullptr);
    ~CountryManager();

    void display();
    QMap<COUNTRYNAME, CountryInfo *> getCountryToCountryObj() const;

    SiteManager* getSiteManager(QString a_country);

public slots:

    void addNewCountryInCountryManager(QString a_countryName);
    void addNewSiteInCountryManager(QString a_countryName,QString a_state,QString a_site,QString a_location,QString a_phno);
    void addNewTurbineInCountryManager(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer);

    void addCountryInCountryManager(QString a_countryName,CountryInfo* a_countryInfo);
    void addSiteInCountryManager(QString a_country,QString a_site,SiteInfo* a_siteInfo);
    void addTurbineInCountryManager(TurbineInfo* a_TurbineInfo);
    void addSiteManager(QString a_countryName, SiteManager* a_siteManager);
    void removeCountry(QString a_countryName);
    void removeSite(QString a_countryName,QString a_siteName);


    bool checkCountry(QString a_countryName,QString a_siteName,QString a_turbineName);

signals:
    void dataUpdated();
    void addCountrySuccess(QString,QString);
    void addCountryFailure(QString,QString);

    void removeCountrySuccess(QString,QString);
    void removeCountryFailure(QString,QString);

    void removeSiteSuccess(QString,QString);
    void removeSiteFailure(QString,QString);

private:
    QMap<COUNTRYNAME,SiteManager*> m_countryToSiteMap;
    QMap<COUNTRYNAME,CountryInfo*> m_countryToCountryObj;
};

#endif // COUNTRYMANAGER_H
