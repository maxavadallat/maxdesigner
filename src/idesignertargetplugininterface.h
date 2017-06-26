#ifndef IDESIGNERTARGETPLUGININTERFACE_H
#define IDESIGNERTARGETPLUGININTERFACE_H

#include <QString>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//==============================================================================
// Designer Target Plugin Interface
//==============================================================================
class IDesignerTargetPluginInterface : public QObject
{
public:
    // Constructor
    explicit IDesignerTargetPluginInterface(QObject* aParent = NULL) : QObject(aParent) { }
    // Destructor
    virtual ~IDesignerTargetPluginInterface() { }

public:

    // Import Components

    // Export Components

    // Get Target Name
    virtual QString targetName() = 0;
    // Get Version Info
    virtual QString version() = 0;

    // Export Base Components
    virtual void exportBaseComponents(const QString& aBaseComponentsPath) = 0;
    // Export Components
    virtual void exportComponents(const QString& aComponentsPath) = 0;
    // Export Views
    virtual void exportViews(const QString& aViewsPath) = 0;
    // Export Data Sources
    virtual void exportDataSources(const QString& aDataSourcesPath) = 0;

    // ...

};


#endif // IDESIGNERTARGETPLUGININTERFACE_H
