#ifndef VIEWSLISTMODEL_H
#define VIEWSLISTMODEL_H

#include <QObject>
#include <QMap>
#include <QAbstractListModel>

class ProjectModel;
class ComponentInfo;

//==============================================================================
// View List Model
//==============================================================================
class ViewsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Set Views Dir
    void setViewsDir(const QString& aDirPath);

    // Add View
    bool addView(ComponentInfo* aView);
    // Remove View
    bool removeView(const int& aIndex);

    // Get View Index By Name
    int getViewIndex(const QString& aName);
    // Get View By Name
    ComponentInfo* getView(const QString& aName, const bool& aPreload = false);
    // Get View By Index
    Q_INVOKABLE ComponentInfo* getViewByIndex(const int& aIndex);

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
    // Update Base Components
    void updateBaseComponents();

    // Save All Components
    void saveAllComponents();

    // Clear All Children
    void clearAllChildren(const bool& aClosing = false);

protected slots:
    // Component Dirty State Changed Slot
    void componentDirtyChanged(const bool& aDirty);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int,QByteArray> roleNames() const;

private: // Data

    // Item Field Roles
    enum EVItemRoles {
        EVRName = Qt::UserRole + 1,
        EVRDirty
    };

    // Project Model
    ProjectModel*                   mProjectModel;
    // Components
    QMap<QString, ComponentInfo*>   mViews;
    // Views Dir
    QString                         mViewsDir;
};

#endif // VIEWSLISTMODEL_H
