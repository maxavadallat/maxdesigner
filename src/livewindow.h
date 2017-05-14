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

//==============================================================================
// Live Window Class
//==============================================================================
class LiveWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(int screenWidth READ screenWidth NOTIFY screenWidthChanged)
    Q_PROPERTY(int screenHeight READ screenHeight NOTIFY screenHeightChanged)

public:
    // Constructor
    explicit LiveWindow(ProjectModel* aProject, QWidget* aParent = NULL);

    // Get Screen Width
    int screenWidth();
    // Get Screen height
    int screenHeight();

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
    // Screen Width Changed Signal
    void screenWidthChanged(const int& aWidth);
    // Screen Height changed Signal
    void screenHeightChanged(const int& aHeight);

protected:
    // Init
    void init();
    // Restore UI
    void restoreUI();

    // Setup Live
    void setupLive();
    // Shut Down Live
    void shutDown();

    // Set Content
    void setLiveContent();

    // Generate Live Code For Base Components
    void generateLiveCodeForBaseComponents();

public: // from QMainWindow
    // Show Event
    virtual void showEvent(QShowEvent* aShowEvent);
    // Close Event
    virtual void closeEvent(QCloseEvent* aCloseEvent);

private slots:
    // Component Updated Slot
    void componentUpdated();
    // Action Close Triggered Slot
    void on_actionClose_triggered();

private:
    // UI
    Ui::LiveWindow*         ui;
    // Settings Controller
    SettingsController*     mSettings;
    // Project Model
    ProjectModel*           mProjectModel;
    // Component Info
    ComponentInfo*          mComponent;
    // Live File name
    QString                 mLiveFileName;
};

#endif // LIVEWINDOW_H
