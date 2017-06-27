#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QPluginLoader>
#include <QJsonObject>

#include "projectpropertiesdialog.h"
#include "ui_projectpropertiesdialog.h"
#include "projectmodel.h"
#include "idesignertargetplugininterface.h"
#include "constants.h"

//==============================================================================
// Construcotr
//==============================================================================
ProjectPropertiesDialog::ProjectPropertiesDialog(ProjectModel* aProject, QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::ProjectPropertiesDialog)
    , mProject(aProject)
    , mSettings(SettingsController::getInstance())
    , mImportPathsModel(NULL)
    , mPluginListModel(NULL)
    , mIPLCurrentIndex(-1)
    , mNewProject(false)
    , mProjectDirEdited(false)
    , mBaseComponentsDirEdited(false)
    , mDataSourcesDirEdited(false)
    , mComponentsDirEdited(false)
    , mViewsDirEdited(false)
    , mAssetsDirEdited(false)
{
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
void ProjectPropertiesDialog::init()
{
    // Check Import Paths Model
    if (!mImportPathsModel) {
        // Create Import Paths Model
        mImportPathsModel = new ImportPathsModel();
    }

    // Set Model
    ui->importPathsList->setModel(mImportPathsModel);

    // Check Plugin Paths Model
    if (!mPluginListModel) {
        // Create Plugin Paths Model
        mPluginListModel = new PluginListModel(mProject);
    }

    // Set Model
    ui->pluginPathsList->setModel(mPluginListModel);
}

//==============================================================================
// Restore UI
//==============================================================================
void ProjectPropertiesDialog::restoreUI()
{
    // ...
}

//==============================================================================
// Get Project Model
//==============================================================================
ProjectModel* ProjectPropertiesDialog::projectModel()
{
    return mProject;
}

//==============================================================================
// Set Project Model
//==============================================================================
void ProjectPropertiesDialog::setProjectModel(ProjectModel* aProjectModel)
{
    // Check Project Model
    if (mProject != aProjectModel) {
        // Set Project Model
        mProject = aProjectModel;

        // Check Plugin List Model
        if (mPluginListModel) {
            // Set Project Model
            mPluginListModel->setProjectModel(mProject);
        }
    }
}

//==============================================================================
// Reset
//==============================================================================
void ProjectPropertiesDialog::reset()
{
    // Reset Project Model
    setProjectModel(NULL);

    // Reset All Imputs
    ui->projectNameEdit->setText("");
    ui->projectDirEdit->setText("");

    ui->dashboardPathEdit->setText("");

    ui->baseComponentsDirEdit->setText("");
    ui->dataSourcesDirEdit->setText("");
    ui->componentsDirEdit->setText("");
    ui->viewsDirEdit->setText("");
    ui->assetsDirEdit->setText("");

    // Check Import Paths Model
    if (mImportPathsModel) {
        // Clear
        mImportPathsModel->clear();
    }

    // Check Plugin List Model
    if (mPluginListModel) {
        // Clear
        //mPluginListModel->clear();
    }

    // Set Remove Import Dir Button Enabled State
    ui->removeImportDirButton->setEnabled(false);

    // Set New Project
    setNewProject(true);

    // ...
}

//==============================================================================
// Set New Project
//==============================================================================
void ProjectPropertiesDialog::setNewProject(const bool& aNewProject)
{
    // Set New Project
    mNewProject = aNewProject;

    // Check If New Project
    if (mNewProject) {
        ui->projectDirLabel->setVisible(true);
        ui->projectDirEdit->setVisible(true);
        ui->projectDirBrowseButton->setVisible(true);

        // Reset Edit Markers
        mProjectDirEdited = false;
        mBaseComponentsDirEdited = false;
        mDataSourcesDirEdited = false;
        mComponentsDirEdited = false;
        mViewsDirEdited = false;
        mAssetsDirEdited = false;

    } else {

        ui->projectDirLabel->setVisible(false);
        ui->projectDirEdit->setVisible(false);
        ui->projectDirBrowseButton->setVisible(false);

        // ...
    }
}

//==============================================================================
// Get Project Name
//==============================================================================
QString ProjectPropertiesDialog::projectName()
{
    return ui->projectNameEdit->text();
}

//==============================================================================
// Set Project Name
//==============================================================================
void ProjectPropertiesDialog::setProjectName(const QString& aName)
{
    ui->projectNameEdit->setText(aName);
}

//==============================================================================
// Get Project Dir
//==============================================================================
QString ProjectPropertiesDialog::projectDir()
{
    return ui->projectDirEdit->text();
}

//==============================================================================
// Set Project Dir
//==============================================================================
void ProjectPropertiesDialog::setProjectDir(const QString& aDir)
{
    ui->projectDirEdit->setText(aDir);
}

//==============================================================================
// Get Project Screen Width
//==============================================================================
int ProjectPropertiesDialog::screenWidth()
{
    return ui->screenWidthSpinBox->value();
}

//==============================================================================
// Set Project Screen Width
//==============================================================================
void ProjectPropertiesDialog::setScreenWidth(const int& aWidth)
{
    ui->screenHeightSpinBox->setValue(aWidth);
}

//==============================================================================
// Get Project Screen Height
//==============================================================================
int ProjectPropertiesDialog::screenHeight()
{
    return ui->screenHeightSpinBox->value();
}

//==============================================================================
// Set Project Screen Height
//==============================================================================
void ProjectPropertiesDialog::setScreenHeight(const int& aHeight)
{
    ui->screenHeightSpinBox->setValue(aHeight);
}

//==============================================================================
// Get Dashboard Image Path
//==============================================================================
QString ProjectPropertiesDialog::dashboardPath()
{
    return ui->dashboardPathEdit->text();
}

//==============================================================================
// Set Dashboard Image Path
//==============================================================================
void ProjectPropertiesDialog::setDashboardPath(const QString& aDashboardPath)
{
    ui->dashboardPathEdit->setText(aDashboardPath);
}

//==============================================================================
// Get Main QML File
//==============================================================================
QString ProjectPropertiesDialog::baseComponentsDir()
{
    return ui->baseComponentsDirEdit->text();
}

//==============================================================================
// Set Main QML File
//==============================================================================
void ProjectPropertiesDialog::setBaseComponentsDir(const QString& aQMLFile)
{
    ui->baseComponentsDirEdit->setText(aQMLFile);
}

//==============================================================================
// Get QML Directory
//==============================================================================
QString ProjectPropertiesDialog::dataSourcesDir()
{
    return ui->dataSourcesDirEdit->text();
}

//==============================================================================
// Set QML Directory
//==============================================================================
void ProjectPropertiesDialog::setDataSourcesDir(const QString& aQMLDir)
{
    ui->dataSourcesDirEdit->setText(aQMLDir);
}

//==============================================================================
// Get Images Directory
//==============================================================================
QString ProjectPropertiesDialog::assetsDir()
{
    return ui->assetsDirEdit->text();
}

//==============================================================================
// Set Images Directory
//==============================================================================
void ProjectPropertiesDialog::setAssetsDir(const QString& aImagesDir)
{
    ui->assetsDirEdit->setText(aImagesDir);
}

//==============================================================================
// Get Components Directory
//==============================================================================
QString ProjectPropertiesDialog::componentsDir()
{
    return ui->componentsDirEdit->text();
}

//==============================================================================
// Set Components Directory
//==============================================================================
void ProjectPropertiesDialog::setComponentsDir(const QString& aComponentsDir)
{
    ui->componentsDirEdit->setText(aComponentsDir);
}

//==============================================================================
// Get Views Directory
//==============================================================================
QString ProjectPropertiesDialog::viewsDir()
{
    return ui->viewsDirEdit->text();
}

//==============================================================================
// Set Views Directory
//==============================================================================
void ProjectPropertiesDialog::setViewsDir(const QString& aViewssDir)
{
    ui->viewsDirEdit->setText(aViewssDir);
}

//==============================================================================
// Get Import Paths
//==============================================================================
QStringList ProjectPropertiesDialog::importPaths()
{
    // Check Import Paths Model
    if (mImportPathsModel) {
        // Get Import Paths
        return mImportPathsModel->importPaths();
    }

    return QStringList();
}

//==============================================================================
// Set Import Paths
//==============================================================================
void ProjectPropertiesDialog::setImportPaths(const QStringList& aImportPaths)
{
    // Check Import Paths Model
    if (mImportPathsModel) {
        // Set Import Paths
        mImportPathsModel->setImportPaths(aImportPaths);
        // Set Import Path List Current Index
        mIPLCurrentIndex = mImportPathsModel->rowCount() > 0 ? 0 : -1;
    }
}

//==============================================================================
// Add Import Path
//==============================================================================
void ProjectPropertiesDialog::addImportPath(const QString& aPath)
{
    // Check Import Paths Model
    if (mImportPathsModel) {
        // Add Import Path
        mImportPathsModel->addImportPath(aPath);
    }
}

//==============================================================================
// Remove Import Path
//==============================================================================
void ProjectPropertiesDialog::removeImportPath(const int& aIndex)
{
    // Check Import Paths Model
    if (mImportPathsModel) {
        // Remove Import Path
        mImportPathsModel->removeImportPath(aIndex);
    }
}

//==============================================================================
// Clear Import Paths
//==============================================================================
void ProjectPropertiesDialog::clearImportPaths()
{
    // Check Import Paths Model
    if (mImportPathsModel) {
        // Clear Import Paths
        mImportPathsModel->clear();
    }

    // Reset Import Path List Current Index
    mIPLCurrentIndex = -1;
}

//==============================================================================
// Get Plugin List
//==============================================================================
QStringList ProjectPropertiesDialog::pluginList()
{
    // Check Plugin Paths Model
    if (mPluginListModel) {
        // Get Plugin Paths
        return mPluginListModel->pluginList();
    }

    return QStringList();
}

//==============================================================================
// Set Plugin List
//==============================================================================
void ProjectPropertiesDialog::setPluginList(const QStringList& aPluginPaths)
{
    // Check Plugin Paths Model
    if (mPluginListModel) {
        // Set Plugin Paths
        mPluginListModel->setPluginList(aPluginPaths);
        // Set Plugin Path List Current Index
        mPLCurrentIndex = mPluginListModel->rowCount() > 0 ? 0 : -1;
    }
}

//==============================================================================
// Add Plugin
//==============================================================================
void ProjectPropertiesDialog::addPlugin(const QString& aPath)
{
    // Check Plugin Paths Model
    if (mPluginListModel) {
        // Add Plugin Path
        mPluginListModel->addPlugin(aPath);
    }
}

//==============================================================================
// Remove Plugin
//==============================================================================
void ProjectPropertiesDialog::removePlugin(const int& aIndex)
{
    // Check Plugin Paths Model
    if (mPluginListModel) {
        // Remove Plugin Path
        mPluginListModel->removePlugin(aIndex);
    }
}

//==============================================================================
// Clear Plugins
//==============================================================================
void ProjectPropertiesDialog::clearPlugins()
{
    // Check Plugin Paths Model
    if (mPluginListModel) {
        // Clear Plugins
        mPluginListModel->clear();
    }

    // Reset Plugin List Current Index
    mPLCurrentIndex = -1;
}

//==============================================================================
// On Project Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_projectDirBrowseButton_clicked()
{
    // Init Project Dir Select Dialog
    QFileDialog sDialog(NULL, "Select Project Directory");

    // Set File Mode
    sDialog.setFileMode(QFileDialog::Directory);

    // Init Selection Directory
    QString sDirectory = ui->projectDirEdit->text();

    // Check Directory
    if (!QFile::exists(sDirectory)) {
        // Adjust Selection Directory
        sDirectory = QDir::homePath();
    }

    // Set Directory
    sDialog.setDirectory(sDirectory);

    // Exec Project Dir Select Dialog
    if (sDialog.exec()) {
        // Set Text
        ui->projectDirEdit->setText(sDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// Dashboar Path Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_dashboardPathBrowseButton_clicked()
{
    // Init Dashboard Select Dialog
    QFileDialog dDialog(NULL, "Select Dashboard Image");
    // Set File Mode
    dDialog.setFileMode(QFileDialog::ExistingFile);

    // Init Selection Directory
    QString dPath = QDir::homePath();

    // Init Dashboard Image File Info
    QFileInfo dFileInfo(ui->dashboardPathEdit->text());
    // Check If Exist
    if (dFileInfo.exists()) {
        // Update Selection Directory
        dPath = dFileInfo.absolutePath();
    }

    // Set Directory
    dDialog.setDirectory(dPath);

    // Exec Dialog
    if (dDialog.exec()) {
        // Set Dashboard Asset Dir
        ui->dashboardPathEdit->setText(dDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// Base Componens Dir Browse Button Clicked
//==============================================================================
void ProjectPropertiesDialog::on_baseComponentsBrowseDirButton_clicked()
{
    // Init Project Dir Select Dialog
    QFileDialog sDialog(NULL, "Select Base Components Directory");

    // Set File Mode
    sDialog.setFileMode(QFileDialog::Directory);

    // Init Selection Directory
    QString sDirectory = ui->baseComponentsDirEdit->text();

    // Check Directory
    if (!QFile::exists(sDirectory)) {
        // Adjust Selection Directory
        sDirectory = QDir::homePath();
    }

    // Set Directory
    sDialog.setDirectory(sDirectory);

    // Exec Project Dir Select Dialog
    if (sDialog.exec()) {
        // Set Text
        ui->baseComponentsDirEdit->setText(sDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// Data Sources Dir Browse Button Clicked
//==============================================================================
void ProjectPropertiesDialog::on_dataSourcesDirBrowseButton_clicked()
{
    // Init Project Dir Select Dialog
    QFileDialog sDialog(NULL, "Select Data Sources Directory");

    // Set File Mode
    sDialog.setFileMode(QFileDialog::Directory);

    // Init Selection Directory
    QString sDirectory = ui->dataSourcesDirEdit->text();

    // Check Directory
    if (!QFile::exists(sDirectory)) {
        // Adjust Selection Directory
        sDirectory = QDir::homePath();
    }

    // Set Directory
    sDialog.setDirectory(sDirectory);

    // Exec Project Dir Select Dialog
    if (sDialog.exec()) {
        // Set Text
        ui->dataSourcesDirEdit->setText(sDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// Assets Dir Browse Button Clicked
//==============================================================================
void ProjectPropertiesDialog::on_assetsDirBrowseButton_clicked()
{
    // Init Project Dir Select Dialog
    QFileDialog sDialog(NULL, "Select Assets Directory");

    // Set File Mode
    sDialog.setFileMode(QFileDialog::Directory);

    // Init Selection Directory
    QString sDirectory = ui->assetsDirEdit->text();

    // Check Directory
    if (!QFile::exists(sDirectory)) {
        // Adjust Selection Directory
        sDirectory = QDir::homePath();
    }

    // Set Directory
    sDialog.setDirectory(sDirectory);

    // Exec Project Dir Select Dialog
    if (sDialog.exec()) {
        // Set Text
        ui->assetsDirEdit->setText(sDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// On Components Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_componentsDirBrowseButton_clicked()
{
    // Init Dir Select Dialog
    QFileDialog sDialog(NULL, "Select Components Directory");

    // Set File Mode
    sDialog.setFileMode(QFileDialog::Directory);

    // Init Selection Directory
    QString sDirectory = ui->componentsDirEdit->text();

    // Check Directory
    if (!QFile::exists(sDirectory)) {
        // Adjust Selection Directory
        sDirectory = QDir::homePath();
    }

    // Set Directory
    sDialog.setDirectory(sDirectory);

    // Exec Project Dir Select Dialog
    if (sDialog.exec()) {
        // Set Text
        ui->componentsDirEdit->setText(sDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// On Views Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_viewsDirBrowseButton_clicked()
{
    // Init Dir Select Dialog
    QFileDialog sDialog(NULL, "Select Views Directory");

    // Set File Mode
    sDialog.setFileMode(QFileDialog::Directory);

    // Init Selection Directory
    QString sDirectory = ui->viewsDirEdit->text();

    // Check Directory
    if (!QFile::exists(sDirectory)) {
        // Adjust Selection Directory
        sDirectory = QDir::homePath();
    }

    // Set Directory
    sDialog.setDirectory(sDirectory);

    // Exec Project Dir Select Dialog
    if (sDialog.exec()) {
        // Set Text
        ui->viewsDirEdit->setText(sDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// On Add Import Path Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_addImportDirButton_clicked()
{
    // Init File Dialog
    QFileDialog aipDialog(NULL, "Add Import Path");

    // Get QML Dir Temp
    QString qmlDirTemp = dataSourcesDir();

    // Check If Dir Exists
    if (!QFile::exists(qmlDirTemp)) {
        // Set QML Dir Temp
        qmlDirTemp = QDir::homePath();
    }

    qDebug() << "ProjectPropertiesDialog::on_addImportDirButton_clicked - qmlDir: " << qmlDirTemp;

    // Set File Mode
    aipDialog.setFileMode(QFileDialog::DirectoryOnly);
    // Set Directory
    aipDialog.setDirectory(qmlDirTemp);

    // Exec Dialog
    if (aipDialog.exec() && mImportPathsModel) {
        // Add Import Path
        mImportPathsModel->addImportPath(aipDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// On Remove Import Path Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_removeImportDirButton_clicked()
{
    // Check Current Index
    if (mImportPathsModel && mIPLCurrentIndex >= 0 && mIPLCurrentIndex < mImportPathsModel->rowCount()) {
        // Remove Import Path
        mImportPathsModel->removeImportPath(mIPLCurrentIndex);
        // Adjust Current Index
        mIPLCurrentIndex = qMin(mIPLCurrentIndex, mImportPathsModel->rowCount() - 1);
    }
}

//==============================================================================
// On Project Name Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_projectNameEdit_textChanged(const QString& arg1)
{
    // Check If New Project
    if (mNewProject) {
        // Set Base components Dir
        ui->baseComponentsDirEdit->setText(ui->projectDirEdit->text() + "/" + arg1 + "/" + DEFAULT_PROJECT_BASECOMPONENTS_DIR_NAME);
        // Set Data Sources Dir Edit
        ui->dataSourcesDirEdit->setText(ui->projectDirEdit->text() + "/" + arg1 + "/" + DEFAULT_PROJECT_DATASOURCES_DIR_NAME);
        // Set Components Dir Edit Text
        ui->componentsDirEdit->setText(ui->projectDirEdit->text() + "/" + arg1 + "/" + DEFAULT_PROJECT_COMPONENTS_DIR_NAME);
        // Set Views Dir Edit Text
        ui->viewsDirEdit->setText(ui->projectDirEdit->text() + "/" + arg1 + "/" + DEFAULT_PROJECT_VIEWS_DIR_NAME);
        // Set Assets Dir
        ui->assetsDirEdit->setText(ui->projectDirEdit->text() + "/" + arg1 + "/" + DEFAULT_PROJECT_ASSETS_DIR_NAME);
    }
}

//==============================================================================
// On Project Dir Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_projectDirEdit_textChanged(const QString& arg1)
{
    // Check If New Project
    if (mNewProject) {
        // Set Base Components Dir
        ui->baseComponentsDirEdit->setText(arg1 + "/" + ui->projectNameEdit->text() + "/" + DEFAULT_PROJECT_BASECOMPONENTS_DIR_NAME);
        // Set Data Sources Dir
        ui->dataSourcesDirEdit->setText(arg1 + "/" + ui->projectNameEdit->text() + "/" + DEFAULT_PROJECT_DATASOURCES_DIR_NAME);
        // Set Components Dir Edit Text
        ui->componentsDirEdit->setText(arg1 + "/" + ui->projectNameEdit->text() + "/" + DEFAULT_PROJECT_COMPONENTS_DIR_NAME);
        // Set Views Dir Edit Text
        ui->viewsDirEdit->setText(arg1 + "/" + ui->projectNameEdit->text() + "/" + DEFAULT_PROJECT_VIEWS_DIR_NAME);
        // Set Assets Dir Edit Text
        ui->assetsDirEdit->setText(arg1 + "/" + ui->projectNameEdit->text() + "/" + DEFAULT_PROJECT_ASSETS_DIR_NAME);
    }
}

//==============================================================================
// On Project Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_projectDirEdit_textEdited(const QString& )
{
    // Set Project Dir Edited
    mProjectDirEdited = true;
}

//==============================================================================
// Base Components Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_baseComponentsDirEdit_textEdited(const QString& )
{
    // Set Base Components Dir Edited
    mBaseComponentsDirEdited = true;
}

//==============================================================================
// Data Sources Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_dataSourcesDirEdit_textEdited(const QString& )
{
    mDataSourcesDirEdited = true;
}

//==============================================================================
// Assets Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_assetsDirEdit_textEdited(const QString& )
{
    mAssetsDirEdited = true;
}

//==============================================================================
// On Components Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_componentsDirEdit_textEdited(const QString&)
{
    // Set Components Dir Edited
    mComponentsDirEdited = true;
}

//==============================================================================
// On Views Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_viewsDirEdit_textEdited(const QString& )
{
    // Set Views Dir Edited
    mViewsDirEdited = true;
}

//==============================================================================
// On Import Paths List Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_importPathsList_clicked(const QModelIndex &index)
{
    // Set Current Index
    mIPLCurrentIndex = index.row();

    // Check Import Paths Model
    if (mImportPathsModel) {
        // Check Current Index
        if (mIPLCurrentIndex >= 0 && mIPLCurrentIndex < mImportPathsModel->rowCount()) {
            // Set Remove Import Path Button Enabled State
            ui->removeImportDirButton->setEnabled(true);
        }
    } else {
        // Set Remove Import Path Button Enabled State
        ui->removeImportDirButton->setEnabled(false);
    }
}

//==============================================================================
// On Import Paths List Double Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_importPathsList_doubleClicked(const QModelIndex &index)
{
    // Set Current Index
    mIPLCurrentIndex = index.row();

    // ...
}


//==============================================================================
// On Add Plugin Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_addPluginButton_clicked()
{
    // Init File Dialog
    QFileDialog apDialog(NULL, "Add Plugin");

    // Get Plugin Dir Temp
    QString pluginDirTemp = projectDir();

    // Check If Dir Exists
    if (!QFile::exists(pluginDirTemp)) {
        // Set Plugin Dir Temp
        pluginDirTemp = QDir::homePath();
    }

    qDebug() << "ProjectPropertiesDialog::on_addPluginButton_clicked - pluginDirTemp: " << pluginDirTemp;

    // Set File Mode
    apDialog.setFileMode(QFileDialog::ExistingFile);
    // Set Directory
    apDialog.setDirectory(pluginDirTemp);

    // Exec Dialog
    if (apDialog.exec() && mPluginListModel) {
        // Add Plugin
        mPluginListModel->addPlugin(apDialog.selectedFiles()[0]);
    }
}

//==============================================================================
// On Remove PLugin Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_removePluginButton_clicked()
{
    // Check Current Index
    if (mPluginListModel && mPLCurrentIndex >= 0 && mPLCurrentIndex < mPluginListModel->rowCount()) {
        qDebug() << "ProjectPropertiesDialog::on_removePluginButton_clicked - mPLCurrentIndex: " << mPLCurrentIndex;
        // Remove Plugin Path
        mPluginListModel->removePlugin(mPLCurrentIndex);
        // Adjust Current Index
        mPLCurrentIndex = qMin(mPLCurrentIndex, mPluginListModel->rowCount() - 1);
    }
}

//==============================================================================
// On Plugin Paths List Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_pluginPathsList_clicked(const QModelIndex &index)
{
    // Set Current Index
    mPLCurrentIndex = index.row();

    qDebug() << "ProjectPropertiesDialog::on_pluginPathsList_clicked - mPLCurrentIndex: " << mPLCurrentIndex;

    // Check Plugin Paths Model
    if (mPluginListModel) {
        // Check Current Index
        if (mPLCurrentIndex >= 0 && mPLCurrentIndex < mPluginListModel->rowCount()) {
            // Set Remove Plugin Path Button Enabled State
            ui->removePluginButton->setEnabled(true);
        }
    } else {
        // Set Remove Plugin Path Button Enabled State
        ui->removePluginButton->setEnabled(false);
    }
}

//==============================================================================
// On Plugin Paths List Double Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_pluginPathsList_doubleClicked(const QModelIndex &index)
{
    // Set Current Index
    mPLCurrentIndex = index.row();

    // ...

}

//==============================================================================
// Destructor
//==============================================================================
ProjectPropertiesDialog::~ProjectPropertiesDialog()
{
    // Delete UI
    delete ui;

    // Check Import Paths Model
    if (mImportPathsModel) {
        // Delete Import Paths Model
        delete mImportPathsModel;
        mImportPathsModel = NULL;
    }

    // Check Plugin Paths Model
    if (mPluginListModel) {
        // Delete Plugin Paths Model
        delete mPluginListModel;
        mPluginListModel = NULL;
    }

    // Release Settings Instance
    mSettings->release();
}













//==============================================================================
// Construcotr
//==============================================================================
ImportPathsModel::ImportPathsModel(QWidget* aParent)
    : QAbstractListModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ImportPathsModel::init()
{
    // ...
}

//==============================================================================
// Get Import Paths
//==============================================================================
QStringList ImportPathsModel::importPaths()
{
    return mImportPaths;
}

//==============================================================================
// Set Import Paths
//==============================================================================
void ImportPathsModel::setImportPaths(const QStringList& aImportPaths)
{
    // Begin Reset Model
    beginResetModel();
    // Set Import Paths
    mImportPaths = aImportPaths;
    // End Reset Model
    endResetModel();
}

//==============================================================================
// Add Import Path
//==============================================================================
void ImportPathsModel::addImportPath(const QString& aPath)
{
    qDebug() << "ImportPathsModel::addImportPath - aPath: " << aPath;

    // Check Path
    if (mImportPaths.indexOf(aPath) == -1) {
        // Iterate Through Import Paths
        for (int i=0; i<mImportPaths.count(); i++) {
            if (mImportPaths[i] < aPath) {
                // Begin Insert Rows
                beginInsertRows(QModelIndex(), mImportPaths.count(), mImportPaths.count());
                // Inser Path
                mImportPaths.insert(i, aPath);
                // End Insert Rows
                endInsertRows();

                return;
            }
        }

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), mImportPaths.count(), mImportPaths.count());
        // Append Path
        mImportPaths << aPath;
        // End Insert Rows
        endInsertRows();
    }
}

//==============================================================================
// Set Import Path
//==============================================================================
void ImportPathsModel::setImportPath(const int& aIndex, const QString& aPath)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mImportPaths.count()) {
        // Set Import Path
        mImportPaths[aIndex] = aPath;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
    }
}

//==============================================================================
// Remove Import Path
//==============================================================================
void ImportPathsModel::removeImportPath(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mImportPaths.count()) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Import Path
        mImportPaths.removeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Clear
//==============================================================================
void ImportPathsModel::clear()
{
    // Begin Reset Model
    beginResetModel();
    // Clear Import Paths
    mImportPaths.clear();
    // End Reset Model
    endResetModel();
}

//==============================================================================
// Column Count
//==============================================================================
int ImportPathsModel::columnCount(const QModelIndex& ) const
{
    return 1;
}

//==============================================================================
// Row Count
//==============================================================================
int ImportPathsModel::rowCount(const QModelIndex& ) const
{
    return mImportPaths.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ImportPathsModel::data(const QModelIndex& index, int role) const
{
    // Check Index
    if (!index.isValid()) {
        return "";
    }

    // Get Row
    int ipmRow = index.row();

    // Check Row
    if (ipmRow >= 0 && ipmRow < mImportPaths.count()) {
        // Switch Role
        switch (role) {
            //case Qt::UserRole:
            case Qt::DisplayRole:   return mImportPaths[ipmRow];
        }
    }

    return QVariant();
}

//==============================================================================
// Destructor
//==============================================================================
ImportPathsModel::~ImportPathsModel()
{
    // Clear
    clear();
}






















//==============================================================================
// Construcotr
//==============================================================================
PluginListModel::PluginListModel(ProjectModel* aProject, QWidget* aParent)
    : QAbstractListModel(aParent)
    , mProject(aProject)
{
    qDebug() << "PluginListModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void PluginListModel::init()
{
    // ...

    // Load Plugins
    loadPlugins();
}

//==============================================================================
// Load PLugins Info
//==============================================================================
void PluginListModel::loadPlugins()
{
    // Check Project Model
    if (mProject) {
        qDebug() << "PluginListModel::loadPlugins - mProject: " << mProject->projectName();

        // Get Plugin Paths Array
        QJsonArray ppArray = mProject->mProperties.value(JSON_KEY_PROJECT_PLUGIN_PATHS).toArray();
        // Get Plugin Paths Count
        int ppCount = ppArray.count();
        // Iterate Through Plugin Paths Array
        for (int i=0; i<ppCount; i++) {
            // Get Plugin Path
            QString pluginPath = ppArray[i].toString();
            // Add Plugin
            addPlugin(pluginPath);
        }
    }
}

//==============================================================================
// Check If Plugin Already Added
//==============================================================================
int PluginListModel::checkPlugin(const QString& aPluginPath)
{
    // Get Plugins List Count
    int plCount = mPluginList.count();
    // Iterate Through Plugin List
    for (int i=0; i<plCount; i++) {
        // Check Path
        if (mPluginList[i].mPath == aPluginPath) {
            return i;
        }
    }

    return -1;
}

//==============================================================================
// Get Project Model
//==============================================================================
ProjectModel* PluginListModel::projectModel()
{
    return mProject;
}

//==============================================================================
// Set Project Model
//==============================================================================
void PluginListModel::setProjectModel(ProjectModel* aProjectModel)
{
    // Check Project Model
    if (mProject != aProjectModel) {
        qDebug() << "PluginListModel::setProjectModel - aProjectModel: " << (aProjectModel ? aProjectModel->projectName() : "NULL");

        // Clear
        clear();

        // Set Project Model
        mProject = aProjectModel;

        // Load Project Plugins
        loadPlugins();
    }
}

//==============================================================================
// Get Plugin List
//==============================================================================
QStringList PluginListModel::pluginList()
{
    // Init Plugin Path List
    QStringList ppList = QStringList();

    // Get Plugin List Count
    int plCount = mPluginList.count();
    // Iterate Through PLugin List
    for (int i=0; i<plCount; i++) {
        // Add Path To Plugin Path List
        ppList << mPluginList[i].mPath;
    }

    return ppList;
}

//==============================================================================
// Set Plugin List
//==============================================================================
void PluginListModel::setPluginList(const QStringList& aPluginPaths)
{
    // Get Plugin Paths Count
    int ppCount = aPluginPaths.count();

    // Check Plugin Paths
    if (ppCount > 0) {
        qDebug() << "PluginListModel::setPluginList - ppCount: " << ppCount;

        // Begin Reset Model
        beginResetModel();

        // Iterate Through Plugin Paths
        for (int i=0; i<ppCount; i++) {
            // Init PLugin Loader
            QPluginLoader pluginLoader(aPluginPaths[i]);

            // Load
            if (pluginLoader.load()) {

                // Init New Plugin List Item
                PluginListItem newListItem;

                // Set Path
                newListItem.mPath = aPluginPaths[i];
                // Set Name
                newListItem.mName = dynamic_cast<IDesignerTargetPluginInterface*>(pluginLoader.instance())->targetName();

                // Append New List Item
                mPluginList << newListItem;

                // Unload Plugin
                pluginLoader.unload();
            }
        }

        // End Reset Model
        endResetModel();
    }
}

//==============================================================================
// Add Plugin Path
//==============================================================================
void PluginListModel::addPlugin(const QString& aPath)
{
    // Check Path
    if (!aPath.isEmpty()) {
        // Init Plugin File Info
        QFileInfo pluginInfo(aPath);

        // Check If Exists
        if (!pluginInfo.exists()) {
            qWarning() << "PluginListModel::addPlugin - aPath: " << aPath << " - PLUGIN DOES NOT EXIST!";
            return;
        }

        // Init PLugin Loader
        QPluginLoader pluginLoader(aPath);
        // Get Plugin Metadata
        QJsonObject pluginMetaData = pluginLoader.metaData();
        // Get Plugin IID
        QString pluginIID = pluginMetaData.value("IID").toString();

        // Check IID
        if (!pluginIID.startsWith(DEFAULT_TARGET_PLUGIN_IID_PREFIX)) {
            qWarning() << "PluginListModel::addPlugin - aPath: " << aPath << " - PLUGIN IS NOT A DESIGNER TARGET PLUGIN!";
            return;
        }

        qDebug() << "PluginListModel::addPlugin - aPath: " << aPath;

        // Load Plugin
        if (pluginLoader.load()) {
            // Get Instance
            IDesignerTargetPluginInterface* pluginInterface = dynamic_cast<IDesignerTargetPluginInterface*>(pluginLoader.instance());
            // Check Instance
            if (pluginInterface) {

                qDebug() << "PluginListModel::addPlugin - targetName: " << pluginInterface->targetName();
                qDebug() << "PluginListModel::addPlugin - version:    " << pluginInterface->version();

                // Init New PLugin List Item
                PluginListItem newPluginListItem;

                // Installed Plugin Path
                QString installedPluginPath = QString(DEFAULT_TARGET_PLUGIN_PATH).arg(QDir::homePath()).arg(pluginInfo.fileName());

                qDebug() << "PluginListModel::addPlugin - installedPluginPath: " << installedPluginPath;

                // Set Path
                newPluginListItem.mPath = installedPluginPath;
                // Set Name
                newPluginListItem.mName = pluginInterface->targetName();

                // Get Plugin Index
                int pluginIndex = checkPlugin(installedPluginPath);

                // Check If Plugin Already Added
                if (pluginIndex != -1) {
                    // Update Plugin List
                    mPluginList[pluginIndex] = newPluginListItem;
                    // Emit Data Changed Signal
                    emit dataChanged(index(pluginIndex), index(pluginIndex));

                } else {
                    // Init Intalled PLugin Dir
                    QDir ipDir(QString(DEFAULT_TARGET_PLUGIN_PATH).arg(QDir::homePath()).arg(""));

                    // Check If Installed Plugin Path Exists
                    if (!ipDir.exists(installedPluginPath)) {
                        // Make Path
                        ipDir.mkpath(ipDir.absolutePath());
                    }

                    // Copy Plugin
                    QFile::copy(pluginInfo.absoluteFilePath(), installedPluginPath);

                    // Begin Insert Rows
                    beginInsertRows(QModelIndex(), rowCount(), rowCount());
                    // Append To Plugin List
                    mPluginList << newPluginListItem;
                    // End Insert Rows
                    endInsertRows();
                }
            }

            // Unload
            pluginLoader.unload();

        } else {
            qDebug() << "Error Loading Plugin: " << pluginLoader.errorString();
        }
    }
}

//==============================================================================
// Set Plugin Path
//==============================================================================
void PluginListModel::setPluginPath(const int& aIndex, const QString& aPath)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mPluginList.count()) {
        qDebug() << "PluginListModel::setPluginPath - aIndex: " << aIndex << " - aPath: " << aPath;

        // Set Plugin Path
        mPluginList[aIndex].mPath = aPath;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
    }
}

//==============================================================================
// Remove Plugin Path
//==============================================================================
void PluginListModel::removePlugin(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mPluginList.count()) {
        qDebug() << "PluginListModel::removePlugin - aIndex: " << aIndex;

        // Get Plugin Path
        QString pluginPath = mPluginList[aIndex].mPath;
        // Remove File
        QFile::remove(pluginPath);

        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Plugin Path
        mPluginList.removeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Clear
//==============================================================================
void PluginListModel::clear()
{
    // Check PLugin List Count
    if (mPluginList.count() > 0) {
        qDebug() << "PluginListModel::clear";
        // Begin Reset Model
        beginResetModel();
        // Clear Plugin Paths
        mPluginList.clear();
        // End Reset Model
        endResetModel();
    }
}

//==============================================================================
// Column Count
//==============================================================================
int PluginListModel::columnCount(const QModelIndex& ) const
{
    return 1;
}

//==============================================================================
// Row Count
//==============================================================================
int PluginListModel::rowCount(const QModelIndex& ) const
{
    return mPluginList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant PluginListModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int ppmRow = index.row();

    // Check Row
    if (ppmRow >= 0 && ppmRow < mPluginList.count()) {
        // Switch Role
        switch (role) {
            case Qt::DisplayRole:   return mPluginList[ppmRow].mName;
        }
    }

    return QVariant();
}

//==============================================================================
// Destructor
//==============================================================================
PluginListModel::~PluginListModel()
{
    // Clear
    clear();

    qDebug() << "PluginListModel deleted.";
}


