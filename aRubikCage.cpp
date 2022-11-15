#include <iostream>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <cstring>

/*
変数variable/argument/return/用途
copy/ cage / new_cage/ 盤面のコピー
fallcube/ cage/ 0/ キューブを下に落とす（重力）
put/ cage, color, position/ cage/ キューブを入れる場所を決める
flip/ cage, cubeslide/ 0/ 1行右にずらす


引数argument
cage[i][j] i段目(0~2)　左上から右回りに通るマスj個目　下表は上から見た穴
0 | 1 | 2
7 | x | 3
6 | 5 | 4
組み合わせとして
(0,1,2)1枚目　(2,3,4)　2枚目　(4,5,6) 3枚目　(6,7,0) 4枚目　とする
値が小さい方向が左、値が大きい方向が右
color 色の種類(1~6 , 0 = 空)
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


int ** fallcube(int **cage){  //キューブを下に落とす test_finish
    for (int j=0; j < num_positions; j++){
        for (int under = 0; under < 2; under++){
            for (int i = 0; i < 2; i++){    //0,1段のみ
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

int** put(int** cage, int color, int position){//position: キューブを入れる場所（1段のマス数0~7）color入れる色(色数1~6(減らすと1~4)) test_finish
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

int** rotate_left(int ** cage, int cubeslide){//時計回り
    copy(cage);//記録
    /* for (int count = 0; count < 2; count++){
        flip(cage,cubeslide);//3回ずらす
    } */
    int * stack;
    stack = new int [num_positions];
    for (int j = 0; j < num_positions; j++){
        stack[j] = cage[cubeslide][(j+2) %8];
        cage[cubeslide][j] = stack[j];
    }
    fallcube(cage);//重力
    delete[] stack;
    return cage;//変更後の盤面
};

int** rotate_right(int ** cage, int cubeslide){//反時計回り
    copy(cage);//記録
    /*for (int count = 0; count < 6; count++){
        flip(cage,cubeslide);//7回ずらす
    } */
    int * stack;
    stack = new int [num_positions];
    for (int j = 0; j < num_positions ; j++){
        stack[j]= cage[cubeslide][(j-2)% 8];
        cage[cubeslide][j] = stack[j];
    }
    cage = fallcube(cage);//重力
    delete[] stack;
    return cage;//変更後の盤面
};

int** updown(int ** cage){ //test_finish
    copy(cage);//記録
    for (int j = 0; j < num_positions; j++){
        int stack = cage[0][j];
        cage[0][j] = cage[1][j];
        cage[1][j] = stack;//上下入れ替え
    }
    cage = fallcube(cage);//重力
    return cage;//変更後の盤面提示
}


int putreach(/*const */int ** cage, int position){
    for (int j = 0; j < num_positions; j++){//j個目縦リーチ判定
        if (cage[0][j] == cage[1][j] && cage[0][j] != 0){ //縦に赤|赤|空の時
            position = j;
            return position;
        }
    }

    for (int i = 0; i < height; i++){//i段(0~2)数横リーチ判定
        for (int t = 0; t < 8; t += 2){
            if (cage[i][0+t] == cage[i][1+t] && cage[i][(2+t) % 8] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|の時1枚目
                position = (2+t) % 8;
                return position;
            }
            if (cage[i][1+t] == cage[i][(2+t) % 8] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//|空|赤|赤|の時
                position = 0+t;
                return position;
            }
            if (cage[i][0+t] == cage[i][(2+t) % 8] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                position = 1+t;
                return position;
            }
            if (i == 1 && cage[i-1][0+t] != 0 && cage[i-1][1+t] != 0 && cage[i-1][(2+t) % 8] != 0){//1段目が空いていない状態
                if (cage[i][0+t] == cage[i][1+t] && cage[i][(2+t) % 8] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|
                    position = (2+t) % 8;
                    return position;
                }
                if (cage[i][1+t] == cage[i][(2+t) % 8] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//|空|赤|赤|の時
                    position = 0+t;
                    return position;
                }
                if (cage[i][0+t] == cage[i][(2+t) % 8] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    return position;
                }
            }
            if (i == 2 && cage[i-1][0+t] != 0 && cage[i-1][1+t] != 0 && cage[i-1][(2+t) % 8] != 0){//2段目が空いていない状態
                if (cage[i][0+t] == cage[i][1+t] && cage[i][(2+t) % 8] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|
                    position = (2+t) % 8;
                    return position;
                }
                if (cage[i][1+t] == cage[i][(2+t) % 8] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//横に|空|赤|赤|の時
                    position = 0+t;
                    return position;
                }
                if (cage[i][0+t] == cage[i][(2+t) % 8] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    return position;
                }
            }
        }
    }
    // ここまで確認

    for (int t = 0; t < 8; t += 2){//斜め1～4枚目
        if (cage[0][1+t] != 0 && cage[1][0+t] != 0){//右下下がり
            if (cage[1][1+t] == cage[0][(2+t) % 8] && cage[1][1+t] != 0 && cage[2][0+t] == 0){//1段目に空
                position = 0+t;
                return position;
            }
            if (cage[1][1+t] == cage[0][0+t] && cage[1][1+t] != 0 && cage[0][(2+t) % 8] == 0){//3段目に空
                position = (2+t) % 8;
                return position;
            }
            if (cage[2][0+t] == cage[0][(2+t) % 8] && cage[0][(2+t) % 8] != 0 && cage[1][1+t] == 0){//真ん中に空
                position = 1+t;
                return position;
            }
        }
        if (cage[0][1+t] != 0 && cage[1][(2+t) % 8] != 0){//右上上がり
            if (cage[1][1+t] == cage[2][(2+t) % 8] && cage[1][1+t] != 0 && cage[0][0+t] == 0){//1段目に空
                position = 0+t;
                return position;
            }
            if (cage[1][1+t] == cage[0][0+t] && cage[1][1+t] != 0 && cage[2][(2+t) % 8] == 0){//3段目に空
                position = (2+t) % 8;
                return position;
            }
            if (cage[0][0+t] == cage[2][(2+t) % 8] && cage[0][0+t] != 0 && cage[1][1+t] == 0){//真ん中に空
                position = 1+t;
                return position;
            }
        }
    }

    return position;
}

int left_slide_reach(const int ** cage, int cubeslide){
    for (int t = 0; t < 8; t+=2){//1~4枚目
        /* code */
    }


    return cubeslide;
}

int right_slide_reach(const int ** cage, int cubeslide){
    for (int t = 0; t < 8; t+=2){//1~4枚目
        /* code */
    }


    return cubeslide;
}

bool updownreach(/*const*/ int ** cage){
    for (int t = 0; t < 8; t+=2){//1~4枚目
        if ((cage[0][0+t] == cage[1][1+t] == cage[0][(2+t) % 8] != 0) && (cage[1][0+t] == cage[1][(2+t) % 8] == cage[2][1+t] == 0)){//山の形
            return true;
        }
        if ((cage[0][0+t] == cage[1][1+t] == cage[2][(2+t) % 8] != 0) && (cage[1][0+t] == cage[2][1+t] == 0)){//真ん中が高い山の形
            return true;
        }
        if ((cage[1][0+t] == cage[2][1+t] == cage[1][(2+t) % 8] != 0) && (cage[2][0+t] == cage[2][(2+t) % 8]  == 0)){//1段目が埋まった山の形
            return true;
        }//失敗
        if ((cage[1][0+t] == cage[0][1+t] == cage[1][(2+t) % 8] != 0) && (cage[2][0+t] == cage[2][(2+t) % 8] == cage[1][1+t] == 0)){//谷の形
            return true;
        }//miss
        if ((cage[2][0+t] == cage[0][1+t] == cage[2][(2+t) % 8] != 0) && (cage[1][1+t] == 0)){//真ん中が深い谷の形
            return true;
        }
        if ((cage[2][0+t] == cage[1][1+t] == cage[2][(2+t) % 8] != 0) && (cage[2][1+t] == 0)){//1段目が埋まった谷の形
            return true;
        }

        if ((cage[0][0+t] == cage[0][1+t] == cage[1][(2+t) % 8] != 0) && (cage[1][0+t] == cage[1][1+t] == cage[2][(2+t) % 8] == 0)){//左寄りに2つ並び、1つ1段上にある形
            return true;
        }//miss
        if ((cage[0][0+t] == cage[0][1+t] == cage[2][(2+t) % 8] != 0) && (cage[1][0+t] == cage[1][1+t] == 0)){//左寄りに2つ並び、1つ2段上にある形（反転L字型）
            return true;
        }//miss
        if ((cage[1][0+t] == cage[1][1+t] == cage[2][(2+t) % 8] != 0) && (cage[2][0+t] == cage[2][1+t] == 0)){//1段目が埋まった左寄りに2つ並び、1つ上にある形
            return true;
        }//miss
        if ((cage[1][0+t] == cage[1][1+t] == cage[0][(2+t) % 8] != 0) && (cage[2][0+t] == cage[2][1+t] == cage[1][(2+t) % 8] == 0)){//左寄りに2つ並び、1つ1段下にある形
            return true;
        }//miss
        if ((cage[2][0+t] == cage[2][1+t] == cage[0][(2+t) % 8] != 0) && (cage[1][(2+t) % 8] == 0)){//左寄りに2つ並び、1つ2段下にある形
            return true;
        }//miss
        if ((cage[2][0+t] == cage[2][1+t] == cage[1][(2+t) % 8] != 0) && (cage[2][(2+t) % 8] == 0)){//1段目が埋まった左寄りに2つ並び、1つ下にある形
            return true;
        }//miss
        if ((cage[1][0+t] == cage[0][1+t] == cage[0][(2+t) % 8] != 0) && (cage[2][0+t] == cage[1][1+t] == cage[1][(2+t) % 8] == 0)){//右寄りに2つ並び1つ1段上にある形
            return true;
        }//miss
        if ((cage[2][0+t] == cage[0][1+t] == cage[0][(2+t) % 8] != 0) && (cage[1][1+t] == cage[1][(2+t) % 8] == 0)){//右寄りに2つ並び1つ2段上にある形(L字型)
            return true;
        }//miss
        if ((cage[2][0+t] == cage[1][1+t] == cage[1][(2+t) % 8] != 0) && (cage[2][1+t] == cage[2][(2+t) % 8] == 0)){//1段目が埋まった右寄りに2つ並び1つ上にある形
            return true;
        }//miss
        if ((cage[0][0+t] == cage[1][1+t] == cage[1][(2+t) % 8] != 0) && (cage[1][0+t] == cage[2][1+t] == cage[2][(2+t) % 8] == 0)){//右寄りに2つ並び1つ1段下にある形
            return true;
        }//miss
        if ((cage[0][0+t] == cage[2][1+t] == cage[2][(2+t) % 8] != 0) && (cage[1][0+t] == 0)){//右寄りに2つ並び1つ2段下にある形
            return true;
        }
        if ((cage[1][0+t] == cage[2][1+t] == cage[2][(2+t) % 8] != 0) && (cage[2][0+t] == 0)){//1段目が埋まった右寄りに2つ並び1つ下にある形
            return true;
        }
        if ((cage[0][0+t] == cage[2][1+t] == cage[1][(2+t) % 8] != 0) && (cage[1][0+t] == cage[2][(2+t) % 8] == 0)){//相手が（」）こんな形
            return true;
        }//miss
        if ((cage[1][0+t] == cage[2][1+t] == cage[0][(2+t) % 8] != 0) && (cage[2][0+t] == cage[1][(2+t) % 8] == 0)){//相手が（反転」）こんな形
            return true;
        }//miss
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

// int **create_cage(int* cage_0, int* cage_1, int* cage_2) {
//     int** new_cage;
//     new_cage = new int*[3];
//     for (int i = 0; i < 3; i++) {
//         new_cage[i] = new int[8];
//     }
//     memcpy(new_cage[0], cage_0, sizeof(cage_0));
//     memcpy(new_cage[1], cage_1, sizeof(cage_1));
//     memcpy(new_cage[2], cage_2, sizeof(cage_2));

//     return new_cage;
// }

// cage を画面に表示
void print_cage(int** cage) {
    for (int i = 0; i < height; i++){
        for (int j = 0; j < num_positions; j++){
            printf("%d ", cage[i][j]);
        }
        printf("\n"); //配列表示
    }
    printf("\n");
}


void test_func(void){
    int test[3][8] = {
        {4, 2, 1, 4, 3, 0, 5, 3},
        {0, 4, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0}
    };

    // int** org = create_cage(test[0], test[1], test[2]);
    // print_cage(org);
    // int** rotated = rotate_left(org, 1);
    // print_cage(rotated);

    int ** test_cage_p = new int*[height];
    for (int i = 0; i < height; i++) {
        test_cage_p[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            test_cage_p[i][j] = test[i][j];
        }
    }
    print_cage(test_cage_p);
    // test_cage_p = rotate_right(test_cage_p,0);
    // int met = (test_cage_p,2);
    // printf("%d\n", met);
    // int reach = putreach(test_cage_p,0);
    // printf("reach %d\n",reach);
    // bool sita = updownreach(test_cage_p);
    // printf("%d\n",sita);

    int** rotated = updown(test_cage_p);
    print_cage(rotated);
    delete[] test_cage_p;
    return;
}



int main (int argc, char *argv[]){
    test_func();
    // main program here
    return 0;
}