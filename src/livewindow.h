#ifndef LIVEWINDOW_H
#define LIVEWINDOW_H

#include <QMainWindow>

namespace Ui {
class LiveWindow;
}

class MainWindow;
class SettingsController;
class ProjectModel;
class ComponentInfo;
class PropertiesController;

//==============================================================================
// Live Window Class
//==============================================================================
class LiveWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent NOTIFY currentComponentChanged)

    Q_PROPERTY(QString liveMain READ liveMain NOTIFY liveMainChanged)

    Q_PROPERTY(int screenWidth READ screenWidth NOTIFY screenWidthChanged)
    Q_PROPERTY(int screenHeight READ screenHeight NOTIFY screenHeightChanged)

    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

public:
    // Constructor
    explicit LiveWindow(ProjectModel* aProject, MainWindow* aMainWindow, QWidget* aParent = NULL);

    // Get Current Component
    ComponentInfo* currentComponent();

    // Get Live Main File Name
    QString liveMain();

    // Get Screen Width
    int screenWidth();
    // Get Screen height
    int screenHeight();

    // Get Busy State
    bool busy();

    // Destructor
    ~LiveWindow();

public slots:
    // Set Component
    void setComponent(ComponentInfo* aComponent);

signals:
    // Load Content Signal
    void loadContent(const QString& liveContent);
    // Clear Content Signal
    void clearContent();
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);
    // Live Main File Name Changed Signal
    void liveMainChanged(const QString& aLiveMain);
    // Screen Width Changed Signal
    void screenWidthChanged(const int& aWidth);
    // Screen Height changed Signal
    void screenHeightChanged(const int& aHeight);
    // Busy State Changed Signal
    void busyChanged(const bool& aBusy);

    // Live View Closed Signal
    void liveViewClosed();

protected:
    // Init
    void init();
    // Restore UI
    void restoreUI();

    // Set Live Main File Name
    void setLiveMain(const QString& aLiveMain);

    // Setup Live
    void setupLive();
    // Shut Down Live
    void shutDown();

    // Trim Component Cache
    void trimQMLComponentCache();
    // Clear Component Cache
    void clearQMLComponentCache();

    // Toggle Show Dashboard
    void toggleDashBoard();
    // Set Busy
    void setBusy(const bool& aBusy);

public: // from QMainWindow
    // Show Event
    virtual void showEvent(QShowEvent* aShowEvent);
    // Close Event
    virtual void closeEvent(QCloseEvent* aCloseEvent);

private slots:
    // Component Updated Slot
    void componentUpdated();
    // On Action Show Dashboard Triggered Slot
    void on_actionShowDashboard_triggered();
    // Action Close Triggered Slot
    void on_actionClose_triggered();

private:
    // UI
    Ui::LiveWindow*         ui;
    // Settings Controller
    SettingsController*     mSettings;
    // Main Window
    MainWindow*             mMainWindow;
    // Project Model
    ProjectModel*           mProjectModel;
    // Properties Controller
    PropertiesController*   mPropertiesController;
    // Component Info
    ComponentInfo*          mComponent;
    // Live File name
    QString                 mLiveFileName;
    // Busy
    bool                    mBusy;
};

#endif // LIVEWINDOW_H
