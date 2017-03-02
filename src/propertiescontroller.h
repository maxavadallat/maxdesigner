#ifndef PROPERTIESCONTROLLER_H
#define PROPERTIESCONTROLLER_H

#include <QObject>

class ProjectModel;
class ComponentInfo;

//==============================================================================
// Properties Controller Class
//==============================================================================
class PropertiesController : public QObject
{
    Q_OBJECT

public:
    // Constructor
    explicit PropertiesController(QObject* aParent = NULL);
    // Destructor
    ~PropertiesController();

signals:

public slots:

private:

    // Init
    void init();
    // Clear
    void clear();

private: // Data


};

#endif // PROPERTIESCONTROLLER_H
