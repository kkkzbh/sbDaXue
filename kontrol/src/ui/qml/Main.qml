import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCore
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
    id: root
    width: 940
    height: 620
    visible: true
    title: "Kontrol"

    property bool darkTheme: true
    property int themeTransitionMs: 220

    Settings {
        id: themeSettings
        category: "appearance"
        property bool themeDark: true
    }

    property color pageBackgroundStart: "#111318"
    property color pageBackgroundEnd: "#1b202a"
    property color panelBackground: "#222736"
    property color panelBorder: "#353d54"
    property color cardBackground: "#232938"
    property color cardBorder: "#323a4d"
    property color titleColor: "#f4f7ff"
    property color secondaryText: "#b8c1d9"
    property color keyText: "#96a0bb"
    property color modeCardBackground: "#1b2130"
    property color modeCardBorder: "#33405a"
    property color modeCardHoverBackground: "#26344d"
    property color modeCardActiveBackground: "#2f4f87"
    property color modeCardActiveDeepBackground: "#243d67"
    property color modeCardActiveBorder: "#4f79c5"
    property color modeCardDisabledBackground: "#242a39"
    property color modeTitleColor: "#f5f8ff"
    property color modeDescColor: "#aab5cf"
    property color modeLiquidShine: "#9ec4ff"
    property string uiSelectedModeLabel: appController.currentModeLabel
    property string liquidFlowFromLabel: ""
    property real liquidFlowProgress: 1.0

    Behavior on pageBackgroundStart { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on pageBackgroundEnd { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on panelBackground { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on panelBorder { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on cardBackground { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on cardBorder { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on titleColor { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on secondaryText { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on keyText { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeCardBackground { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeCardBorder { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeCardHoverBackground { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeCardActiveBackground { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeCardActiveDeepBackground { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeCardActiveBorder { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeCardDisabledBackground { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeTitleColor { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeDescColor { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }
    Behavior on modeLiquidShine { ColorAnimation { duration: root.themeTransitionMs; easing.type: Easing.InOutQuad } }

    function applyThemePalette(useDark) {
        pageBackgroundStart = useDark ? "#111318" : "#f0f4fb"
        pageBackgroundEnd = useDark ? "#1b202a" : "#e8edf8"
        panelBackground = useDark ? "#222736" : "#f7f9ff"
        panelBorder = useDark ? "#353d54" : "#cfd8ea"
        cardBackground = useDark ? "#232938" : "#ffffff"
        cardBorder = useDark ? "#323a4d" : "#d9e1f2"
        titleColor = useDark ? "#f4f7ff" : "#1f293d"
        secondaryText = useDark ? "#b8c1d9" : "#52617e"
        keyText = useDark ? "#96a0bb" : "#697a99"
        modeCardBackground = useDark ? "#1b2130" : "#f3f6fd"
        modeCardBorder = useDark ? "#33405a" : "#c8d3e8"
        modeCardHoverBackground = useDark ? "#26344d" : "#e5edfc"
        modeCardActiveBackground = useDark ? "#2f4f87" : "#dbe8ff"
        modeCardActiveDeepBackground = useDark ? "#243d67" : "#bdd4fb"
        modeCardActiveBorder = useDark ? "#4f79c5" : "#7ba3ed"
        modeCardDisabledBackground = useDark ? "#242a39" : "#e7ecf7"
        modeTitleColor = useDark ? "#f5f8ff" : "#1d2a42"
        modeDescColor = useDark ? "#aab5cf" : "#64779d"
        modeLiquidShine = useDark ? "#9ec4ff" : "#77a7f4"
    }

    function toggleTheme() {
        darkTheme = !darkTheme
        applyThemePalette(darkTheme)
    }

    onDarkThemeChanged: {
        themeSettings.themeDark = darkTheme
    }

    function modeDescription(modeId) {
        if (modeId === "asus_mux_dgpu") {
            return "性能优先，独显直连输出"
        }

        if (modeId === "hybrid") {
            return "自动协同，兼顾性能与续航"
        }

        if (modeId === "integrated") {
            return "低功耗运行，续航优先"
        }

        return "根据当前负载自动处理"
    }

    function mixColor(fromColor, toColor, progress) {
        var t = Math.max(0.0, Math.min(1.0, progress))
        return Qt.rgba(
            fromColor.r + (toColor.r - fromColor.r) * t,
            fromColor.g + (toColor.g - fromColor.g) * t,
            fromColor.b + (toColor.b - fromColor.b) * t,
            fromColor.a + (toColor.a - fromColor.a) * t
        )
    }

    Component.onCompleted: {
        darkTheme = themeSettings.themeDark
        applyThemePalette(darkTheme)
        uiSelectedModeLabel = appController.currentModeLabel
    }

    Connections {
        target: appController
        function onSnapshotChanged() {
            root.uiSelectedModeLabel = appController.currentModeLabel
            root.liquidFlowFromLabel = ""
            root.liquidFlowProgress = 1.0
        }
    }

    pageStack.initialPage: Kirigami.Page {
        title: ""
        actions: [
            Kirigami.Action {
                icon.name: root.darkTheme ? "weather-clear-night-symbolic" : "weather-clear-symbolic"
                text: root.darkTheme ? "切换浅色模式" : "切换深色模式"
                tooltip: text
                displayHint: Kirigami.DisplayHint.IconOnly | Kirigami.DisplayHint.KeepVisible
                onTriggered: root.toggleTheme()
            }
        ]

        background: Rectangle {
            gradient: Gradient {
                GradientStop { position: 0.0; color: root.pageBackgroundStart }
                GradientStop { position: 1.0; color: root.pageBackgroundEnd }
            }
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 16

            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                Repeater {
                    model: [
                        { key: "产品", value: appController.productFamily },
                        { key: "主板", value: appController.boardName },
                        { key: "dGPU", value: appController.dgpuVendor }
                    ]

                    delegate: Rectangle {
                        radius: 14
                        color: root.cardBackground
                        border.color: root.cardBorder
                        Layout.fillWidth: true
                        implicitHeight: 96

                        Column {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 6

                            Label {
                                text: modelData.key
                                color: root.keyText
                                font.pixelSize: 12
                            }

                            Label {
                                text: modelData.value
                                color: root.modeTitleColor
                                font.pixelSize: 18
                                font.bold: true
                            }
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                radius: 16
                color: root.panelBackground
                border.color: root.panelBorder
                implicitHeight: 420

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 18
                    spacing: 12

                    Label {
                        text: "显卡模式"
                        color: root.titleColor
                        font.pixelSize: 24
                        font.bold: true
                    }

                    Label {
                        text: "当前模式: " + appController.currentModeLabel
                        color: root.secondaryText
                    }

                    Item {
                        Layout.fillWidth: true
                        implicitHeight: modeGrid.implicitHeight + 16

                        Rectangle {
                            id: liquidSelectionBar
                            visible: modeGrid.activeTile !== null
                            x: {
                                var toTile = modeGrid.activeTile
                                var fromTile = modeGrid.findTile(root.liquidFlowFromLabel)
                                if (!toTile) {
                                    return 0
                                }
                                if (!fromTile || fromTile === toTile || root.liquidFlowProgress >= 1.0) {
                                    return toTile.x
                                }
                                return fromTile.x + (toTile.x - fromTile.x) * root.liquidFlowProgress
                            }
                            y: {
                                var toTile = modeGrid.activeTile
                                var fromTile = modeGrid.findTile(root.liquidFlowFromLabel)
                                if (!toTile) {
                                    return 0
                                }
                                if (!fromTile || fromTile === toTile || root.liquidFlowProgress >= 1.0) {
                                    return toTile.y + toTile.hoverOffset
                                }
                                var fromY = fromTile.y + fromTile.hoverOffset
                                var toY = toTile.y + toTile.hoverOffset
                                return fromY + (toY - fromY) * root.liquidFlowProgress
                            }
                            width: {
                                var toTile = modeGrid.activeTile
                                var fromTile = modeGrid.findTile(root.liquidFlowFromLabel)
                                if (!toTile) {
                                    return 0
                                }
                                if (!fromTile || fromTile === toTile || root.liquidFlowProgress >= 1.0) {
                                    return toTile.width
                                }
                                return fromTile.width + (toTile.width - fromTile.width) * root.liquidFlowProgress
                            }
                            height: {
                                var toTile = modeGrid.activeTile
                                var fromTile = modeGrid.findTile(root.liquidFlowFromLabel)
                                if (!toTile) {
                                    return 0
                                }
                                if (!fromTile || fromTile === toTile || root.liquidFlowProgress >= 1.0) {
                                    return toTile.height
                                }
                                return fromTile.height + (toTile.height - fromTile.height) * root.liquidFlowProgress
                            }
                            radius: 14
                            color: root.modeCardActiveDeepBackground
                            border.color: Qt.lighter(root.modeCardActiveBorder, 1.08)
                            border.width: 2
                            clip: true
                            z: 0
                            transform: Scale {
                                origin.x: liquidSelectionBar.width / 2
                                origin.y: liquidSelectionBar.height / 2
                                xScale: {
                                    var toTile = modeGrid.activeTile
                                    var fromTile = modeGrid.findTile(root.liquidFlowFromLabel)
                                    if (!toTile) {
                                        return 1.0
                                    }
                                    if (!fromTile || fromTile === toTile || root.liquidFlowProgress >= 1.0) {
                                        return toTile.hoverScale
                                    }
                                    return fromTile.hoverScale + (toTile.hoverScale - fromTile.hoverScale) * root.liquidFlowProgress
                                }
                                yScale: {
                                    var toTile = modeGrid.activeTile
                                    var fromTile = modeGrid.findTile(root.liquidFlowFromLabel)
                                    if (!toTile) {
                                        return 1.0
                                    }
                                    if (!fromTile || fromTile === toTile || root.liquidFlowProgress >= 1.0) {
                                        return toTile.hoverScale
                                    }
                                    return fromTile.hoverScale + (toTile.hoverScale - fromTile.hoverScale) * root.liquidFlowProgress
                                }
                            }

                            Rectangle {
                                anchors.fill: parent
                                radius: parent.radius
                                color: root.modeLiquidShine
                                opacity: 0.12
                            }
                        }

                        GridLayout {
                            id: modeGrid
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            columns: 3
                            rowSpacing: 10
                            columnSpacing: 10
                            property Item activeTile: null
                            z: 1

                            function syncActiveTile(tile) {
                                if (!tile || !tile.active) {
                                    return
                                }
                                activeTile = tile
                            }

                            function findTile(label) {
                                if (!label || label.length === 0) {
                                    return null
                                }
                                for (var i = 0; i < modeRepeater.count; ++i) {
                                    var candidate = modeRepeater.itemAt(i)
                                    if (candidate && candidate.modelData.label === label) {
                                        return candidate
                                    }
                                }
                                return null
                            }

                            Repeater {
                                id: modeRepeater
                                model: appController.modes

                                delegate: Item {
                                    id: modeTile
                                    required property var modelData
                                    property bool active: root.uiSelectedModeLabel === modelData.label
                                    property bool hovered: hoverArea.containsMouse && modelData.supported
                                    property bool transitioningFrom: root.liquidFlowProgress < 1.0
                                                                   && root.liquidFlowFromLabel === modelData.label
                                                                   && root.liquidFlowFromLabel !== root.uiSelectedModeLabel
                                    property bool transitioningTo: modeTile.active
                                                                 && root.liquidFlowProgress < 1.0
                                                                 && root.liquidFlowFromLabel.length > 0
                                                                 && root.liquidFlowFromLabel !== modeTile.modelData.label
                                    property real hoverOffset: hovered ? -6 : 0
                                    property real hoverScale: hovered ? 1.015 : 1.0
                                    property real flowOutProgress: transitioningFrom ? root.liquidFlowProgress : 1.0
                                    property real flowInProgress: transitioningTo ? root.liquidFlowProgress : 1.0
                                    property color baseCardColor: hovered ? root.modeCardHoverBackground : root.modeCardBackground
                                    property color transparentBaseColor: Qt.rgba(modeTile.baseCardColor.r, modeTile.baseCardColor.g, modeTile.baseCardColor.b, 0.0)
                                    property color cardFillColor: !modeTile.modelData.supported
                                                                  ? root.modeCardDisabledBackground
                                                                  : (modeTile.active
                                                                     ? (modeTile.transitioningTo
                                                                        ? root.mixColor(modeTile.baseCardColor, modeTile.transparentBaseColor, modeTile.flowInProgress)
                                                                        : "transparent")
                                                                     : (modeTile.transitioningFrom
                                                                        ? root.mixColor(root.modeCardActiveDeepBackground, modeTile.baseCardColor, modeTile.flowOutProgress)
                                                                        : modeTile.baseCardColor))
                                    property color inactiveBorderColor: modeTile.hovered ? Qt.lighter(root.modeCardBorder, 1.16) : root.modeCardBorder
                                    property color cardBorderColor: modeTile.active
                                                                    ? (modeTile.transitioningTo
                                                                       ? root.mixColor(modeTile.inactiveBorderColor, root.modeCardActiveBorder, modeTile.flowInProgress)
                                                                       : root.modeCardActiveBorder)
                                                                    : (modeTile.transitioningFrom
                                                                       ? root.mixColor(root.modeCardActiveBorder, modeTile.inactiveBorderColor, modeTile.flowOutProgress)
                                                                       : modeTile.inactiveBorderColor)
                                    property real cardBorderWidth: modeTile.active
                                                                    ? (modeTile.transitioningTo ? (1.0 + modeTile.flowInProgress) : 2)
                                                                    : (modeTile.transitioningFrom ? (2.0 - modeTile.flowOutProgress) : 1)
                                    property color titleLabelColor: modeTile.active
                                                                    ? (modeTile.transitioningTo
                                                                       ? root.mixColor(root.titleColor, root.modeTitleColor, modeTile.flowInProgress)
                                                                       : root.modeTitleColor)
                                                                    : (modeTile.transitioningFrom
                                                                       ? root.mixColor(root.modeTitleColor, root.titleColor, modeTile.flowOutProgress)
                                                                       : root.titleColor)

                                    Layout.fillWidth: true
                                    implicitHeight: 96
                                    opacity: modelData.supported ? 1.0 : 0.6

                                    Component.onCompleted: {
                                        if (active) {
                                            modeGrid.syncActiveTile(modeTile)
                                        }
                                    }

                                    onActiveChanged: {
                                        if (active) {
                                            modeGrid.syncActiveTile(modeTile)
                                        } else if (modeGrid.activeTile === modeTile) {
                                            modeGrid.activeTile = null
                                        }
                                    }

                                    transform: [
                                        Translate { y: modeTile.hoverOffset },
                                        Scale {
                                            origin.x: modeTile.width / 2
                                            origin.y: modeTile.height / 2
                                            xScale: modeTile.hoverScale
                                            yScale: modeTile.hoverScale
                                        }
                                    ]

                                    Behavior on hoverOffset {
                                        NumberAnimation { duration: 140; easing.type: Easing.OutCubic }
                                    }

                                    Behavior on hoverScale {
                                        NumberAnimation { duration: 140; easing.type: Easing.OutCubic }
                                    }

                                    Behavior on cardFillColor {
                                        enabled: !modeTile.transitioningFrom && !modeTile.transitioningTo
                                        ColorAnimation { duration: 180; easing.type: Easing.InOutQuad }
                                    }

                                    Behavior on cardBorderColor {
                                        enabled: !modeTile.transitioningFrom && !modeTile.transitioningTo
                                        ColorAnimation { duration: 180; easing.type: Easing.InOutQuad }
                                    }

                                    Behavior on cardBorderWidth {
                                        enabled: !modeTile.transitioningFrom && !modeTile.transitioningTo
                                        NumberAnimation { duration: 180; easing.type: Easing.InOutQuad }
                                    }

                                    Rectangle {
                                        anchors.fill: parent
                                        radius: 14
                                        color: modeTile.cardFillColor
                                        border.color: modeTile.cardBorderColor
                                        border.width: modeTile.cardBorderWidth
                                    }

                                    ColumnLayout {
                                        anchors.fill: parent
                                        anchors.margins: 12
                                        spacing: 4

                                        Label {
                                            text: modeTile.modelData.label
                                            color: modeTile.titleLabelColor
                                            font.pixelSize: 24
                                            font.bold: true
                                            horizontalAlignment: Text.AlignHCenter
                                            Layout.fillWidth: true
                                        }

                                        Item {
                                            Layout.fillHeight: true
                                        }

                                        Label {
                                            text: root.modeDescription(modeTile.modelData.id)
                                            color: root.modeDescColor
                                            font.pixelSize: 12
                                            horizontalAlignment: Text.AlignHCenter
                                            Layout.fillWidth: true
                                        }
                                    }

                                    MouseArea {
                                        id: hoverArea
                                        anchors.fill: parent
                                        enabled: modeTile.modelData.supported
                                        hoverEnabled: true
                                        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
                                        onClicked: {
                                            var previousLabel = root.uiSelectedModeLabel
                                            root.uiSelectedModeLabel = modeTile.modelData.label
                                            if (previousLabel !== modeTile.modelData.label) {
                                                root.liquidFlowFromLabel = previousLabel
                                                root.liquidFlowProgress = 0.0
                                                liquidFlowAnimation.restart()
                                            }
                                            appController.selectMode(modeTile.modelData.rawMode)
                                        }
                                    }
                                }
                            }
                        }

                        NumberAnimation {
                            id: liquidFlowAnimation
                            target: root
                            property: "liquidFlowProgress"
                            from: 0.0
                            to: 1.0
                            duration: 360
                            easing.type: Easing.OutCubic
                        }

                    }

                    Item { Layout.fillHeight: true }

                    Rectangle {
                        Layout.fillWidth: true
                        visible: appController.actionBarVisible
                        implicitHeight: appController.actionBarVisible ? 88 : 0
                        radius: 10
                        color: root.modeCardBackground
                        border.color: root.modeCardBorder

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            spacing: 10

                            Label {
                                Layout.fillWidth: true
                                text: appController.statusMessage
                                wrapMode: Text.Wrap
                                color: root.titleColor
                            }

                            Button {
                                visible: appController.actionSecondaryVisible
                                text: appController.actionSecondaryText
                                onClicked: {
                                    appController.handleSecondaryAction()
                                    root.uiSelectedModeLabel = appController.currentModeLabel
                                }
                            }

                            Button {
                                visible: appController.actionPrimaryVisible
                                text: appController.actionPrimaryText
                                onClicked: appController.handlePrimaryAction()
                            }
                        }
                    }
                }
            }
        }
    }
}
