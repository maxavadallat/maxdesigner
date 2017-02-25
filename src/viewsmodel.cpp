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

    // Init Views Dir Iterator
    QDirIterator vIterator(mViewsDir, QStringList(DEFAULT_JSON_SUFFIX), QDir::Files | QDir::NoDotAndDotDot);

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
            case ViewNameRole:  return mViewsList[row]->property(JSON_KEY_COMPONENT_NAME).toString();
        }
    }

    return "";
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
}




















/*

//==============================================================================
// Constructor
//==============================================================================
ViewInfo::ViewInfo(const QString& aName, QObject* aParent)
    : QObject(aParent)
    , mName(aName)
{
    // Init
    init();

    // ...
}

//==============================================================================
// Init
//==============================================================================
void ViewInfo::init()
{
    // Init JSON File
    QFile infoFile(mName);

    // Open File
    if (infoFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read All
        QString infoText = infoFile.readAll();
        // Close File
        infoFile.close();
        // Init JSON Document
        QJsonDocument jsonDoc = QJsonDocument::fromJson(infoText.toUtf8());
        // Set JSON Object
        mInfo = jsonDoc.object();
    } else {
        qWarning() << "ViewInfo::init - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Get Component Name
//==============================================================================
QString ViewInfo::name()
{
    return mName;
}

//==============================================================================
// Save Info
//==============================================================================
void ViewInfo::save()
{
    // Init Info File
    QFile infoFile(mName);

    // Open File For Save
    if (infoFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init JSON Document
        QJsonDocument jsonDoc(mInfo);
        // Init JSON Text
        QString infoText = jsonDoc.toJson();
        // Init Text Stream
        QTextStream textStream(&infoFile);
        // Write Info Text
        textStream << infoText;
        // Flush
        textStream.flush();
        // Close File
        infoFile.close();
    } else {
        qWarning() << "ViewInfo::save - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Destructor
//==============================================================================
ViewInfo::~ViewInfo()
{
    // ...
}
*/
