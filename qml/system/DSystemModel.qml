pragma Singleton

import QtQuick 2.0

QtObject {
    id: systemmModelRoot

    property bool testValue: true

    signal cancelMarkForDeletion()

    // ...
}
