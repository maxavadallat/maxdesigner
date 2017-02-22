#ifndef PROJECTPROPERTIESDIALOG_H
#define PROJECTPROPERTIESDIALOG_H

#include <QDialog>
#include <QAbstractListModel>

#include "settingscontroler.h"

namespace Ui {
class ProjectPropertiesDialog;
}

class ImportPathsModel;

//==============================================================================
// New Project Dialog Class
//==============================================================================
class ProjectPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    // Construcotr
    explicit ProjectPropertiesDialog(QWidget* aParent = NULL);

    // Reset
    void reset();

    // Set New Project
    void setNewProject(const bool& aNewProject);

    // Get Project Name
    QString projectName();
    // Set Project Name
    void setProjectName(const QString& aName);

    // Get Project Dir
    QString projectDir();
    // Set Project Dir
    void setProjectDir(const QString& aDir);

    // Get Main QML File
    QString mainQMLFile();
    // Set Main QML File
    void setMainQMLFile(const QString& aQMLFile);

    // Get QML Directory
    QString qmlDir();
    // Set QML Directory
    void setQMLDir(const QString& aQMLDir);

    // Get JS Directory
    QString jsDir();
    // Set JS Directory
    void setJSDir(const QString& aJSDir);

    // Get Images Directory
    QString imagesDir();
    // Set Images Directory
    void setImagesDir(const QString& aImagesDir);

    // Get Components Directory
    QString componentsDir();
    // Set Components Directory
    void setComponentsDir(const QString& aComponentsDir);

    // Get Views Directory
    QString viewsDir();
    // Set Views Directory
    void setViewsDir(const QString& aViewssDir);

    // Add Import Path
    void addImportPath(const QString& aPath);
    // Remove Import Path
    void removeImportPath(const int& aIndex);
    // Clear Import Paths
    void clearImportPaths();

    // Destructor
    ~ProjectPropertiesDialog();

private:
    // Init
    void init();
    // Restore UI
    void restoreUI();

private slots:

    // On Project Dir Browse Button Clicked Slot
    void on_projectDirBrowseButton_clicked();
    // On Main QML File Browse Button Clicked Slot
    void on_qmlFileBrowseButton_clicked();
    // On QML Dir Browse Button Clicked Slot
    void on_qmlDirBrowseButton_clicked();
    // On JS Dir Browse Button Clicked Slot
    void on_jsDirBrowseButton_clicked();
    // On Images Dir Browse Button Clicked Slot
    void on_imagesDirBrowseButton_clicked();
    // On Components Dir Browse Button Clicked Slot
    void on_componentsDirBrowseButton_clicked();
    // On Views Dir Browse Button Clicked Slot
    void on_viewsDirBrowseButton_clicked();
    // On Add Import Path Button Clicked Slot
    void on_addImportDirButton_clicked();
    // On Remove Import Path Button Clicked Slot
    void on_removeImportDirButton_clicked();

    // On Project Name Edit Text Changed Slot
    void on_projectNameEdit_textChanged(const QString& arg1);

    // On Project Dir Edit Text Changed Slot
    void on_projectDirEdit_textChanged(const QString& arg1);
    // On Project Dir Edit Text Edited Slot
    void on_projectDirEdit_textEdited(const QString& arg1);

    // On QML Dir Edit Text Edited Slot
    void on_mainQmlFileEdit_textEdited(const QString& arg1);

    // On QML Dir Edit Text Changed Slot
    void on_qmlDirEdit_textChanged(const QString& arg1);
    // On QML Dir Edit Text Edited Slot
    void on_qmlDirEdit_textEdited(const QString& arg1);

    // On JS Dir Edit Text Changed Slot
    void on_jsDirEdit_textChanged(const QString& arg1);
    // On JS Dir Edit Text Edited Slot
    void on_jsDirEdit_textEdited(const QString& arg1);

    // On Images Dir Edit Text Changed Slot
    void on_imagesDirEdit_textChanged(const QString& arg1);
    // On Images Dir Edit Text Edited Slot
    void on_imagesDirEdit_textEdited(const QString& arg1);

    // On Components Dir Edit Text Changed Slot
    void on_componentsDirEdit_textChanged(const QString& arg1);
    // On Components Dir Edit Text Edited Slot
    void on_componentsDirEdit_textEdited(const QString& arg1);

    // On Views Dir Edit Text Changed Slot
    void on_viewsDirEdit_textChanged(const QString& arg1);
    // On Views Dir Edit Text Edited Slot
    void on_viewsDirEdit_textEdited(const QString& arg1);

    // On Import Paths List Clicked Slot
    void on_importPathsList_clicked(const QModelIndex &index);
    // On Import Paths List Double Clicked Slot
    void on_importPathsList_doubleClicked(const QModelIndex &index);


private: // Data

    // UI
    Ui::ProjectPropertiesDialog*    ui;
    // Settings Controller
    SettingsControler*              mSettings;
    // Import Paths Model
    ImportPathsModel*               mImportPathsModel;

    // Import Path List Current Index
    int                             mIPLCurrentIndex;

    // New Project
    bool                            mNewProject;

    // Project Dir Edited
    bool                            mProjectDirEdited;
    // Main QML File Edited
    bool                            mMainQMLFileEdited;
    // QML Dir Edited
    bool                            mQMLDirEdited;
    // JS Dir Edited
    bool                            mJSDirEdited;
    // Images Dir Edited
    bool                            mImagesDirEdited;
    // Components Dir Edited
    bool                            mComponentsDirEdited;
    // Views Dir Edited
    bool                            mViewsDirEdited;
};








//==============================================================================
// Import Paths Model Class
//==============================================================================
class ImportPathsModel : public QAbstractListModel
{
public:
    // Construcotr
    explicit ImportPathsModel(QWidget* aParent = NULL);

    // Add Import Path
    void addImportPath(const QString& aPath);
    // Set Import Path
    void setImportPath(const int& aIndex, const QString& aPath);
    // Remove Import Path
    void removeImportPath(const int& aIndex);
    // Clear
    void clear();

    // Destructor
    ~ImportPathsModel();

private:
    // Init
    void init();

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int,QByteArray> roleNames() const;

private: // Data

    // Roles
    enum IPMRoles {
        ImportPathRole = Qt::UserRole + 1
    };

    // Import Paths
    QStringList     mImportPaths;
};




#endif // PROJECTPROPERTIESDIALOG_H
