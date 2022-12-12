#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

const int height = 3;   // ケージの高さ
const int length_of_edge = 3;   // ケージを上から見た正方形の一辺の長さ
const int num_positions = length_of_edge * 2 + (length_of_edge - 2) * 2;    // 上から見た、ブロックを入れる穴の数。一辺の長さが3のときは8

int** make_cage(int base_cage[height][num_positions]){ //2次元配列をポインタにする　test_finish
    int** cage = new int*[height];
    for (int i = 0; i < height; i++) {
        cage[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            cage[i][j] = base_cage[i][j];
        }
    }

    return cage;
}

/**
 * すでに存在する盤面 dest に、盤面 src をそのままコピーする
*/
void copy(int** src, int** dest) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < num_positions; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int** copy(int** src){
    int **dest; // コピー先の盤面

    dest = new int*[height];
    for(int i = 0; i < height; i++) {
        dest[i] = new int[num_positions];
    }
    copy(src, dest);

    return dest;
};


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

    cage[2][position] = color;//入力された場所に指定された色のキューブを入れる
    cage = fallcube(cage);//重力
    return cage;//変更後の盤面
};

int** counterclockwise(int ** cage, int cubeslide){//反時計回り test_finish
    int **stack  = copy(cage);

    for (int j = 0; j < num_positions; j++) {
        stack[cubeslide][j] = cage[cubeslide][(j+2) %8];
    }
    stack = fallcube(stack);//重力

    return stack;//変更後の盤面
};

int** clockwise(int ** cage, int cubeslide) {//時計回り test_finish
    int **stack  = copy(cage);

    for (int j = 0; j < num_positions ; j++) {
        cage[cubeslide][(j+2)%8] = stack[cubeslide][j];
    }
    cage = fallcube(cage);//重力
    delete[] stack;

    return cage;//変更後の盤面
};

int** updown(int ** cage) { //test_finish
    for (int j = 0; j < num_positions; j++) {
        int stack = cage[0][j];
        cage[0][j] = cage[2][j];
        cage[2][j] = stack;//上下入れ替え
    }
    cage = fallcube(cage);//重力
    return cage;//変更後の盤面提示
}


pair<int, int> putreach(/*const */int ** cage) { //test_finish
    int position; //キューブを入れる箇所
    int color; //揃っている色
    for (int j = 0; j < num_positions; j++){//j個目縦リーチ判定
        if (cage[0][j] == cage[1][j] && cage[0][j] != 0) { //縦に赤|赤|空の時
            position = j;
            color = cage[0][j];
            return std::make_pair(position, color);
        }
    }

    for (int i = 0; i < height; i++){//i段(0~2)数横リーチ判定
        for (int t = 0; t < 8; t += 2){
            if (i == 0){// 1段目
                if (cage[i][0+t] == cage[i][1+t] && cage[i][((2+t) % 8)] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|の時1枚目
                    position = (2+t) % 8;
                    color = cage[i][0+t];
                    return std::make_pair(position, color);
                }
                if (cage[i][1+t] == cage[i][((2+t) % 8)] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//|空|赤|赤|の時
                    position = 0+t;
                    color = cage[i][1+t];
                    return std::make_pair(position, color);
                }
                if (cage[i][0+t] == cage[i][((2+t) % 8)] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    color = cage[i][0+t];
                    return std::make_pair(position, color);
                }
            }
            if (i == 1 && cage[i-1][0+t] != 0 && cage[i-1][1+t] != 0 && cage[i-1][((2+t) % 8)] != 0){//1段目が空いていない状態
                if (cage[i][0+t] == cage[i][1+t] && cage[i][((2+t) % 8)] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|
                    position = (2+t) % 8;
                    color = cage[i][0+t];
                    return std::make_pair(position, color);
                }
                if (cage[i][1+t] == cage[i][((2+t) % 8)] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//|空|赤|赤|の時
                    position = 0+t;
                    color = cage[i][1+t];
                    return std::make_pair(position, color);
                }
                if (cage[i][0+t] == cage[i][((2+t) % 8)] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    color = cage[i][0+t];
                    return std::make_pair(position, color);
                }
            }
            if (i == 2 && cage[i-1][0+t] != 0 && cage[i-1][1+t] != 0 && cage[i-1][((2+t) % 8)] != 0){//2段目が空いていない状態
                if (cage[i][0+t] == cage[i][1+t] && cage[i][((2+t) % 8)] == 0 && cage[i][1+t] != 0){//横に|赤|赤|空|
                    position = (2+t) % 8;
                    color = cage[i][0+t];
                    return std::make_pair(position, color);
                }
                if (cage[i][1+t] == cage[i][((2+t) % 8)] && cage[i][0+t] == 0 && cage[i][1+t] != 0){//横に|空|赤|赤|の時
                    position = 0+t;
                    color = cage[i][1+t];
                    return std::make_pair(position, color);
                }
                if (cage[i][0+t] == cage[i][((2+t) % 8)] && cage[i][0+t] != 0 && cage[i][1+t] == 0){//横に|赤|空|赤|の時
                    position = 1+t;
                    color = cage[i][0+t];
                    return std::make_pair(position, color);
                }
            }
        }
    }

    for (int t = 0; t < 8; t += 2){//斜め1～4枚目
        if (cage[0][1+t] != 0 && cage[1][((2+t) % 8)] != 0){//右上上がり
            if (cage[1][1+t] == cage[2][((2+t) % 8)] && cage[1][1+t] != 0 && cage[0][0+t] == 0){//1段目に空
                position = 0+t;
                color = cage[1][1+t];
                return std::make_pair(position, color);
            }
            if (cage[1][1+t] == cage[0][0+t] && cage[1][1+t] != 0 && cage[2][((2+t) % 8)] == 0){//3段目に空
                position = (2+t) % 8;
                color = cage[1][1+t];
                return std::make_pair(position, color);
            }
            if (cage[0][0+t] == cage[2][((2+t) % 8)] && cage[0][0+t] != 0 && cage[1][1+t] == 0){//真ん中に空
                position = 1+t;
                color = cage[0][0+t];
                return std::make_pair(position, color);
            }
        }
        if (cage[0][1+t] != 0 && cage[1][0+t] != 0){//右下下がり
            if (cage[1][1+t] == cage[0][((2+t) % 8)] && cage[1][1+t] != 0 && cage[2][0+t] == 0){//1段目に空
                position = 0+t;
                color = cage[1][1+t];
                return std::make_pair(position, color);
            }
            if (cage[1][1+t] == cage[0][0+t] && cage[1][1+t] != 0 && cage[0][((2+t) % 8)] == 0){//3段目に空
                position = (2+t) % 8;
                color = cage[1][1+t];
                return std::make_pair(position, color);
            }
            if (cage[2][0+t] == cage[0][((2+t) % 8)] && cage[0][((2+t) % 8)] != 0 && cage[1][1+t] == 0){//真ん中に空
                position = 1+t;
                color = cage[2][0+t];
                return std::make_pair(position, color);
            }
        }

    }

    return std::make_pair(position, 0);
}

/** cage を時計回りに90度回転したものに置き換える*/
void rotate_cage(int** cage){ //回転体
    int** stack  = copy(cage);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < num_positions; j++) {
            cage[i][((2+j) % 8)] = stack[i][j];
        }
    }
}

/**
 * return True iff cage1 is less than or equal to cage2
 * i.e., cage1 <= cage2
*/
bool le(int** cage1, int** cage2) {
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < num_positions; j++) {
            if (cage1[i][j] < cage2[i][j]) {
                return true;
            } else if (cage1[i][j] > cage2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int** create_swap_cage(int** cage) {
    int** swapped = copy(cage);
    for (int i = 0; i < height; i++) { //鏡像
        swap(swapped[i][7], swapped[i][1]);
        swap(swapped[i][6], swapped[i][2]);
        swap(swapped[i][5], swapped[i][3]);
    }
    return swapped;
}


/**
 * cage を標準形に書き換える
*/
void to_canonical(int** org) {
    int **tmp = copy(org);

    // 最初の鏡像が小さかったら org 書き換え
    int ** swapped = create_swap_cage(tmp);
    if (le(swapped, org)) {
        copy(swapped, org);
    }
    delete[] swapped;

    // 回転を3回
    for (int r = 0; r < 3; r++) {
        rotate_cage(tmp);
        if (le(tmp, org)) {
            copy(tmp, org);
        }

        int ** swapped = create_swap_cage(tmp);
        if (le(swapped, org)) {
            copy(swapped, org);
        }
        delete[] swapped;
    }
    delete[] tmp;
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
    std::sort(buffer_color.begin(), buffer_color.end());
    return buffer_color;
}