#ifndef DESIGNERFILESORTPROXY_H
#define DESIGNERFILESORTPROXY_H

#include <QObject>
#include <QtQml>
#include <QSortFilterProxyModel>
#include <QQmlExpression>

//==============================================================================
// File Sort Filter Proxy Model
//==============================================================================
class DesignerFileSortProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    // Constructor
    explicit DesignerFileSortProxy(QObject* aParent = NULL);

    // Less Than
    virtual bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const;

    // Sort
    virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
};

// Declare QML Type
QML_DECLARE_TYPE(DesignerFileSortProxy)

#endif // DESIGNERFILESORTPROXY_H
