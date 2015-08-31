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

ListModel {
    id: model
    property string stockId: ""
    property string stockName: ""
    property string stockDataCycle: "d"
    property bool ready: false
    property real stockPrice: 0.0
    property real stockPriceChanged: 0.0
    property real data:myObject.curr
    onDataChanged: {console.log(data);}
    signal dataReady
    property int dataIdx:0
    function indexOf(date) {
        var newest = new Date(model.get(0).date);
        var oldest = new Date(model.get(model.count - 1).date);
        if (newest <= date)
            return -1;

        if (oldest >= date)
            return model.count - 1;

        var currDiff = 0;
        var bestDiff = Math.abs(date.getTime() - newest.getTime());
        var retval = 0;
        for (var i = 0; i < model.count; i++) {
            var d = new Date(model.get(i).date);
            currDiff = Math.abs(d.getTime() - date.getTime());
            if (currDiff < bestDiff) {
                bestDiff = currDiff;
                retval = i;
            }
            if (currDiff > bestDiff)
                return retval;
        }

        return -1;
    }

    function createStockPrice(r) {
        return {
   //             "date": r[0],
                "time1":r[1],
                "time2":r[2],
                "ask":r[3],
                "bid":r[4],
 //               "volume":r[5],
 //               "adjusted":r[6]
               };
    }

    function updateStock() {
   //     var req = requestUrl();

 //       if (!req)
 //           return;

 //       var xhr = new XMLHttpRequest;

    //    xhr.open("GET", req, true);
 //       xhr.open("GET", 'ab.txt');
        model.ready = false;
        model.clear();
 //       var i = 0; //skip the first line
//        xhr.onreadystatechange = function() {
 //           if (xhr.readyState === XMLHttpRequest.DONE) {

  //              var records = data;

                for (;dataIdx < 4; dataIdx++ ) {
   //                 myObject.readnextdata();
  //                  console.log(data);
  //                  var r = records[i].split(',');
 //                   if (r.length === 5)
 //                       model.append(createStockPrice(r));
                }

 //               if (xhr.readyState === XMLHttpRequest.DONE) {
 //                   if (model.count > 0) {
 //                       model.ready = true;
 //                       model.stockPrice = model.get(0).adjusted;
 //                       model.stockPriceChanged = model.count > 1 ? (Math.round((model.stockPrice - model.get(1).close) * 100) / 100) : 0;
  //                      model.dataReady(); //emit signal
  //                  }
                }
            }
 //       }
//        xhr.send()
//    }
//}
