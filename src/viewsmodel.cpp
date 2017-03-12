#include <QDebug>
#include <QJsonDocument>
#include <QDirIterator>

#include "viewsmodel.h"
#include "componentinfo.h"
#include "projectmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ViewsModel::ViewsModel(ProjectModel* aProjectModel, QObject* aParent)
    : QAbstractListModel(aParent)
    , mProjectModel(aProjectModel)
    , mViewsDir(mProjectModel ? mProjectModel->viewsDir() : "")
{
    qDebug() << "ViewsModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ViewsModel::init()
{
    // Load Views
    loadViews();
}

//==============================================================================
// Clear
//==============================================================================
void ViewsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Iterate Through Views List
    while (mViewsList.count() > 0) {
        // Delete Item
        delete mViewsList.takeLast();
    }

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Views
//==============================================================================
void ViewsModel::loadViews()
{
    // Check Components Dir
    if (mViewsDir.isEmpty()) {
        return;
    }

    qDebug() << "ViewsModel::loadViews - mViewsDir: " << mViewsDir;

    // Init Info Filter
    QString infoFilter = QString("*.%1").arg(DEFAULT_JSON_SUFFIX);

    // Init Views Dir Iterator
    QDirIterator vIterator(mViewsDir, QStringList(infoFilter), QDir::Files | QDir::NoDotAndDotDot);

    // Iterate Through Views Dir
    while (vIterator.hasNext()) {
        // Get Next Item
        vIterator.next();
        // Get Item Path
        QString itemPath = vIterator.filePath();

        qDebug() << "ViewsModel::loadViews - itemPath: " << itemPath;

        // Create View Info
        ComponentInfo* newComponent = ComponentInfo::fromInfoFile(itemPath, mProjectModel);
        // Add View
        addView(newComponent);
    }
}

//==============================================================================
// Set Views Dir
//==============================================================================
void ViewsModel::setViewsDir(const QString& aDirPath)
{
    // Check Views Dir
    if (mViewsDir != aDirPath) {
        // Set Views Dir
        mViewsDir = aDirPath;
        // Clear
        clear();
        // Load Views
        loadViews();
    }
}

//==============================================================================
// Add View
//==============================================================================
void ViewsModel::addView(ComponentInfo* aView)
{
    // Check Component
    if (aView) {
        // Get Views Count
        int vCount = mViewsList.count();
        // Get Index Of View
        int vIndex = mViewsList.indexOf(aView);
        // Check View Index
        if (vIndex < 0) {
            // Begin Insert Rows
            beginInsertRows(QModelIndex(), vCount, vCount);
            // Append Component
            mViewsList << aView;
            // End Insert Rows
            endInsertRows();
        }
    }
}

//==============================================================================
// Remove View
//==============================================================================
void ViewsModel::removeView(ComponentInfo* aView, const bool& aDelete)
{
    // Check Component
    if (aView) {
        // Get Views Count
        int vCount = mViewsList.count();
        // Get Index Of Component
        int vIndex = mViewsList.indexOf(aView);
        // Check View Index
        if (vIndex >= 0 && vIndex < vCount) {
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), vIndex, vIndex);
            // Check Deletion
            if (aDelete) {
                // Delete Item
                delete mViewsList.takeAt(vIndex);
            } else {
                // Remove Item
                mViewsList.removeAt(vIndex);
            }
            // End Remove Rows
            endRemoveRows();
        }
    }
}

//==============================================================================
// Get Views Index By Name
//==============================================================================
int ViewsModel::getViewIndex(const QString& aName)
{
    // Get Viewss Count
    int cCount = mViewsList.count();
    // Iterate Through Viewss
    for (int i=0; i<cCount; i++) {
        // Get Views Info
        ComponentInfo* component = mViewsList[i];
        // Check Views Name
        if (component->componentName() == aName) {
            return i;
        }
    }

    return -1;
}

//==============================================================================
// Get Views By Name
//==============================================================================
ComponentInfo* ViewsModel::getView(const QString& aName)
{
    // Get Viewss Count
    int cCount = mViewsList.count();
    // Iterate Through Viewss
    for (int i=0; i<cCount; i++) {
        // Get Views Info
        ComponentInfo* component = mViewsList[i];
        // Check Views Name
        if (component->componentName() == aName) {
            return component;
        }
    }

    return NULL;
}

//==============================================================================
// Get Compoennt By Index
//==============================================================================
ComponentInfo* ViewsModel::getViewByIndex(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mViewsList.count()) {
        return mViewsList[aIndex];
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int ViewsModel::rowCount(const QModelIndex& ) const
{
    return mViewsList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ViewsModel::data(const QModelIndex& index, int role) const
{
    // Get Ro
    int row = index.row();
    // Check Row
    if (row >= 0 && row < mViewsList.count()) {
        // Switch Role
        switch (role) {
            case Qt::DisplayRole:
            case Qt::UserRole:
            case ViewNameRole:  return mViewsList[row]->componentName();
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> ViewsModel::roleNames() const
{
    // Init Role Names
    QHash<int,QByteArray> rNames;

    // Set Role Names
    rNames[ViewNameRole] = "viewName";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ViewsModel::~ViewsModel()
{
    // Clear
    clear();

    // ...

    qDebug() << "ViewsModel deleted.";
}
