#include <QFile>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>

#include "qmlgenerator.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
QMLGenerator::QMLGenerator(QObject* aParent)
    : QObject(aParent)
{

}
