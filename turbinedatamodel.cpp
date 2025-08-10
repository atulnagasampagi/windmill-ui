#include "turbinedatamodel.h"

TurbineDataModel::TurbineDataModel(QObject *parent)
    : QObject{parent}
{
    qDebug() << Q_FUNC_INFO;
}

TurbineDataModel::~TurbineDataModel()
{
    for(TurbineInfo* turbine : m_turbineList){
        delete turbine;
    }
    m_turbineList.clear();
}

void TurbineDataModel::addTurbine(TurbineInfo *a_turbineInfo)
{
    qDebug() << Q_FUNC_INFO;
    m_turbineList.append(a_turbineInfo);
}

QList<TurbineInfo *> TurbineDataModel::getTurbineList() const
{
    return m_turbineList;
}
