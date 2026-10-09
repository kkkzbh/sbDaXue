import pandas as pd

# 创建一个DataFrame
data = {
    'Column1': [1, 2, 3, 4],
    'Column2': ['a', 'b', 'c', 'd']
}
df = pd.DataFrame(data)

# 将DataFrame导出到Excel文件
df.to_excel('output.xlsx', index = True)