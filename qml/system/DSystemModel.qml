pragma Singleton

import QtQuick 2.0

QtObject {
    id: systemmModelRoot

    property string firstMousePressOwner: ""

    property bool systemBusy: false

    signal cancelMarkForDeletion()

    // ...
}
