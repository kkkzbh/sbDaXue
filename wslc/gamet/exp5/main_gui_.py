"""
讲解重点函数/流程:
1) main(): GUI 启动入口，完成 Qt 应用初始化、控制器注入、QML 加载与事件循环。
"""

import sys
import os

# Set environment variable to handle high DPI if needed
os.environ["QT_AUTO_SCREEN_SCALE_FACTOR"] = "1"

from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtQuickControls2 import QQuickStyle
from gui_bridge_ import GameController


def main():
    """
    GUI 启动主流程
    - 设定 Qt Quick 样式
    - 创建应用实例与 QML 引擎
    - 把 Python 控制器注入到 QML
    - 加载主界面并进入事件循环
    """
    # 1) 设置控件样式（避免不同平台默认样式差异过大）
    QQuickStyle.setStyle("Basic")

    # 2) 创建 Qt 应用对象（必须先创建，后续 GUI 组件依赖它）
    app = QGuiApplication(sys.argv)

    # 3) 可选：设置组织信息，便于 Qt 保存配置/缓存
    app.setOrganizationName("GameTheoryLab")
    app.setOrganizationDomain("gametheory.example")

    # 4) 创建 QML 引擎，用于加载和管理 QML UI
    engine = QQmlApplicationEngine()

    # 5) 创建控制器，把 Python 逻辑对象暴露给 QML 使用
    controller = GameController()
    engine.rootContext().setContextProperty("gameController", controller)

    # 6) 加载 QML 主文件（界面布局、按钮、矩阵可视化都在这里）
    qml_file = os.path.join(os.path.dirname(__file__), "qml/Main.qml")
    engine.load(qml_file)

    # 7) 如果 QML 加载失败，直接退出并返回错误码
    if not engine.rootObjects():
        sys.exit(-1)

    # 8) 启动 Qt 事件循环，开始响应用户交互
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
