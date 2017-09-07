# -*- coding:utf-8 -*-

from __future__ import print_function

class data_t:
    def __init__(self, Str = None, Ary = None):
        self.str = Str
        self.ary = Ary

    def shape(self, Rows = None, Cols = None, Ch = None):
        self.rows = Rows
        self.cols = Cols
        self.ch   = Ch

def func(data):
    print("| " + data.str + " |") 

    for i in range(data.rows):
        print("|", end = "")

        for j in range(data.cols):
            for k in range(data.ch):
                print(" %.2f " %(data.ary[i, j, k]), end = "")

            print("|", end = "")
        print(end = "\n")
