#ifndef SITEVIEWMODEL_H
#define SITEVIEWMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <sitemanager.h>

class SiteViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SiteViewModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void setSiteManager(SiteManager* a_siteManager);

public slots:
    void changeToView();

signals:
    void addSiteSucess(QString,QString);
    void addSiteFailure(QString,QString);

    void removeSiteSucess(QString,QString);
    void removeSiteFailure(QString,QString);
private:
    SiteManager* m_siteManager = nullptr;
};

#endif // SITEVIEWMODEL_H
