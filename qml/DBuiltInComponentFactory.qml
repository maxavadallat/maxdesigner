pragma Singleton

import QtQuick 2.0

QtObject {
    id: builtInComponentFactoryRoot

    Component {
        id: itemComponent
        Item { }
    }

    Component {
        id: rectangleComponent
        Rectangle { }
    }

    Component {
        id: imageComponent
        Image { }
    }

    Component {
        id: borderImageComponent
        BorderImage { }
    }

    // Create Built In Component
    function createBuiltInComponent(componentName) {

    }
}
