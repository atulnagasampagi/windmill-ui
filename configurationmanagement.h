#ifndef CONFIGURATIONMANAGEMENT_H
#define CONFIGURATIONMANAGEMENT_H

#include <QObject>
#include <csvprocessor.h>
#include <countrymanager.h>

class ConfigurationManagement : public QObject
{
    Q_OBJECT
public:
    explicit ConfigurationManagement(QObject *parent = nullptr);
    ~ConfigurationManagement();

    CountryManager *getCountryManager() const;

    void addCountryToCountryManager(QString a_countryName);
    void addSiteToCountryManager(QString a_countryName, QString a_state, QString a_site, QString a_location, QString a_phno);
    void addTurbineToCountryManager(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer);
    void removeCountry(QString a_countryName);
    void removeSite(QString a_countryName,QString a_siteName);

signals:
    void settrue();
    void setfalse();

    void addCountrySuccess(QString,QString);
    void addCountryFailure(QString,QString);


    void removeCountrySuccess(QString,QString);
    void removeCountryFailure(QString,QString);

    void removeSiteSuccess(QString,QString);
    void removeSiteFailure(QString,QString);
public slots:

    bool checkParameters(QString a_countryName,QString a_siteName,QString a_turbineName);

private:
    CsvProcessor* m_csvProcessor = nullptr;
    CountryManager* m_countryManager = nullptr;
};

#endif // CONFIGURATIONMANAGEMENT_H
