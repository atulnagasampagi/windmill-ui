#include "turbineinfoviewmodel.h"

TurbineInfoViewModel::TurbineInfoViewModel(QObject *parent)
    : QAbstractListModel{parent}
{
    qDebug() << Q_FUNC_INFO;
}

TurbineInfoViewModel::~TurbineInfoViewModel()
{

}

void TurbineInfoViewModel::setTurbineDataModel(TurbineDataModel *a_turbineDataModel)
{
    m_turbineData = a_turbineDataModel;
}

int TurbineInfoViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_turbineData->getTurbineList().count();
}

QVariant TurbineInfoViewModel::data(const QModelIndex &index, int role) const
{
    switch(role){
    case 0: return m_turbineData->getTurbineList().at(index.row())->country();
        break;
    case 1: return m_turbineData->getTurbineList().at(index.row())->siteName();
        break;
    case 2: return m_turbineData->getTurbineList().at(index.row())->turbineName();
        break;
    case 3: return m_turbineData->getTurbineList().at(index.row())->manufacturer();
        break;
    case 4: return m_turbineData->getTurbineList().at(index.row())->latitude();
        break;
    case 5: return m_turbineData->getTurbineList().at(index.row())->longitude();
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TurbineInfoViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "MyCountryName";
    roles[1] = "MySiteName";
    roles[2] = "MyTurbineName";
    roles[3] = "MyManufacturer";
    roles[4] = "MyTurbineLatitude";
    roles[5] = "MyTurbineLongitude";

    return roles;
}
