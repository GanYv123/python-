#直方图 茎叶图绘制
#MyGUI.py
import numpy as np
import matplotlib.pyplot as plt
# 设置字体为微软雅黑
plt.rcParams['font.family'] = ['Microsoft YaHei']

class Draw_Data:
    def __init__(self,stu_dicts) -> None:
        self.stu_dict = stu_dicts # {name: {'score': score, 'point': point}}

    def show_histogram(self):
        # 将学生分数按照10分为一组统计
        scores = np.array([info['score'] for info in self.stu_dict.values()])
        bins = np.arange(0, 101, 10)  # 分组边界：0, 10, 20, ..., 100
        hist, _ = np.histogram(scores, bins=bins)#分好的数组和边界

        # 绘制直方图S
        fig, ax1 = plt.subplots(figsize=(10, 6)) #返回主图 子图
        ax1.bar(bins[:-1], hist, width=10, color='skyblue', label='Student Count', edgecolor='black')
        ax1.set_xlabel('Score')
        ax1.set_ylabel('Student Count')

        # 计算方差、平均分和中位数
        variance = np.var(scores)
        mean = np.mean(scores)
        median = np.median(scores)

        # 在图上显示标签 将文本位置设置在最大频数的90%
        ax1.text(80, max(hist) * 0.9, f'方差 Variance: {variance:.2f}')
        ax1.text(80, max(hist) * 0.8, f'平均 Mean: {mean:.2f}')
        ax1.text(80, max(hist) * 0.7, f'中位 Median: {median}')

        plt.tight_layout()
        plt.show()


    def close_histogram(self):
        # 关闭图形
        print("关闭直方图")
        plt.close()

    def show_stem_leaf(self):
        scores = np.array([info['score'] for info in self.stu_dict.values()])  # 获取分数数据
        stem = scores // 10  # 茎部是十位数
        leaf = scores % 10   # 叶部是个位数

        # 构建茎叶图
        stem_and_leaf = {}
        for s, l in zip(stem, leaf):
            if s not in stem_and_leaf:
                stem_and_leaf[s] = []
            stem_and_leaf[s].append(l)

        # 创建茎叶图的文本表示
        stem_and_leaf_str = 'Stem | Leaf\n-----|-----\n'
        for key in sorted(stem_and_leaf.keys()):
            leaves = ' '.join(str(leaf) for leaf in sorted(stem_and_leaf[key]))
            stem_and_leaf_str += f"{key}    | {leaves}\n"

        #print(stem_and_leaf_str)
                # 返回字符串
        return stem_and_leaf_str