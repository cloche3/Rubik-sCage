#include <iostream>
#include <algorithm>
#include <map>

/*
引数
cage[i][j] i段目(1~3)　左上から右回りに通るマスj個目
1 | 2 | 3
8 | x | 4
7 | 6 | 5
組み合わせとして
(1,2,3)1枚目　(3,4,5)　2枚目　(5,6,7) 3枚目　(7,8,1) 4枚目　とする

color 色数(1~6)
putcube ブロックを入れる時の穴決定(1~8)
flippoint ケージを回転させる段決定(1~3)

*/


const int height = 3;   // ケージの高さ
const int length_of_edge = 3;   // ケージを上から見た正方形の一辺の長さ
const int num_positions = length_of_edge * 2 + (length_of_edge - 2) * 2;    // 上から見た、ブロックを入れる穴の数。一辺の長さが3のときは8

int** copy(/*const*/int** cage){
    int **new_cage; // コピー先の盤面
    new_cage = new int*[height];
    for (int i = 0; i < height; i++) {
        *new_cage = new int[num_positions];
    }

    //盤面のコピー
    for (int i = 0; i < height ; i++) {
        for (int j = 0; j < num_positions; j++) new_cage[i][j] = cage[i][j];
    }

    return new_cage;
};


void fallcube(int **cage){//キューブを下に落とす
    for (int j=0; j < num_positions ; j++){
        for (int under = 0; under < 2; under++){
            for (int i = 0; i < 2; i++){//1,2段のみ
                cage[i][j] == 0 && (cage[i][j] = cage[i + 1][j], cage[i + 1][j] = 0);//下に落とす
            }
        }
    }
    return;////コピーせず今の盤面を上書き（変更後の盤面）
};


int** put(int** cage,signed char color,signed char putcube){//putcubeキューブを入れる（1段のマス数1~8）color入れる色(色数1~6(減らすと1~4))
    if (cage[3][putcube] != 0 || color == 0){//エラー確認
        return 0;//値なし
    };
    copy(cage);//記録
    cage[2][putcube] = color;//入力された場所に指定された色のキューブを入れる
    fallcube(cage);//重力
    return cage;//変更後の盤面
};

void flip(int ** cage,signed char flippoint){//flippoint横にずらす場所決め(段数1~3)
    for (int stack = cage[flippoint][0],cubeslide; cubeslide < 7; cubeslide++){
        cage[flippoint][cubeslide] = cage[flippoint][cubeslide + 1];
        cage[flippoint][7] = stack;
        stack = cage[flippoint][0];//i段全体的に1行ずらす
    }
    return;//変更後の盤面
};

int** rotate_left(int ** cage,signed char flippoint){
    copy(cage);//記録
    for (int count = 0; count < 2; count++){//右回転
        flip(cage,flippoint);//3回ずらす
    }
    fallcube(cage);//重力
    return cage;//変更後の盤面
};

int** rotate_right(int ** cage,signed char flippoint){
    copy(cage);//記録
    for (int count = 0; count < 6; count++){//左回転
        flip(cage,flippoint);//7回ずらす
    }
    fallcube(cage);//重力
    return cage;//変更後の盤面
};

int** updown(int ** cage){
    copy(cage);//記録
    for (int stack,j = 0; j < num_positions; j++){
        stack = cage[0][j];
        cage[0][j] = cage[2][j];
        cage[2][j] = stack;//上下入れ替え
    }
    fallcube(cage);//重力
    return cage;//変更後の盤面提示
}

int **reset(int ** cage){
    int **reset_cage; // コピー元の盤面
    reset_cage = new int*[height];
    for (int i = 0; i < height; i++) {
        *reset_cage = new int[num_positions];
    }
    //盤面の上書き
    for (int i = 0; i < height ; i++) {
        for (int j = 0; j < num_positions; j++) cage[i][j] = reset_cage[i][j];
    }
    return cage;//初期化された盤面
}

bool reach(const int ** cage){
    for (int j = 0; j < num_positions; j++){//j個目縦リーチ判定
        if (cage[1][j] == cage[2][j]){ //縦に赤|赤|空の時
            return true;
        }
    }

    for (int i = 0; i < height; i++){//i段数横リーチ判定
        if (((cage[i][1] == cage[i][2] && cage[i][3] == 0)|| (cage[i][2] == cage[i][3] && cage[i][1] == 0)) && cage[i][2] != 0){
        //横に|赤|赤|空|or |空|赤|赤|の時1枚目
            return true;
        }
        if (cage[i][1] == cage[i][3] && cage[i][1] != 0 && cage[i][3] != 0 && cage[i][2] == 0){//横に|赤|空|赤|の時
            return true;
        }
        if (i = 2 && cage[i-1][1] != 0 && cage[i-1][2] != 0 && cage[i-1][3] != 0){//1段目が空いていない状態
            if (((cage[i][1] == cage[i][2] && cage[i][3] == 0)|| (cage[i][2] == cage[i][3] && cage[i][1] == 0)) && cage[i][2] != 0){
            //横に|赤|赤|空|or |空|赤|赤|の時
                return true;
            }
            if (cage[i][1] == cage[i][3] && cage[i][1] != 0 && cage[i][3] != 0 && cage[i][2] == 0){//横に|赤|空|赤|の時
                return true;
            }
        }
        if (i = 3 && cage[i-1][1] != 0 && cage[i-1][2] != 0 && cage[i-1][3] != 0){//2段目が空いていない状態
            if (((cage[i][1] == cage[i][2] && cage[i][3] == 0)|| (cage[i][2] == cage[i][3] && cage[i][1] == 0)) && cage[i][2] != 0){
            //横に|赤|赤|空|or |空|赤|赤|の時
                return true;
            }
            if (cage[i][1] == cage[i][3] && cage[i][1] != 0 && cage[i][3] != 0 && cage[i][2] == 0){//横に|赤|空|赤|の時
                return true;
            }
        }

        if (((cage[i][3] == cage[i][4] && cage[i][5] == 0)|| (cage[i][4] == cage[i][5] && cage[i][3] == 0)) && cage[i][4] != 0 ){
        //2枚目
            return true;
        }
        if (cage[i][3] == cage[i][5] && cage[i][3] != 0 && cage[i][5] != 0 && cage[i][4] == 0){//横に|赤|空|赤|の時
            return true;
        }
        if (i = 2 && cage[i-1][3] != 0 && cage[i-1][4] != 0 && cage[i-1][5] != 0){//1段目が空いていない状態
            if (((cage[i][3] == cage[i][4] && cage[i][5] == 0)|| (cage[i][4] == cage[i][5] && cage[i][3] == 0)) && cage[i][4] != 0 ){
            //横に|赤|赤|空|or |空|赤|赤|の時
            return true;
            }
            if (cage[i][3] == cage[i][5] && cage[i][3] != 0 && cage[i][5] != 0 && cage[i][4] == 0){//横に|赤|空|赤|の時
            return true;
            }
        }
        if (i = 3 && cage[i-1][3] != 0 && cage[i-1][4] != 0 && cage[i-1][5] != 0){//2段目が空いていない状態
            if (((cage[i][3] == cage[i][4] && cage[i][5] == 0)|| (cage[i][4] == cage[i][5] && cage[i][3] == 0)) && cage[i][4] != 0 ){
            //横に|赤|赤|空|or |空|赤|赤|の時
            return true;
            }
            if (cage[i][3] == cage[i][5] && cage[i][3] != 0 && cage[i][5] != 0 && cage[i][4] == 0){//横に|赤|空|赤|の時
            return true;
            }
        }

        if (((cage[i][5] == cage[i][6] && cage[i][7] == 0)|| (cage[i][6] == cage[i][7] && cage[i][5] == 0)) && cage[i][6] != 0 ){
        //3枚目
            return true;
        }
        if (cage[i][5] == cage[i][7] && cage[i][5] != 0 && cage[i][7] != 0 && cage[i][6] == 0){//横に|赤|空|赤|の時
            return true;
        }
        if (i = 2 && cage[i-1][5] != 0 && cage[i-1][6] != 0 && cage[i-1][7] != 0){//1段目が空いていない状態
            if (((cage[i][5] == cage[i][6] && cage[i][7] == 0)|| (cage[i][6] == cage[i][7] && cage[i][5] == 0)) && cage[i][6] != 0 ){
            //横に|赤|赤|空|or |空|赤|赤|の時
                return true;
            }
            if (cage[i][5] == cage[i][7] && cage[i][5] != 0 && cage[i][7] != 0 && cage[i][6] == 0){//横に|赤|空|赤|の時
                return true;
            }
        }
        if (i = 3 && cage[i-1][5] != 0 && cage[i-1][6] != 0 && cage[i-1][7] != 0){//2段目が空いていない状態
            if (((cage[i][5] == cage[i][6] && cage[i][7] == 0)|| (cage[i][6] == cage[i][7] && cage[i][5] == 0)) && cage[i][6] != 0 ){
            //横に|赤|赤|空|or |空|赤|赤|の時
                return true;
            }
            if (cage[i][5] == cage[i][7] && cage[i][5] != 0 && cage[i][7] != 0 && cage[i][6] == 0){//横に|赤|空|赤|の時
                return true;
            }
        }

        if (((cage[i][7] == cage[i][8] && cage[i][1] == 0)|| (cage[i][8] == cage[i][1] && cage[i][7] == 0)) && cage[i][8] != 0 ){
        //4枚目
            return true;
        }
        if (cage[i][7] == cage[i][1] && cage[i][7] != 0 && cage[i][1] != 0 && cage[i][8] == 0){//横に|赤|空|赤|の時
            return true;
        }
        if (i = 2 && cage[i-1][7] != 0 && cage[i-1][8] != 0 && cage[i-1][1] != 0){//1段目が空いていない状態
            if (((cage[i][7] == cage[i][8] && cage[i][1] == 0)|| (cage[i][8] == cage[i][1] && cage[i][7] == 0)) && cage[i][8] != 0 ){
            //横に|赤|赤|空|or |空|赤|赤|の時
                return true;
            }
            if (cage[i][7] == cage[i][1] && cage[i][7] != 0 && cage[i][1] != 0 && cage[i][8] == 0){//横に|赤|空|赤|の時
                return true;
            }
        }
        if (i = 3 && cage[i-1][7] != 0 && cage[i-1][8] != 0 && cage[i-1][1] != 0){//2段目が空いていない状態
            if (((cage[i][7] == cage[i][8] && cage[i][1] == 0)|| (cage[i][8] == cage[i][1] && cage[i][7] == 0)) && cage[i][8] != 0 ){
            //横に|赤|赤|空|or |空|赤|赤|の時
                return true;
            }
            if (cage[i][7] == cage[i][1] && cage[i][7] != 0 && cage[i][1] != 0 && cage[i][8] == 0){//横に|赤|空|赤|の時
                return true;
            }
        }
    }

    if (cage[1][2] != 0 || cage[1][4] != 0 || cage[1][6] != 0 || cage[1][8] != 0){//斜めの時真ん中1段目は必ずブロックが存在する
        if (cage[2][1] != 0 || cage[2][3] != 0 || cage[2][5] != 0 || cage[2][7] != 0)
        {
        }

    }


    return false;
}

int ** to_canonical(const int ** cage){
    int **min_cage; // コピー先の盤面
    min_cage = new int*[height];
    for (int i = 0; i < height; i++) {
        *min_cage = new int[num_positions];
    }
    for (int i = 0; i < height ; i++){
        for (int j = 0; j < num_positions; j++)min_cage[i][j] = cage[i][j];//コピー
    }
    for (int board = 0; board < 4; board++){//8状態を保存
        /* code */
    }

    return min_cage;//標準形
}
