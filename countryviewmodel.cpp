#include "countryviewmodel.h"

CountryViewModel::CountryViewModel()
{
    qDebug()<<Q_FUNC_INFO;
}

CountryViewModel::~CountryViewModel()
{
    qDebug()<<Q_FUNC_INFO;
    if(!m_CountryDataModel)
        delete m_CountryDataModel;
}

CountryManager *CountryViewModel::getCountryDataModel() const
{
    qDebug()<<Q_FUNC_INFO;
    return m_CountryDataModel;
}

void CountryViewModel::setDataModel(CountryManager *a_countryManager)
{
    qDebug()<<Q_FUNC_INFO;
    m_CountryDataModel = a_countryManager;
    connect(m_CountryDataModel,&CountryManager::dataUpdated,this,&CountryViewModel::changeToView);
}

void CountryViewModel::setCountryDataModel(CountryManager *a_CountryDataModel)
{
    qDebug()<<Q_FUNC_INFO;
    m_CountryDataModel = a_CountryDataModel;
}

void CountryViewModel::changeToView()
{
    qDebug()<<Q_FUNC_INFO;
    beginResetModel();
    endResetModel();
}

int CountryViewModel::rowCount(const QModelIndex &parent) const{
    qDebug()<<Q_FUNC_INFO;
    Q_UNUSED(parent)
    return m_CountryDataModel->getCountryToCountryObj().count();
}

QVariant CountryViewModel::data(const QModelIndex &index, int role) const{
    qDebug()<<Q_FUNC_INFO;
    if (!index.isValid() || !m_CountryDataModel)
        return QVariant();

    QList<COUNTRYNAME> keys = m_CountryDataModel->getCountryToCountryObj().keys();
    COUNTRYNAME key = keys[index.row()];
    CountryInfo *countryInfo = m_CountryDataModel->getCountryToCountryObj().value(key);

    if(role == 0){
        return countryInfo->CountryName();
    }else{
        return countryInfo->CountryFlag();
    }
}

QHash<int, QByteArray> CountryViewModel::roleNames() const{
    qDebug()<<Q_FUNC_INFO;
    QHash<int, QByteArray> roles;
    roles[0] = "CName";
    roles[1] = "CFlag";

    return roles;
}
