# -*- coding: gbk -*-
import random
import datetime

class Divination:
    element_table = {
        0: "��", 1: "ɽ", 2: "ˮ", 3: "��",
        4: "��", 5: "��", 6: "��", 7: "��"
    }
    divination_table = {
        0: "��", 1: "��", 2: "��", 3: "��",
        4: "��", 5: "��", 6: "��", 7: "Ǭ"
    }
    divination_map = [
        ["��", "ǫ", "ʦ", "��", "��", "����", "��", "̩"],
        ["��", "��", "��", "��", "��", "��", "��", "����"],
        ["��", "�", "��", "��", "��", "�ȼ�", "��", "��"],
        ["��", "��", "��", "��", "��", "����", "����", "С��"],
        ["ԥ", "С��", "��", "��", "��", "��", "����", "��׳"],
        ["��", "��", "δ��", "��", "���", "��", "�", "����"],
        ["��", "��", "��", "���", "��", "��", "��", "��"],
        ["��", "��", "��", "��", "����", "ͬ��", "��", "��"]
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
        self.output_result("ռ�����.txt")

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
            self.result += "��" + str(i + 1) + "��س��"
            if gram == 6:
                temp1 = 0
                temp2 = 1
                self.visited[i] = True
                self.result += "����\n"
            elif gram == 7:
                temp1 = 1
                temp2 = 1
                self.result += "����\n"
            elif gram == 8:
                temp1 = 0
                temp2 = 0
                self.result += "����\n"
            elif gram == 9:
                temp1 = 1
                temp2 = 0
                self.visited[i] = True
                self.result += "����\n"
            self.first = self.first * 2 + temp1
            self.second = self.second * 2 + temp2

    def output_gram(self, gram):
        up = gram % 8
        down = gram // 8
        if up == down:
            self.result += self.element_table[up] + "Ϊ" + self.divination_table[down] + "��"
        else:
            self.result += self.element_table[up] + self.element_table[down] + self.divination_map[up][down] + "��"

    def consolidate(self):
        self.result += "���ν��Ϊ��\n"
        if self.first == self.second:
            self.output_gram(self.first)
            self.result += "\n"
        else:
            self.result += "��"
            self.output_gram(self.first)
            self.result += "��سΪ"
            self.output_gram(self.second)
            self.result += "\n"

    def output_result(self, filename):
        with open(filename, "a") as outfile:
            outfile.write("ռ��ʱ��Ϊ��" + self.divinate_time + "\n")
            outfile.write(self.result + "\n")

if __name__ == "__main__":
    d = Divination()
    d.run()
