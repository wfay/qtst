import QtQuick 2.0
import QtQuick.Controls 1.4
import QtPositioning 5.2
Rectangle {
    id:root
    width: 100; height: 100
    color: "green"
    property var direction:"买"
    property var offset:"开"
    property var volume:"1"
    property var price:"1"
    property var arbtrigeflag
    property var selS:stockSelect.currentText
    property var tradeIdx
    property var cpp
    property var hpp
    property var available
    onTradeIdxChanged:
    {
        console.log("Changed\n"); insertoUndealed()
    }
    function removeSelection( naum)
    {
        for (var i=0; i<libraryModel.count; ++i)
        {
            if (libraryModel.get(i).num === naum){
                libraryModel2.append(libraryModel.get(i))
                libraryModel.remove(i);
                i=0; //read from the start! Because index has changed after removing
            }
        }
    }

    function insertoUndealed()//,pvolume,pdirection,poffset,pprice
    {
       libraryModel.append({num:tradeIdx,volume:volume,kaiping:offset,sell:direction,price:price,contractID:selS,AFlag:arbtrigeflag})
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.tradeIdx="abc"
 //           insertoUndealed();
        }
    }
    Text {
        id:cpprofit
        x:200
        y:100
        width: 125
        height: 40
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        verticalAlignment: Text.AlignVCenter
        text: "平仓盈利："+cpp
    }

    Text {
        id:hpprofit
        x:200
        y:150
        width: 125
        height: 40
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        verticalAlignment: Text.AlignVCenter
        text: "持仓盈利："+hpp
    }
    Text {
        id:ava
        x:200
        y:150
        width: 125
        height: 40
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        verticalAlignment: Text.AlignVCenter
        text: "可用资金："+available
    }
    Text {
        id:askText
        x:20
        y:100
        width: 125
        height: 40
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        verticalAlignment: Text.AlignVCenter
        text: "当前一档卖出价："+myObject.ask.toFixed(2)
    }
    Text {
        id:bidText
        x:20
        y:70
        width: 125
        height: 40
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        verticalAlignment: Text.AlignVCenter
        text: "当前一档买入价："+myObject.bid.toFixed(2)
    }
    ComboBox {
  //      anchors.top: parent.top
 //       anchors.topMargin: 15
        id:stockSelect
        activeFocusOnPress: true
        width: 200
        model: [ "请选择","IF1508","IF1509", "IF1512","IH1508","IH1509","IH1512","IF1603","IH1603" ]
        objectName:"stockSelect"
 //       currentText: "IF1508"
        onCurrentIndexChanged:{
            myObject.getSelect(currentText);
        }
    }

    Column {
        x:400
        y:90
        objectName:"TradeType1"
        ExclusiveGroup { id: checked1 }

        CheckBox {
            id: buy
            text: qsTr("买入")
 //           text.ffont.pointSize: 20
            exclusiveGroup: checked1
            checked:false
            onCheckedChanged: {if(buy.checked){ myObject.set_direction(0);}}
        }
        CheckBox {
            id:sale
            text: qsTr("卖出")
            exclusiveGroup: checked1
            checked:false
            onCheckedChanged: {if(sale.checked){myObject.set_direction(1);}}
        }

    }
    Column {
        x:330
        y:90
        id:t2
        objectName:"TradeType2"
        ExclusiveGroup { id: checked2 }

        CheckBox {
            id:pull
            text: qsTr("开仓")
            checked:false
            exclusiveGroup: checked2
            onCheckedChanged: {if(pull.checked){myObject.set_offset(0);}}

        }
        CheckBox {
            id:even
            text: qsTr("平仓")
            checked:false
            exclusiveGroup: checked2
            onCheckedChanged: {if(even.checked){myObject.set_offset(1);}}

        }
    }
    Column {
        x:470
        y:90
        objectName:"priceType"
        ExclusiveGroup { id: priceT }

        CheckBox {
            id:market
            text: qsTr("市价")
            checked:false
            exclusiveGroup: priceT
            onCheckedChanged: {if(market.checked){myObject.set_pricetype(1);}}

        }
        CheckBox {
            id:limited
            text: qsTr("限价")
            checked:false
            exclusiveGroup: priceT
            onCheckedChanged: {if(limited.checked){myObject.set_pricetype(2);}}

        }
    }

    Column {
        x:450
        y:150
        objectName:"priceType"
        ExclusiveGroup { id: hedgeT }
        CheckBox {
            id:touji
            text: qsTr("投机")
            checked:false
            exclusiveGroup: hedgeT
            onCheckedChanged: {if(touji.checked){myObject.set_hedge(1);}}

        }
        CheckBox {
            id:taobao
            text: qsTr("套保")
            checked:false
            exclusiveGroup: hedgeT
            onCheckedChanged: {if(taobao.checked){myObject.set_hedge(2);}}

        }
        CheckBox {
            id:taoli
            text: qsTr("套利")
            checked:false
            exclusiveGroup: hedgeT
            onCheckedChanged: {if(taoli.checked){myObject.set_hedge(3);}}

        }
    }
    Column {
        x:330
        y:150
        objectName:"timeCon"
        ExclusiveGroup { id: timeT }
        CheckBox {
            id:ioc
            text: qsTr("IOC")
            checked:false
            exclusiveGroup: timeT
            onCheckedChanged: {if(ioc.checked){myObject.set_timeCon(1);}}

        }
        CheckBox {
            id:benjie
            text: qsTr("本节有效")
            checked:false
            exclusiveGroup: timeT
            onCheckedChanged: {if(benjie.checked){myObject.set_timeCon(2);}}

        }
        CheckBox {
            id:dangri
            text: qsTr("当日有效")
            checked:false
            exclusiveGroup: timeT
            onCheckedChanged: {if(dangri.checked){myObject.set_timeCon(3);}}

        }
    }
    Column {
        x:130
        y:150
        objectName:"volumeCon"
        ExclusiveGroup { id: volumeC }
        CheckBox {
            id:any
            text: qsTr("任意数量")
            checked:false
            exclusiveGroup: volumeC
            onCheckedChanged: {if(any.checked){myObject.set_volume_condition(1);}}

        }
        CheckBox {
            id:min
            text: qsTr("最小数量")
            checked:false
            exclusiveGroup: volumeC
            onCheckedChanged: {if(min.checked){myObject.set_volume_condition(2);}}

        }
        CheckBox {
            id:all
            text: qsTr("全部数量")
            checked:false
            exclusiveGroup: volumeC
            onCheckedChanged: {if(all.checked){myObject.set_volume_condition(3);}}

        }
    }
    Text {
        x:50
        y:250
        width: 125
        height: 40
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        verticalAlignment: Text.AlignVCenter
        text: "输入价格："
    }
    TextField {
        id:pricetext
        x:200
        y:260
        placeholderText: qsTr("price")
                onAccepted: {
                    myObject.set_limitprice(text)}
    }
    Text {
        x:50
        y:300
        width: 125
        height: 40
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        verticalAlignment: Text.AlignVCenter
        text: "手    数："
    }
    TextField {
        id:volumetext
        x:200
        y:310
        placeholderText: qsTr("volume")
                onAccepted: {
                    myObject.set_volume(text)}
    }
    Button {
        x:200
        y:350
        text: "确定"
        onClicked:
        {
 //           console.log("clicked\n")
            myObject.set_limitprice(pricetext.text)
            myObject.set_volume(volumetext.text)
            myObject.set_g_choose(1);
 //           libraryModel.append({num:"3",volume:volumetext.text,kaiping:"开",sell:"买",price:"23",contractID:selS})
        }
    }
    Button {
        x:370
        y:260
        text: "当前买一价"
        onClicked:
        {
            pricetext.text=myObject.ask.toFixed(2);
        }
    }
    Button {
        x:470
        y:260
        text: "当前卖一价"
        onClicked:
        {
            pricetext.text=myObject.bid.toFixed(2);
        }
    }
        Text {
            id:undealedText
            x:750
            y:50
            width: 125
            height: 40
            color: "#000000"
            font.family: "Open Sans"
            font.pointSize: 20
            font.weight: Font.Bold
            verticalAlignment: Text.AlignVCenter
            text: "尚未成交"
        }
        TableView {
            x:750
            y:100
            width:800
            sortIndicatorVisible:true
            onDoubleClicked: {myObject.set_g_choose(2); myObject.set_drop_num(libraryModel.get(row).num )}
            TableViewColumn {
                role: "num"
                title: "单号"
                width: 100
            }
            TableViewColumn {
                role: "volume"
                title: "手数"
                width: 100
            }
            TableViewColumn {
                role: "kaiping"
                title: "开平"
                width: 100
            }
            TableViewColumn {
                role: "sell"
                title: "买卖"
                width: 100
            }

            TableViewColumn {
                role: "price"
                title: "价格"
                width: 100
            }
            TableViewColumn {
                role: "contractID"
                title: "合约代码"
                width: 100
            }
            TableViewColumn {
                role: "AFlag"
                title: "投保标志"
                width: 100
            }
// undealed
            model: libraryModel
        }
        ListModel {
            id: libraryModel
        }
        Text {
            id:dealedText
            x:750
            y:300
            width: 125
            height: 40
            color: "#000000"
            font.family: "Open Sans"
            font.pointSize: 20
            font.weight: Font.Bold
            verticalAlignment: Text.AlignVCenter
            text: "已成交"
        }
        TableView {
            x:750
            y:350
            width:800
//            sortIndicatorVisible:true
//            onDoubleClicked: {myObject.set_g_choose(2); myObject.set_drop_num(libraryModel.get(row).num )}
            TableViewColumn {
                role: "num"
                title: "单号"
                width: 100
            }
            TableViewColumn {
                role: "volume"
                title: "手数"
                width: 100
            }
            TableViewColumn {
                role: "kaiping"
                title: "开平"
                width: 100
            }
            TableViewColumn {
                role: "sell"
                title: "买卖"
                width: 100
            }

            TableViewColumn {
                role: "price"
                title: "价格"
                width: 100
            }
            TableViewColumn {
                role: "contractID"
                title: "合约代码"
                width: 100
            }
            TableViewColumn {
                role: "AFlag"
                title: "投保标志"
                width: 100
            }
            //dealed
            model: libraryModel2
        }
        ListModel {
            id: libraryModel2
        }
}

