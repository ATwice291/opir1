import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    Rectangle {
        anchors.fill: parent
        visible: true
        color: "#000000"

        Text {
            id: tClock
            anchors {
                top:  parent.top
                left: parent.left
                right: parent.right
            }
            height: 18
            color: "#efefef"
            text: timeProvider.timeString
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }

        Image {
            id: image
            x: 60
            y: 10
            width: 100
            height: 100
            source: "images/" + weatherProvider.currentWeatherIcon + ".png"
            scale: 0.5
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: tTemperature
            x: 0
            y: 17
            width: 100
            height: 61
            color: "#efefef"
            text: weatherProvider.currentTemp + "°"
            font.letterSpacing: -3
            font.pixelSize: 50
            horizontalAlignment: Text.AlignRight
            textFormat: Text.PlainText
            font.family: "PF DinDisplay Pro"
        }

        Text {
            id: tDescription
            x: 0
            y: 84
            width: 160
            height: 18
            color: "#efefef"
            text: weatherProvider.currentWeatherDescription
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
            NumberAnimation on x {
                from: (tDescription.width-tDescription.contentWidth)/2
                to: (tDescription.contentWidth-tDescription.width)/2
                duration: 5000
                loops: Animation.Infinite
            }
        }

        Text {
            id: tHumidity
            x: 0
            y: 105
            width: 80
            height: 18
            color: "#efefef"
            text: weatherProvider.currentHumid + "%"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }

        Text {
            id: tPressure
            x: 80
            y: 105
            width: 80
            height: 18
            color: "#efefef"
            text: weatherProvider.currentPress + "hPa"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }
    }
}
