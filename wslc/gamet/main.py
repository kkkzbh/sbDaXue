
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'cmake-build-debug'))
import std


if __name__ == '__main__':
    std.start()