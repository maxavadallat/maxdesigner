#ifndef DESIGNEREVENTFILTER_H
#define DESIGNEREVENTFILTER_H

#include <QObject>

//==============================================================================
// Event Filter Class
//==============================================================================
class DesignerEventFilter : public QObject
{
    Q_OBJECT

public:
    // Constructor
    explicit DesignerEventFilter(QObject* aParent = NULL);

signals:

protected:
    // Event Filter
    virtual bool eventFilter(QObject* aObject, QEvent* aEvent);

};

#endif // DESIGNEREVENTFILTER_H
