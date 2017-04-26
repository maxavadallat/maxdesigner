#ifndef MINIMIZEDCOMPONENTS_H
#define MINIMIZEDCOMPONENTS_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>

class ComponentInfo;

//==============================================================================
// Minimized Components Model
//==============================================================================
class MinimizedComponents : public QAbstractListModel
{
public:
    // Constructor
    MinimizedComponents(QObject* aParent);

    // Add Compoennt
    void addComponent(ComponentInfo* aComponent);
    // Remove Component
    void removeComponent(ComponentInfo* aComponent);

    // Destructor
    ~MinimizedComponents();

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int,QByteArray> roleNames() const;

private:
    // Init
    void init();
    // Clear
    void clear();

private: // Data

    // Item Field Roles
    enum ItemRoles {
        ComponentNameRole = Qt::UserRole + 1
    };

    // Minimzed Compoennts
    QList<ComponentInfo*>   mMinimizedComponents;
};

#endif // MINIMIZEDCOMPONENTS_H
