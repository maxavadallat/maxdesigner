#include <QDebug>
#include <QJsonDocument>
#include "src/viewslistmodel.h"

//==============================================================================
// Constructor
//==============================================================================
ViewsListModel::ViewsListModel(QObject* aParent)
    : QAbstractListModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ViewsListModel::init()
{
    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ViewsListModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Clear File Info List
    mViewList.clear();

    // End Reset Model
    endResetModel();

}

//==============================================================================
// Row Count
//==============================================================================
int ViewsListModel::rowCount(const QModelIndex& ) const
{
    return mViewList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ViewsListModel::data(const QModelIndex& index, int role) const
{
    // Get Ro
    int row = index.row();
    // Check Row
    if (row >= 0 && row < mViewList.count()) {
        // Switch Role
        switch (role) {

        }
    }

    return "";
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> ViewsListModel::roleNames() const
{
    QHash<int,QByteArray> rNames;

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ViewsListModel::~ViewsListModel()
{
    // Clear
    clear();

    // ...
}






















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
