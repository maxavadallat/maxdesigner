#ifndef LIVEWINDOW_H
#define LIVEWINDOW_H

#include <QMainWindow>

namespace Ui {
class LiveWindow;
}

class MainWindow;
class SettingsController;

//==============================================================================
// Live Window Class
//==============================================================================
class LiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit LiveWindow(QWidget* aParent = NULL);
    // Destructor
    ~LiveWindow();

protected:
    // Init
    void init();
    // Restore UI
    void restoreUI();

private:
    // UI
    Ui::LiveWindow*         ui;
    // Settings Controller
    SettingsController*     mSettings;
};

#endif // LIVEWINDOW_H
