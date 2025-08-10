#ifndef TURBINEMANAGER_H
#define TURBINEMANAGER_H

#include <QObject>
#include <turbineinfo.h>

using TURBINENAME = QString;

class TurbineManager : public QObject
{
    Q_OBJECT
public:
    explicit TurbineManager(QObject *parent = nullptr);
    ~TurbineManager();

    void addNewTurbine(QString a_countryName, QString a_siteName, QString a_turbineName, QString a_manufacturer);

    void addTurbine(TurbineInfo* a_turbineInfo);




    bool checkTurbine(QString a_turbineName);
    QMap<TURBINENAME, TurbineInfo *> getTurbineNameToTurbineObjMap() const;

signals:
    void addTurbineSuccess();
    void addTurbineFailure();

private:
    QMap<TURBINENAME,TurbineInfo*> m_turbineNameToTurbineObjMap;
};

#endif // TURBINEMANAGER_H
