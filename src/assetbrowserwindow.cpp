#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>

#include "assetbrowserwindow.h"
#include "ui_assetbrowserwindow.h"
#include "mainwindow.h"
#include "projectmodel.h"
#include "designerimageprovider.h"
#include "constants.h"
#include "settingscontroller.h"
#include "assetstreemodel.h"
#include "assetlistmodel.h"

//==============================================================================
// Constructor
//==============================================================================
AssetBrowserWindow::AssetBrowserWindow(MainWindow* aMainWindow, ProjectModel* aProjectModel, QWidget* aParent)
    : QMainWindow(aParent)
    , ui(new Ui::AssetBrowserWindow)
    , mMainWindow(aMainWindow)
    , mProjectModel(aProjectModel)
    , mSettings(SettingsController::getInstance())
    , mAssetsTreeModel(NULL)
    , mAssetListModel(NULL)
    , mCurrentDir("")
    , mLastDirName("")
    , mSelectedAsset("")
{
    qDebug() << "AssetBrowserWindow created.";

    // Setup UI
    ui->setupUi(this);
    // Init
    init();
    // Restore UI
    restoreUI();
}

//==============================================================================
// Init
//==============================================================================
void AssetBrowserWindow::init()
{
    qDebug() << "AssetBrowserWindow::init";

    // Check Assets Tree Model
    if (!mAssetsTreeModel) {
        // Create Assets Tree Model
        mAssetsTreeModel = new AssetsTreeModel();
    }

    // Check Asset List Model
    if (!mAssetListModel) {
        // Create Assrt List Model
        mAssetListModel = new AssetListModel();
    }

    // Init Current File Info
    mCurrentFileInfo = mProjectModel ? mProjectModel->assetsDir() : QFileInfo(QDir::homePath());
    // Set Current Dir
    mCurrentDir = mCurrentFileInfo.absoluteFilePath();
    // Set Last Dir Name
    mLastDirName = mCurrentFileInfo.fileName();

    // Check Project Model
    if (mProjectModel) {
        // Set Current Path For Tree Model
        mAssetsTreeModel->setCurrentPath(mProjectModel->assetsDir());
        // Set Assets Dir
        mAssetListModel->setAssetsDir(mProjectModel->assetsDir());
    }

    // Set Context Properties
    QQmlContext* ctx = ui->assetsQuickWidget->rootContext();

    // Set Context Properties - Main Controller
    ctx->setContextProperty(DEFAULT_ASSET_BROWSER_CONTROLLER_NAME, this);

    // Set Context Properties - Settings
    ctx->setContextProperty(DEFAULT_GLOBAL_SETTINGS_CONTROLLER, mSettings);

    // Set Context Properties - Asset List Model
    ctx->setContextProperty(MODEL_NAME_ASSETS_TREE, mAssetsTreeModel);

    // Set Context Properties - Asset List Model
    ctx->setContextProperty(MODEL_NAME_ASSETS_LIST, mAssetListModel);

    // Get Engine
    QQmlEngine* engine = ui->assetsQuickWidget->engine();

    // Add Image Provider
    engine->addImageProvider(QLatin1String(DEFAULT_IMAGE_PROVIDER_ID), new DesignerImageProvider());

    // Set Resize Mode
    ui->assetsQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Set Source
    ui->assetsQuickWidget->setSource(QUrl(DEFAULT_ASSETBROWSER_QMLFILE_URL));

    // Set Focuse Policy
    ui->assetsQuickWidget->setFocusPolicy(Qt::StrongFocus);

    // ...

}

//==============================================================================
// Restore UI
//==============================================================================
void AssetBrowserWindow::restoreUI()
{
    qDebug() << "AssetBrowserWindow::restoreUI";

    // Set Window Title
    setWindowTitle(QString("Asset Browser - %1").arg(mCurrentDir));

    // ...

    // Set Last Width & Height

    // ...

    // Set Always On top
    setWindowFlags(Qt::WindowStaysOnTopHint);

}

//==============================================================================
// ShutDown
//==============================================================================
void AssetBrowserWindow::shutDown()
{
    qDebug() << "AssetBrowserWindow::shutDown";

    // ...
}

//==============================================================================
// Close Window
//==============================================================================
void AssetBrowserWindow::closeWindow()
{
    // ...

    // Normalize Window
    showNormal();
    // Close
    close();
}

//==============================================================================
// Set Assets Dir
//==============================================================================
void AssetBrowserWindow::setAssetsDir(const QString& aAssetsDir)
{
    // Check Asset Tree Model
    if (mAssetsTreeModel) {
        // Set Current Path
        mAssetsTreeModel->setCurrentPath(aAssetsDir);
    }

    // Check Assets List Model
    if (mAssetListModel) {
        // Set Assets Dir
        mAssetListModel->setAssetsDir(aAssetsDir);
    }
}

//==============================================================================
// Get Selected File
//==============================================================================
QString AssetBrowserWindow::currentFile()
{
    return mCurrentFileInfo.absoluteFilePath();
}

//==============================================================================
// Set Selected File
//==============================================================================
void AssetBrowserWindow::setCurrentFile(const QString& aFilePath)
{
    // Init Clean Path
    QString cleanPath = QDir::cleanPath(aFilePath);

    // Check Current File Info
    if (mCurrentFileInfo.absoluteFilePath() != cleanPath) {
        qDebug() << "AssetBrowserWindow::setCurrentFile - cleanPath: " << cleanPath;

        // Set Current File Info
        mCurrentFileInfo = QFileInfo(cleanPath);
        // Emit Current File Changed Signal
        emit currentFileChanged(mCurrentFileInfo.absoluteFilePath());
        // Emit Current name Changed Signal
        emit currentNameChanged(currentName());
        // Emit Current Size Changed
        emit currentSizeChanged(currentSize());
        // Emit Current Is Dir Changed Signal
        emit currentIsDirChanged(currentIsDir());
    }
}

//==============================================================================
// Get Current Name
//==============================================================================
QString AssetBrowserWindow::currentName()
{
    return mCurrentFileInfo.fileName();
}

//==============================================================================
// Get Current File Size
//==============================================================================
int AssetBrowserWindow::currentSize()
{
    return mCurrentFileInfo.size() / 1024;
}

//==============================================================================
// Get Current File Is Dir
//==============================================================================
bool AssetBrowserWindow::currentIsDir()
{
    return mCurrentFileInfo.isDir();
}

//==============================================================================
// Get Current Dir
//==============================================================================
QString AssetBrowserWindow::currentDir()
{
    return mAssetListModel ? mAssetListModel->currentDir() : "";
}

//==============================================================================
// Set Current Dir
//==============================================================================
void AssetBrowserWindow::setCurrentDir(const QString& aCurrentDir)
{
    // Check Assets List Model
    if (mAssetListModel) {
        // Check New Current Dir
        if (aCurrentDir == QString("%1/..").arg(mAssetListModel->mAssetsDir)) {
            // Lock To Assets Dir

            return;
        }
    }

    // Init Clean Path
    QString cleanPath = QDir::cleanPath(aCurrentDir);
    // Check Clean Path
    if (cleanPath == "/.."){
        // Adjust Clean Path
        cleanPath = "/";
    }

    // Check Current Dir
    if (mCurrentDir != cleanPath) {
        qDebug() << "AssetBrowserWindow::setCurrentDir - cleanPath: " << cleanPath;

        // Set Last Dir Name
        mLastDirName = QFileInfo(mCurrentDir).fileName();

        // Emit Last Dir Name Changed Signal
        emit lastDirNameChanged(mLastDirName);

        // Set Current Dir
        mCurrentDir = cleanPath;

        // Set Window Title
        setWindowTitle(QString("Asset Browser - %1").arg(mCurrentDir));

    //    // Check Assets Tree Model
    //    if (mAssetsTreeModel) {
    //        // Set Current Dir
    //        mAssetsTreeModel->setCurrentPath(aCurrentDir);
    //    }

        // Check Assets List Model
        if (mAssetListModel) {
            // Set Current Dir
            mAssetListModel->setCurrentDir(mCurrentDir);
        }

        // ...

        // Emit Current Dir Changed
        emit currentDirChanged(mCurrentDir);
    }
}

//==============================================================================
// Get Last Dir Name
//==============================================================================
QString AssetBrowserWindow::lastDirName()
{
    return mLastDirName;
}

//==============================================================================
// Asset Item Selected Callback
//==============================================================================
void AssetBrowserWindow::assetItemSelected(const QString& aAssetPath)
{
    // Set Selected Asset
    mSelectedAsset = aAssetPath;

    qDebug() << "AssetBrowserWindow::assetItemSelected - mSelectedAsset: " << mSelectedAsset;

    // Emit Asset Selected Signal
    emit assetSelected(mSelectedAsset);

    // Close Window
    closeWindow();

    // ...
}

//==============================================================================
// Show Event
//==============================================================================
void AssetBrowserWindow::showEvent(QShowEvent* aShowEvent)
{
    QMainWindow::showEvent(aShowEvent);

    // ...
}

//==============================================================================
// Close Event
//==============================================================================
void AssetBrowserWindow::closeEvent(QCloseEvent* aCloseEvent)
{
    QMainWindow::closeEvent(aCloseEvent);

    // Shut Down
    shutDown();

    qDebug() << "AssetBrowserWindow::closeEvent - windowSize: " << size();

    // Save Size

    // ...

    // Emit Asset Browser Window Closed Signal
    emit assetBrowserClosed();
}

//==============================================================================
// Project Assets Dir Changed
//==============================================================================
void AssetBrowserWindow::projectAssetsDirChanged(const QString& aAssetsDir)
{
    // Set Current Dir
    setCurrentDir(aAssetsDir);
}

//==============================================================================
// On Action Close Triggered SLot
//==============================================================================
void AssetBrowserWindow::on_actionClose_triggered()
{
    // Clear Selected Assetd
    mSelectedAsset = "";

    // Close Window
    closeWindow();
}

//==============================================================================
// Destructor
//==============================================================================
AssetBrowserWindow::~AssetBrowserWindow()
{
    // Shut Down
    shutDown();

    // Delete Asset Window QuickWidget
    delete ui->assetsQuickWidget;
    // Delete UI
    delete ui;

    // Check Assets Tree Model
    if (mAssetsTreeModel) {
        delete mAssetsTreeModel;
        mAssetsTreeModel = NULL;
    }

    // Check Assets List Model
    if (mAssetListModel) {
        delete mAssetListModel;
        mAssetListModel = NULL;
    }

    // ...

    // Release Settings
    mSettings->release();

    qDebug() << "AssetBrowserWindow deleted.";
}

