#ifndef COMPONENTSFILTER_H
#define COMPONENTSFILTER_H

#include <QObject>
#include <QSortFilterProxyModel>


class SettingsController;

//==============================================================================
// Components Filter Proxy Model
//==============================================================================
class ComponentsFilter : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList filteredComponents READ filteredComponents WRITE setFilteredComponents NOTIFY filteredComponentsChanged)
    Q_PROPERTY(QStringList filteredTypes READ filteredTypes WRITE setFilteredTypes NOTIFY filteredTypesChanged)

public:
    // Constructor
    explicit ComponentsFilter(QObject* aParent = NULL);

    // Get Filtered Components
    QStringList filteredComponents();
    // Set Filtered Components
    void setFilteredComponents(const QStringList& aFilteredComponents);

    // Get Filtered Types
    QStringList filteredTypes();
    // Set Filtered Types
    void setFilteredTypes(const QStringList& aFilteredTypes);

    // Get Source Index
    Q_INVOKABLE int getSourceIndex(const int& aIndex);

    // Destructor
    ~ComponentsFilter();

signals:
    // Filtered Components Changed Signal
    void filteredComponentsChanged(const QStringList& aFilteredComponents);
    // Filtered Types Changed Signal
    void filteredTypesChanged(const QStringList& aFilteredTypes);

public: // From QSortFilterProxyModel
    // Filter Accepts Row
    virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;

protected:
    // Init
    void init();
    // Clear
    void clear();

protected slots:
    // Update Roles
    void updateRoles();

protected: // Data
    // Settings
    SettingsController* mSettings;
    // Filtered Component Names
    QStringList         mFilteredComponents;
    // Filtered Component Types
    QStringList         mFilteredTypes;
};

#endif // COMPONENTSFILTER_H
