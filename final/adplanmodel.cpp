#include<QColor>
#include "adplanmodel.h"

AdPlanModel::AdPlanModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_dbHandler(new DatabaseHandler(this))
{
    m_dbHandler->initDatabase();
    refresh();
}

int AdPlanModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_ads.size();
}

int AdPlanModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_headers.size();
}

QVariant AdPlanModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_ads.size())
        return QVariant();

    const QVariantMap &ad = m_ads.at(index.row());

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0: return ad["id"].toString().left(8) + "..."; // 缩短ID显示
        case 1: return ad["title"].toString();
        case 2: return ad["type"].toString();
        case 3: {
            QString content = ad["content"].toString();
            return content.length() > 20 ? content.left(20) + "..." : content;
        }
        case 4: return ad["duration"].toInt();
        case 5: return ad["priority"].toInt();
        case 6: return ad["last_update"].toString();
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    } else if (role == Qt::BackgroundRole) {
        QString type = ad["type"].toString();
        if (type == "image") return QColor(255, 255, 200); // 浅黄色
        else if (type == "text") return QColor(200, 255, 200); // 浅绿色
    } else if (role == Qt::ToolTipRole) {
        return "完整ID: " + ad["id"].toString() + "\n路径: " + ad["local_path"].toString();
    }

    return QVariant();
}

QVariant AdPlanModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section < m_headers.size())
            return m_headers[section];
    } else {
        return QString::number(section + 1);
    }

    return QVariant();
}

bool AdPlanModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= m_ads.size() || role != Qt::EditRole)
        return false;

    QVariantMap &ad = m_ads[index.row()];
    bool success = false;

    switch (index.column()) {
    case 1: ad["title"] = value.toString(); success = true; break;
    case 2: ad["type"] = value.toString(); success = true; break;
    case 3: ad["content"] = value.toString(); success = true; break;
    case 4: ad["duration"] = value.toInt(); success = true; break;
    case 5: ad["priority"] = value.toInt(); success = true; break;
    }

    if (success) {
        // 更新数据库
        m_dbHandler->updateAd(ad);
        emit dataChanged(index, index, {role});
    }

    return success;
}

Qt::ItemFlags AdPlanModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    if (index.column() >= 1) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void AdPlanModel::refresh()
{
    beginResetModel();
    m_ads = m_dbHandler->getAllAds();
    endResetModel();
}

void AdPlanModel::addAd(const QVariantMap &adData)
{
    beginInsertRows(QModelIndex(), m_ads.size(), m_ads.size());
    m_ads.append(adData);
    m_dbHandler->updateAd(adData);
    endInsertRows();
}

void AdPlanModel::removeAd(int row)
{
    if (row < 0 || row >= m_ads.size())
        return;
    beginRemoveRows(QModelIndex(), row, row);
    QString adId = m_ads[row]["id"].toString();
    m_ads.removeAt(row);

    QVariantMap adData;
    adData["id"] = adId;
    m_dbHandler->updateAd(adData);
    endRemoveRows();
}

QVariantMap AdPlanModel::getAd(int row) const
{
    if (row >= 0 && row < m_ads.size())
        return m_ads[row];
    return QVariantMap();
}
