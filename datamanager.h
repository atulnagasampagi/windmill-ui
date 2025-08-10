#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QDebug>
#include <QMap>
#include<turbinedata.h>
#include<firebasereader.h>
#include<QTimer>

using SiteName = QString;
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
    ~DataManager();

    void addTurbine(TurbineData *a_turbineData);
    QList<TurbineData *> getTurbineList(QString a_sitename);
public slots:

    void callTurbineDataobj();
    void checkParameters(TurbineData *a_turbineData);

    void checkstatus();
signals:
    void sendParameters(QString , QString ,QString);
    void dataChanged();

private:

    QMap<SiteName,QList<TurbineData*>> m_TurbineDatamap;
    FireBaseReader *m_firebase;
    TurbineData *m_TurbineData=nullptr;
    QTimer *m_timer;
};

#endif // DATAMANAGER_H
