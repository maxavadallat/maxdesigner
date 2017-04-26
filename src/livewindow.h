#ifndef LIVEWINDOW_H
#define LIVEWINDOW_H

#include <QMainWindow>

namespace Ui {
class LiveWindow;
}

class MainWindow;
class SettingsController;
class ComponentInfo;

//==============================================================================
// Live Window Class
//==============================================================================
class LiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit LiveWindow(QWidget* aParent = NULL);

    // Set Component
    void setComponent(ComponentInfo* aComponent);

    // Destructor
    ~LiveWindow();

protected:
    // Init
    void init();
    // Restore UI
    void restoreUI();

    // Setup Live
    void setupLive();
    // Shut Down Live
    void shutDown();

private slots:
    // Action Close Triggered Slot
    void on_actionClose_triggered();

private:
    // UI
    Ui::LiveWindow*         ui;
    // Settings Controller
    SettingsController*     mSettings;
    // Component Info
    ComponentInfo*          mComponent;
};

#endif // LIVEWINDOW_H
