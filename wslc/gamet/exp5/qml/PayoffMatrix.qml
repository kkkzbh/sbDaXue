import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Effects

Rectangle {
    id: root
    width: 340 // Increased width for better fit
    height: 220
    radius: 12
    color: "#1a1a2e"
    border.color: isHighlighted ? "#4ade80" : "#3b3b5c"
    border.width: isHighlighted ? 2 : 1
    
    property string title: "收益矩阵"
    property bool isHighlighted: false
    
    property var p1Data: [[0,0],[0,0]] 
    property var p2Data: [[0,0],[0,0]]
    property var strategies1: ["策略1", "策略2"]
    property var strategies2: ["策略1", "策略2"]
    property var eqCoords: [] // [[r,c], ...] coordinates of equilibria
    
    // Gradient overlay
    Rectangle {
        anchors.fill: parent
        radius: parent.radius
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#16213e" }
            GradientStop { position: 1.0; color: "#0f0f23" }
        }
        opacity: 0.7
    }
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12
        
        // Title
        Text {
            text: root.title
            font.pixelSize: 15
            font.bold: true
            font.family: "Microsoft YaHei"
            color: "#e0e0e0"
            Layout.alignment: Qt.AlignHCenter
        }
        
        // Matrix Grid
        GridLayout {
            id: grid
            columns: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            rowSpacing: 6
            columnSpacing: 6
            
            // --- Row 0: Headers ---
            
            // Corner (Empty)
            Item { 
                Layout.preferredWidth: 60
                Layout.preferredHeight: 30
            }
            
            // Column Header 1
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 30
                color: "#2a2a4a"
                radius: 4
                Text {
                    anchors.centerIn: parent
                    text: root.strategies2[0]
                    font.pixelSize: 12
                    font.family: "Microsoft YaHei"
                    color: "#a0a0c0"
                }
            }

            // Column Header 2
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 30
                color: "#2a2a4a"
                radius: 4
                Text {
                    anchors.centerIn: parent
                    text: root.strategies2[1]
                    font.pixelSize: 12
                    font.family: "Microsoft YaHei"
                    color: "#a0a0c0"
                }
            }

            // --- Row 1: Strategy 1 ---
            
            // Row Header 1
            Rectangle {
                Layout.preferredWidth: 60
                Layout.fillHeight: true
                color: "#2a2a4a"
                radius: 4
                Text {
                    anchors.centerIn: parent
                    text: root.strategies1[0]
                    font.pixelSize: 12
                    font.family: "Microsoft YaHei"
                    color: "#a0a0c0"
                }
            }

            // Cell (0,0)
            PayoffCell { row: 0; col: 0 }

            // Cell (0,1)
            PayoffCell { row: 0; col: 1 }

            // --- Row 2: Strategy 2 ---

            // Row Header 2
            Rectangle {
                Layout.preferredWidth: 60
                Layout.fillHeight: true
                color: "#2a2a4a"
                radius: 4
                Text {
                    anchors.centerIn: parent
                    text: root.strategies1[1]
                    font.pixelSize: 12
                    font.family: "Microsoft YaHei"
                    color: "#a0a0c0"
                }
            }

            // Cell (1,0)
            PayoffCell { row: 1; col: 0 }

            // Cell (1,1)
            PayoffCell { row: 1; col: 1 }
        }
    }
    
    // Inline Component for Cells to avoid repetition and ensure consistency
    component PayoffCell : Rectangle {
        property int row
        property int col
        property bool isEq: checkEq(row, col)
        
        Layout.fillWidth: true
        Layout.fillHeight: true
        radius: 6
        
        gradient: Gradient {
            GradientStop { 
                position: 0.0
                color: isEq ? "#166534" : "#252545"
            }
            GradientStop { 
                position: 1.0
                color: isEq ? "#14532d" : "#1e1e3a"
            }
        }
        
        border.color: isEq ? "#22c55e" : "#3b3b5c"
        border.width: isEq ? 2 : 1
        
        ColumnLayout {
            anchors.centerIn: parent
            width: parent.width * 0.9 // Padding
            spacing: 2
            
            Text {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                text: formatPayoff(row, col)
                
                // CRITICAL FIX: Fit text to width to avoid garbling
                fontSizeMode: Text.Fit
                minimumPixelSize: 8
                font.pixelSize: 13
                
                font.bold: true
                font.family: "Consolas"
                color: isEq ? "#86efac" : "#e0e0e0"
            }
            
            Text {
                visible: isEq
                Layout.alignment: Qt.AlignHCenter
                text: "★ 均衡"
                font.pixelSize: 10
                font.family: "Microsoft YaHei"
                color: "#4ade80"
            }
        }
    }
    
    function formatPayoff(r, c) {
        var v1 = p1Data[r] ? p1Data[r][c] : 0;
        var v2 = p2Data[r] ? p2Data[r][c] : 0;
        // Add space after comma for better readability
        return v1.toFixed(1) + ", " + v2.toFixed(1);
    }
    
    function checkEq(r, c) {
        if (!eqCoords) return false;
        for (var i = 0; i < eqCoords.length; i++) {
            if (eqCoords[i][0] === r && eqCoords[i][1] === c) return true;
        }
        return false;
    }
}
