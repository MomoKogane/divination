# -*- coding: gbk -*-
import random
import datetime

class Divination:
    element_table = {
        0: "地", 1: "山", 2: "水", 3: "风",
        4: "雷", 5: "火", 6: "泽", 7: "天"
    }
    divination_table = {
        0: "坤", 1: "艮", 2: "坎", 3: "巽",
        4: "震", 5: "离", 6: "兑", 7: "乾"
    }
    divination_map = [
        ["坤", "谦", "师", "升", "复", "明夷", "临", "泰"],
        ["剥", "艮", "蒙", "蛊", "颐", "贲", "损", "大畜"],
        ["比", "蹇", "坎", "井", "屯", "既济", "节", "需"],
        ["观", "渐", "涣", "巽", "益", "家人", "中孚", "小畜"],
        ["豫", "小过", "解", "恒", "震", "丰", "归妹", "大壮"],
        ["晋", "旅", "未济", "鼎", "噬嗑", "离", "睽", "大有"],
        ["萃", "咸", "困", "大过", "随", "革", "泽", "夬"],
        ["否", "退", "讼", "姤", "无妄", "同人", "履", "天"]
    ]

    def __init__(self):
        self.first = 0
        self.second = 0
        self.visited = [False] * 6
        self.result = ""
        self.divinate_time = self.get_time()
        self.rng = random.Random()
        self.rng.seed(int(datetime.datetime.now().timestamp()))

    def run(self):
        self.init()
        self.analyze()
        self.consolidate()
        self.output_result("占卜结果.txt")

    def get_result(self):
        return self.result

    def debug(self):
        self.result += "first=" + str(self.first) + ",second=" + str(self.second) + "\n"

    def get_time(self):
        return datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    def single_gram(self):
        start = 48
        cal_result = 1
        count = 3
        while count:
            left = random.randint(1, start - 1)
            temp = ((left - 1) % 4 + 1) + ((start - left - 1) % 4 + 1)
            cal_result += temp
            start -= temp
            count -= 1
        return (49 - cal_result) // 4

    def init(self):
        self.first = 0
        self.second = 0
        self.visited = [False] * 6
        self.result = ""
        self.divinate_time = self.get_time()

    def analyze(self):
        temp1 = 0
        temp2 = 0
        for i in range(6):
            temp1 = temp2 = 0
            gram = self.single_gram()
            self.result += "第" + str(i + 1) + "个爻："
            if gram == 6:
                temp1 = 0
                temp2 = 1
                self.visited[i] = True
                self.result += "老阴\n"
            elif gram == 7:
                temp1 = 1
                temp2 = 1
                self.result += "少阳\n"
            elif gram == 8:
                temp1 = 0
                temp2 = 0
                self.result += "少阴\n"
            elif gram == 9:
                temp1 = 1
                temp2 = 0
                self.visited[i] = True
                self.result += "老阳\n"
            self.first = self.first * 2 + temp1
            self.second = self.second * 2 + temp2

    def output_gram(self, gram):
        up = gram % 8
        down = gram // 8
        if up == down:
            self.result += self.element_table[up] + "为" + self.divination_table[down] + "卦"
        else:
            self.result += self.element_table[up] + self.element_table[down] + self.divination_map[up][down] + "卦"

    def consolidate(self):
        self.result += "本次结果为：\n"
        if self.first == self.second:
            self.output_gram(self.first)
            self.result += "\n"
        else:
            self.result += "从"
            self.output_gram(self.first)
            self.result += "变爻为"
            self.output_gram(self.second)
            self.result += "\n"

    def output_result(self, filename):
        with open(filename, "a") as outfile:
            outfile.write("占卜时间为：" + self.divinate_time + "\n")
            outfile.write(self.result + "\n")

if __name__ == "__main__":
    d = Divination()
    d.run()
