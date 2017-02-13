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

signals:


private:
    // Settings
    QSettings       mSettings;
    // Reference Counter
    int             mRefCounter;
};

#endif // SETTINGSCONTROLER_H
