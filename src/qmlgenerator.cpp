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
void QMLGenerator::updateQML(const QString& aQMLPath, ComponentInfo* aComponent)
{
    // ...
}

//==============================================================================
// Constructor
//==============================================================================
QMLGenerator::QMLGenerator(QObject* aParent)
    : QObject(aParent)
{

}
