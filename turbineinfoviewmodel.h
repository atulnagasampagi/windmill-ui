#ifndef TURBINEINFOVIEWMODEL_H
#define TURBINEINFOVIEWMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <turbinedatamodel.h>

class TurbineInfoViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TurbineInfoViewModel(QObject *parent = nullptr);
    ~TurbineInfoViewModel();

    void setTurbineDataModel(TurbineDataModel* a_turbineDataModel);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
private:
    TurbineDataModel* m_turbineData = nullptr;

};

#endif // TURBINEINFOVIEWMODEL_H
