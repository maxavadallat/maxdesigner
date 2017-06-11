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

        // ...
    }

    // Check Asset List Model
    if (!mAssetListModel) {
        // Create Assrt List Model
        mAssetListModel = new AssetListModel();

        // ...
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

    // Grab Keyboard
    //grabKeyboard();

    // ...

}

//==============================================================================
// Restore UI
//==============================================================================
void AssetBrowserWindow::restoreUI()
{
    qDebug() << "AssetBrowserWindow::restoreUI";

    // ...

    // Set Current Dir

    // Check Project Model


}

//==============================================================================
// ShutDown
//==============================================================================
void AssetBrowserWindow::shutDown()
{
    qDebug() << "AssetBrowserWindow::shutDown";

    // Release Keyboard
    releaseKeyboard();

    // ...
}

//==============================================================================
// Get Selected File
//==============================================================================
QString AssetBrowserWindow::selectedFile()
{
    return "";
}

//==============================================================================
// Set Selected File
//==============================================================================
void AssetBrowserWindow::setSelectedFile(const QString& aFilePath)
{

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
    // Check Assets Tree Model
    if (mAssetsTreeModel) {
        // Set Current Dir
        mAssetsTreeModel->setCurrentPath(aCurrentDir);
    }

    // Check Assets List Model
    if (mAssetListModel) {
        // Set Current Dir
        mAssetListModel->setCurrentDir(aCurrentDir);
    }

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
    // ...

    // Normalize Window
    showNormal();
    // Close
    close();
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

