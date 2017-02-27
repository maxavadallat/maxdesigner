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
    // Create/Update QML
    static void updateQML(const QString& aQMLPath, ComponentInfo* aComponent);

    // Constructor
    explicit QMLGenerator(QObject* aParent = NULL);

private: // Data

};

#endif // QMLGENERATOR_H
