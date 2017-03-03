#include <QDebug>

#include "settingscontroler.h"
#include "settingskeys.h"
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
    , mTracerVisible(DEFAULT_SETTINGS_VALUE_TRACER_VISIBLE)
    , mMainWindowState(DEFAULT_SETTINGS_VALUE_MAIN_WINDOW_STATE)
    , mDesignerMode(DEFAULT_SETTINGS_VALUE_DESIGNER_MODE)

    , mProjectPaneSticky(DEFAULT_SETTINGS_VALUE_PROJECT_PANE_STICKY)
    , mProjectPaneX(0)
    , mProjectPaneY(0)
    , mProjectPaneWidth(DEFAULT_SETTINGS_VALUE_PROJECT_PANE_WIDTH)
    , mProjectPaneHeight(DEFAULT_SETTINGS_VALUE_PROJECT_PANE_HEIGHT)

    , mPropertiesPaneSticky(DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_STICKY)
    , mPropertiesPaneX(0)
    , mPropertiesPaneY(0)
    , mPropertiesPaneWidth(DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_WIDTH)
    , mPropertiesPaneHeight(DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_HEIGHT)

    , mEditorSyntaxHighlight(DEFAULT_SETTINGS_VALUE_EDITOR_SYNTAX_HIGHLIGHT)
    , mEditorLineNumbers(DEFAULT_SETTINGS_VALUE_EDITOR_SHOW_LINE_NUMBERS)
    , mEditorFontSize(DEFAULT_SETTINGS_VALUE_EDITOR_FONT_SIZE)

    , mDirty(false)
{
    qDebug() << "SettingsControler created.";

    // Load Settings
    loadSettings();
}

//==============================================================================
// Load Settings
//==============================================================================
void SettingsControler::loadSettings()
{
    qDebug() << "SettingsControler::loadSettings";

    // Emit Global Update Started Signal
    emit globalUpdateStarted();

    setTracerVisible(mSettings.value(SETTINGS_KEY_TRACER_VISIBLE, DEFAULT_SETTINGS_VALUE_TRACER_VISIBLE).toBool());

    setMainWindowState(mSettings.value(SETTINGS_KEY_MAIN_WINDOW_STATE, DEFAULT_SETTINGS_VALUE_MAIN_WINDOW_STATE).toInt());
    setDesignerMode(mSettings.value(SETTINGS_KEY_DESIGNER_MODE, DEFAULT_SETTINGS_VALUE_DESIGNER_MODE).toString());

    setProjectPaneSticky(mSettings.value(SETTINGS_KEY_PROJECT_PANE_STICKY, DEFAULT_SETTINGS_VALUE_PROJECT_PANE_STICKY).toBool());
    setProjectPaneX(mSettings.value(SETTINGS_KEY_PROJECT_PANE_POS_X, 0).toInt());
    setProjectPaneY(mSettings.value(SETTINGS_KEY_PROJECT_PANE_POS_Y, 0).toInt());
    setProjectPaneWidth(mSettings.value(SETTINGS_KEY_PROJECT_PANE_WIDTH, DEFAULT_SETTINGS_VALUE_PROJECT_PANE_WIDTH).toInt());
    setProjectPaneHeight(mSettings.value(SETTINGS_KEY_PROJECT_PANE_HEIGHT, DEFAULT_SETTINGS_VALUE_PROJECT_PANE_HEIGHT).toInt());

    setPropertiesPaneSticky(mSettings.value(SETTINGS_KEY_PROPERTIES_PANE_STICKY, DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_STICKY).toBool());
    setPropertiesPaneX(mSettings.value(SETTINGS_KEY_PROPERTIES_PANE_POS_X, 0).toInt());
    setPropertiesPaneY(mSettings.value(SETTINGS_KEY_PROPERTIES_PANE_POS_Y, 0).toInt());
    setPropertiesPaneWidth(mSettings.value(SETTINGS_KEY_PROPERTIES_PANE_WIDTH, DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_WIDTH).toInt());
    setPropertiesPaneHeight(mSettings.value(SETTINGS_KEY_PROPERTIES_PANE_HEIGHT, DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_HEIGHT).toInt());

    setEditorSyntaxHighlight(mSettings.value(SETTINGS_KEY_QML_EDITOR_SYNTAX_HIGHLIGHT, DEFAULT_SETTINGS_VALUE_EDITOR_SYNTAX_HIGHLIGHT).toBool());
    setEditorLineNumbers(mSettings.value(SETTINGS_KEY_QML_EDITOR_SHOW_LINE_NUMBERS, DEFAULT_SETTINGS_VALUE_EDITOR_SHOW_LINE_NUMBERS).toBool());
    setEditorFontSize(mSettings.value(SETTINGS_KEY_QML_EDITOR_FONT_SIZE, DEFAULT_SETTINGS_VALUE_EDITOR_FONT_SIZE).toInt());

    // ...

    // Set Dirty
    setDirty(false);

    // Emit Global Update Finished Signal
    emit globalUpdateFinished();
}

//==============================================================================
// Save Settings
//==============================================================================
void SettingsControler::saveSettings()
{
    qDebug() << "SettingsControler::saveSettings";

    mSettings.setValue(SETTINGS_KEY_TRACER_VISIBLE, mTracerVisible);
    mSettings.setValue(SETTINGS_KEY_MAIN_WINDOW_STATE, mMainWindowState);
    mSettings.setValue(SETTINGS_KEY_DESIGNER_MODE, mDesignerMode);

    mSettings.setValue(SETTINGS_KEY_PROJECT_PANE_STICKY, mProjectPaneSticky);
    mSettings.setValue(SETTINGS_KEY_PROJECT_PANE_POS_X, mProjectPaneX);
    mSettings.setValue(SETTINGS_KEY_PROJECT_PANE_POS_Y, mProjectPaneY);
    mSettings.setValue(SETTINGS_KEY_PROJECT_PANE_WIDTH, mProjectPaneWidth);
    mSettings.setValue(SETTINGS_KEY_PROJECT_PANE_HEIGHT, mProjectPaneHeight);

    mSettings.setValue(SETTINGS_KEY_PROPERTIES_PANE_STICKY, mPropertiesPaneSticky);
    mSettings.setValue(SETTINGS_KEY_PROPERTIES_PANE_POS_X, mPropertiesPaneX);
    mSettings.setValue(SETTINGS_KEY_PROPERTIES_PANE_POS_Y, mPropertiesPaneY);
    mSettings.setValue(SETTINGS_KEY_PROPERTIES_PANE_WIDTH, mProjectPaneWidth);
    mSettings.setValue(SETTINGS_KEY_PROPERTIES_PANE_HEIGHT, mPropertiesPaneHeight);

    mSettings.setValue(SETTINGS_KEY_QML_EDITOR_SYNTAX_HIGHLIGHT, mEditorSyntaxHighlight);
    mSettings.setValue(SETTINGS_KEY_QML_EDITOR_SHOW_LINE_NUMBERS, mEditorLineNumbers);
    mSettings.setValue(SETTINGS_KEY_QML_EDITOR_FONT_SIZE, mEditorFontSize);

    // ...

    // Sync Settings
    mSettings.sync();

    // Set Dirty
    setDirty(false);
}

//==============================================================================
// Restore Defaults
//==============================================================================
void SettingsControler::restoreDefaults()
{
    qDebug() << "SettingsControler::restoreDefaults";

    // Emit Global Update Started
    emit globalUpdateStarted();

    setTracerVisible(DEFAULT_SETTINGS_VALUE_TRACER_VISIBLE);
    setMainWindowState(DEFAULT_SETTINGS_VALUE_TRACER_VISIBLE);
    setDesignerMode(DEFAULT_SETTINGS_VALUE_DESIGNER_MODE);

    setProjectPaneSticky(DEFAULT_SETTINGS_VALUE_PROJECT_PANE_STICKY);
    setProjectPaneX(0);
    setProjectPaneY(0);
    setProjectPaneWidth(DEFAULT_SETTINGS_VALUE_PROJECT_PANE_WIDTH);
    setProjectPaneHeight(DEFAULT_SETTINGS_VALUE_PROJECT_PANE_HEIGHT);

    setPropertiesPaneSticky(DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_STICKY);
    setPropertiesPaneX(0);
    setPropertiesPaneY(0);
    setPropertiesPaneWidth(DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_WIDTH);
    setPropertiesPaneHeight(DEFAULT_SETTINGS_VALUE_PROPERTIES_PANE_HEIGHT);

    setEditorSyntaxHighlight(DEFAULT_SETTINGS_VALUE_EDITOR_SYNTAX_HIGHLIGHT);
    setEditorLineNumbers(DEFAULT_SETTINGS_VALUE_EDITOR_SHOW_LINE_NUMBERS);
    setEditorFontSize(DEFAULT_SETTINGS_VALUE_EDITOR_FONT_SIZE);

    // ...

    // Sync Settings
    mSettings.sync();

    // Set Dirty
    setDirty(false);

    // Emit Global Update Finished
    emit globalUpdateFinished();
}

//==============================================================================
// Get Value
//==============================================================================
QVariant SettingsControler::value(const QString& aKey)
{
    return mSettings.value(aKey);
}

//==============================================================================
// Set Value
//==============================================================================
void SettingsControler::setValue(const QString& aKey, const QVariant& aValue)
{
    qDebug() << "SettingsControler::setValue - aKey: " << aKey << " - aValue: " << aValue;

    // Set Value
    mSettings.setValue(aKey, aValue);
    // Sync Values
    mSettings.sync();
}

//==============================================================================
// Clear Value
//==============================================================================
void SettingsControler::clearValue(const QString& aKey)
{
    qDebug() << "SettingsControler::clearValue - aKey: " << aKey;

    // Remove Value
    mSettings.remove(aKey);
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
// Get Tracer Visible
//==============================================================================
bool SettingsControler::tracerVisible()
{
    return mTracerVisible;
}

//==============================================================================
// Set Tracer Visible
//==============================================================================
void SettingsControler::setTracerVisible(const bool& aVisible)
{
    // Check Tracer Visible
    if (mTracerVisible != aVisible) {
        // Set Tracer Visible
        mTracerVisible = aVisible;
        // Emit Tracer Visible Changed Signal
        emit tracerVisibleChanged(mTracerVisible);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Get Main Window State
//==============================================================================
int SettingsControler::mainWindowState()
{
    return mMainWindowState;
}

//==============================================================================
// Set Main Window State
//==============================================================================
void SettingsControler::setMainWindowState(const int& aWindowState)
{
    // Check Main Window State
    if (mMainWindowState != aWindowState) {
        // Set Main Window State
        mMainWindowState = aWindowState;
        // Emit Main Window State changed Signal
        emit mainWindowStateChanged(mMainWindowState);
    }
}

//==============================================================================
// Get Designer Mode
//==============================================================================
QString SettingsControler::designerMode()
{
    return mDesignerMode;
}

//==============================================================================
// Set Designer Mode
//==============================================================================
void SettingsControler::setDesignerMode(const QString& aMode)
{
    // Check Designer Mode
    if (mDesignerMode != aMode) {
        // Set Designer Mode
        mDesignerMode = aMode;
        // Emit Designer Mode Changed Signal
        emit designerModeChanged(mDesignerMode);
    }
}

//==============================================================================
// Get Project Pane Sticky
//==============================================================================
bool SettingsControler::projectPaneSticky()
{
    return mProjectPaneSticky;
}

//==============================================================================
// Set Project Pane Sticky
//==============================================================================
void SettingsControler::setProjectPaneSticky(const bool& aSticky)
{
    // Check Project Pane Sticky
    if (mProjectPaneSticky != aSticky) {
        // Set Project Pane Sticky
        mProjectPaneSticky = aSticky;
        // Emit Project Pane Sticky Changed Signal
        emit projectPaneStickyChanged(mProjectPaneSticky);
    }
}

//==============================================================================
// Get Project Pane Pos X
//==============================================================================
int SettingsControler::projectPaneX()
{
    return mProjectPaneX;
}

//==============================================================================
// Set Project Pane Pos X
//==============================================================================
void SettingsControler::setProjectPaneX(const int& aPosX)
{
    // Check Project Pane X
    if (mProjectPaneX != aPosX) {
        // Set Project Pane X
        mProjectPaneX = aPosX;
        // Emit Project Pane Pos X Changed Signal
        emit projectPaneXChanged(mProjectPaneX);
    }
}

//==============================================================================
// Get Project Pane Pos Y
//==============================================================================
int SettingsControler::projectPaneY()
{
    return mProjectPaneY;
}

//==============================================================================
// Set Project Pane Pos Y
//==============================================================================
void SettingsControler::setProjectPaneY(const int& aPosY)
{
    // Check Project Pane Y
    if (mProjectPaneY != aPosY) {
        // Set Project Pane Y
        mProjectPaneY = aPosY;
        // Emit Project Pane Y Changed Signal
        emit projectPaneYChanged(mProjectPaneY);
    }
}

//==============================================================================
// Get Project Pane Width
//==============================================================================
int SettingsControler::projectPaneWidth()
{
    return mProjectPaneWidth;
}

//==============================================================================
// Set Project Pane Width
//==============================================================================
void SettingsControler::setProjectPaneWidth(const int& aWidth)
{
    // Check Project Pane Width
    if (mProjectPaneWidth != aWidth) {
        // Set Project Pane Width
        mProjectPaneWidth = aWidth;
        // Emit Project Pane Width Changed Signal
        emit projectPaneWidthChanged(mProjectPaneWidth);
    }
}

//==============================================================================
// Get Project Pane Height
//==============================================================================
int SettingsControler::projectPaneHeight()
{
    return mProjectPaneHeight;
}

//==============================================================================
// Set Project Pane Height
//==============================================================================
void SettingsControler::setProjectPaneHeight(const int& aHeight)
{
    // Check Project Pane Height
    if (mProjectPaneHeight != aHeight) {
        // Set Project Pane Height
        mProjectPaneHeight = aHeight;
        // Emit Project Pane Height Changed Signal
        emit projectPaneHeightChanged(mProjectPaneHeight);
    }
}

//==============================================================================
// Get Properties Pane Sticky
//==============================================================================
bool SettingsControler::propertiesPaneSticky()
{
    return mPropertiesPaneSticky;
}

//==============================================================================
// Set Properties Pane Sticky
//==============================================================================
void SettingsControler::setPropertiesPaneSticky(const bool& aSticky)
{
    // Check Properties Pane Sticky
    if (mPropertiesPaneSticky != aSticky) {
        // Set Properties Pane Sticky
        mPropertiesPaneSticky = aSticky;
        // Emit Properties Pane Sticky Changed
        emit propertiesPaneStickyChanged(mPropertiesPaneSticky);
    }
}

//==============================================================================
// Get Properties Pane Pos X
//==============================================================================
int SettingsControler::propertiesPaneX()
{
    return mPropertiesPaneX;
}

//==============================================================================
// Set Properties Pane Pos X
//==============================================================================
void SettingsControler::setPropertiesPaneX(const int& aPosX)
{
    // Check Properties Pane X
    if (mPropertiesPaneX != aPosX) {
        // Set Properties Pane X
        mPropertiesPaneX = aPosX;
        // Emit Properties Pane X Changed Signal
        emit propertiesPaneXChanged(mPropertiesPaneX);
    }
}

//==============================================================================
// Get Properties Pane Pos Y
//==============================================================================
int SettingsControler::propertiesPaneY()
{
    return mPropertiesPaneY;
}

//==============================================================================
// Set Properties Pane Pos Y
//==============================================================================
void SettingsControler::setPropertiesPaneY(const int& aPosY)
{
    // Check Properties Pane Y
    if (mPropertiesPaneY != aPosY) {
        // Set Properties Pane Y
        mPropertiesPaneY = aPosY;
        // Emit Properties Pane Y Changed Signal
        emit propertiesPaneYChanged(mPropertiesPaneY);
    }
}

//==============================================================================
// Get Properties Pane Width
//==============================================================================
int SettingsControler::propertiesPaneWidth()
{
    return mPropertiesPaneWidth;
}

//==============================================================================
// Set Properties Pane Width
//==============================================================================
void SettingsControler::setPropertiesPaneWidth(const int& aWidth)
{
    // Check Properties Pane Width
    if (mPropertiesPaneWidth != aWidth) {
        // Set Properties Pane Width
        mPropertiesPaneWidth = aWidth;
        // Emit Properties Pane Width Changed Signal
        emit propertiesPaneWidthChanged(mPropertiesPaneWidth);
    }
}

//==============================================================================
// Get Properties Pane Height
//==============================================================================
int SettingsControler::propertiesPaneHeight()
{
    return mPropertiesPaneHeight;
}

//==============================================================================
// Set Properties Pane Height
//==============================================================================
void SettingsControler::setPropertiesPaneHeight(const int& aHeight)
{
    // Check Properties Pane Height
    if (mPropertiesPaneHeight != aHeight) {
        // Set Properties Pane Height
        mPropertiesPaneHeight = aHeight;
        // Emit Properties Pane Height Changed Signal
        emit propertiesPaneHeightChanged(mPropertiesPaneHeight);
    }
}

//==============================================================================
// Get Editor Syntax Highlight
//==============================================================================
bool SettingsControler::editorSyntaxHighlight()
{
    return mEditorSyntaxHighlight;
}

//==============================================================================
// Set Editor Syntax Highlight
//==============================================================================
void SettingsControler::setEditorSyntaxHighlight(const bool& aHighlight)
{
    // Check Editor Syntax Highlight
    if (mEditorSyntaxHighlight != aHighlight) {
        // Set Editor Syntax Highlight
        mEditorSyntaxHighlight = aHighlight;
        // Emit Editor Syntax Highlight changed Signal
        emit editorSyntaxHighlightChanged(mEditorSyntaxHighlight);
    }
}

//==============================================================================
// Get Editor Show Line Numbers
//==============================================================================
bool SettingsControler::editorLineNumbers()
{
    return mEditorLineNumbers;
}

//==============================================================================
// Set Editor Show Line Numbers
//==============================================================================
void SettingsControler::setEditorLineNumbers(const bool& aShowLineNumbers)
{
    // Check Editor Show Line Numbers
    if (mEditorLineNumbers != aShowLineNumbers) {
        // Set Editor Show Line Numbers
        mEditorLineNumbers = aShowLineNumbers;
        // Emit Editor Show Line Numbers Changed Signal
        emit editorLineNumbersChanged(mEditorLineNumbers);
    }
}

//==============================================================================
// Get Editor Font Size
//==============================================================================
int SettingsControler::editorFontSize()
{
    return mEditorFontSize;
}

//==============================================================================
// Set Editor Font Size
//==============================================================================
void SettingsControler::setEditorFontSize(const int& aSize)
{
    // Check Editor Font Size
    if (mEditorFontSize != aSize) {
        // Set Editor Font Size
        mEditorFontSize = aSize;
        // Emit Editor Font Size Changed Signal
        emit editorFontSizeChanged(mEditorFontSize);
    }
}

// ...

//==============================================================================
// Get Dirty State
//==============================================================================
bool SettingsControler::dirty()
{
    return mDirty;
}

//==============================================================================
// Set Dirty State
//==============================================================================
void SettingsControler::setDirty(const bool& aDirty)
{
    // Check Dirty State
    if (mDirty != aDirty) {
        qDebug() << "SettingsControler::setDirty - aDirty: " << aDirty;

        // Set Dirty State
        mDirty = aDirty;
        // Emit Dirty State Changed Signal
        emit dirtyChanged(mDirty);
    }
}

//==============================================================================
// Destructor
//==============================================================================
SettingsControler::~SettingsControler()
{
    // Save Settings
    saveSettings();

    qDebug() << "SettingsControler deleted.";
}
