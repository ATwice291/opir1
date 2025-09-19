import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts 2.15

Page {
    Rectangle {
        anchors.fill: parent
        visible: true
        color: "#000000"


        Text {
            id: tTime1
            x: 0
            y: 0
            width: 40
            height: 18
            color: "#efefef"
            text: weatherProvider.forecast[0].hour + "h"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }


        Text {
            id: tTime2
            x: 40
            y: 0
            width: 40
            height: 18
            color: "#efefef"
            text: weatherProvider.forecast[1].hour + "h"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }

        Text {
            id: tTime3
            x: 80
            y: 0
            width: 40
            height: 18
            color: "#efefef"
            text: weatherProvider.forecast[2].hour + "h"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }

        Text {
            id: tTime4
            x: 120
            y: 0
            width: 40
            height: 18
            color: "#efefef"
            text: weatherProvider.forecast[3].hour + "h"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }


        Image {
            id: image1
            x: 0
            y: 15
            width: 40
            height: 40
            source: "images/" + weatherProvider.forecast[0].icon + ".png"
            scale: 1
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: image2
            x: 40
            y: 15
            width: 40
            height: 40
            source: "images/" + weatherProvider.forecast[1].icon + ".png"
            scale: 1
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: image3
            x: 80
            y: 15
            width: 40
            height: 40
            source: "images/" + weatherProvider.forecast[2].icon + ".png"
            scale: 1
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: image4
            x: 120
            y: 15
            width: 40
            height: 40
            source: "images/" + weatherProvider.forecast[3].icon + ".png"
            scale: 1
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: tTemp1
            x: 0
            y: 110
            width: 40
            height: 18
            color: "#efefef"
            text: weatherProvider.forecast[0].temp + "°"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }

        Text {
            id: tTemp2
            x: 40
            y: 110
            width: 40
            height: 18
            color: "#efefef"
            text: weatherProvider.forecast[1].temp + "°"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }

        Text {
            id: tTemp3
            x: 80
            y: 110
            width: 40
            height: 18
            color: "#efefef"
            text: weatherProvider.forecast[2].temp + "°"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }

        Text {
            id: tTemp4
            x: 120
            y: 110
            width: 40
            height: 18
            color: "#efefef"
            text: weatherProvider.forecast[3].temp + "°"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            font.family: "PF DinDisplay Pro"
        }

        ChartView {
            id: chart
            objectName: "chart"
            anchors.top: image2.bottom
            anchors.bottom: tTemp2.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: -5
            anchors.rightMargin: -5
            margins { right: 0; bottom: 0; left: 0; top: 0 }
            legend.visible: false
            backgroundColor: "transparent"
            antialiasing: true

            Component.onCompleted: {
                weatherProvider.setChart(chart)
            }

            ValueAxis {
                id: axisY
                objectName: "axisY"
                min: 10
                max: 30
                visible: false
                labelsVisible: false
                gridLineColor: "darkgray"
                titleVisible: false
            }

            ValueAxis {
                id: axisX
                min: 0
                max: 8
                visible: false
                labelsVisible: false
                gridLineColor: "darkgray"
                titleVisible: false
            }

            LineSeries {
                id: ser
                axisX: axisX
                axisY: axisY
                color: "orange"
                width: 4
            }

            ScatterSeries {
                id: scatSer
                axisX: axisX
                axisY: axisY
                borderColor: "orange"
                color: "orange"
                markerSize: 8
            }

            function updatePoints(points) {
                ser.clear();
                scatSer.clear();
                var minY = 100;
                var maxY = -100;
                for (var i = 0; i < points.length; ++i) {
                    var p = points[i];
                    ser.append(p.x, p.y);
                    scatSer.append(p.x, p.y);
                    if(minY > p.y) minY = p.y;
                    if(maxY < p.y) maxY = p.y;
                }
                axisY.min = minY - 2;
                axisY.max = maxY + 2;
            }
        }
    }
}
