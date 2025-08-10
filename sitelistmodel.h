#ifndef SITELISTMODEL_H
#define SITELISTMODEL_H

#include <QAbstractTableModel>
#include <S
#include <QObject>

class SiteListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SiteListModel(QObject *parent = nullptr);
    ~SiteListModel();

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    int columnCount(const QModelIndex &parent) const;

    void setmanager(SiteManager *a_siteManager);
    void sendSiteNumber(QString a_row);

    void setSiteManager(SiteManager *newSiteManager);

    void resetModel();

signals:
    void successFromSiteListModel(QString a_title,QString a_text);
    void failureFromSiteListModel(QString a_title,QString a_text);
    void sendCountryAndSitetoCountryProxy(QString a_country,QString a_state);

private:
    SiteManager *m_siteManager = nullptr;
};

#endif // SITELISTMODEL_H
