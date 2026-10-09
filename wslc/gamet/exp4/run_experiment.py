import sys
import os
from pathlib import Path

def main():
    # 获取当前脚本所在目录 (即 exp4 目录)
    current_dir = Path(__file__).resolve().parent
    
    # 获取父目录 (即包含 exp4 的目录)
    parent_dir = current_dir.parent
    
    # 将父目录加入 sys.path，这样 Python 就能找到 'exp4' 包
    if str(parent_dir) not in sys.path:
        sys.path.insert(0, str(parent_dir))
    
    try:
        # 现在可以作为模块导入了
        from exp4.main import main as experiment_main
        experiment_main()
    except ImportError as e:
        print("启动失败：无法导入 exp4 模块。")
        print(f"调试信息：\n当前目录: {current_dir}\n父目录: {parent_dir}\nsys.path: {sys.path}")
        raise e

if __name__ == "__main__":
    main()
