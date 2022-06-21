import copy
import numpy as np


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

def nxbl(self):
    n_bl = []
    if self.reach != []:
        return [self.reach]
    else:
        for y in range(size):
            for x in range(size):
                if self.height[x][y] < 9:
                    n_bl.append((x,y))
        return n_bl

def nxst(self):
    next_st = []
    st_list = []
    hash_t = set()
    nxway = self.nxbl()
    for x,y in nxway:
