
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

ApplicationWindow {
    visible: true
    width: 1400
    height: 900
    title: "实验5：动态囚徒困境博弈模拟系统"
    color: "#0f0f1a"
    
    property var stage1Data: null
    property var stage2Data: {}
    property string resultText: "就绪"
    property bool success: false
    
    // Custom Font - WSL Path to Windows Fonts
    FontLoader { 
        id: msYaHei
        source: "/mnt/c/Windows/Fonts/msyh.ttc" 
    }
    FontLoader {
        id: consolas
        source: "/mnt/c/Windows/Fonts/consola.ttf"
    }

    Connections {
        target: gameController
        function onMatrixDataChanged(jsonData) {
            var data = JSON.parse(jsonData);
            stage1Data = data.stage1;
            stage2Data = data.stage2;
            success = data.success;
        }
        function onResultSummaryChanged(text) {
            // Translate summary manually or from backend
            if (text.indexOf("SUCCESS") !== -1) resultText = "策略结果: 成功 (至少有一人坦白)";
            else if (text.indexOf("FAILURE") !== -1) resultText = "策略结果: 失败 (两人均沉默)";
            else resultText = text;
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        // --- Controls Panel (Left) ---
        Rectangle {
            Layout.preferredWidth: 380
            Layout.fillHeight: true
            color: "#161623"
            border.color: "#3b3b5c"
            
            ScrollView {
                anchors.fill: parent
                contentWidth: parent.width
                clip: true
                
                ColumnLayout {
                    width: parent.width - 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    spacing: 20
                    
                    Text { 
                        text: "警察信念 (概率分布)" 
                        font.family: "Microsoft YaHei"
                        font.bold: true
                        font.pixelSize: 16
                        color: "#a0a0c0"
                    }
                    
                    Repeater {
                        model: ["一级报复 (轻微)", "二级报复", "三级报复", "四级报复 (严重)"]
                        ColumnLayout {
                            spacing: 5
                            Layout.fillWidth: true
                            
                            RowLayout {
                                Text { text: modelData; color: "#e0e0e0"; font.pixelSize: 13; Layout.fillWidth: true }
                                Text { text: (slider.value).toFixed(0) + "%"; color: "#4ade80"; font.bold: true }
                            }
                            
                            Slider {
                                id: slider
                                Layout.fillWidth: true
                                from: 0; to: 100; value: 25
                                stepSize: 5
                                onValueChanged: updateBeliefs()
                                
                                background: Rectangle {
                                    x: slider.leftPadding
                                    y: slider.topPadding + slider.availableHeight / 2 - height / 2
                                    implicitWidth: 200
                                    implicitHeight: 4
                                    width: slider.availableWidth
                                    height: implicitHeight
                                    radius: 2
                                    color: "#3b3b5c"
                                    
                                    Rectangle {
                                        width: slider.visualPosition * parent.width
                                        height: parent.height
                                        color: "#4ade80"
                                        radius: 2
                                    }
                                }
                                handle: Rectangle {
                                    x: slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
                                    y: slider.topPadding + slider.availableHeight / 2 - height / 2
                                    implicitWidth: 16
                                    implicitHeight: 16
                                    radius: 8
                                    color: "#f0f0f0"
                                    border.color: "#4ade80"
                                }

                                Component.onCompleted: sliders[index] = this
                            }
                        }
                    }
                    
                    Rectangle { height: 1; Layout.fillWidth: true; color: "#3b3b5c" }
                    
                    Text { 
                        text: "报复环境设定" 
                        font.family: "Microsoft YaHei"
                        font.bold: true; font.pixelSize: 16
                        color: "#a0a0c0"
                    }
                    
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 8
                        RowLayout {
                            Text { text: "黑社会强度系数"; color: "#e0e0e0"; Layout.fillWidth: true }
                            Text { text: gangSlider.value.toFixed(1); color: "#60a5fa" }
                        }
                        Slider {
                            id: gangSlider
                            Layout.fillWidth: true
                            from: 0.5; to: 5.0; value: 2.0; stepSize: 0.1
                            onValueChanged: updateSettings()
                        }
                    }
                    
                    CheckBox {
                        id: inverseCheck
                        text: "启用逆向规则 (沉默方报复)"
                        checked: true
                        onCheckedChanged: updateSettings()
                        
                        contentItem: Text {
                            text: inverseCheck.text
                            font.family: "Microsoft YaHei"
                            color: "#e0e0e0"
                            leftPadding: inverseCheck.indicator.width + inverseCheck.spacing
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    
                    ColumnLayout {
                        spacing: 8
                        Text { text: "均衡选择策略 (保守/乐观)"; color: "#a0a0c0" }
                        ComboBox {
                            id: strategyBox
                            Layout.fillWidth: true
                            model: ["optimistic", "pessimistic", "average"]
                            textRole: "display"
                            currentIndex: 1 // pessimistic
                            onActivated: updateSettings()
                            
                            delegate: ItemDelegate {
                                width: strategyBox.width
                                contentItem: Text {
                                    text: modelData === "optimistic" ? "乐观 (取最大收益)" : 
                                          modelData === "pessimistic" ? "保守 (取最小收益)" : "平均 (取期望值)"
                                    color: "#e0e0e0"
                                    elide: Text.ElideRight
                                    verticalAlignment: Text.AlignVCenter
                                }
                                background: Rectangle { color: parent.highlighted ? "#3b3b5c" : "transparent" }
                            }
                            contentItem: Text {
                                text: strategyBox.currentText === "optimistic" ? "乐观 (取最大收益)" : 
                                      strategyBox.currentText === "pessimistic" ? "保守 (取最小收益)" : "平均 (取期望值)"
                                color: "#e0e0e0"
                                verticalAlignment: Text.AlignVCenter
                                leftPadding: 10
                            }
                            background: Rectangle {
                                color: "#2a2a4a"
                                border.color: "#3b3b5c"
                                radius: 4
                            }
                        }
                    }
                    
                    Rectangle { height: 1; Layout.fillWidth: true; color: "#3b3b5c" }
                    
                    Text { 
                        text: "第一阶段刑期设定 (年)" 
                        font.family: "Microsoft YaHei"
                        font.bold: true; font.pixelSize: 16
                        color: "#a0a0c0"
                    }
                    
                    GridLayout {
                        columns: 2
                        columnSpacing: 15
                        rowSpacing: 15
                        
                        Text { text: "坦白/沉默 (奖励)"; color: "#e0e0e0" }
                        MySpinBox { id: sb_cs; value: 0; onValueModified: updateYears() }
                        
                        Text { text: "沉默/坦白 (受骗)"; color: "#e0e0e0" }
                        MySpinBox { id: sb_sc; value: 10; onValueModified: updateYears() }
                        
                        Text { text: "双方坦白 (惩罚)"; color: "#e0e0e0" }
                        MySpinBox { id: sb_cc; value: 5; onValueModified: updateYears() }
                        
                        Text { text: "双方沉默 (合谋)"; color: "#e0e0e0" }
                        MySpinBox { id: sb_dd; value: 1; onValueModified: updateYears() }
                    }
                    
                    Rectangle { height: 1; Layout.fillWidth: true; color: "#3b3b5c" }
                    
                    Button {
                        text: "🔍 自动寻找最优激励策略"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 40
                        onClicked: gameController.findOptimalStrategy()
                        
                        contentItem: Text {
                            text: parent.text
                            font.family: "Microsoft YaHei"
                            font.bold: true
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            color: parent.down ? "#1d4ed8" : "#2563eb"
                            radius: 6
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 80
                        color: success ? "#14532d" : "#450a0a"
                        radius: 8
                        border.color: success ? "#22c55e" : "#ef4444"
                        
                        ColumnLayout {
                            anchors.centerIn: parent
                            Text { 
                                text: resultText
                                font.family: "Microsoft YaHei"
                                font.bold: true
                                font.pixelSize: 14
                                color: "#ffffff"
                            }
                        }
                    }
                }
            }
        }
        
        // --- Visualization Panel (Right) ---
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            
            ColumnLayout {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 80 
                spacing: 40 
                
                // Stage 1
                ColumnLayout {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 15
                    
                    Text { 
                        text: "第一阶段：坦白-沉默博弈 (包含未来预期)"
                        font.family: "Microsoft YaHei"
                        font.pixelSize: 24
                        font.bold: true
                        color: success ? "#4ade80" : "#ef4444"
                        Layout.alignment: Qt.AlignHCenter
                    }
                    
                    Text {
                        text: "表格数值 = 基础刑期(负值) + 第二阶段期望收益"
                        color: "#a0a0c0"
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignHCenter
                    }
                    
                    PayoffMatrix {
                        Layout.alignment: Qt.AlignHCenter
                        title: "囚徒困境 (调整后收益矩阵)"
                        strategies1: ["坦白", "沉默"]
                        strategies2: ["坦白", "沉默"]
                        p1Data: stage1Data ? stage1Data.p1 : [[0,0],[0,0]]
                        p2Data: stage1Data ? stage1Data.p2 : [[0,0],[0,0]]
                        eqCoords: stage1Data ? stage1Data.eqCoords : []
                        isHighlighted: true
                    }
                    
                    RowLayout {
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 30
                        Text { 
                            text: "坦白者未来期望值: " + (stage1Data ? stage1Data.confessor_future.toFixed(2) : "0.00")
                            color: "#60a5fa" 
                            font.bold: true
                            font.pixelSize: 16
                        }
                        Text { 
                            text: "报复者(沉默方)未来期望值: " + (stage1Data ? stage1Data.retaliator_future.toFixed(2) : "0.00")
                            color: "#f472b6" 
                            font.bold: true
                            font.pixelSize: 16
                        }
                    }
                }
                
                Rectangle { height: 1; Layout.fillWidth: true; color: "#3b3b5c" }
                
                // Stage 2
                Text { 
                    text: "第二阶段：报复-对抗博弈 (各等级详情)"
                    font.family: "Microsoft YaHei"
                    font.pixelSize: 20
                    font.bold: true
                    color: "#e0e0e0"
                    Layout.alignment: Qt.AlignHCenter
                }
                
                GridLayout {
                    columns: 2
                    columnSpacing: 40
                    rowSpacing: 40
                    Layout.alignment: Qt.AlignHCenter
                    
                    Repeater {
                        model: [1, 2, 3, 4]
                        PayoffMatrix {
                            property var d: stage2Data ? stage2Data[modelData] : null
                            title: "报复等级 " + modelData + " (概率: " + (sliders[modelData-1] ? sliders[modelData-1].value : 25) + "%)"
                            strategies1: ["对抗", "不对抗"]
                            strategies2: ["报复", "不报复"]
                            p1Data: d ? d.p1 : [[0,0],[0,0]]
                            p2Data: d ? d.p2 : [[0,0],[0,0]]
                            eqCoords: d ? d.eqCoords : []
                        }
                    }
                }
            }
        }
    }

    // Custom SpinBox Component
    component MySpinBox : SpinBox {
        from: 0; to: 20
        editable: true
        contentItem: TextInput {
            text: parent.value
            color: "#e0e0e0"
            font.bold: true
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            readOnly: !parent.editable
            validator: parent.validator
        }
        background: Rectangle {
            color: "#2a2a4a"
            border.color: "#3b3b5c"
            radius: 4
        }
        up.indicator: Rectangle {
            width: parent.height
            height: parent.height
            color: parent.up.pressed ? "#3b3b5c" : "transparent"
            Text { text: "+"; color: "#a0a0c0"; anchors.centerIn: parent }
        }
        down.indicator: Rectangle {
            width: parent.height
            height: parent.height
            color: parent.down.pressed ? "#3b3b5c" : "transparent"
            Text { text: "-"; color: "#a0a0c0"; anchors.centerIn: parent }
        }
    }

    // Slider Logic
    property var sliders: [null, null, null, null]
    function updateBeliefs() {
        if (sliders[0])
            gameController.updateBeliefs(sliders[0].value, sliders[1].value, sliders[2].value, sliders[3].value);
    }
    function updateSettings() {
        gameController.updateSettings(gangSlider.value, inverseCheck.checked, strategyBox.currentText);
    }
    function updateYears() {
        gameController.updatePrisonYears(sb_cc.value, sb_cs.value, sb_sc.value, sb_dd.value);
    }
    
    // 在 QML 加载完成后触发初始计算
    // 这样可以确保信号连接已建立，GUI 能接收到数据
    Component.onCompleted: {
        // 延迟一小段时间确保所有组件都已初始化
        Qt.callLater(function() {
            updateSettings();
        });
    }
}
