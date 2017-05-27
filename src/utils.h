#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QString>
#include <QStringList>

//==============================================================================
// Utils Class
//==============================================================================
class Utils : public QObject
{
    Q_OBJECT

public:
    // Constructor
    explicit Utils(QObject* aParent = NULL);

    // Compose Type And Vlaue
    static QString composeTypeAndValue(const QString& aType,
                                       const QString& aValue,
                                       const QString& aMin = "",
                                       const QString& aMax = "",
                                       const QString& aEnums = "",
                                       const bool& aReadOnly = false,
                                       const bool& aDefault = false);

    // Parse Component Property Type
    static QString parseType(const QString& aTypeAndValue, bool& readOnly, bool& defaultAlias, const bool& aTypeOnly = false);
    // Parse Component Property Enum Values
    static QStringList parseEnumValues(const QString& aTypeAndValue);
    // Parse Component Property Enum Values
    static QString parseEnumValuesToString(const QString& aTypeAndValue);
    // Parse Component Property Min Value
    static QString parseMinValue(const QString& aTypeAndValue);
    // Parse Component Property Max Value
    static QString parseMaxValue(const QString& aTypeAndValue);
    // Parse Component Property Value
    static QString parseValue(const QString& aTypeAndValue, const bool& aRaw = false);
    // Parse Component Property Formula
    static QString parseFormula(const QString& aTypeAndValue);
    // Parse Component Property Binding
    static QString parseBinding(const QString& aTypeAndValue);
    // Parse has Formula
    static int hasFormula(const QString& aTypeAndValue, const int& aStart = 0);
    // Parse has Binding
    static int hasBinding(const QString& aTypeAndValue);

    // ...

};

#endif // UTILS_H
