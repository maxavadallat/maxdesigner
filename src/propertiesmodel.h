#ifndef PROPERTIESMODEL_H
#define PROPERTIESMODEL_H

#include <QObject>

//==============================================================================
// Properties Model
//==============================================================================
class PropertiesModel : public QObject
{
    Q_OBJECT

public:
    // Constructor
    explicit PropertiesModel(QObject* aParent = NULL);
    // Destructor
    ~PropertiesModel();

signals:

public slots:
};

#endif // PROPERTIESMODEL_H
