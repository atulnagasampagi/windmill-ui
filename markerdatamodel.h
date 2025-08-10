#ifndef MARKERDATAMODEL_H
#define MARKERDATAMODEL_H

#include <QObject>
#include <QFile>
#include <siteinfo.h>

class MarkerDataModel : public QObject
{
    Q_OBJECT
public:
    explicit MarkerDataModel(QObject *parent = nullptr);
    ~MarkerDataModel();

    void readSiteInfo();

    QList<SiteInfo *> getMarkerList() const;

signals:

private:
    QList<SiteInfo*> m_markerList;
};

#endif // MARKERDATAMODEL_H
