#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>

#include "projectmodel.h"
#include "qmlparser.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
QMLParser::QMLParser(QObject* aParent)
    : QObject(aParent)
{
}

//==============================================================================
// Parse QML
//==============================================================================
ComponentInfo* QMLParser::parseQML(const QString& aFilePath, ProjectModel* aProjectModel)
{
    // Init File Info
    QFile qmlFile(aFilePath);

    // Open File
    if (qmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Init File Content
        QString qmlContent = qmlFile.readAll();
        // Close File
        qmlFile.close();

        qDebug() << "QMLParser::parseQML - aFilePath: " << aFilePath << " - qmlContent: " << qmlContent;

        // Init File Info
        QFileInfo qmlInfo(aFilePath);

        // Create New Component Info
        ComponentInfo* newComponentInfo = new ComponentInfo(qmlInfo.baseName(), "", aProjectModel);

        // ...

        return newComponentInfo;

    } else {
        qWarning() << "QMLParser::parseQML - aFilePath: " << aFilePath << " - ERROR OPENING FILE!";
    }

    return NULL;
}
