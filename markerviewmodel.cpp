#include "markerviewmodel.h"

MarkerViewModel::MarkerViewModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_markerDataModel = new MarkerDataModel();
}

MarkerViewModel::~MarkerViewModel()
{
    qDebug()<<Q_FUNC_INFO;
    delete m_markerDataModel;
}

int MarkerViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    qDebug() << Q_FUNC_INFO;
    return m_markerDataModel->getMarkerList().count();
}

QVariant MarkerViewModel::data(const QModelIndex &index, int role) const
{
    switch(role){
    case 0: return m_markerDataModel->getMarkerList().at(index.row())->latitude();
        break;
    case 1: return m_markerDataModel->getMarkerList().at(index.row())->longitude();
        break;
    case 2: return m_markerDataModel->getMarkerList().at(index.row())->country();
        break;
    case 3: return m_markerDataModel->getMarkerList().at(index.row())->siteName();
        break;
    case 4: return m_markerDataModel->getMarkerList().at(index.row())->location();
        break;
    case 5: return m_markerDataModel->getMarkerList().at(index.row())->state();
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> MarkerViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "MyLatitude";
    roles[1] = "MyLongitude";
    roles[2] = "MyCountry";
    roles[3] = "MySite";
    roles[4] = "MyLocation";
    roles[5] = "MyState";

    return roles;
}

