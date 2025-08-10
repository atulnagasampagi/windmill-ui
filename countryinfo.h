#ifndef COUNTRYINFO_H
#define COUNTRYINFO_H

#include <QDebug>

class CountryInfo
{
public:
    CountryInfo();
    ~CountryInfo();
    QString CountryName() const;
    QString CountryFlag() const;

    void setCountryName(const QString &newCountryName);
    void setCountryFlag(const QString &newCountryFlag);

private:
    QString m_CountryName = "";
    QString m_CountryFlag = "";
};

#endif // COUNTRYINFO_H
