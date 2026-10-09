

import os
import sys
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'cmake-build-debug'))
import std # NOLINT 忽略这个报错 IDE的问题


a = [1,2,3,4,5,6,7,8,9]
b = []

v1 = std.get_even_sum(a)
v2 = std.get_even_sum(b)

f = lambda x: x.sum if x.have else "empty value"

print(f(v1))
print(f(v2))

