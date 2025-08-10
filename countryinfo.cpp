#include "countryinfo.h"

CountryInfo::CountryInfo() {
    qDebug() << Q_FUNC_INFO;
}

CountryInfo::~CountryInfo()
{
    qDebug() << Q_FUNC_INFO;
}

QString CountryInfo::CountryName() const
{
    qDebug()<<Q_FUNC_INFO;
    return m_CountryName;
}

void CountryInfo::setCountryName(const QString &newCountryName)
{
    qDebug()<<Q_FUNC_INFO;
    m_CountryName = newCountryName;
}

QString CountryInfo::CountryFlag() const
{
    qDebug()<<Q_FUNC_INFO;
    return m_CountryFlag;
}

void CountryInfo::setCountryFlag(const QString &newCountryFlag)
{
    qDebug()<<Q_FUNC_INFO;
    m_CountryFlag = newCountryFlag;
}
