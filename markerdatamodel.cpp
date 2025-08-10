#include "markerdatamodel.h"

MarkerDataModel::MarkerDataModel(QObject *parent)
    : QObject{parent}
{
    MarkerDataModel::readSiteInfo();
}

MarkerDataModel::~MarkerDataModel()
{
    for(SiteInfo* site : m_markerList){
        delete site;
    }
    m_markerList.clear();
}

QList<SiteInfo *> MarkerDataModel::getMarkerList() const
{
    return m_markerList;
}

void MarkerDataModel::readSiteInfo()
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
            SiteInfo* m_site = new SiteInfo();
            m_site->setSiteName(parts[0]);
            m_site->setState(parts[2]);
            m_site->setLocation(parts[1]);
            m_site->setCountry(parts[3]);
            m_site->setLatitude(parts[5].toDouble());
            m_site->setLongitude(parts[6].toDouble());

            m_markerList.append(m_site);
        } else {
            qDebug() << "Invalid line:" << line;
        }
    }

    file.close();
}

