import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 1280
    height: 800
    title: qsTr("CryptoM Calculator")

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#f4f0f8"

        Rectangle {
            height: 60
            width: parent.width
            color: "#ffffff"
            border.color: "#d4d4d4"

            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.margins: 20
                spacing: 30

                Text {
                    text: "CryptoM"
                    font.bold: true
                    font.pixelSize: 22
                    color: "#000000"
                }

                Button {
                    text: "Поиск"
                    font.pixelSize: 16
                }

                Button {
                    text: "Калькулятор"
                    font.pixelSize: 16
                }

                Button {
                    text: "Оборудование"
                    font.pixelSize: 16
                }
            }

            Text {
                text: "Поддержка | О сайте"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.margins: 20
                font.pixelSize: 16
                color: "#000000"
            }
        }

        Column {
            spacing: 20
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 80

            Text {
                text: "Калькулятор доходности"
                font.pixelSize: 28
                color: "#000000"
            }

            Row {
                spacing: 40

                Column {
                    spacing: 10

                    Text {
                        text: "Фильтр по алгоритмам"
                        font.pixelSize: 18
                        color: "#000000"
                    }

                    Rectangle {
                        width: 200
                        height: 120
                        color: "#ffffff"
                        border.color: "#d4d4d4"
                        radius: 10

                        Column {
                            spacing: 10
                            anchors.centerIn: parent

                            CheckBox {
                                text: "SHA-56"
                            }
                            CheckBox {
                                text: "Script"
                            }
                            CheckBox {
                                text: "Kadena"
                            }
                        }
                    }
                }

                Column {
                    spacing: 10

                    Text {
                        text: "Фильтр по Hash-мощности"
                        font.pixelSize: 18
                        color: "#000000"
                    }

                    Row {
                        spacing: 10

                        TextField {
                            placeholderText: "Мин. значение"
                            width: 150
                        }

                        TextField {
                            placeholderText: "Макс. значение"
                            width: 150
                        }
                    }
                }
            }

            Rectangle {
                width: parent.width * 0.8
                height: 300
                color: "#ffffff"
                radius: 10
                border.color: "#d4d4d4"

                Column {
                    spacing: 20
                    anchors.fill: parent
                    anchors.margins: 20

                    Row {
                        spacing: 20

                        Image {
                            source: "bitcoin_icon.png"
                            width: 50
                            height: 50
                        }

                        Text {
                            text: "Bitcoin"
                            font.pixelSize: 24
                            color: "#000000"
                        }

                        Text {
                            text: "$20,121.64"
                            font.pixelSize: 24
                            color: "#00a000"
                        }
                    }

                    Row {
                        spacing: 40

                        Column {
                            Text { text: "Валюта: USD"; font.pixelSize: 16 }
                            Text { text: "Hash-мощность: 2800 MH/s"; font.pixelSize: 16 }
                        }

                        Column {
                            Text { text: "Тариф электроэнергии: 0.04 RUB/kWh"; font.pixelSize: 16 }
                            Text { text: "Потребление энергии: 1370 W"; font.pixelSize: 16 }
                        }
                    }
                }
            }

            Rectangle {
                width: parent.width * 0.8
                height: 150
                color: "#ffffff"
                radius: 10
                border.color: "#d4d4d4"

                Row {
                    spacing: 50
                    anchors.centerIn: parent

                    Column {
                        spacing: 10
                        Text { text: "Позиция 1: 15642"; font.pixelSize: 16 }
                        Text { text: "Позиция 2: 236.67"; font.pixelSize: 16 }
                    }

                    Column {
                        spacing: 10
                        Text { text: "Позиция 3: SHA-256"; font.pixelSize: 16 }
                        Text { text: "Позиция 4: 254.2M"; font.pixelSize: 16 }
                    }
                }
            }
        }
    }
}
