#ifndef COMPONENTANCHORSMODEL_H
#define COMPONENTANCHORSMODEL_H

#include <QObject>
#include <QList>
#include <QJsonObject>

class ComponentInfo;

//==============================================================================
// Component Anchors Model
//==============================================================================
class ComponentAnchorsModel : public QObject
{
    Q_OBJECT

    // Current Component
    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

    // Left Anchor Target
    Q_PROPERTY(QString anchorsLeft READ anchorsLeft WRITE setAnchorsLeft NOTIFY anchorsLeftChanged)
    // Right Anchor Target
    Q_PROPERTY(QString anchorsRight READ anchorsRight WRITE setAnchorsRight NOTIFY anchorsRightChanged)
    // Top Anchor Target
    Q_PROPERTY(QString anchorsTop READ anchorsTop WRITE setAnchorsTop NOTIFY anchorsTopChanged)
    // Bottom Anchor Target
    Q_PROPERTY(QString anchorsBottom READ anchorsBottom WRITE setAnchorsBottom NOTIFY anchorsBottomChanged)

    // Fill Target
    Q_PROPERTY(QString anchorsFill READ anchorsFill WRITE setAnchorsFill NOTIFY anchorsFillChanged)
    // CenterIn Target
    Q_PROPERTY(QString anchorsCenterIn READ anchorsCenterIn WRITE setAnchorsCenterIn NOTIFY anchorsCenterInChanged)

    // Margins
    Q_PROPERTY(QString anchorsMargins READ anchorsMargins WRITE setAnchorsMargins NOTIFY anchorsMarginsChanged)

    // Left Margin
    Q_PROPERTY(QString anchorsLeftMargin READ anchorsLeftMargin WRITE setAnchorsLeftMargin NOTIFY anchorsLeftMarginChanged)
    // Right Margin
    Q_PROPERTY(QString anchorsRightMargin READ anchorsRightMargin WRITE setAnchorsRightMargin NOTIFY anchorsRightMarginChanged)
    // Top Margin
    Q_PROPERTY(QString anchorsTopMargin READ anchorsTopMargin WRITE setAnchorsTopMargin NOTIFY anchorsTopMarginChanged)
    // Bottom Margin
    Q_PROPERTY(QString anchorsBottomMargin READ anchorsBottomMargin WRITE setAnchorsBottomMargin NOTIFY anchorsBottomMarginChanged)

    // Horizontal Center Offset
    Q_PROPERTY(QString anchorsHorizontalOffset READ anchorsHorizontalOffset WRITE setAnchorsHorizontalOffset NOTIFY anchorsHorizontalOffsetChanged)
    // Vertical Center Offset
    Q_PROPERTY(QString anchorsVerticalOffset READ anchorsVerticalOffset WRITE setAnchorsVerticalOffset NOTIFY anchorsVerticalOffsetChanged)

public:
    // From JSON Object
    static ComponentAnchorsModel* fromJSONObject(ComponentInfo* aComponent, const QJsonObject& aObject);

    // Constructor
    explicit ComponentAnchorsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Left Anchor Target
    QString anchorsLeft();
    // Set Left Anchor Target
    void setAnchorsLeft(const QString& aAnchorLeft);

    // Right Anchor Target
    QString anchorsRight();
    // Set Right Anchor Target
    void setAnchorsRight(const QString& aAnchorRight);

    // Top Anchor Target
    QString anchorsTop();
    // Set Top Anchor Target
    void setAnchorsTop(const QString& aAnchorTop);

    // Bottom Anchor Target
    QString anchorsBottom();
    // Set Bottom Anchor Target
    void setAnchorsBottom(const QString& aAnchorBottom);

    // Fill Target
    QString anchorsFill();
    // Set Fill Target
    void setAnchorsFill(const QString& aAnchorFill);

    // CenterIn Target
    QString anchorsCenterIn();
    // Set CenterIn Target
    void setAnchorsCenterIn(const QString& aAnchorCenterIn);

    // Margins
    QString anchorsMargins();
    // Set Margins
    void setAnchorsMargins(const QString& aAnchorMargins);

    // Left Margin
    QString anchorsLeftMargin();
    // Set Left Margin
    void setAnchorsLeftMargin(const QString& aAnchorLeftMargin);

    // Right Margin
    QString anchorsRightMargin();
    // Set Right Margin
    void setAnchorsRightMargin(const QString& aAnchorRightMargin);

    // Top Margin
    QString anchorsTopMargin();
    // Set Top Margin
    void setAnchorsTopMargin(const QString& aAnchorTopMargin);

    // Bottom Margin
    QString anchorsBottomMargin();
    // Set Bottom Margin
    void setAnchorsBottomMargin(const QString& aAnchorBottomMargin);

    // Horizontal Center Offset
    QString anchorsHorizontalOffset();
    // Set Horizontal Center Offset
    void setAnchorsHorizontalOffset(const QString& aAnchorHorizontalOffset);

    // Vertical Center Offset
    QString anchorsVerticalOffset();
    // Set Vertical Center Offset
    void setAnchorsVerticalOffset(const QString& aAnchorVerticalOffset);

    // To JSON Object
    QJsonObject toJSONObject();

    // Destructor
    ~ComponentAnchorsModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);
    // Left Anchor Target Changed Signal
    void anchorsLeftChanged(const QString& aAnchorLeft);
    // Right Anchor Target Changed Signal
    void anchorsRightChanged(const QString& aAncorRight);
    // Top Anchor Target Changed Signal
    void anchorsTopChanged(const QString& aAnchorTop);
    // Bottom Anchor Target Changed Signal
    void anchorsBottomChanged(const QString& aAnchorBottom);
    // Fill Target Changed Signal
    void anchorsFillChanged(const QString& aAnchorFill);
    // CenterIn Target Changed Signal
    void anchorsCenterInChanged(const QString& aAnchorCenterIn);
    // Margins Changed Signal
    void anchorsMarginsChanged(const QString& aAnchorMargins);
    // Left Margin Changed Signal
    void anchorsLeftMarginChanged(const QString& aAnchorLeftMargin);
    // Right Margin Changed Signal
    void anchorsRightMarginChanged(const QString& aAnchorRightMargin);
    // Top Margin Changed Signal
    void anchorsTopMarginChanged(const QString& aAnchorTopMargin);
    // Bottom Margin Changed Signal
    void anchorsBottomMarginChanged(const QString& aAnchorBottomMargin);
    // Horizontal Center Offset Changed Signal
    void anchorsHorizontalOffsetChanged(const QString& aAnchorHorizontalOffset);
    // Vertical Center Offset Changed Signal
    void anchorsVerticalOffsetChanged(const QString& aAnchorVerticalOffset);

protected:
    // Init
    void init();
    // Clear
    void clear();

    // Load Component Anchors
    void loadComponentAnchors(const QJsonObject& aObject);
    // Save Component Anchors
    void saveComponentAnchors();

protected: // Data
    // Component
    ComponentInfo*      mComponent;

    // Ancors Left Target
    QString             mAnchorLeft;
    // Ancors Right Target
    QString             mAnchorRight;
    // Ancors Top Target
    QString             mAnchorTop;
    // Ancors Bottom Target
    QString             mAnchorBottom;

    // Ancors Fill Target
    QString             mAnchorFill;
    // Ancors Center In Target
    QString             mAnchorCenterIn;

    // Anchor Margins
    QString             mAnchorMargins;

    // Ancors Left Margin
    QString             mAnchorLeftMargin;
    // Ancors Right Margin
    QString             mAnchorRightMargin;
    // Ancors Top Margin
    QString             mAnchorTopMargin;
    // Ancors Bottom Margin
    QString             mAnchorBottomMargin;

    // Ancors Horizontal Center Offset
    QString             mAnchorHorizontalOffset;
    // Ancors Vertical Center Offset
    QString             mAnchorVerticalOffset;
};

#endif // COMPONENTANCHORSMODEL_H
