#include <QDebug>
#include <QFileInfo>

#include "designerfilesortproxy.h"
#include "projecttreemodel.h"

//==============================================================================
// Constructor
//==============================================================================
DesignerFileSortProxy::DesignerFileSortProxy(QObject* aParent)
    : QSortFilterProxyModel(aParent)
{
    qDebug() << "DesignerFileSortProxy created.";

    // ...

//    // Set Filter Role
//    setFilterRole(QFileSystemModel::FileNameRole);

    // Set Sort Role
    setSortRole(QFileSystemModel::FileNameRole);

    // Set Dynamic Sort Filter
    setDynamicSortFilter(true);
}

//==============================================================================
// Less Than
//==============================================================================
bool DesignerFileSortProxy::lessThan(const QModelIndex& aLeft, const QModelIndex& aRight) const
{
    // Check Sort Column
    if (sortColumn() == 0) {
        qDebug() << "#### DesignerFileSortProxy::lessThan";

        // Get File System Model
        QFileSystemModel* fsm = qobject_cast<QFileSystemModel*>(sourceModel());
        // Get Ascending Order
        bool asc = (sortOrder() == Qt::AscendingOrder);

        QFileInfo leftFileInfo  = fsm->fileInfo(aLeft);
        QFileInfo rightFileInfo = fsm->fileInfo(aRight);

        // If DotAndDot move in the beginning
        if (sourceModel()->data(aLeft).toString() == "..") {
            return asc;
        }

        if (sourceModel()->data(aRight).toString() == "..") {
            return !asc;
        }

        // Move dirs upper
        if (!leftFileInfo.isDir() && rightFileInfo.isDir()) {
            return !asc;
        }

        if (leftFileInfo.isDir() && !rightFileInfo.isDir()) {
            return asc;
        }

    }
//    // Get Source Model
//    QFileSystemModel* sm = static_cast<QFileSystemModel*>(sourceModel());

//    // Get Left File Info
//    QFileInfo leftFileInfo(sm->data(aLeft, QFileSystemModel::FilePathRole).toString());
//    // Get Right File Info
//    QFileInfo rightFileInfo(sm->data(aRight, QFileSystemModel::FilePathRole).toString());

//    qDebug() << "DesignerFileSortProxy::lessThan - aLeft: " << leftFileInfo.fileName() << " - aRight: " << rightFileInfo.fileName();

//    // Check If Is Dir
//    if (leftFileInfo.isDir() && !rightFileInfo.isDir()) {
//        return mSortOrder == Qt::DescendingOrder;
//    }

//    // Check If Is Dir
//    if (!leftFileInfo.isDir() && rightFileInfo.isDir()) {
//        return mSortOrder == Qt::AscendingOrder;
//    }

//    if (mSortOrder == Qt::AscendingOrder) {
//        return leftFileInfo.fileName() > rightFileInfo.fileName();
//    }

//    return leftFileInfo.fileName() < rightFileInfo.fileName();

    return QSortFilterProxyModel::lessThan(aLeft, aRight);
}

//==============================================================================
// Sort
//==============================================================================
void DesignerFileSortProxy::sort(int column, Qt::SortOrder order)
{
    qDebug() << "#### DesignerFileSortProxy::sort";


    QSortFilterProxyModel::sort(column, order);
}
