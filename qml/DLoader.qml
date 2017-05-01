import QtQuick 2.0

Loader {
    id: loaderRoot
    asynchronous: true
    active: false

    onStatusChanged: {
        console.log("DLoader.onStatusChanged - status: " + status);
    }
}
