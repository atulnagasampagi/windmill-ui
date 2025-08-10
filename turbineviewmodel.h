#ifndef TURBINEVIEWMODEL_H
#define TURBINEVIEWMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QDebug>
#include <QList>
#include <turbinedata.h>
#include<QTimer>

class TurbineViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TurbineViewModel(QObject *parent = nullptr);
    ~TurbineViewModel();
    void setTurbineData(QList<TurbineData* > a_turbineList);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void changeToView();
signals:
    void addTurbineSuccess();
    void addTurbineFailure();

private:

    QList<TurbineData* > m_turbineList;
    QTimer *m_timer;
};

#endif // TURBINEVIEWMODEL_H
