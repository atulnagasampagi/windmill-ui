#ifndef SITEMANAGER_H
#define SITEMANAGER_H

#include <QObject>
#include <turbinemanager.h>
#include <siteinfo.h>

using SITENAME = QString;

class SiteManager : public QObject
{
    Q_OBJECT
public:
    explicit SiteManager(QObject *parent = nullptr);
    ~SiteManager();

    void addNewSite(QString a_countryName, QString a_state, QString a_site, QString a_location, QString a_phno);
    void addNewTurbineInSiteManager(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer);

    void addSite(QString a_siteName, SiteInfo* a_siteInfo);
    void addTurbineManager(QString a_siteName,TurbineManager* a_turbineManager);
    void addTurbineinTurbineManager(TurbineInfo* a_turbineManager);
    void disp();
    void removeSite(QString a_siteName);

    QMap<SITENAME, SiteInfo *> getSiteToSiteObjMap() const;

    bool checkSite(QString a_siteName,QString a_turbineName);

signals:
    void dataUpdated();
    void addSiteSuccess(QString,QString);
    void addSiteFailure(QString,QString);

    void removeSiteSuccess(QString,QString);
    void removeSiteFailure(QString,QString);
private:
    QMap<SITENAME,TurbineManager*> m_siteToTurbineMap;
    QMap<SITENAME,SiteInfo*> m_siteToSiteObjMap;
};

#endif // SITEMANAGER_H
