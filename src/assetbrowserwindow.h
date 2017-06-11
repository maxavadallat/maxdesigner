#ifndef ASSETBROWSERWINDOW_H
#define ASSETBROWSERWINDOW_H

#include <QMainWindow>

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

    Q_PROPERTY(QString selectedFile READ selectedFile WRITE setSelectedFile NOTIFY selectedFileChanged)
    Q_PROPERTY(QString currentDir READ currentDir WRITE setCurrentDir NOTIFY currentDirChanged)

public:
    // Constructor
    explicit AssetBrowserWindow(MainWindow* aMainWindow, ProjectModel* aProjectModel, QWidget* aParent = NULL);

    // Get Selected File
    QString selectedFile();
    // Set Selected File
    void setSelectedFile(const QString& aFilePath);

    // Get Current Dir
    QString currentDir();
    // Set Current Dir
    void setCurrentDir(const QString& aCurrentDir);

    // Destructor
    ~AssetBrowserWindow();

signals:
    // Asset Browser Window Closed Signal
    void assetBrowserClosed();
    // Selected File Changed Signel
    void selectedFileChanged(const QString& aFilePath);
    // Current Dir Changed Signal
    void currentDirChanged(const QString& aCurrentDir);

protected:
    // Init
    void init();
    // Restore UI
    void restoreUI();
    // ShutDown
    void shutDown();

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
};

#endif // ASSETBROWSERWINDOW_H
