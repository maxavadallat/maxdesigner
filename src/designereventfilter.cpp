#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

#include "designereventfilter.h"

//==============================================================================
// Constructor
//==============================================================================
DesignerEventFilter::DesignerEventFilter(QObject* aParent)
    : QObject(aParent)
{
    // ...
}

//==============================================================================
// Event Filter
//==============================================================================
bool DesignerEventFilter::eventFilter(QObject* aObject, QEvent* aEvent)
{
    // Check Event
    if (aEvent && aEvent->type() == QEvent::KeyRelease) {
        // Get Key Event
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(aEvent);

        // Switch Key
        switch (keyEvent->key()) {
            case Qt::Key_T:
                qDebug() << "DesignerEventFilter::eventFilter - TRACER VISIBILITY";
            break;

            default:
            break;
        }
    }
    // ...

    return QObject::eventFilter(aObject, aEvent);
}
