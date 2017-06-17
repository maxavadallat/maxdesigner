#ifndef DESIGNERTEXTDOCUMENT_H
#define DESIGNERTEXTDOCUMENT_H

#include <QObject>
#include <QQuickTextDocument>
#include <QSyntaxHighlighter>

//==============================================================================
// Designer Text Document Class For Syntax Highlight
//==============================================================================
class DesignerTextDocument : public QQuickTextDocument
{
    Q_OBJECT

public:
    // Condstructor
    explicit DesignerTextDocument(QQuickItem* aParent = NULL);

    // Destructor
    ~DesignerTextDocument();
};





//==============================================================================
// Designer Syntax Highlighter Class
//==============================================================================
class DesignerSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    // Constructor
    explicit DesignerSyntaxHighlighter(QObject* aParent = NULL);
    // Constructor
    explicit DesignerSyntaxHighlighter(QTextDocument* aParent = NULL);

    // Highlight Block
    virtual void  highlightBlock(const QString& aText);

    // Destructor
    ~DesignerSyntaxHighlighter();
};



#endif // DESIGNERTEXTDOCUMENT_H
