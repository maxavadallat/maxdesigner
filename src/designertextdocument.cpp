#include <QDebug>

#include "designertextdocument.h"
#include "settingscontroller.h"
#include "constants.h"


//==============================================================================
// Constructor
//==============================================================================
DesignerTextDocument::DesignerTextDocument(QQuickItem* aParent)
    : QQuickTextDocument(aParent)
{
    qDebug() << "DesignerTextDocument created.";

    // ...
}

//==============================================================================
// Destructor
//==============================================================================
DesignerTextDocument::~DesignerTextDocument()
{
    // ...

    qDebug() << "DesignerTextDocument deleted.";
}










//==============================================================================
// Constructor
//==============================================================================
DesignerSyntaxHighlighter::DesignerSyntaxHighlighter(QObject* aParent)
    : QSyntaxHighlighter(aParent)
{
    qDebug() << "DesignerSyntaxHighlighter created.";

    // ...
}

//==============================================================================
// Constructor
//==============================================================================
DesignerSyntaxHighlighter::DesignerSyntaxHighlighter(QTextDocument* aParent)
    : QSyntaxHighlighter(aParent)
{
    qDebug() << "DesignerSyntaxHighlighter created.";

}

//==============================================================================
// Highlight Block
//==============================================================================
void DesignerSyntaxHighlighter::highlightBlock(const QString& aText)
{
    qDebug() << "DesignerSyntaxHighlighter::highlightBlock - aText: " << aText;

    // ...
}

//==============================================================================
// Destructor
//==============================================================================
DesignerSyntaxHighlighter::~DesignerSyntaxHighlighter()
{
    // ...

    qDebug() << "DesignerSyntaxHighlighter deleted.";
}
