#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>

#include "projectpropertiesdialog.h"
#include "ui_projectpropertiesdialog.h"
#include "constants.h"

//==============================================================================
// Construcotr
//==============================================================================
ProjectPropertiesDialog::ProjectPropertiesDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::ProjectPropertiesDialog)
    , mSettings(SettingsControler::getInstance())
    , mImportPathsModel(NULL)
    , mPluginPathsModel(NULL)
    , mIPLCurrentIndex(-1)
    , mNewProject(false)
    , mProjectDirEdited(false)
    , mMainQMLFileEdited(false)
    , mQMLDirEdited(false)
    , mJSDirEdited(false)
    , mImagesDirEdited(false)
    , mComponentsDirEdited(false)
    , mViewsDirEdited(false)
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
    if (!mPluginPathsModel) {
        // Create Plugin Paths Model
        mPluginPathsModel = new PluginPathsModel();
    }

    // Set Model
    ui->pluginPathsList->setModel(mPluginPathsModel);
}

//==============================================================================
// Restore UI
//==============================================================================
void ProjectPropertiesDialog::restoreUI()
{
    // ...
}

//==============================================================================
// Reset
//==============================================================================
void ProjectPropertiesDialog::reset()
{
    // Reset All Imputs
    ui->projectNameEdit->setText("");
    ui->projectDirEdit->setText("");
    ui->mainQmlFileEdit->setText("");
    ui->qmlDirEdit->setText("");
    ui->jsDirEdit->setText("");
    ui->imagesDirEdit->setText("");
    ui->componentsDirEdit->setText("");
    ui->viewsDirEdit->setText("");

    if (mImportPathsModel) {
        mImportPathsModel->clear();
    }

    if (mPluginPathsModel) {
        mPluginPathsModel->clear();
    }

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
        // Reset Edit Markers
        mProjectDirEdited = false;
        mMainQMLFileEdited = false;
        mQMLDirEdited = false;
        mJSDirEdited = false;
        mImagesDirEdited = false;
        mComponentsDirEdited = false;
        mViewsDirEdited = false;
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
// Get Main QML File
//==============================================================================
QString ProjectPropertiesDialog::mainQMLFile()
{
    return ui->mainQmlFileEdit->text();
}

//==============================================================================
// Set Main QML File
//==============================================================================
void ProjectPropertiesDialog::setMainQMLFile(const QString& aQMLFile)
{
    ui->mainQmlFileEdit->setText(aQMLFile);
}

//==============================================================================
// Get QML Directory
//==============================================================================
QString ProjectPropertiesDialog::qmlDir()
{
    return ui->qmlDirEdit->text();
}

//==============================================================================
// Set QML Directory
//==============================================================================
void ProjectPropertiesDialog::setQMLDir(const QString& aQMLDir)
{
    ui->qmlDirEdit->setText(aQMLDir);
}

//==============================================================================
// Get JS Directory
//==============================================================================
QString ProjectPropertiesDialog::jsDir()
{
    return ui->jsDirEdit->text();
}

//==============================================================================
// Set JS Directory
//==============================================================================
void ProjectPropertiesDialog::setJSDir(const QString& aJSDir)
{
    ui->jsDirEdit->setText(aJSDir);
}

//==============================================================================
// Get Images Directory
//==============================================================================
QString ProjectPropertiesDialog::imagesDir()
{
    return ui->imagesDirEdit->text();
}

//==============================================================================
// Set Images Directory
//==============================================================================
void ProjectPropertiesDialog::setImagesDir(const QString& aImagesDir)
{
    ui->imagesDirEdit->setText(aImagesDir);
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
// Set Plugin Paths
//==============================================================================
void ProjectPropertiesDialog::setPluginPaths(const QStringList& aPluginPaths)
{
    // Check Plugin Paths Model
    if (mPluginPathsModel) {
        // Set Plugin Paths
        mPluginPathsModel->setPluginPaths(aPluginPaths);
        // Set Plugin Path List Current Index
        mPPLCurrentIndex = mPluginPathsModel->rowCount() > 0 ? 0 : -1;
    }
}

//==============================================================================
// Add Plugin Path
//==============================================================================
void ProjectPropertiesDialog::addPluginPath(const QString& aPath)
{
    // Check Plugin Paths Model
    if (mPluginPathsModel) {
        // Add Plugin Path
        mPluginPathsModel->addPluginPath(aPath);
    }
}

//==============================================================================
// Remove Plugin Path
//==============================================================================
void ProjectPropertiesDialog::removePluginPath(const int& aIndex)
{
    // Check Plugin Paths Model
    if (mPluginPathsModel) {
        // Remove Plugin Path
        mPluginPathsModel->removePluginPath(aIndex);
    }
}

//==============================================================================
// Clear Plugin Paths
//==============================================================================
void ProjectPropertiesDialog::clearPluginPaths()
{
    // Check Plugin Paths Model
    if (mPluginPathsModel) {
        // Clear Plugin Paths
        mPluginPathsModel->clear();
    }

    // Reset Plugin Path List Current Index
    mPPLCurrentIndex = -1;
}

//==============================================================================
// On Project Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_projectDirBrowseButton_clicked()
{

}

//==============================================================================
// On Main QML File Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_qmlFileBrowseButton_clicked()
{

}

//==============================================================================
// On QML Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_qmlDirBrowseButton_clicked()
{

}

//==============================================================================
// On JS Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_jsDirBrowseButton_clicked()
{

}

//==============================================================================
// On Images Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_imagesDirBrowseButton_clicked()
{

}

//==============================================================================
// On Components Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_componentsDirBrowseButton_clicked()
{

}

//==============================================================================
// On Views Dir Browse Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_viewsDirBrowseButton_clicked()
{

}

//==============================================================================
// On Add Import Path Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_addImportDirButton_clicked()
{
    // Init File Dialog
    QFileDialog aipDialog(NULL, "Add Import Path");

    qDebug() << "ProjectPropertiesDialog::on_addImportDirButton_clicked - qmlDir: " << ui->qmlDirEdit->text();

    // Set File Mode
    aipDialog.setFileMode(QFileDialog::DirectoryOnly);
    // Set Directory
    aipDialog.setDirectory(ui->qmlDirEdit->text());

    // Exec Dialog
    if (aipDialog.exec()) {
        // ...
    }
}

//==============================================================================
// On Remove Import Path Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_removeImportDirButton_clicked()
{
    // ...
}

//==============================================================================
// On Project Name Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_projectNameEdit_textChanged(const QString& arg1)
{
    // Check If New Project
    if (mNewProject) {
        // Set QML Dir Editor Text
        ui->qmlDirEdit->setText(ui->projectDirEdit->text() + "/" + arg1 + "/" + DEFAULT_PROJECT_QML_DIR_NAME);
        // Set Components Dir Edit Text
        ui->componentsDirEdit->setText(ui->projectDirEdit->text() + "/" + arg1 + "/" + DEFAULT_PROJECT_COMPONENTS_DIR_NAME);
        // Set Views Dir Edit Text
        ui->viewsDirEdit->setText(ui->projectDirEdit->text() + "/" + arg1 + "/" + DEFAULT_PROJECT_VIEWS_DIR_NAME);
    }
}

//==============================================================================
// On Project Dir Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_projectDirEdit_textChanged(const QString& arg1)
{
    // Check If New Project
    if (mNewProject) {
        // Set QML Dir Editor Text
        ui->qmlDirEdit->setText(arg1 + "/" + ui->projectNameEdit->text() + "/" + DEFAULT_PROJECT_QML_DIR_NAME);
        // Set Components Dir Edit Text
        ui->componentsDirEdit->setText(arg1 + "/" + ui->projectNameEdit->text() + "/" + DEFAULT_PROJECT_COMPONENTS_DIR_NAME);
        // Set Views Dir Edit Text
        ui->viewsDirEdit->setText(arg1 + "/" + ui->projectNameEdit->text() + "/" + DEFAULT_PROJECT_VIEWS_DIR_NAME);
    }
}

//==============================================================================
// On Project Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_projectDirEdit_textEdited(const QString&)
{
    // Set Project Dir Edited
    mProjectDirEdited = true;
}

//==============================================================================
// On Main QML File Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_mainQmlFileEdit_textEdited(const QString&)
{
    // Set Main QML File Edited
    mMainQMLFileEdited = true;
}

//==============================================================================
// On QML Dir Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_qmlDirEdit_textChanged(const QString& arg1)
{
    // Check If New Project
    if (mNewProject) {
        // Set Main QML File Name
        ui->mainQmlFileEdit->setText(arg1 + "/" + DEFAULT_PROJECT_MAIN_QML_FILE_NAME);
        // Set JS Dir Editor Text
        ui->jsDirEdit->setText(arg1);
        // Set Images Dir Editor Text
        ui->imagesDirEdit->setText(arg1);
    }
}

//==============================================================================
// On QML Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_qmlDirEdit_textEdited(const QString&)
{
    // Set QML Dir Edited
    mQMLDirEdited = true;
}

//==============================================================================
// On JS Dir Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_jsDirEdit_textChanged(const QString& arg1)
{
    Q_UNUSED(arg1);

    // Check If Dir Valid
}

//==============================================================================
// On JS Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_jsDirEdit_textEdited(const QString&)
{
    // Set JS Dir Edited
    mJSDirEdited = true;
}

//==============================================================================
// On Images Dir Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_imagesDirEdit_textChanged(const QString& arg1)
{
    Q_UNUSED(arg1);

    // Check If Dir Valid
}

//==============================================================================
// On Images Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_imagesDirEdit_textEdited(const QString&)
{
    // Set Images Dir Edited
    mImagesDirEdited = true;
}

//==============================================================================
// On Components Dir Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_componentsDirEdit_textChanged(const QString& arg1)
{
    // Check If Dir Valid

    QFileInfo dirInfo(arg1);

    //if (dirInfo.)

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
// On Views Dir Edit Text Changed Slot
//==============================================================================
void ProjectPropertiesDialog::on_viewsDirEdit_textChanged(const QString& arg1)
{
    Q_UNUSED(arg1);

    // ...
}

//==============================================================================
// On Views Dir Edit Text Edited Slot
//==============================================================================
void ProjectPropertiesDialog::on_viewsDirEdit_textEdited(const QString&)
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
// On Add Plugin Path Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_addPluginDirButton_clicked()
{
    // Init File Dialog
    QFileDialog aupDialog(NULL, "Add Plugin Path");

    qDebug() << "ProjectPropertiesDialog::on_addPluginDirButton_clicked - qmlDir: " << ui->qmlDirEdit->text();

    // Set File Mode
    aupDialog.setFileMode(QFileDialog::DirectoryOnly);
    // Set Directory
    aupDialog.setDirectory(ui->qmlDirEdit->text());

    // Exec Dialog
    if (aupDialog.exec()) {
        // ...
    }
}

//==============================================================================
// On Remove Plugin Path Button Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_removePluginDirButton_clicked()
{
}

//==============================================================================
// On Plugin Paths List Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_pluginPathsList_clicked(const QModelIndex &index)
{
    // Set Current Index
    mPPLCurrentIndex = index.row();

    // Check Plugin Paths Model
    if (mPluginPathsModel) {
        // Check Current Index
        if (mIPLCurrentIndex >= 0 && mIPLCurrentIndex < mPluginPathsModel->rowCount()) {
            // Set Remove Plugin Path Button Enabled State
            ui->removePluginDirButton->setEnabled(true);
        }
    } else {
        // Set Remove Plugin Path Button Enabled State
        ui->removePluginDirButton->setEnabled(false);
    }
}

//==============================================================================
// On Plugin Paths List Double Clicked Slot
//==============================================================================
void ProjectPropertiesDialog::on_pluginPathsList_doubleClicked(const QModelIndex &index)
{
    // Set Current Index
    mPPLCurrentIndex = index.row();

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
    if (mPluginPathsModel) {
        // Delete Plugin Paths Model
        delete mPluginPathsModel;
        mPluginPathsModel = NULL;
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
    // Get Row
    int ipmRow = index.row();

    // Check Row
    if (ipmRow >= 0 && ipmRow < mImportPaths.count()) {
        // Switch Role
        switch (role) {
            case Qt::DisplayRole:   return mImportPaths[ipmRow];
//            case ImportPathRole:
        }
    }

    return "";
}

//==============================================================================
// Get Role Names
//==============================================================================
//QHash<int,QByteArray> ImportPathsModel::roleNames() const
//{
//    // Init Role Names
//    QHash<int,QByteArray> ipmRoleNames;

//    // Set Up Role Names
//    ipmRoleNames[ImportPathRole] = "importPath";

//    return ipmRoleNames;
//}

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
PluginPathsModel::PluginPathsModel(QWidget* aParent)
    : QAbstractListModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void PluginPathsModel::init()
{
    // ...
}

//==============================================================================
// Set Plugin Paths
//==============================================================================
void PluginPathsModel::setPluginPaths(const QStringList& aPluginPaths)
{
    // Begin Reset Model
    beginResetModel();
    // Set Plugin Paths
    mPluginPaths = aPluginPaths;
    // End Reset Model
    endResetModel();
}

//==============================================================================
// Add Plugin Path
//==============================================================================
void PluginPathsModel::addPluginPath(const QString& aPath)
{
    // Check Path
    if (mPluginPaths.indexOf(aPath) == -1) {
        // Iterate Through Plugin Paths
        for (int i=0; i<mPluginPaths.count(); i++) {
            if (mPluginPaths[i] < aPath) {
                // Begin Insert Rows
                beginInsertRows(QModelIndex(), mPluginPaths.count(), mPluginPaths.count());
                // Inser Path
                mPluginPaths.insert(i, aPath);
                // End Insert Rows
                endInsertRows();

                return;
            }
        }

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), mPluginPaths.count(), mPluginPaths.count());
        // Append Path
        mPluginPaths << aPath;
        // End Insert Rows
        endInsertRows();
    }
}

//==============================================================================
// Set Plugin Path
//==============================================================================
void PluginPathsModel::setPluginPath(const int& aIndex, const QString& aPath)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mPluginPaths.count()) {
        // Set Plugin Path
        mPluginPaths[aIndex] = aPath;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
    }
}

//==============================================================================
// Remove Plugin Path
//==============================================================================
void PluginPathsModel::removePluginPath(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mPluginPaths.count()) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Plugin Path
        mPluginPaths.removeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Clear
//==============================================================================
void PluginPathsModel::clear()
{
    // Begin Reset Model
    beginResetModel();
    // Clear Plugin Paths
    mPluginPaths.clear();
    // End Reset Model
    endResetModel();
}

//==============================================================================
// Row Count
//==============================================================================
int PluginPathsModel::rowCount(const QModelIndex& ) const
{
    return mPluginPaths.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant PluginPathsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int ipmRow = index.row();

    // Check Row
    if (ipmRow >= 0 && ipmRow < mPluginPaths.count()) {
        // Switch Role
        switch (role) {
            case Qt::DisplayRole:   return mPluginPaths[ipmRow];
//            case PluginPathRole:
        }
    }

    return "";
}

//==============================================================================
// Get Role Names
//==============================================================================
//QHash<int,QByteArray> PluginPathsModel::roleNames() const
//{
//    // Init Role Names
//    QHash<int,QByteArray> ipmRoleNames;

//    // Set Up Role Names
//    ipmRoleNames[PluginPathRole] = "importPath";

//    return ipmRoleNames;
//}

//==============================================================================
// Destructor
//==============================================================================
PluginPathsModel::~PluginPathsModel()
{
    // Clear
    clear();
}
