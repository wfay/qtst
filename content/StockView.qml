/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Window 2.1
import QtPositioning 5.2
Rectangle {
    id: root
    width: 320
    height: 480
    color: "transparent"

    property var stock: null
    property var stocklist: null
    property string tradeinfo:tradepanel.selS
    signal settingsClicked

    function update() {
        chart.update()
    }

    Rectangle {
        id: mainRect
        color: "transparent"
        anchors.fill: parent

        StockInfo {
            id: stockInfo
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 15
            height: 160
            anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : chart.left
            anchors.rightMargin: 20
            stock: root.stock
        }

        StockChart {
            id: chart
            anchors.bottom: Screen.primaryOrientation === Qt.PortraitOrientation ? settingsPanel.top : parent.bottom
            anchors.bottomMargin: 20
            anchors.top : Screen.primaryOrientation === Qt.PortraitOrientation ? stockInfo.bottom : parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.width - 40 : 0.6 * parent.width
            stockModel: root.stock
            settings: settingsPanel
        }

        StockSettingsPanel {
            id: settingsPanel
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : chart.left
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            onDrawOpenPriceChanged: root.update()
            onDrawClosePriceChanged: root.update();
 //           onDrawHighPriceChanged: root.update();
 //           onDrawLowPriceChanged: root.update();
        }
        Tradepanel {
            x:10
            y:200
            id: tradepanel
//            anchors.left: parent.left
//            anchors.leftMargin: 20
//            anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : chart.left
//            anchors.rightMargin: 20
//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: 400
//            onDrawOpenPriceChanged: root.update()
//            onDrawClosePriceChanged: root.update();
//            onDrawHighPriceChanged: root.update();
//            onDrawLowPriceChanged: root.update();
        }

    }
}
