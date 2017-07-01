#ifndef FLOWWINDOW_H
#define FLOWWINDOW_H

#include <QMainWindow>

namespace Ui {
class FlowWindow;
}

class SettingsController;
class MainWindow;
class ProjectModel;

//==============================================================================
// UI Flow Window
//==============================================================================
class FlowWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit FlowWindow(ProjectModel* aProject, MainWindow* aMainWindow, QWidget* aParent = NULL);

    // Destructor
    ~FlowWindow();

signals:
    // Flow View Closed Signal
    void flowViewClosed();

protected:
    // Init
    void init();
    // Restore UI
    void restoreUI();

    // Shut Down Live
    void shutDown();

public: // from QMainWindow
    // Show Event
    virtual void showEvent(QShowEvent* aShowEvent);
    // Close Event
    virtual void closeEvent(QCloseEvent* aCloseEvent);

private slots:
    // On Actin Close Triggered Slot
    void on_actionClose_triggered();

private:
    // UI
    Ui::FlowWindow*         ui;

    // Settings Controller
    SettingsController*     mSettings;
    // Main Window
    MainWindow*             mMainWindow;
    // Project Model
    ProjectModel*           mProject;
};

#endif // FLOWWINDOW_H
