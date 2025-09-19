import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 160
    height: 128
    visible: true
    color: "#000000"
    title: qsTr("Hello World")

    SwipeView {
        id: swiper
        anchors.fill: parent

        WeatherPage {}
        ForecastPage {}
    }

    Timer {
            interval: 5000
            running: true
            repeat: true
            onTriggered: swiper.currentIndex = (swiper.currentIndex + 1) % swiper.count
        }

}
