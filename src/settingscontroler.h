#ifndef SETTINGSCONTROLER_H
#define SETTINGSCONTROLER_H

#include <QObject>
#include <QSettings>

//==============================================================================
// Settings Controller Class
//==============================================================================
class SettingsControler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool tracerVisible READ tracerVisible WRITE setTracerVisible NOTIFY tracerVisibleChanged)

//    Q_PROPERTY(bool showProjectPane READ showProjectPane WRITE setShowProjectPane NOTIFY showProjectPaneChanged)
//    Q_PROPERTY(bool showPropertiesPane READ showPropertiesPane WRITE setShowPropertiesPane NOTIFY showPropertiesPaneChanged)

//    Q_PROPERTY(QPoint projectPanePos READ projectPanePos WRITE setProjectPanePos NOTIFY projectPanePosChanged)
//    Q_PROPERTY(QPoint propertiesPanePos READ propertiesPanePos WRITE setPropertiesPanePos NOTIFY propertiesPanePosChanged)


public:
    // Get Instance
    static SettingsControler* getInstance();

protected:
    // Constructor
    explicit SettingsControler(QObject* aParent = NULL);
    // Destructor
    ~SettingsControler();

public:

    // Release
    void release();

    // Load Settings
    void loadSettings();
    // Save Settings
    void saveSettings();
    // Restore Defaults
    void restoreDefaults();

    // Get Tracer Visible
    bool tracerVisible();
    // Set Tracer Visible
    void setTracerVisible(const bool& aVisible);

signals:

    // Tracer Visible Changed Signal
    void tracerVisibleChanged(const bool& aVisible);

private:
    // Settings
    QSettings       mSettings;
    // Reference Counter
    int             mRefCounter;

    // Tracer Visible
    bool            mTracerVisible;
};

#endif // SETTINGSCONTROLER_H
