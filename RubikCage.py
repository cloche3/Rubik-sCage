import copy
from hashlib import new
from string import hexdigits
import numpy as np

size = 3

def __init__(self, height=None, new_stone = 0,depth = 0, reach =0):
    if height is None:
        self.height=((0,0,0),(0,0,0),(0,0,0))
        self.new_stone = (0,0,0)
        self.depth = 0
        self.reach = []
    elif height is not None:
        self.height = height
        self.new_stone = new_stone
        self.depth = depth
        self.reach = []
    else:
        pass

def next_reach(self):
    n_bl = []
    if self.reach != []:
        return [self.reach]
    else:
        for y in range(size):
            for x in range(size):
                if self.height[x][y] < 9:   # enter center
                    n_bl.append((x,y))
        return n_bl

def next_stage(self):
    next_st = []
    st_list = []
    hash_t = set()
    nxway = self.next_reach()
    for x,y in nxway:
        child = copy.deepcopy(self)
        size = 3
        stage_low = []
        for j in range(size):
            if j == y:
                low = []
                for k in range(size):
                    if k == x:
                        pass # 未実装
                    else:
                        pass # 未実装
            if len(stage_low) != 0:
                pass # 未実装
            else:
                pass # 未実装
        else:
            if len(stage_low) != 0:
                pass # 未実装
            else:
                pass # 未実装
    child.heights = tuple(stage_low)

def to_canonical(self):
    st_dic = {}
    new_stone = self.new_stone
    s_array = self.heights

    for i in range(4):

        #転置
        st_ins = stage(heights = s_array, new_stone = new_stone, depth = self.depth)
        st_dic[st_ins.heights] = st_ins
        s_array = tuple(tuple(s_array[i][j] for i in range(size)) for j in range(size))
        new_stone = (new_stone[1], new_stone[0], new_stone[2])

        #回転
        st_ins = stage(heights = s_array, new_stone = new_stone, depth = self.depth)
        st_dic[st_ins.heights] = st_ins
        s_array = tuple(l[::1] for l in s_array)
        new_stone = (size-1-new_stone[0], new_stone[1], new_stone[2])

    st_can = st_dic[min(st_dic)]
    return st_can

def is_finish(target):
    children = target.next_stage()
    for i in children:
        all_in = i.check_call()
        if all_in == 1 and target.depth%2 == 0:
            return 1
        elif all_in == 2 and target.depth%2 == 1:
            return 2
        draw = 0
    for i in children:
        judge = is_finish(i)
        if judge == 1 and target.depth % 2 == 0:
            return 1
        elif judge == 2 and target.depth % 2 == 1:
            return 2
        elif judge == 0 or len(children) == 0:
            draw = 1
        if draw == 1:
            return 0
    if target.depth%2 == 0:
        return 2
    else:
        return 1

