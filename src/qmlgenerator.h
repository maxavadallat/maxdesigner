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
    static void updateQML(ComponentInfo* aComponent, const QString& aQMLPath);
    // Generate QML Source
    static void generateQML(ComponentInfo* aComponent, const QString& aQMLPath);

    // Constructor
    explicit QMLGenerator(QObject* aParent = NULL);

private: // Data

};

#endif // QMLGENERATOR_H
