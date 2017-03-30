#include <QFile>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>

#include "qmlgenerator.h"
#include "componentinfo.h"
#include "projectmodel.h"
#include "constants.h"

//==============================================================================
// Create/Update QML
//==============================================================================
void QMLGenerator::updateQML(ComponentInfo* aComponent, const QString& aQMLPath)
{
    Q_UNUSED(aQMLPath);
    Q_UNUSED(aComponent);

    // ...

}

//==============================================================================
// Generate QML Source
//==============================================================================
void QMLGenerator::generateQML(ComponentInfo* aComponent, const QString& aQMLPath)
{
    Q_UNUSED(aQMLPath);
    Q_UNUSED(aComponent);

    // ...

}

//==============================================================================
// Constructor
//==============================================================================
QMLGenerator::QMLGenerator(QObject* aParent)
    : QObject(aParent)
{

}
