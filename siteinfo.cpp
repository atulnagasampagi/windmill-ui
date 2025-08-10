#include "siteinfo.h"

SiteInfo::SiteInfo() {
    qDebug() << Q_FUNC_INFO;
}

SiteInfo::~SiteInfo() {
    qDebug()<<Q_FUNC_INFO;
}

QString SiteInfo::siteName() const
{
    return m_siteName;
}

void SiteInfo::setSiteName(const QString &newSiteName)
{
    m_siteName = newSiteName;
}

QString SiteInfo::location() const
{
    return m_location;
}

void SiteInfo::setLocation(const QString &newLocation)
{
    m_location = newLocation;
}

QString SiteInfo::state() const
{
    return m_state;
}

void SiteInfo::setState(const QString &newState)
{
    m_state = newState;
}

QString SiteInfo::country() const
{
    return m_country;
}

void SiteInfo::setCountry(const QString &newCountry)
{
    m_country = newCountry;
}

QString SiteInfo::phno() const
{
    return m_phno;
}

void SiteInfo::setPhno(const QString &newPhno)
{
    m_phno = newPhno;
}

double SiteInfo::latitude() const
{
    return m_latitude;
}

void SiteInfo::setLatitude(double newLatitude)
{
    m_latitude = newLatitude;
}

double SiteInfo::longitude() const
{
    return m_longitude;
}

void SiteInfo::setLongitude(double newLongitude)
{
    m_longitude = newLongitude;
}
