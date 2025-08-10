#ifndef CSVPROCESSOR_H
#define CSVPROCESSOR_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <turbineinfo.h>
#include <countryinfo.h>
#include <turbinemanager.h>
#include <logincredentials.h>
#include <siteinfo.h>
#include <sitemanager.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class CsvProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CsvProcessor(QObject *parent = nullptr);
    ~CsvProcessor();

    void readMappedData();
    void readCountryInfoFile();
    void readSiteInfofile();
    void readTurbineInfoFile();
    void readRegisterData();

public slots:
    void writeRegisterDataToCsv(QString a_username,QString a_email,QString a_password,QString a_confirmPassword);
signals:
    void sendCountrytoCountryManager(QString a_countryName, CountryInfo* a_countryInfo);
    void sendSitetoCountryManager(QString a_countryName,QString a_site,SiteInfo* a_siteInfo);
    void sendturbinetoCountryManager(TurbineInfo* a_turbineInfo);
    void sendlogintoCountryProxy(QString a_username,QString a_password);

private:
    CountryInfo* m_countryInfo = nullptr;
    SiteInfo *m_site = nullptr;
    TurbineInfo *m_turbine = nullptr;
    TurbineManager* m_turbineManager = nullptr;
};

#endif // CSVPROCESSOR_H
