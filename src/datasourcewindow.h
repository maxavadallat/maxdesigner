#ifndef DATASOURCEWINDOW_H
#define DATASOURCEWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QAbstractListModel>

namespace Ui {
class DataSourceWindow;
}

class LiveWindow;
class MainWindow;
class SettingsController;
class ProjectModel;
class ComponentInfo;
class PropertiesController;

//==============================================================================
// Data Source Remote/Controller Window
//==============================================================================
class DataSourceWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit DataSourceWindow(LiveWindow* aLiveWindow, ProjectModel* aProjectModel, QWidget* aParent = NULL);

    // Add DataSource To Control
    void addDataSource(const QString& aName);
    // Remove Data Source From Controleld Data Sources
    void removeDataSource(const int& aIndex);
    // Clear Controlled Data Sources
    void clearDataSources();

    // Destructor
    ~DataSourceWindow();

protected:
    // Init
    void init();
    // Restore UI
    void restoreUI();
    // Shut Down
    void shutDown();

private:
    // UI
    Ui::DataSourceWindow*   ui;
    // Live Window
    LiveWindow*             mLiveWindow;
    // Project Model
    ProjectModel*           mProject;
    // Settings
    SettingsController*     mSettings;
    // Data Sources
    QStringList             mDataSources;
};






// Data Sources List Model
class DataSourcesListModel : public QAbstractListModel
{
public:
    // Constructor
    explicit DataSourcesListModel(QObject* aParent = NULL);
    // Destructor
    ~DataSourcesListModel();

protected:

    // Init
    void init();
    // Clear
    void clear();

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

protected: // Data
    // Data Item Roles
    enum EDSItemRoles {
        EDSIRName   = Qt::UserRole + 1
    };


};





#endif // DATASOURCEWINDOW_H
