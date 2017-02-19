#include <QDebug>
#include <QJsonDocument>
#include "src/basecomponentsmodel.h"

//==============================================================================
// Constructor
//==============================================================================
BaseComponentsModel::BaseComponentsModel(QObject* aParent)
    : QAbstractListModel(aParent)
{

}

//==============================================================================
// Init
//==============================================================================
void BaseComponentsModel::init()
{

}

//==============================================================================
// Clear
//==============================================================================
void BaseComponentsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Clear File Info List
    mBaseComponentList.clear();

    // End Reset Model
    endResetModel();

}

//==============================================================================
// Row Count
//==============================================================================
int BaseComponentsModel::rowCount(const QModelIndex& ) const
{
    return mBaseComponentList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant BaseComponentsModel::data(const QModelIndex& index, int role) const
{
    // Get Ro
    int row = index.row();
    // Check Row
    if (row >= 0 && row < mBaseComponentList.count()) {
        // Switch Role
        switch (role) {

        }
    }

    return "";
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> BaseComponentsModel::roleNames() const
{
    QHash<int,QByteArray> rNames;

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
BaseComponentsModel::~BaseComponentsModel()
{
    // Clear
    clear();

    // ...
}






















//==============================================================================
// Constructor
//==============================================================================
BaseComponentInfo::BaseComponentInfo(const QString& aName, QObject* aParent)
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
void BaseComponentInfo::init()
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
        qWarning() << "BaseComponentInfo::init - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Get Component Name
//==============================================================================
QString BaseComponentInfo::name()
{
    return mName;
}

//==============================================================================
// Save Info
//==============================================================================
void BaseComponentInfo::save()
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
        qWarning() << "BaseComponentInfo::save - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Destructor
//==============================================================================
BaseComponentInfo::~BaseComponentInfo()
{
    // ...
}
