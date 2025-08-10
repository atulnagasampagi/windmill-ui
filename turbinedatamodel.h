#ifndef TURBINEDATAMODEL_H
#define TURBINEDATAMODEL_H

#include <QObject>
#include <turbineinfo.h>

using TURBINENAME = QString;

class TurbineDataModel : public QObject
{
    Q_OBJECT
public:
    explicit TurbineDataModel(QObject *parent = nullptr);
    ~TurbineDataModel();

    QList<TurbineInfo *> getTurbineList() const;
public slots:
    void addTurbine(TurbineInfo* a_turbineInfo);
signals:

private:
    QList<TurbineInfo*> m_turbineList;
};

#endif // TURBINEDATAMODEL_H
