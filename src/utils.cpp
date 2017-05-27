#include <QDebug>

#include "utils.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
Utils::Utils(QObject* aParent)
    : QObject(aParent)
{

}

//==============================================================================
// Compose Type And Vlaue
//==============================================================================
QString Utils::composeTypeAndValue(const QString& aType,
                                   const QString& aValue,
                                   const QString& aMin,
                                   const QString& aMax,
                                   const QString& aEnums,
                                   const bool& aReadOnly,
                                   const bool& aDefault)
{
    // Init New Type
    QString newType = aReadOnly ? QString("%1 %2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_READONLY).arg(aType) : aType;

    // Check Default
    if (aDefault && !aReadOnly) {
        // Set New Type
        newType = QString("%1 %2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_DEFAULT).arg(aType);
    }

    return QString("%1:%2:%3:%4:%5").arg(newType).arg(aMin).arg(aMax).arg(aEnums).arg(aValue);
}

//==============================================================================
// Parse Component Property Type
//==============================================================================
QString Utils::parseType(const QString& aTypeAndValue, bool& readOnly, bool& defaultAlias, const bool& aTypeOnly)
{
    // Get Property Type
    QString pType = aTypeAndValue.left(aTypeAndValue.indexOf(":"));
    // Init Type Pos
    int typePos = 0;

    // Check Type
    if (pType.indexOf(JSON_VALUE_PROPERTY_TYPE_PREFIX_READONLY) >= 0) {
        // Set Read Only
        readOnly = true;
        // Set Type Pos
        typePos = 9;
    } else {
        // Check Type
        if (pType.indexOf(JSON_VALUE_PROPERTY_TYPE_PREFIX_DEFAULT) >= 0) {
            // Set Default Alias
            defaultAlias = true;
            // Set Type Pos
            typePos = 8;
        }
    }

    return aTypeOnly ? pType.mid(typePos) : pType;
}

//==============================================================================
// Parse Component Property Enum Values
//==============================================================================
QStringList Utils::parseEnumValues(const QString& aTypeAndValue)
{
    // Get Value Elements
    QStringList valueElements = aTypeAndValue.split(":");

    // Check Type
    if (valueElements.count() >= 5 && valueElements[0] == JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM && valueElements[3].length() > 0) {
        return valueElements[3].split(",");
    }

    return QStringList();
}

//==============================================================================
// Parse Component Property Enum Values
//==============================================================================
QString Utils::parseEnumValuesToString(const QString& aTypeAndValue)
{
    // Get Value Elements
    QStringList valueElements = aTypeAndValue.split(":");

    // Check Type
    if (valueElements.count() >= 5 && valueElements[0] == JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM && valueElements[3].length() > 0) {
        return valueElements[3];
    }

    return "";
}

//==============================================================================
// Parse Component Property Min Value
//==============================================================================
QString Utils::parseMinValue(const QString& aTypeAndValue)
{
    // Get Value Elements
    QStringList valueElements = aTypeAndValue.split(":");
    // Check Value Elements
    if (valueElements.count() >= 5) {
        return valueElements[1];
    }

    return "";
}

//==============================================================================
// Parse Component Property Max Value
//==============================================================================
QString Utils::parseMaxValue(const QString& aTypeAndValue)
{
    // Get Value Elements
    QStringList valueElements = aTypeAndValue.split(":");

    // Check Value Elements
    if (valueElements.count() >= 5) {
        return valueElements[2];
    }

    return "";
}

//==============================================================================
// Parse Component Property Value
//==============================================================================
QString Utils::parseValue(const QString& aTypeAndValue, const bool& aRaw)
{
    // Check Raw
    if (!aRaw) {
        // Get Binding Pos
        int bPos = hasBinding(aTypeAndValue);

        // Check Binding Pos
        if (bPos > 0) {
            return "";
        }
    }

    // Init Value Section Pos
    int vsPos = 0;

    // Get To Values Section
    for (int i=0; i<4; i++) {
        // Get New : pos
        vsPos = aTypeAndValue.indexOf(":", vsPos + 1);
        // Check : Pos
        if (vsPos == -1) {
            return "";
        }
    }

    return aTypeAndValue.mid(vsPos + 1);
}

//==============================================================================
// Parse Component Property Formula
//==============================================================================
QString Utils::parseFormula(const QString& aTypeAndValue)
{
//    // Get Biding Pos
//    int bPos = hasBinding(aTypeAndValue);
//    // Int Formula Pos
//    int fPos = hasFormula(aTypeAndValue, bPos);

//    // Check Formula Pos
//    if (fPos > 0) {
//        return aTypeAndValue.mid(fPos + 1, aTypeAndValue.lastIndexOf("}") - fPos);
//    }

    // Get Formula Pos
    int fPos = hasFormula(aTypeAndValue);

    // Check Formula Pos
    if (fPos > 0) {
        // Get { Pos
        int obPos = aTypeAndValue.indexOf("{", fPos);
        // Get } Pos
        int cbPos = aTypeAndValue.lastIndexOf("}");

        return aTypeAndValue.mid(obPos + 1, cbPos - obPos - 1);
    }

    return "";
}

//==============================================================================
// Parse Component Property Binding
//==============================================================================
QString Utils::parseBinding(const QString& aTypeAndValue)
{
    // Get Biding Pos
    int bPos = hasBinding(aTypeAndValue);

    // Check Binding Pos
    if (bPos > 0) {
        // Get Formula Pos
        int fPos = hasFormula(aTypeAndValue, bPos);
        // Check Formula Pos
        if (fPos - bPos == 1) {
            return "";
        }

        return aTypeAndValue.mid(bPos + 1);
    }

    return "";
}

//==============================================================================
// Parse has Formula
//==============================================================================
int Utils::hasFormula(const QString& aTypeAndValue, const int& aStart)
{
    return aTypeAndValue.indexOf("{", aStart);
}

//==============================================================================
// Parse has Binding
//==============================================================================
int Utils::hasBinding(const QString& aTypeAndValue)
{
    return aTypeAndValue.indexOf("$");
}
