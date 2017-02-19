#ifndef QMLPROJECTPARSER_H
#define QMLPROJECTPARSER_H

#include <QObject>
#include <QString>

//==============================================================================
// QML Project Parser Class
//==============================================================================
class QMLProjectParser : public QObject
{
    Q_OBJECT

//    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
//    Q_PROPERTY(QString currDir READ currDir WRITE setcurrDir NOTIFY currDirChanged)
//    Q_PROPERTY(QString mainFile READ mainFile WRITE setMainFile NOTIFY mainFileChanged)
//    Q_PROPERTY(QStringList importPaths READ importPaths WRITE setImportPaths NOTIFY importPathsChanged)
//    Q_PROPERTY(QString qmlDir READ qmlDir WRITE setQmlDir NOTIFY qmlDirChanged)
//    Q_PROPERTY(QString jsDir READ jsDir WRITE setJsDir NOTIFY jsDirChanged)
//    Q_PROPERTY(QString imagesDir READ imagesDir WRITE setImagesDir NOTIFY imagesDirChanged)

public:
    // Constructor
    explicit QMLProjectParser(QObject* aParent = NULL);
    // Destructor
    ~QMLProjectParser();

signals:

public slots:


private:
    // File Name
    QString         mFileName;
    // Current Directory
    QString         mCurrDir;

    // Main File
    QString         mMainFile;

    // Import Paths
    QStringList     mImportPaths;

    // QML Dir
    QString         mQMLDir;
    // JS Dir
    QString         mJSDir;
    // Images Dir
    QString         mImagesDir;


};

#endif // QMLPROJECTPARSER_H
