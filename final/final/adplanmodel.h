#ifndef ADPLANMODEL_H
#define ADPLANMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariantMap>
#include "databasehandler.h"

class AdPlanModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AdPlanModel(QObject *parent = nullptr);
    void addAd(const QVariantMap &adData);
    void removeAd(int row);
    // 重写父类方法
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // 自定义方法
    void refresh();

    QVariantMap getAd(int row) const;

private:
    QList<QVariantMap> m_ads;
    DatabaseHandler *m_dbHandler;
    QStringList m_headers = {"ID", "标题", "类型", "内容", "时长", "优先级", "最后更新"};
};
#endif // ADPLANMODEL_H
