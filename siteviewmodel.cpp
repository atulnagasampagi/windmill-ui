#include "siteviewmodel.h"

SiteViewModel::SiteViewModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    Q_UNUSED(parent)
    qDebug() << Q_FUNC_INFO;
}

int SiteViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if(m_siteManager)
        return m_siteManager->getSiteToSiteObjMap().count();
    else
        return -1;
}

int SiteViewModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if(m_siteManager)
        return m_siteManager->getSiteToSiteObjMap().count();
    else
        return -1;
}

QVariant SiteViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_siteManager)
        return QVariant();

    QList<SITENAME> keys = m_siteManager->getSiteToSiteObjMap().keys();
    SITENAME key = keys[index.row()];
    SiteInfo *siteInfo = m_siteManager->getSiteToSiteObjMap().value(key);

    switch(role){
    case 0: return siteInfo->siteName();
        break;
    case 1: return siteInfo->location();
        break;
    case 2: return siteInfo->state();
        break;
    case 3: return siteInfo->country();
        break;
    case 4: return siteInfo->phno();
        break;
    case 5: return siteInfo->latitude();
        break;
    case 6: return siteInfo->longitude();
    }

    return QVariant();
}

QHash<int, QByteArray> SiteViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "PowerPlants";
    roles[1] = "Locations";
    roles[2] = "States";
    roles[3] = "Countries";
    roles[4] = "PhoneNumbers";
    roles[5] = "latitude";
    roles[6] = "longitude";
    return roles;
}

void SiteViewModel::setSiteManager(SiteManager *a_siteManager)
{
    m_siteManager = a_siteManager;

    SiteViewModel::changeToView();
    connect(m_siteManager,&SiteManager::dataUpdated,this,&SiteViewModel::changeToView,Qt::UniqueConnection);
    connect(m_siteManager,&SiteManager::addSiteSuccess,this,&SiteViewModel::addSiteSucess,Qt::UniqueConnection);
    connect(m_siteManager,&SiteManager::addSiteFailure,this,&SiteViewModel::addSiteFailure,Qt::UniqueConnection);

    connect(m_siteManager,&SiteManager::removeSiteSuccess,this,&SiteViewModel::removeSiteSucess,Qt::UniqueConnection);
    connect(m_siteManager,&SiteManager::removeSiteFailure,this,&SiteViewModel::removeSiteFailure,Qt::UniqueConnection);
}

void SiteViewModel::changeToView()
{
    beginResetModel();
    endResetModel();
}

