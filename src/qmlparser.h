#ifndef QMLPARSER_H
#define QMLPARSER_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class ComponentInfo;
class ProjectModel;

//==============================================================================
// QML Parser Class
//==============================================================================
class QMLParser : public QObject
{
    Q_OBJECT

public:
    // Constructor
    explicit QMLParser(QObject* aParent = NULL);
    // Parse QML
    ComponentInfo* parseQML(const QString& aFilePath, ProjectModel* aProjectModel = NULL);

private:

    // Parse Properties


};

#endif // QMLPARSER_H
