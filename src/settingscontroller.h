#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QObject>
#include <QVariant>
#include <QSettings>

//==============================================================================
// Settings Controller Class
//==============================================================================
class SettingsController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool tracerVisible READ tracerVisible WRITE setTracerVisible NOTIFY tracerVisibleChanged)
    Q_PROPERTY(bool borderVisible READ borderVisible WRITE setBorderVisible NOTIFY borderVisibleChanged)
    Q_PROPERTY(bool slowMotion READ slowMotion WRITE setSlowMotion NOTIFY slowMotionChanged)
    Q_PROPERTY(bool componentNamesVisible READ componentNamesVisible WRITE setComponentNamesVisible NOTIFY componentNamesVisibleChanged)

    Q_PROPERTY(int mainWindowState READ mainWindowState WRITE setMainWindowState NOTIFY mainWindowStateChanged)

    Q_PROPERTY(QString designerMode READ designerMode WRITE setDesignerMode NOTIFY designerModeChanged)

    Q_PROPERTY(bool projectPaneSticky READ projectPaneSticky WRITE setProjectPaneSticky NOTIFY projectPaneStickyChanged)
    Q_PROPERTY(int projectPaneX READ projectPaneX WRITE setProjectPaneX NOTIFY projectPaneXChanged)
    Q_PROPERTY(int projectPaneY READ projectPaneY WRITE setProjectPaneY NOTIFY projectPaneYChanged)
    Q_PROPERTY(int projectPaneWidth READ projectPaneWidth WRITE setProjectPaneWidth NOTIFY projectPaneWidthChanged)
    Q_PROPERTY(int projectPaneHeight READ projectPaneHeight WRITE setProjectPaneHeight NOTIFY projectPaneHeightChanged)

    Q_PROPERTY(bool propertiesPaneSticky READ propertiesPaneSticky WRITE setPropertiesPaneSticky NOTIFY propertiesPaneStickyChanged)
    Q_PROPERTY(int propertiesPaneX READ propertiesPaneX WRITE setPropertiesPaneX NOTIFY propertiesPaneXChanged)
    Q_PROPERTY(int propertiesPaneY READ propertiesPaneY WRITE setPropertiesPaneY NOTIFY propertiesPaneYChanged)
    Q_PROPERTY(int propertiesPaneWidth READ propertiesPaneWidth WRITE setPropertiesPaneWidth NOTIFY propertiesPaneWidthChanged)
    Q_PROPERTY(int propertiesPaneHeight READ propertiesPaneHeight WRITE setPropertiesPaneHeight NOTIFY propertiesPaneHeightChanged)

    Q_PROPERTY(bool editorSyntaxHighlight READ editorSyntaxHighlight WRITE setEditorSyntaxHighlight NOTIFY editorSyntaxHighlightChanged)
    Q_PROPERTY(bool editorLineNumbers READ editorLineNumbers WRITE setEditorLineNumbers NOTIFY editorLineNumbersChanged)
    Q_PROPERTY(int editorFontSize READ editorFontSize WRITE setEditorFontSize NOTIFY editorFontSizeChanged)

    // ...

    Q_PROPERTY(bool dirty READ dirty WRITE setDirty NOTIFY dirtyChanged)

public:
    // Get Instance
    static SettingsController* getInstance();

protected:
    // Constructor
    explicit SettingsController(QObject* aParent = NULL);
    // Destructor
    ~SettingsController();

public:
    // Release
    void release();

    // Load Settings
    void loadSettings();
    // Save Settings
    void saveSettings();
    // Restore Defaults
    void restoreDefaults();

    // Get Value
    QVariant value(const QString& aKey);
    // Set Value
    void setValue(const QString& aKey, const QVariant& aValue);
    // Clear Value
    void clearValue(const QString& aKey);

    // Get Tracer Visible
    bool tracerVisible();
    // Set Tracer Visible
    void setTracerVisible(const bool& aVisible);

    // Get Borders Visible
    bool borderVisible();
    // Set Borders Visible
    void setBorderVisible(const bool& aVisible);

    // Get Slow Motion
    bool slowMotion();
    // Set Slow Motion
    void setSlowMotion(const bool& aSlowMotion);

    // Get Component Names Visible
    bool componentNamesVisible();
    // Set Component Names Visible
    void setComponentNamesVisible(const bool& aNamesVisible);

    // Get Main Window State
    int mainWindowState();
    // Set Main Window State
    void setMainWindowState(const int& aWindowState);

    // Get Designer Mode
    QString designerMode();
    // Set Designer Mode
    void setDesignerMode(const QString& aMode);

    // Get Project Pane Sticky
    bool projectPaneSticky();
    // Set Project Pane Sticky
    void setProjectPaneSticky(const bool& aSticky);

    // Get Project Pane Pos X
    int projectPaneX();
    // Set Project Pane Pos X
    void setProjectPaneX(const int& aPosX);

    // Get Project Pane Pos Y
    int projectPaneY();
    // Set Project Pane Pos Y
    void setProjectPaneY(const int& aPosY);

    // Get Project Pane Width
    int projectPaneWidth();
    // Set Project Pane Width
    void setProjectPaneWidth(const int& aWidth);

    // Get Project Pane Height
    int projectPaneHeight();
    // Set Project Pane Height
    void setProjectPaneHeight(const int& aHeight);

    // Get Properties Pane Sticky
    bool propertiesPaneSticky();
    // Set Properties Pane Sticky
    void setPropertiesPaneSticky(const bool& aSticky);

    // Get Properties Pane Pos X
    int propertiesPaneX();
    // Set Properties Pane Pos X
    void setPropertiesPaneX(const int& aPosX);

    // Get Properties Pane Pos Y
    int propertiesPaneY();
    // Set Properties Pane Pos Y
    void setPropertiesPaneY(const int& aPosY);

    // Get Properties Pane Width
    int propertiesPaneWidth();
    // Set Properties Pane Width
    void setPropertiesPaneWidth(const int& aWidth);

    // Get Properties Pane Height
    int propertiesPaneHeight();
    // Set Properties Pane Height
    void setPropertiesPaneHeight(const int& aHeight);

    // Get Editor Syntax Highlight
    bool editorSyntaxHighlight();
    // Set Editor Syntax Highlight
    void setEditorSyntaxHighlight(const bool& aHighlight);

    // Get Editor Show Line Numbers
    bool editorLineNumbers();
    // Set Editor Show Line Numbers
    void setEditorLineNumbers(const bool& aShowLineNumbers);

    // Get Editor Font Size
    int editorFontSize();
    // Set Editor Font Size
    void setEditorFontSize(const int& aSize);

    // Get Dirty State
    bool dirty();

signals:
    // Tracer Visible Changed Signal
    void tracerVisibleChanged(const bool& aVisible);
    // Border Visible Changed Signal
    void borderVisibleChanged(const bool& aVisible);
    // Slow Motion Changed Signal
    void slowMotionChanged(const bool& aSlowMotion);
    // Component names Visible Changed Signal
    void componentNamesVisibleChanged(const bool& aNamesVisible);
    // Main Window State Changed Signal
    void mainWindowStateChanged(const int& aWindowState);
    // Designer Mode Changed Signal
    void designerModeChanged(const QString& aMode);
    // Project Pane Sticky State Changed Signal
    void projectPaneStickyChanged(const bool& aSticky);
    // Project Pane Pos X Chnaged Signal
    void projectPaneXChanged(const int& aPosX);
    // Project Pane Pos Y Chnaged Signal
    void projectPaneYChanged(const int& aPosY);
    // Project Pane Width Chnaged Signal
    void projectPaneWidthChanged(const int& aWidth);
    // Project Pane Height Chnaged Signal
    void projectPaneHeightChanged(const int& aHeight);
    // Properties Pane Sticky State Chnaged Signal
    void propertiesPaneStickyChanged(const bool& aSticky);
    // Properties Pane Pos X Chnaged Signal
    void propertiesPaneXChanged(const int& aPosX);
    // Properties Pane Pos Y Chnaged Signal
    void propertiesPaneYChanged(const int& aPosY);
    // Properties Pane Width Chnaged Signal
    void propertiesPaneWidthChanged(const int& aWidth);
    // Properties Pane Height Chnaged Signal
    void propertiesPaneHeightChanged(const int& aHeight);
    // Editor Syntax Highlight State Chnaged Signal
    void editorSyntaxHighlightChanged(const bool& aHighlight);
    // Editor Show Line Numbers Chnaged Signal
    void editorLineNumbersChanged(const bool& aShowLineNumbers);
    // EDitor Font Size Chnaged Signal
    void editorFontSizeChanged(const int& aSize);

    // ...

    // Dirty State Changed Signal
    void dirtyChanged(const bool& aDirty);

    // Global Update Started Signal
    void globalUpdateStarted();
    // Global Update Finished Signal
    void globalUpdateFinished();

private:
    // Set Dirty State
    void setDirty(const bool& aDirty);

private:
    // Settings
    QSettings       mSettings;
    // Reference Counter
    int             mRefCounter;

    // Tracer Visible
    bool            mTracerVisible;
    // Border Visible
    bool            mBorderVisible;
    // Component Names Visible
    bool            mComponentNamesVisible;
    // Slow Motion
    bool            mSlowMotion;

    // Main Window State
    int             mMainWindowState;

    // Designer Mode
    QString         mDesignerMode;

    // Project Pane Sticky
    bool            mProjectPaneSticky;
    // Project Pane Pos X
    int             mProjectPaneX;
    // Project Pane Pos Y
    int             mProjectPaneY;
    // Project Pane Width
    int             mProjectPaneWidth;
    // Project Pane Height
    int             mProjectPaneHeight;

    // Properties Pane Sticky
    bool            mPropertiesPaneSticky;
    // Properties Pane X
    int             mPropertiesPaneX;
    // Properties Pane Y
    int             mPropertiesPaneY;
    // Properties Pane Width
    int             mPropertiesPaneWidth;
    // Properties Pane Height
    int             mPropertiesPaneHeight;

    // Editor Syntax Highlight
    bool            mEditorSyntaxHighlight;
    // Editor Line Numbers
    bool            mEditorLineNumbers;
    // Editor Font Size
    int             mEditorFontSize;

    // ...

    // Settings Dirty State
    bool            mDirty;
};

#endif // SETTINGSCONTROLLER_H
