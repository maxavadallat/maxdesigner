#include <QDebug>
#include <QJsonDocument>
#include "src/componentslistmodel.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentsListModel::ComponentsListModel(QObject* aParent)
    : QAbstractListModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentsListModel::init()
{

}

//==============================================================================
// Clear
//==============================================================================
void ComponentsListModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Clear File Info List
    mComponentList.clear();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentsListModel::rowCount(const QModelIndex& ) const
{
    return mComponentList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentsListModel::data(const QModelIndex& index, int role) const
{
    // Ger Row
    int row = index.row();

    // Check Row
    if (row >= 0 && row < mComponentList.count()) {
        // Switch Role
        switch (role) {

        }
    }

    return "";
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> ComponentsListModel::roleNames() const
{
    QHash<int,QByteArray> rNames;

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentsListModel::~ComponentsListModel()
{
    // Clear
    clear();
}



















//==============================================================================
// Constructor
//==============================================================================
ComponentInfo::ComponentInfo(const QString& aName, QObject* aParent)
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
void ComponentInfo::init()
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
        qWarning() << "ComponentInfo::init - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Get Component Name
//==============================================================================
QString ComponentInfo::name()
{
    return mName;
}

//==============================================================================
// Save Info
//==============================================================================
void ComponentInfo::save()
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
        qWarning() << "ComponentInfo::save - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Destructor
//==============================================================================
ComponentInfo::~ComponentInfo()
{
    // ...
}
