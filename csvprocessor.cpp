#include "csvprocessor.h"

CsvProcessor::CsvProcessor(QObject *parent)
    : QObject{parent}
{
    qDebug()<<Q_FUNC_INFO;
}

CsvProcessor::~CsvProcessor()
{
    qDebug()<<Q_FUNC_INFO;
}

void CsvProcessor::readMappedData()
{
    qDebug()<<Q_FUNC_INFO;
    QString filePath = "JSONFiles/ParameterMapping.json";

    QFile file(filePath);
    if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file: " << file.errorString();
        return;
    }
}

void CsvProcessor::readCountryInfoFile()
{
    qDebug()<<Q_FUNC_INFO;
    QString filePath = "CountryList.csv";

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(",");

        if (parts.size() == 2) {
            m_countryInfo = new CountryInfo();
            m_countryInfo->setCountryName(parts[0]);
            m_countryInfo->setCountryFlag(parts[1]);

            emit sendCountrytoCountryManager(m_countryInfo->CountryName(),m_countryInfo);
        } else {
            qDebug() << "Invalid line:" << line;
        }
    }

    file.close();
}
void CsvProcessor::readSiteInfofile()
{
    qDebug()<<Q_FUNC_INFO;
    QString filePath = "Siteinfo.csv";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(",");

        if (parts.size() == 7) {
            m_site = new SiteInfo();
            m_site->setSiteName(parts[0]);
            m_site->setLocation(parts[1]);
            m_site->setState(parts[2]);
            m_site->setCountry(parts[3]);
            m_site->setPhno(parts[4]);

            emit sendSitetoCountryManager(m_site->country(),m_site->siteName(), m_site);

        } else {
            qDebug() << "Invalid line:" << line;
        }
    }
    file.close();
}

void CsvProcessor::readTurbineInfoFile()
{
    qDebug()<<Q_FUNC_INFO;
    QFile file("turbine_data.json");

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << file.errorString();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse JSON:" << jsonError.errorString();
        return;
    }

    if (!jsonDoc.isObject()) {
        qWarning() << "JSON document is not an object.";
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();
    for (const QString &country : jsonObject.keys()) {
        QJsonObject countryObject = jsonObject.value(country).toObject();
        for (const QString &site : countryObject.keys()) {
            QJsonObject siteObject = countryObject.value(site).toObject();
            QString manufacturer = siteObject.value("TB1").toObject().value("Manufacturer").toString();
            for (const QString &turbine : siteObject.keys()) {
                QJsonObject turbineObject = siteObject.value(turbine).toObject();
                TurbineInfo* l_turbine = new TurbineInfo();
                l_turbine->setCountry(country);
                l_turbine->setSiteName(site);
                l_turbine->setTurbineName(turbine);
                l_turbine->setManufacturer(manufacturer);
                l_turbine->setLatitude(turbineObject.value("Latitude").toDouble());
                l_turbine->setLongitude(turbineObject.value("Longitude").toDouble());

                emit sendturbinetoCountryManager(l_turbine);
            }
        }
    }
}

void CsvProcessor::readRegisterData()
{
    QFile file("LoginData.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Could not open the CSV file for reading.");
        return;
    }

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(",");

        if (fields.size() == 4) {
            QString l_username = fields.at(0);
            QString l_password = fields.at(2);

            emit sendlogintoCountryProxy(l_username,l_password);
        } else {
            qWarning() << "Incorrectly formatted line:" << line;
        }
    }

    file.close();
}

void CsvProcessor::writeRegisterDataToCsv(QString a_username, QString a_email, QString a_password, QString a_confirmPassword)
{
    QFile file("LoginData.csv");

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning("Could not open the CSV file for writing.");
        return;
    }

    QTextStream stream(&file);

    stream << a_username << "," << a_email << "," << a_password << "," << a_confirmPassword << "\n";
    file.close();
}
