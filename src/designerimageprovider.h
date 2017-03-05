#ifndef DESIGNERIMAGEPROVIDER_H
#define DESIGNERIMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>
#include <QFileIconProvider>

//==============================================================================
// Designer Image Provider
//==============================================================================
class DesignerImageProvider : public QQuickImageProvider
{
public:
    // Constructor
    explicit DesignerImageProvider();

    // Request Image
    virtual QImage requestImage(const QString& aID, QSize* aSize, const QSize& aRequestedSize);

private:
    // File Icon Provider
    QFileIconProvider   mFileIconProvider;
};

#endif // DESIGNERIMAGEPROVIDER_H
