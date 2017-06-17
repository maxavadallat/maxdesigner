#ifndef IDESIGNERTARGETPLUGININTERFACE_H
#define IDESIGNERTARGETPLUGININTERFACE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

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



};


#endif // IDESIGNERTARGETPLUGININTERFACE_H
