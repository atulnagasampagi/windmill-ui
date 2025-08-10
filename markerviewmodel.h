#ifndef MARKERVIEWMODEL_H
#define MARKERVIEWMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <markerdatamodel.h>

class MarkerViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MarkerViewModel(QObject *parent = nullptr);
    ~MarkerViewModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    MarkerDataModel* m_markerDataModel = nullptr;
};

#endif // MARKERVIEWMODEL_H
