#ifndef COUNTRYVIEWMODEL_H
#define COUNTRYVIEWMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDebug>
#include <countrymanager.h>

class CountryViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    CountryViewModel();
    ~CountryViewModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    CountryManager *getCountryDataModel() const;

    void setDataModel(CountryManager* a_countryManager);
    void setCountryDataModel(CountryManager *a_CountryDataModel);
    void changeToView();

signals:
    void CountryDataModelChanged();

    void addCountrySuccess(QString,QString);
    void addCountryFailure(QString,QString);

private:
    CountryManager* m_CountryDataModel = nullptr;
};

#endif // COUNTRYVIEWMODEL_H
