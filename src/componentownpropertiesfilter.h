#ifndef COMPONENTOWNPROPERTIESFILTER_H
#define COMPONENTOWNPROPERTIESFILTER_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QStringList>

class ComponentOwnPropertiesModel;

//==============================================================================
// Component Own Properties Filter
//==============================================================================
class ComponentOwnPropertiesFilter : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList filteredNames READ filteredNames WRITE setFilteredNames NOTIFY filteredNamesChanged)

public:
    // Constructor
    explicit ComponentOwnPropertiesFilter(QObject* aParent = NULL);

    // Get Filtered Names
    QStringList filteredNames();
    // Set Filtered Names
    void setFilteredNames(const QStringList& aFilteredNames);

    // Destructor
    ~ComponentOwnPropertiesFilter();

signals:
    // Filtered Names Changed Signal
    void filteredNamesChanged(const QStringList& aFilteredNames);

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
    // Filtered Property Names
    QStringList     mFilteredNames;
};

#endif // COMPONENTOWNPROPERTIESFILTER_H
