#include <QFileInfo>
#include <QDebug>

#include "designerimageprovider.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
DesignerImageProvider::DesignerImageProvider()
    : QQuickImageProvider(QQmlImageProviderBase::Image, QQmlImageProviderBase::ForceAsynchronousImageLoading)
{
    // ...
}

//==============================================================================
// Request Image
//==============================================================================
QImage DesignerImageProvider::requestImage(const QString& aID, QSize* , const QSize& )
{
    // Init File Name
    QString fileName = aID;
    // Init File Info
    QFileInfo fileInfo(fileName);

    // Get Icon Image
    QImage iconImage = mFileIconProvider.icon(fileInfo).pixmap(QSize(64, 64)).toImage();

    // Check Image
    if (!iconImage.isNull()) {
        return iconImage;
    }

    return QImage(DEFAULT_IMAGE_PROVIDER_ICON);
}
