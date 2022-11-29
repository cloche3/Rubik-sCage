#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <vector>

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

using namespace std;

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
    std::memcpy(new_cage, cage, sizeof(2000));

    return new_cage;
};

void print_cage(int** cage) {
    for (int i = 0; i < height; i++){
        for (int j = 0; j < num_positions; j++){
            printf("%d ", cage[i][j]);
        }
        printf("\n"); //配列表示
    }
    printf("\n");
}

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

int** counterclockwise(int ** cage, int cubeslide){//反時計回り test_finish
    copy(cage);//記録

    int **stack  = new int*[height];
    for (int i = 0; i < height; i++) {
        stack[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            stack[i][j] = cage[i][j];
        }
    }

    for (int j = 0; j < num_positions; j++) {
        stack[cubeslide][j] = cage[cubeslide][(j+2) %8];
    }
    stack = fallcube(stack);//重力

    return stack;//変更後の盤面
};

int** clockwise(int ** cage, int cubeslide) {//時計回り test_finish
    copy(cage);//記録

    int **stack  = new int*[height];
    for (int i = 0; i < height; i++) {
        stack[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            stack[i][j] = cage[i][j];
        }
    }

    for (int j = 0; j < num_positions ; j++) {
        cage[cubeslide][(j+2)%8] = stack[cubeslide][j];
    }
    cage = fallcube(cage);//重力
    delete[] stack;

    return cage;//変更後の盤面
};

int** updown(int ** cage) { //test_finish
    copy(cage);//記録
    for (int j = 0; j < num_positions; j++) {
        int stack = cage[0][j];
        cage[0][j] = cage[2][j];
        cage[2][j] = stack;//上下入れ替え
    }
    cage = fallcube(cage);//重力
    return cage;//変更後の盤面提示
}


int putreach(/*const */int ** cage) { //test_finish
    int position; //キューブを入れる箇所
    for (int j = 0; j < num_positions; j++){//j個目縦リーチ判定
        if (cage[0][j] == cage[1][j] && cage[0][j] != 0) { //縦に赤|赤|空の時
            position = j;
            return position;
        }
    }

    for (int i = 0; i < height; i++){//i段(0~2)数横リーチ判定
        for (int t = 0; t < 8; t += 2){
            if (i == 0){// 1段目
                if (cage[i][0+t] == cage[i][1+t] && cage[i][((2+t) % 8)] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|の時1枚目
                    position = (2+t) % 8;
                    return position;
                }
                if (cage[i][1+t] == cage[i][((2+t) % 8)] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//|空|赤|赤|の時
                    position = 0+t;
                    return position;
                }
                if (cage[i][0+t] == cage[i][((2+t) % 8)] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    return position;
                }
            }
            if (i == 1 && cage[i-1][0+t] != 0 && cage[i-1][1+t] != 0 && cage[i-1][((2+t) % 8)] != 0){//1段目が空いていない状態
                if (cage[i][0+t] == cage[i][1+t] && cage[i][((2+t) % 8)] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|
                    position = (2+t) % 8;
                    return position;
                }
                if (cage[i][1+t] == cage[i][((2+t) % 8)] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//|空|赤|赤|の時
                    position = 0+t;
                    return position;
                }
                if (cage[i][0+t] == cage[i][((2+t) % 8)] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    return position;
                }
            }
            if (i == 2 && cage[i-1][0+t] != 0 && cage[i-1][1+t] != 0 && cage[i-1][((2+t) % 8)] != 0){//2段目が空いていない状態
                if (cage[i][0+t] == cage[i][1+t] && cage[i][((2+t) % 8)] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|
                    position = (2+t) % 8;
                    return position;
                }
                if (cage[i][1+t] == cage[i][((2+t) % 8)] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//横に|空|赤|赤|の時
                    position = 0+t;
                    return position;
                }
                if (cage[i][0+t] == cage[i][((2+t) % 8)] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    return position;
                }
            }
        }
    }

    for (int t = 0; t < 8; t += 2){//斜め1～4枚目
        if (cage[0][1+t] != 0 && cage[1][((2+t) % 8)] != 0){//右上上がり
            if (cage[1][1+t] == cage[2][((2+t) % 8)] && cage[1][1+t] != 0 && cage[0][0+t] == 0){//1段目に空
                position = 0+t;
                return position;
            }
            if (cage[1][1+t] == cage[0][0+t] && cage[1][1+t] != 0 && cage[2][((2+t) % 8)] == 0){//3段目に空
                position = (2+t) % 8;
                return position;
            }
            if (cage[0][0+t] == cage[2][((2+t) % 8)] && cage[0][0+t] != 0 && cage[1][1+t] == 0){//真ん中に空
                position = 1+t;
                return position;
            }
        }
        if (cage[0][1+t] != 0 && cage[1][0+t] != 0){//右下下がり
            if (cage[1][1+t] == cage[0][((2+t) % 8)] && cage[1][1+t] != 0 && cage[2][0+t] == 0){//1段目に空
                position = 0+t;
                return position;
            }
            if (cage[1][1+t] == cage[0][0+t] && cage[1][1+t] != 0 && cage[0][((2+t) % 8)] == 0){//3段目に空
                position = (2+t) % 8;
                return position;
            }
            if (cage[2][0+t] == cage[0][((2+t) % 8)] && cage[0][((2+t) % 8)] != 0 && cage[1][1+t] == 0){//真ん中に空
                position = 1+t;
                return position;
            }
        }

    }

    return position;
}

/*
int** rotate_cage(int** cage){ //回転体
    int** stack  = new int*[height];
    for (int i = 0; i < height; i++) {
        stack[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            stack[i][j] = cage[i][j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < num_positions; j++) {
            stack[i][((2+j) % 8)] = cage[i][j];
        }
    }

    return stack;

}*/

/** return True if cage1 <= cage2*/
bool le(int** cage1, int** cage2) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < num_positions; j++) {
            if ((cage1[i][j] == 0) && (0 < cage2[i][j])){
                return true;
            }else if (cage1[i][j] > cage2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int** to_canonical(int** cage){ //標準形
    int** min_cage; // 最小盤面
    min_cage = new int*[height];
    for (int i = 0; i < height; i++) {
        min_cage[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            min_cage[i][j] = cage[i][j];
        }
    }
    int** rotate_cage; // 回転体
    rotate_cage = new int*[height];
    for (int i = 0; i < height; i++) {
        rotate_cage[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            rotate_cage[i][j] = cage[i][j];
        }
    }
    int count = 1; //test
    for (int board = 0; board < 4; board++){ //8状態を保存

        for (int i = 0; i < height; i++) { //鏡像
            swap(cage[i][(7+board) % 8],cage[i][1+board]);
            swap(cage[i][(6+board) % 8],cage[i][2+board]);
            swap(cage[i][(5+board) % 8],cage[i][3+board]);
        }

        printf("mirror %d\n",count);
        if (le(min_cage, cage)){// 大小比較
            printf("true\n");
        }
        print_cage(cage);
        count += 1;

        if (le(min_cage, cage)){ // 大小比較
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < num_positions; j++) {
                    min_cage[i][j] = cage[i][j];
                }
            }
        }
        for (int i = 0; i < height; i++) { // 鏡像を戻す
            swap(cage[i][(7+board) % 8], cage[i][1+board]);
            swap(cage[i][(6+board) % 8], cage[i][2+board]);
            swap(cage[i][(5+board) % 8], cage[i][3+board]);
        }

        // for (int i = 0; i < height; i++) {
        //     for (int j = 0; j < num_positions; j++) {
        //         if (le(cage, min_cage)){
        //             cage[i][j] = min_cage[i][j];
        //         }
        //     }
        // }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < num_positions; j++) {
                rotate_cage[i][j] = cage[i][(((board*2)+2+j) % 8)];
            }
        }

        printf("rotate %d\n",count);
        if (le(min_cage, rotate_cage)){
            printf("true\n");
        }
        print_cage(rotate_cage);
        count += 1;

        if (le(min_cage, rotate_cage)){ // 大小比較
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < num_positions; j++) {
                    min_cage[i][j] = rotate_cage[i][j];
                }
            }
        }
        // for (int i = 0; i < height; i++) {
        //     for (int j = 0; j < num_positions; j++) {
        //         if (le(cage, min_cage)){
        //             cage[i][j] = min_cage[i][j];
        //         }
        //     }
        // }

    }
    delete [] rotate_cage;
    return min_cage;
}



vector<int> three_cube_line(int ** cage) { //　3つ揃った状態、引き分け（2色以上）も加味 test_finish
    std::vector<int> buffer_color;   //色の一時保存
    for (int j = 0; j < num_positions; j++) {//j列目縦3揃い判定
        if ((cage[0][j] == cage[1][j]) && (cage[1][j] == cage[2][j])){
            if (cage[0][j] != 0) {
                buffer_color.push_back(cage[0][j]);
            }
        }
    }

    for (int i = 0; i < height; i++){
        for (int t = 0; t < 8; t += 2){//i段目横3揃い判定
            if ((cage[i][0+t] == cage[i][1+t]) && (cage[i][1+t] == cage [i][((2+t)%8)])){
                if (cage[i][0+t] != 0){
                    buffer_color.push_back(cage[i][0+t]);
                }
            }
        }
    }

    for (int t = 0; t < 8; t += 2){//斜め3揃い判定
        if ((cage[0][0+t] == cage[1][1+t]) && (cage[1][1+t] == cage [2][((2+t)%8)])){
            if (cage[0][0+t] != 0){
                buffer_color.push_back(cage[0][0+t]);
            }
        }
        if ((cage[2][0+t] == cage[1][1+t]) && (cage[1][1+t] == cage [0][((2+t)%8)])){
            if (cage[2][0+t] != 0){
                buffer_color.push_back(cage[2][0+t]);
            }
        }
    }
    return buffer_color;
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



void test_func(void){
    int test[3][8] = {
        {3, 0, 0, 0, 0, 0, 1, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    // int test2[3][8] = {
    //     {6, 5, 4, 3, 2, 2, 1, 1},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0}
    // };

    // int** org = create_cage(test[0], test[1], test[2]);
    // print_cage(org);
    // int** rotated = clockwise(org, 1);
    // print_cage(rotated);

    int ** test_cage_p = new int*[height];
    for (int i = 0; i < height; i++) {
        test_cage_p[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            test_cage_p[i][j] = test[i][j];
        }
    }

    // int ** test_cage_p2 = new int*[height];
    // for (int i = 0; i < height; i++) {
    //     test_cage_p2[i] = new int[num_positions];
    //     for (int j = 0; j < num_positions; j++) {
    //         test_cage_p2[i][j] = test2[i][j];
    //     }
    // }
    printf("test_cage\n");
    print_cage(test_cage_p);

    // test_cage_p = clockwise(test_cage_p,0);
    // test_cage_p = counterclockwise(test_cage_p, 0);

    // int met = putreach(test_cage_p);
    // printf("putreach %d\n", met);

    // vector<int> line = three_cube_line(test_cage_p);
    // for (int i = 0; i < line.size(); i++) {
    //     cout << line.at(i) << ", ";
    // }
    // cout << endl;

    // bool sita = updownreach(test_cage_p);
    // printf("updownreach %d\n",sita);

    test_cage_p = to_canonical(test_cage_p);

    printf("result\n");
    print_cage(test_cage_p);
    delete [] test_cage_p;
    return;
}



int main (int argc, char *argv[]){
    test_func();
    // main program here
    return 0;
}