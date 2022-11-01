#include <iostream>
#include <algorithm>
#include <map>
#include <stdio.h>

/*
変数variable/argument/return/用途
copy/ cage / new_cage/ 盤面のコピー
fallcube/ cage/ 0/ キューブを下に落とす（重力）
put/ cage,color,position/ cage/ キューブを入れる場所を決める
flip/ cage,cubeslide/ 0/ 1行右にずらす


引数argument
cage[i][j] i段目(0~2)　左上から右回りに通るマスj個目　下表は上から見た穴
0 | 1 | 2
7 | x | 3
6 | 5 | 4
組み合わせとして
(0,1,2)1枚目　(2,3,4)　2枚目　(4,5,6) 3枚目　(6,7,0) 4枚目　とする
値が小さい方向が左、値が大きい方向が右
color 色数(1~6 , 0 = 空)
position ブロックを入れる時の穴決定(0~7)
cubeslide ケージを回転させる段決定(0~2)


*/


const int height = 3;   // ケージの高さ
const int length_of_edge = 3;   // ケージを上から見た正方形の一辺の長さ
const int num_positions = length_of_edge * 2 + (length_of_edge - 2) * 2;    // 上から見た、ブロックを入れる穴の数。一辺の長さが3のときは8

int** copy(/*const*/int** cage){
    int **new_cage; // コピー先の盤面

    new_cage = new int*[height];
    for (int i = 0; i < height; i++) {
        new_cage[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            new_cage[i][j] = cage[i][j];
        }
    }

    return new_cage;
};


int ** fallcube(int **cage){  //キューブを下に落とす
    for (int j=0; j < num_positions; j++){
        for (int top = 2; top > 0; top--){
            for (int i = 0; i < top; i++){    //0,1段のみ
                if (cage[i][j] == 0 && cage[i+1][j] != 0) {  // 場所 j の i 段目が空で、i+1段目が空じゃない時
                    cage[i][j] = cage[i + 1][j];
                    cage[i + 1][j] = 0;
                    //下に落とす
                }
            }
        }
    }
    return cage;////コピーせず今の盤面を上書き（変更後の盤面）
};

int** put(int** cage, int color, int position){//position: キューブを入れる場所（1段のマス数0~7）color入れる色(色数1~6(減らすと1~4))
    copy(cage);//記録
    cage[2][position] = color;//入力された場所に指定された色のキューブを入れる
    cage = fallcube(cage);//重力
    return cage;//変更後の盤面
};

/* void flip(int ** cage,int cubeslide){//cubeslide横にずらす場所決め(段数0~2)
    for (int stack = cage[cubeslide][0],t; t < 7; t++){
        cage[cubeslide][t] = cage[cubeslide][t + 1];
        cage[cubeslide][7] = stack;
        stack = cage[cubeslide][0];//i段全体的に1行ずらす
    }
    return;//変更後の盤面
}; */

int** rotate_left(int ** cage,int cubeslide){//右回転
    copy(cage);//記録
    /* for (int count = 0; count < 2; count++){
        flip(cage,cubeslide);//3回ずらす
    } */
    for (int j; j < num_positions; j++){
        int stack = cage[cubeslide][j];
        cage[cubeslide][j] = cage[cubeslide][(j-2) % 8];
        cage[cubeslide][7] = stack;
        stack = cage[cubeslide][0];//i段全体的に1行ずらす
    }
    fallcube(cage);//重力
    return cage;//変更後の盤面
};

int** rotate_right(int ** cage,int cubeslide){
    copy(cage);//記録
    /* for (int count = 0; count < 6; count++){//左回転
        flip(cage,cubeslide);//7回ずらす
    } */
    for (int j; j < num_positions ; j++ ){
        int stack = cage[cubeslide][0];
        cage[cubeslide][j] = cage[cubeslide][j + 1];
        cage[cubeslide][7] = stack;
        stack = cage[cubeslide][0];//i段全体的に1行ずらす
    }
    cage = fallcube(cage);//重力
    return cage;//変更後の盤面
};

int** updown(int ** cage){
    copy(cage);//記録
    for (int j = 0; j < num_positions; j++){
        int stack = cage[0][j];
        cage[0][j] = cage[1][j];
        cage[1][j] = stack;//上下入れ替え
    }
    cage = fallcube(cage);//重力
    return cage;//変更後の盤面提示
}

int **reset(int ** cage){
    int **reset_cage; // コピー元の盤面
    reset_cage = new int*[height];
    for (int i = 0; i < height; i++) {
        reset_cage[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++){
            cage[i][j] = reset_cage[i][j];
        }
    }

    return cage;//初期化された盤面
}

int putreach(const int ** cage,int color,int position){
    for (int j = 0; j < num_positions; j++){//j個目縦リーチ判定
        if (cage[0][j] == cage[1][j]){ //縦に赤|赤|空の時
            position = j;
            color = cage[0][j];
            return position,color;
        }
    }

    for (int i = 0; i < height; i++){//i段(0~2)数横リーチ判定
        for (int t = 0; t < 8; t += 2){
            if (cage[i][0+t] == cage[i][1+t] && cage[i][(2+t) % 8] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|の時1枚目
            position = (2+t) % 8;
            color = cage[i][0+t];
            return position,color;
            }
            if (cage[i][1+t] == cage[i][(2+t) % 8] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//|空|赤|赤|の時
                position = 0+t;
                color = cage[i][(2+t) % 8];
                return position,color;
            }
            if (cage[i][0+t] == cage[i][(2+t) % 8] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                position = 1+t;
                color = cage[i][(2+t) % 8];
                return position,color;
            }
            if (i = 1 && cage[i-1][0+t] != 0 && cage[i-1][1+t] != 0 && cage[i-1][(2+t) % 8] != 0){//1段目が空いていない状態
                if (cage[i][0+t] == cage[i][1+t] && cage[i][(2+t) % 8] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|
                    position = (2+t) % 8;
                    color = cage[i][0+t];
                    return position,color;
                }
                if (cage[i][1+t] == cage[i][(2+t) % 8] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//|空|赤|赤|の時
                    position = 0+t;
                    color = cage[i][(2+t) % 8];
                    return position,color;
                }
                if (cage[i][0+t] == cage[i][(2+t) % 8] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    color = cage[i][(2+t) % 8];
                    return position,color;
                }
            }
            if (i = 2 && cage[i-1][0+t] != 0 && cage[i-1][1+t] != 0 && cage[i-1][(2+t) % 8] != 0){//2段目が空いていない状態
                if (cage[i][0+t] == cage[i][1+t] && cage[i][(2+t) % 8] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|
                    position = (2+t) % 8;
                    color = cage[i][0+t];
                    return position,color;
                }
                if (cage[i][1+t] == cage[i][(2+t) % 8] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//横に|空|赤|赤|の時
                    position = 0+t;
                    color = cage[i][(2+t) % 8];
                    return position,color;
                }
                if (cage[i][0+t] == cage[i][(2+t) % 8] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    color = cage[i][(2+t) % 8];
                    return position,color;
                }
            }
        }
    }

    for (int t = 0; t < 8; t += 2){//斜め1～4枚目
        if (cage[0][1+t] != 0 && cage[1][0+t] != 0){//左上がり
            if (cage[1][1+t] == cage[2][(2+t) % 8] && cage[1][1+t] != 0 && cage[0][0+t] == 0){//3段目にある
                position = 0+t;
                color = cage[1][1+t];
                return position,color;
            }
            if (cage[1][1+t] == cage[0][0+t] && cage[1][1+t] != 0 && cage[2][(2+t) % 8] == 0){//3段目にない
                position = 2+t;
                color = cage[1][1+t];
                return position,color;
            }
            if (cage[2][(2+t) % 8] == cage[0][0+t] && cage[1][1+t] == 0 && cage[2][(2+t) % 8] != 0){//真ん中にない
                position = 1+t;
                color = cage[0][0+t];
                return position,color;
            }
        }
        if (cage[0][1+t] != 0 && cage[1][(2+t) % 8] != 0){//右上上がり
            if (cage[1][1+t] == cage[2][0+t] && cage[1][1+t] != 0 && cage[0][(2+t) % 8] == 0){//3段目にある
                position = 2+t;
                color = cage[1][1+t];
                return position,color;
            }
            if (cage[1][1+t] == cage[0][(2+t) % 8] && cage[1][1+t] != 0 && cage[2][0+t] == 0){//3段目にない
                position = 0+t;
                color = cage[1][1+t];
                return position,color;
            }
            if (cage[2][0+t] == cage[0][(2+t) % 8] && cage[1][1+t] == 0 && cage[2][0+t] != 0){//真ん中にない
                position = 1+t;
                color = cage[2][0+t];
                return position,color;
            }
        }
    }

    return position,color;
}

int slidereach(const int ** cage, int cubeslide){
    for (int t = 0; t < 8; t+=2){//1~4枚目
        /* code */
    }


    return cubeslide;
}

bool updownreach(const int ** cage){
    for (int t = 0; t < 8; t+=2){//1~4枚目
        if (cage[0][0+t] == cage[1][1+t] == cage[0][(2+t) % 8] || cage[1][0+t] == cage[1][(2+t) % 8] == cage[2][1+t] == 0){//山の形
            return true;
        }
        if (cage[0][0+t] == cage[1][1+t] == cage[2][(2+t) % 8] || cage[1][0+t] == cage[2][1+t] == 0){//真ん中が高い山の形
            return true;
        }
        if (cage[1][0+t] == cage[2][1+t] == cage[1][(2+t) % 8] || cage[2][0+t] == cage[2][(2+t) % 8]  == 0){//1段目が埋まった山の形
            return true;
        }
        if (cage[1][0+t] == cage[0][1+t] == cage[1][(2+t) % 8] || cage[2][0+t] == cage[2][(2+t) % 8] == cage[1][1+t] == 0){//谷の形
            return true;
        }
        if (cage[2][0+t] == cage[0][1+t] == cage[2][(2+t) % 8] || cage[1][1+t] == 0){//真ん中が深い谷の形
            return true;
        }
        if (cage[2][0+t] == cage[1][1+t] == cage[2][(2+t) % 8] || cage[2][1+t] == 0){//1段目が埋まった谷の形
            return true;
        }

        if (cage[0][0+t] == cage[0][1+t] == cage[1][(2+t) % 8] || cage[1][0+t] == cage[1][1+t] == cage[2][(2+t) % 8] == 0){//左寄りに2つ並び、1つ1段上にある形
            return true;
        }
        if (cage[0][0+t] == cage[0][1+t] == cage[2][(2+t) % 8] || cage[1][0+t] == cage[1][1+t] == 0){//左寄りに2つ並び、1つ2段上にある形（反転L字型）
            return true;
        }
        if (cage[1][0+t] == cage[1][1+t] == cage[2][(2+t) % 8] || cage[2][0+t] == cage[2][1+t] == 0){//1段目が埋まった左寄りに2つ並び、1つ上にある形
            return true;
        }
        if (cage[1][0+t] == cage[1][1+t] == cage[0][(2+t) % 8] || cage[2][0+t] == cage[2][1+t] == cage[1][(2+t) % 8] == 0){//左寄りに2つ並び、1つ1段下にある形
            return true;
        }
        if (cage[2][0+t] == cage[2][1+t] == cage[0][(2+t) % 8] || cage[1][(2+t) % 8] == 0){//左寄りに2つ並び、1つ2段下にある形
            return true;
        }
        if (cage[2][0+t] == cage[2][1+t] == cage[1][(2+t) % 8] || cage[2][(2+t) % 8] == 0){//1段目が埋まった左寄りに2つ並び、1つ下にある形
            return true;
        }
        if (cage[1][0+t] == cage[0][1+t] == cage[0][(2+t) % 8] || cage[2][0+t] == cage[1][1+t] == cage[1][(2+t) % 8] == 0){//右寄りに2つ並び1つ1段上にある形
            return true;
        }
        if (cage[2][0+t] == cage[0][1+t] == cage[0][(2+t) % 8] || cage[1][1+t] == cage[1][(2+t) % 8] == 0){//右寄りに2つ並び1つ2段上にある形(L字型)
            return true;
        }
        if (cage[2][0+t] == cage[1][1+t] == cage[1][(2+t) % 8] || cage[2][1+t] == cage[2][(2+t) % 8] == 0){//1段目が埋まった右寄りに2つ並び1つ上にある形
            return true;
        }
        if (cage[0][0+t] == cage[1][1+t] == cage[1][(2+t) % 8] || cage[1][0+t] == cage[2][1+t] == cage[2][(2+t) % 8] == 0){//右寄りに2つ並び1つ1段下にある形
            return true;
        }
        if (cage[0][0+t] == cage[2][1+t] == cage[2][(2+t) % 8] || cage[1][0+t] == 0){//右寄りに2つ並び1つ2段下にある形
            return true;
        }
        if (cage[1][0+t] == cage[2][1+t] == cage[2][(2+t) % 8] || cage[2][0+t] == 0){//1段目が埋まった右寄りに2つ並び1つ下にある形
            return true;
        }
        if (cage[0][0+t] == cage[2][1+t] == cage[1][(2+t) % 8] || cage[1][0+t] == cage[2][(2+t) % 8] == 0){//相手が（」）こんな形
            return true;
        }
        if (cage[1][0+t] == cage[2][1+t] == cage[0][(2+t) % 8] || cage[2][0+t] == cage[1][(2+t) % 8] == 0){//相手が（反転」）こんな形
            return true;
        }
    }
    return false;
}

int ** to_canonical(const int ** cage){
    int **min_cage; // コピー先の盤面
    min_cage = new int*[height];
    for (int i = 0; i < height; i++) {
        min_cage[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            min_cage[i][j] = cage[i][j];
        }
    }
    for (int board = 0; board < 4; board++){//8状態を保存
        /* code */
    }

    return min_cage;//標準形
}

void printlist(void){
    int basecage[3][8] ={
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 3, 0}
    };//テスト入力
    int ** basecage_p = new int*[height];
    for (int i = 0; i < height; i++) {
        basecage_p[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            basecage_p[i][j] = basecage[i][j];
        }
    }
    basecage_p = put(basecage_p,2,4);

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 8; j++){
            basecage[i][j] = basecage_p[i][j];
            printf("%d ", basecage[i][j]);
        }
        printf("\n"); //配列表示
    }
    return;
}



int main (int argc, char *argv[]){
    printlist();
    // main program here
    return 0;
}