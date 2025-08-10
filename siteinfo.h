#ifndef SITEINFO_H
#define SITEINFO_H

#include<QDebug>

class SiteInfo
{
public:
    SiteInfo();
    ~SiteInfo();
    QString siteName() const;
    QString location() const;
    QString state() const;
    QString country() const;
    QString phno() const;
    double latitude() const;
    double longitude() const;

    void setSiteName(const QString &newSiteName);
    void setLocation(const QString &newLocation);
    void setState(const QString &newState);
    void setCountry(const QString &newCountry);
    void setPhno(const QString &newPhno);
    void setLatitude(double newLatitude);
    void setLongitude(double newLongitude);

private:
    QString m_siteName = "";
    QString m_location = "";
    QString m_state = "";
    QString m_country = "";
    QString m_phno = "";
    double m_latitude = 0.0;
    double m_longitude = 0.0;
};

#endif // SITEINFO_H
