#include <QDebug>

#include "settingscontroler.h"
#include "defaultsettings.h"
#include "constants.h"

// Settings Controller Singleton Instance
static SettingsControler* settingsSingleton = NULL;


//==============================================================================
// Get Instance
//==============================================================================
SettingsControler* SettingsControler::getInstance()
{
    // Check Singleton Instance
    if (!settingsSingleton) {
        // Create Singleton Instance
        settingsSingleton = new SettingsControler();
    } else {
        // Inc ref Counter
        settingsSingleton->mRefCounter++;
    }

    return settingsSingleton;
}

//==============================================================================
// Constructor
//==============================================================================
SettingsControler::SettingsControler(QObject* aParent)
    : QObject(aParent)
    , mRefCounter(1)
{

}

//==============================================================================
// Load Settings
//==============================================================================
void SettingsControler::loadSettings()
{

}

//==============================================================================
// Save Settings
//==============================================================================
void SettingsControler::saveSettings()
{

}

//==============================================================================
// Restore Defaults
//==============================================================================
void SettingsControler::restoreDefaults()
{

}


//==============================================================================
// Release
//==============================================================================
void SettingsControler::release()
{
    // Dec Ref Counter
    mRefCounter--;

    // Check Ref Counter
    if (mRefCounter <= 0 && settingsSingleton) {
        // Delete Settings Controller Singleton instance
        delete settingsSingleton;
        settingsSingleton = NULL;
    }
}

//==============================================================================
// Destructor
//==============================================================================
SettingsControler::~SettingsControler()
{

}
