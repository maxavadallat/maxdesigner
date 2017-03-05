#ifndef VIEWSLISTMODEL_H
#define VIEWSLISTMODEL_H

#include <QObject>
#include <QList>
#include <QAbstractListModel>

class ProjectModel;
class ComponentInfo;

//==============================================================================
// View List Model
//==============================================================================
class ViewsModel : public QAbstractListModel
{
public:
    // Set Views Dir
    void setViewsDir(const QString& aDirPath);

    // Add View
    void addView(ComponentInfo* aView);
    // Remove View
    void removeView(ComponentInfo* aView, const bool& aDelete = true);

    // Get View Index By Name
    int getViewIndex(const QString& aName);
    // Get View By Name
    ComponentInfo* getView(const QString& aName);

    // Destructor
    ~ViewsModel();

protected:
    friend class ProjectModel;

    // Constructor
    explicit ViewsModel(ProjectModel* aProjectModel, QObject* aParent = NULL);
    // Init
    void init();
    // Clear
    void clear();

    // Load Views
    void loadViews();

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int,QByteArray> roleNames() const;

private: // Data

    // Item Field Roles
    enum ItemRoles {
        ViewNameRole = Qt::UserRole + 1
    };

    // Project Model
    ProjectModel*           mProjectModel;
    // View List
    QList<ComponentInfo*>   mViewsList;
    // Views Dir
    QString                 mViewsDir;
};








/*
//==============================================================================
// View Info Class
//==============================================================================
class ViewInfo : public QObject
{
public:
    // Constructor
    explicit ViewInfo(const QString& aName, QObject* aParent = NULL);

    // Get Component Name
    QString name();

    // Save Info
    void save();

    // Destructor
    ~ViewInfo();

private:

    // Init
    void init();

private: // Data
    // Name
    QString     mName;
    // Component Info
    QJsonObject mInfo;
};
*/

#endif // VIEWSLISTMODEL_H
