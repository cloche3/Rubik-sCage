import copy
import numpy as np

size = 3

class Base_Stage:

    def __init__(self, heights=None, new_stone = 0,depth = 0, reach =0):
        if heights is None:
            self.heights=[[0,0,0],[0,0,0],[0,0,0]]
            self.new_stone = [0,0,0]
            self.depth = 0
            self.reach = []
        elif heights is not None:
            self.heights = heights
            self.new_stone = new_stone
            self.depth = depth
            self.reach = []
        else:
            pass


    def next_reach(self): # 既にリーチがある場合はキューブを入れる。
        n_bl = []
        if self.reach != []:
            return [self.reach]
        else:
            for y in range(size):
                for x in range(size):
                    if self.heights[x][y] < 10:
                        if not self.heights[2][2]:   # not enter center
                            n_bl.append((x,y))
            return n_bl

    def next_stage(self): # 動作後の盤面
        next_stage = []
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
                            low.append(child.heights[j][k] + (child.depth %2 +1) * (3*len(Base_Stage(child.heights[j][k]))))
                        else:
                            low.append(child.heights[j][k])
                if len(stage_low) != 0:
                    stage_low.append(tuple(low))
                else:
                    stage_low.append(tuple(low))
            else:
                if len(stage_low) != 0:
                    stage_low.append(child.heights[j])
                else:
                    stage_low.append(child.heights[j])
        child.heights = tuple(stage_low)

        return next_stage # 未定義



    def to_canonical(self): #標準形設定
        st_dic = {}
        new_stone = self.new_stone
        s_array = self.heights

        for i in range(4):

            #転置
            st_ins = Base_Stage(heights = s_array, new_stone = new_stone, depth = self.depth)
            st_dic[st_ins.heights] = st_ins
            s_array = tuple(tuple(s_array[i][j] for i in range(size)) for j in range(size))
            new_stone = (new_stone[1], new_stone[0], new_stone[2])

            #回転
            st_ins = Base_Stage(heights = s_array, new_stone = new_stone, depth = self.depth)
            st_dic[st_ins.heights] = st_ins
            s_array = tuple(l[::1] for l in s_array)
            new_stone = (size-1-new_stone[0], new_stone[1], new_stone[2])

        to_canonical = st_dic[min(st_dic)]

        return to_canonical

    def check_win(Base_stage,y, z ,d):
        win = 0
        reach = []

        return win,reach

def is_finish(target):
    children = target.next_stage()
    for i in children:
        all_in = i.check_call()
        if all_in == 1 and target.depth%2 == 0:
            i.log_write()
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
    return 0
if __name__ == '__main__':
    is_finish()
