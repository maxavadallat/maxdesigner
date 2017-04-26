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
    //loadViews();
}

//==============================================================================
// Clear
//==============================================================================
void ViewsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Get Keys Count
    int bckCount = rowCount();

    //qDebug() << "ViewsModel::clear - count: " << bckCount;

    // Iterate Thru Keys
    for (int i=0; i<bckCount; i++) {
        // Get Component Info
        ComponentInfo* component = mViews[mViews.keys()[i]];
        // Delete Component
        delete component;
    }

    // Clear
    mViews.clear();

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

    //qDebug() << "ViewsModel::loadViews - mViewsDir: " << mViewsDir;

    // Init Info Filter
    QString infoFilter = QString("*.%1").arg(DEFAULT_JSON_SUFFIX);

    // Init Views Dir Iterator
    QDirIterator vIterator(mViewsDir, QStringList(infoFilter), QDir::Files | QDir::NoDotAndDotDot);

    // Iterate Through Views Dir
    while (vIterator.hasNext()) {
        // Get Next Item
        vIterator.next();

        // Get Item NAme
        QString itemName = vIterator.fileInfo().baseName();

        // Check If Component HAs Been Already Loaded
        if (mViews.keys().indexOf(itemName) < 0) {
            // Get Item Path
            QString itemPath = vIterator.filePath();
            //qDebug() << "ViewsModel::loadViews - itemPath: " << itemPath;
            // Create View Info
            ComponentInfo* newComponent = ComponentInfo::fromInfoFile(itemPath, mProjectModel);
            // Add View
            addView(newComponent);
        } else {
            qDebug() << "ViewsModel::loadViews - itemName: " << itemName << " - View Already Added.";
        }
    }
}

//==============================================================================
// Update Components
//==============================================================================
void ViewsModel::updateBaseComponents()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Get Base Components Count
    int bcCount = rowCount();
    // Iterate Through Base Components
    for (int i=0; i<bcCount; i++) {
        // Get Component
        ComponentInfo* component = getViewByIndex(i);
        // Check Base Name
        if (component && !component->mBaseName.isEmpty() && !component->mBase) {
            //qDebug() << "ViewsModel::updateBaseComponents - name: " << component->mName;
            // Set Base Component
            component->mBase = mProjectModel->getComponentByName(component->mBaseName);
        }
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
bool ViewsModel::addView(ComponentInfo* aView)
{
    // Check Component
    if (aView) {
        // Get Component Name
        QString cName = aView->mName;

        // Check Base Component
        ComponentInfo* component = mViews.value(cName);

        // Check Component
        if (component) {
            qWarning() << "ViewsModel::addBaseComponent - name: " << cName << " - ALREADY EXITS!";
            return false;
        }

        //qDebug() << "ViewsModel::addView - name: " << cName;

        // Add Base Component To Base Component Map
        mViews[cName] = aView;
        // Get New Key Index
        int newIndex = mViews.keys().indexOf(cName);

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), newIndex, newIndex);

        // End Insert Rows
        endInsertRows();

        return true;
    }

    return false;
}

//==============================================================================
// Remove View
//==============================================================================
bool ViewsModel::removeView(const int& aIndex)
{
    // Get Base Components Count
    int bcCount = rowCount();
    // Check Index
    if (aIndex >= 0 && aIndex < bcCount) {
        // Get Component
        ComponentInfo* component = getViewByIndex(aIndex);
        // Get Info File
        QFile ciFile(component->mInfoPath);
        // Get Key
        QString bcKey = mViews.keys()[aIndex];
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Key
        mViews.remove(bcKey);
        // Delete Component
        delete component;
        // Delete Component Info File
        if (!ciFile.remove()) {
            qWarning() << "ViewsModel::removeBaseComponent - ERROR REMOVING FILE!";
        }
        // End Remove Rows
        endRemoveRows();

        return true;
    }

    return false;
}

//==============================================================================
// Get Views Index By Name
//==============================================================================
int ViewsModel::getViewIndex(const QString& aName)
{
    return mViews.keys().indexOf(aName);
}

//==============================================================================
// Get Views By Name
//==============================================================================
ComponentInfo* ViewsModel::getView(const QString& aName, const bool& aPreload)
{
    // Check Name
    if (aName.isEmpty()) {
        return NULL;
    }

    // Get View Component Info
    ComponentInfo* vInfo = mViews.value(aName);

    // Check View Component Info
    if (vInfo) {
        return vInfo;
    }

    // Check Preload
    if (aPreload) {
        // Get Full File Path
        QString vFilePath = QString("%1/%2.%3").arg(mViewsDir).arg(aName).arg(DEFAULT_JSON_SUFFIX);

        qDebug() << "ViewsModel::getView - vFilePath: " << vFilePath << " - Trying to Load...";

        // Try To Load Component From Info File
        vInfo = ComponentInfo::fromInfoFile(vFilePath, mProjectModel);

        // Check Base Component Info
        if (vInfo) {
            // Add View Component
            addView(vInfo);
        }
    }

    return vInfo;
}

//==============================================================================
// Get Compoennt By Index
//==============================================================================
ComponentInfo* ViewsModel::getViewByIndex(const int& aIndex)
{
    if (aIndex >= 0 && aIndex < rowCount()) {
        return mViews[mViews.keys()[aIndex]];
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int ViewsModel::rowCount(const QModelIndex& ) const
{
    return mViews.keys().count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ViewsModel::data(const QModelIndex& index, int role) const
{
    // Get Row Index
    int vRow = index.row();
    // Check Row
    if (vRow >= 0 && vRow < rowCount()) {
        // Get Component Info
        ComponentInfo* component = mViews[mViews.keys()[vRow]];
        // Switch Role
        switch (role) {
            case Qt::DisplayRole:
            case Qt::UserRole:
            case EVRName:  return component->mName;
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
    rNames[EVRName] = "vName";

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
