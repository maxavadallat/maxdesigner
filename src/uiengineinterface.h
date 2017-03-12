#ifndef UIENGINEINTERFACE_H
#define UIENGINEINTERFACE_H

#include <QObject>

//==============================================================================
// UI Engine Interface Class
//==============================================================================
class UIEngineInterface : public QObject
{
    Q_OBJECT

public:
    // Constructor
    explicit UIEngineInterface(QObject* aParent = NULL) : QObject(aParent) { }

    // Destructor
    ~UIEngineInterface() { }

};

#endif // UIENGINEINTERFACE_H
