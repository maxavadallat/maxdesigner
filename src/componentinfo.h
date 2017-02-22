#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <QObject>
#include <QJsonObject>
#include <QList>
#include <QString>

//==============================================================================
// Component Info Class
//==============================================================================
class ComponentInfo : public QObject, public QJsonObject
{
    Q_OBJECT

//    Q_PROPERTY(QString componentName READ componentName WRITE setComponentName NOTIFY componentNameChanged)
//    Q_PROPERTY(QString componentType READ componentType WRITE setComponentType NOTIFY componentTypeChanged)

public:
    // Create Component From QML File
    static ComponentInfo* fromQML(const QString& aFilePath);

    // Constructor
    explicit ComponentInfo(const QString& aName, const QString& aType, const QString& aParentName = "", QObject* aParent = NULL);

    // Set Parent
    void setParent(ComponentInfo* aParent);

    // Export To QML
    void exportToQML(const QString& aFilePath);

    // Add Propery
    void addProperty(const QString& aName, const QVariant& aValue);

    // Get Property
    QVariant property(const QString& aName);
    // Set Property
    void setProperty(const QString& aName, const QVariant& aValue);

    // Add Child
    void addChild(ComponentInfo* aChild);
    // Remove Child
    void removeChild(ComponentInfo* aChild);

    // Destructor
    ~ComponentInfo();

private:
    // Init
    void init();
    // Clear
    void clear();
    // Load
    void load();
    // Save
    void save();

private: // Data
    // Name
    QString                 mName;
    // Type
    QString                 mType;
    // Parent Name
    QString                 mParentName;
    // Parent
    ComponentInfo*          mParent;
    // Properties
    QJsonObject             mProperties;
    // Children
    QList<ComponentInfo*>   mChildren;
};

#endif // COMPONENTINFO_H
