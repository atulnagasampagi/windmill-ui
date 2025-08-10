#include "turbineinfo.h"

TurbineInfo::TurbineInfo() {
    qDebug() << Q_FUNC_INFO;
}

TurbineInfo::~TurbineInfo()
{

 qDebug()<<Q_FUNC_INFO;

}

QString TurbineInfo::manufacturer() const
{
    return m_manufacturer;
}

void TurbineInfo::setManufacturer(const QString &newManufacturer)
{
    m_manufacturer = newManufacturer;
}

QString TurbineInfo::siteName() const
{
    return m_siteName;
}

void TurbineInfo::setSiteName(const QString &newSiteName)
{
    m_siteName = newSiteName;
}

QString TurbineInfo::country() const
{
    return m_country;
}

void TurbineInfo::setCountry(const QString &newCountry)
{
    m_country = newCountry;
}

QString TurbineInfo::turbineName() const
{
    return m_turbineName;
}

void TurbineInfo::setTurbineName(const QString &newTurbineName)
{
    m_turbineName = newTurbineName;
}


double TurbineInfo::latitude() const
{
    return m_latitude;
}

void TurbineInfo::setLatitude(double newLatitude)
{
    m_latitude = newLatitude;
}

double TurbineInfo::longitude() const
{
    return m_longitude;
}

void TurbineInfo::setLongitude(double newLongitude)
{
    m_longitude = newLongitude;
}

