#ifndef TURBINEINFO_H
#define TURBINEINFO_H

#include <QDebug>

class TurbineInfo
{
public:
    TurbineInfo();
    ~TurbineInfo();

    QString manufacturer() const;
    QString siteName() const;
    QString country() const;
    QString turbineName() const;
    double turbineLatitude() const;
    double turbineLongitude() const;

    void setManufacturer(const QString &newManufacturer);
    void setSiteName(const QString &newSiteName);
    void setCountry(const QString &newCountry);
    void setTurbineName(const QString &newTurbineName);
    void setTurbineLatitude(double newTurbineLatitude);
    void setTurbineLongitude(double newTurbineLongitude);

    double latitude() const;
    void setLatitude(double newLatitude);

    double longitude() const;
    void setLongitude(double newLongitude);

private:
    QString m_manufacturer = "";
    QString m_siteName = "";
    QString m_country = "";
    QString m_turbineName = "";

    double m_latitude = 0.0;
    double m_longitude = 0.0;

};

#endif // TURBINEINFO_H
