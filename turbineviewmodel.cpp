#include "turbineviewmodel.h"

TurbineViewModel::TurbineViewModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    m_timer=new QTimer;
    connect(m_timer,&QTimer::timeout,this,&TurbineViewModel::changeToView);
    m_timer->start(6000);
}

void TurbineViewModel::setTurbineData(QList<TurbineData *> a_turbineList)
{
    qDebug()<<Q_FUNC_INFO;
    m_turbineList=a_turbineList;
}

TurbineViewModel::~TurbineViewModel()
{
    qDebug()<<Q_FUNC_INFO;
}

int TurbineViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_turbineList.size();
}

int TurbineViewModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_turbineList.size();
}

QVariant TurbineViewModel::data(const QModelIndex &index, int role) const
{
    TurbineData* turbine = m_turbineList[index.row()];

    switch(role){
    case 0:
        return turbine->turbineName();
        break;
    case 1:
        return turbine->windSpeed();
        break;
    case 2:
        return turbine->windDirection();
        break;
    case 3:
        return turbine->powerOutput();
        break;
    case 4:
        return turbine->temperature();
        break;
    case 5:
        return turbine->pressure();
        break;
    case 6:
        return turbine->pitchAngle();
        break;
    case 7:
        return turbine->bladeAngle();
        break;
    case 8:
        return turbine->yawDirection();
        break;

    }
    return QVariant();
}

QHash<int, QByteArray> TurbineViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0]="Turbine";
    roles[1]="Wind Speed";
    roles[2]="Wind Direction";
    roles[3]="Power Output(KW)";
    roles[4]="Temperature";
    roles[5]="Pressure";
    roles[6]="Pitch Angle";
    roles[7]="Blade Angle";
    roles[8]="Yaw Direction";

    return roles;
}

void TurbineViewModel::changeToView()
{
    beginResetModel();
    endResetModel();
}

