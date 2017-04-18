pragma Singleton

import QtQuick 2.0

QtObject {
    id: systemmModelRoot

    property string lastMousePressOwner: ""

    signal cancelMarkForDeletion()

    // ...
}
