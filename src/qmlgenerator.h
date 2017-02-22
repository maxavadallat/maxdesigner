#ifndef QMLGENERATOR_H
#define QMLGENERATOR_H

#include <QObject>
#include <QString>

class ComponentInfo;

//==============================================================================
// QML Generator
//==============================================================================
class QMLGenerator : public QObject
{
    Q_OBJECT

public:
    // Constructor
    explicit QMLGenerator(QObject* aParent = NULL);

private: // Data

};

#endif // QMLGENERATOR_H
