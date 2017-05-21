#include <QDebug>

#include "componentcategorymodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentCategoryModel::ComponentCategoryModel(QObject* aParent)
    : QAbstractListModel(aParent)
{
    //qDebug() << "ComponentCategoryModel created.";
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentCategoryModel::init()
{
    // Append Categories
    mCategories << COMPONENT_CATEGORY_VISUAL;
    mCategories << COMPONENT_CATEGORY_NONVISUAL;
    mCategories << COMPONENT_CATEGORY_LAYOUT;
    mCategories << COMPONENT_CATEGORY_CONTAINER;
    mCategories << COMPONENT_CATEGORY_DELEGATE;
    mCategories << COMPONENT_CATEGORY_ANIMATION;
    mCategories << COMPONENT_CATEGORY_IMAGE;

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentCategoryModel::clear()
{
    // Clear Categories
    mCategories.clear();
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentCategoryModel::rowCount(const QModelIndex& ) const
{
    return mCategories.count();
}

//==============================================================================
// Get index
//==============================================================================
int ComponentCategoryModel::getIndex(const QString& aCategory)
{
    return mCategories.indexOf(aCategory);
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentCategoryModel::data(const QModelIndex& index, int role) const
{
    // Check Index
    if (!index.isValid()) {
        return QVariant();
    }

    // Get Row
    int cRow = index.row();

    // Check Row
    if (cRow >= 0 && cRow < mCategories.count()) {
        // Check Role
        if (role == Qt::DisplayRole) {
            return mCategories[cRow];
        }
    }

    return QVariant();
}

//==============================================================================
// Destructor
//==============================================================================
ComponentCategoryModel::~ComponentCategoryModel()
{
    // Clear
    clear();

    //qDebug() << "ComponentCategoryModel deleted.";
}
