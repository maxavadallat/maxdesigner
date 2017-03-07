#ifndef PROPERTIESCONTROLLER_H
#define PROPERTIESCONTROLLER_H

#include <QObject>

class ProjectModel;
class ComponentInfo;

//==============================================================================
// Properties Controller Class
//==============================================================================
class PropertiesController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ProjectModel* currentProject READ currentProject NOTIFY currentProjectChanged)
    Q_PROPERTY(ComponentInfo* focusedComponent READ focusedComponent WRITE setFocusedComponent NOTIFY focusedComponentChanged)

    Q_PROPERTY(QString cID READ cID  NOTIFY cIDChanged)
    Q_PROPERTY(QString cObjectName READ cObjectName NOTIFY cObjectNameChanged)

    Q_PROPERTY(QString cX READ cX NOTIFY cXChanged)
    Q_PROPERTY(QString cY READ cY NOTIFY cYChanged)
    Q_PROPERTY(QString cZ READ cZ NOTIFY cZChanged)

    Q_PROPERTY(QString cWidth READ cWidth NOTIFY cWidthChanged)
    Q_PROPERTY(QString cHeight READ cHeight NOTIFY cHeightChanged)

    // ...
public:
    // Property Type
    enum class EPropertyType
    {
        EPTString   = 0,
        EPTInt,
        EPTDouble
    };
    Q_ENUM(EPropertyType)

public:
    // Constructor
    explicit PropertiesController(ProjectModel* aProjectModel = NULL, QObject* aParent = NULL);

    // Get Current Project
    ProjectModel* currentProject();
    // Set Current Project
    void setCurrentProject(ProjectModel* aProjectModel);

    // Get Focused Component
    ComponentInfo* focusedComponent();
    // Set Focused Component
    void setFocusedComponent(ComponentInfo* aComponent);

    // Get Component ID
    QString cID();
    // Request Component ID
    Q_INVOKABLE void requestCID(const QString& aID);

    // Get Component Object Name
    QString cObjectName();
    // Request Component Object Name
    Q_INVOKABLE void requestCObjectName(const QString& aObjectName);

    // Get Component X
    QString cX();
    // Request Component X
    Q_INVOKABLE void requestCX(const QString& aX);

    // Get Component Y
    QString cY();
    // Request Component Y
    Q_INVOKABLE void requestCY(const QString& aY);

    // Get Component Z
    QString cZ();
    // Request Component Z
    Q_INVOKABLE void requestCZ(const QString& aZ);

    // Get Component Width
    QString cWidth();
    // Request Component Width
    Q_INVOKABLE void requestCWidth(const QString& aWidth);

    // Get Component Height
    QString cHeight();
    // Request Component Height
    Q_INVOKABLE void requestCHeight(const QString& aHeight);

    // Add Own Property
    Q_INVOKABLE void addOwnProperty(const QString& aKey, PropertiesController::EPropertyType aType);
    // Remove Own Property
    Q_INVOKABLE void removeOwnProperty(const QString& aKey);
    // Set Property
    Q_INVOKABLE void setProperty(const QString& aKey, const QString& aValue);
    // Clear Property
    Q_INVOKABLE void clearProperty(const QString& aKey);

    // Add Signal
    Q_INVOKABLE void addSignal(const QString& aSignalDef);
    // Remove Signal
    Q_INVOKABLE void removeSignal(const QString& aSignalDef);

    // Add State
    Q_INVOKABLE void addState(const QString& aName);
    // Remove State
    Q_INVOKABLE void removeState(const QString& aName);

    // Add Transition
    Q_INVOKABLE void addTransition(const QString& aFrom, const QString& aTo);
    // Remove Transition
    Q_INVOKABLE void removeTransition(const QString& aFrom, const QString& aTo);

    // ...

    // Destructor
    ~PropertiesController();

signals:
    // Current Project Changed Signal
    void currentProjectChanged(ProjectModel* aProjectModel);
    // Focused Component Changed Signal
    void focusedComponentChanged(ComponentInfo* aComponent);

    // Component ID Changed Signal
    void cIDChanged(const QString& aID);
    // Component Object Name Changed Signal
    void cObjectNameChanged(const QString& aObjectName);
    // Component X Changed Signal
    void cXChanged(const QString& aX);
    // Component Y Changed Signal
    void cYChanged(const QString& aY);
    // Component Z Changed Signal
    void cZChanged(const QString& aZ);
    // Component Width Changed Signal
    void cWidthChanged(const QString& aWidth);
    // Component Height Changed Signal
    void cHeightChanged(const QString& aHeight);

    // ...


public slots:

private:
    // Init
    void init();
    // Clear
    void clear();

private: // Data
    // Project Model
    ProjectModel*   mProject;

    // Focused Component
    ComponentInfo*  mFocusedComponent;

};

#endif // PROPERTIESCONTROLLER_H
