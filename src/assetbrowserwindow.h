#ifndef ASSETBROWSERWINDOW_H
#define ASSETBROWSERWINDOW_H

#include <QMainWindow>
#include <QFileInfo>

namespace Ui {
class AssetBrowserWindow;
}

class MainWindow;
class ProjectModel;
class SettingsController;
class AssetsTreeModel;
class AssetListModel;


//==============================================================================
// Asset Browswer Window Class
//==============================================================================
class AssetBrowserWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(QString currentFile READ currentFile WRITE setCurrentFile NOTIFY currentFileChanged)
    Q_PROPERTY(QString currentDir READ currentDir WRITE setCurrentDir NOTIFY currentDirChanged)
    Q_PROPERTY(QString currentName READ currentName NOTIFY currentNameChanged)
    Q_PROPERTY(int currentSize READ currentSize NOTIFY currentSizeChanged)
    Q_PROPERTY(bool currentIsDir READ currentIsDir NOTIFY currentIsDirChanged)
    Q_PROPERTY(QString lastDirName READ lastDirName NOTIFY lastDirNameChanged)

public:
    // Constructor
    explicit AssetBrowserWindow(MainWindow* aMainWindow, ProjectModel* aProjectModel, QWidget* aParent = NULL);

    // Set Assets Dir
    void setAssetsDir(const QString& aAssetsDir);

    // Get Selected File
    QString currentFile();
    // Set Selected File
    void setCurrentFile(const QString& aFilePath);

    // Get Current Name
    QString currentName();

    // Get Current File Size
    int currentSize();

    // Get Current File Is Dir
    bool currentIsDir();

    // Get Current Dir
    QString currentDir();
    // Set Current Dir
    void setCurrentDir(const QString& aCurrentDir);

    // Get Last Dir Name
    QString lastDirName();

    // Asset Item Selected Callback
    Q_INVOKABLE void assetItemSelected(const QString& aAssetPath);

    // Destructor
    ~AssetBrowserWindow();

signals:
    // Asset Browser Window Closed Signal
    void assetBrowserClosed();
    // Selected File Changed Signel
    void currentFileChanged(const QString& aFilePath);
    // Current Name Changed Signal
    void currentNameChanged(const QString& aCurrentName);
    // Current Size Changed Signal
    void currentSizeChanged(const int& aCurrentSize);
    // Current File Is Dir Changed Signal
    void currentIsDirChanged(const bool& aIsDir);
    // Current Dir Changed Signal
    void currentDirChanged(const QString& aCurrentDir);
    // Last Dir Name Changed Signal
    void lastDirNameChanged(const QString& aLastDir);
    // Asset Selected Signal
    void assetSelected(const QString& aAssetPath);

protected:
    // Init
    void init();
    // Restore UI
    void restoreUI();
    // ShutDown
    void shutDown();
    // Close Window
    void closeWindow();

public: // from QMainWindow
    // Show Event
    virtual void showEvent(QShowEvent* aShowEvent);
    // Close Event
    virtual void closeEvent(QCloseEvent* aCloseEvent);

private slots:
    // Project Assets Dir Changed
    void projectAssetsDirChanged(const QString& aAssetsDir);
    // On Action Close Triggered SLot
    void on_actionClose_triggered();

private:
    // UI
    Ui::AssetBrowserWindow* ui;

    // Main Window
    MainWindow*             mMainWindow;
    // Project Model
    ProjectModel*           mProjectModel;
    // Settings Controller
    SettingsController*     mSettings;
    // Assets Tree Model
    AssetsTreeModel*        mAssetsTreeModel;
    // Asset List Model
    AssetListModel*         mAssetListModel;
    // Current Dir
    QString                 mCurrentDir;
    // Current File Info
    QFileInfo               mCurrentFileInfo;
    // Last Dir Name
    QString                 mLastDirName;
    // Selected Asset
    QString                 mSelectedAsset;
};

#endif // ASSETBROWSERWINDOW_H
