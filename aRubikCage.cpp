#include <iostream>
#include <map>

//using namespace std;

void fallcube(int **cage){//キューブを下に落とす
    for (int e,n,t=0; t < 8 ; t++)
    {
        for (n = 0; n < 2; n++)
        {
            for (e = 0; e < 2; e++)
            {
                cage[e][t] == 0 && (cage[e][t] = cage[e + 1][t], cage[e + 1][t] = 0);//下に落とす
            }
        }
    }
    return cage;////コピーせず今の盤面を上書き（変更後の盤面）
};

int mem(const int ** cage){
    int N[3][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},//N[i][j] i段目　左上から右回りに通るマスj個目
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    };
    for (int e,i = 0; i < 3 ; i++)
    {
        for (e = 0; e < 8; e++) {N[i][e] = cage[i][e];}//盤面のコピー
    }

    return N;//コピーした変数
};

int put(int ** cage,signed char mycolor,signed char e){//e入力変数（マス数2~9）mycolor入力変数(色数1~6(減らすと1~4))
    if (cage[2][e -1] != -1 || mycolor == -1)//エラー確認
    {
        return 0;//値なし
    };
    mem(cage);//記録
    cage[2][e - 1] = mycolor;//入力された場所に指定された色のキューブを入れる
    fallcube(cage);//重力
    return 0;//cage;//変更後の盤面
};

int * flip(int ** cage/*,signed char e　サイズエラー*/){//e入力変数(段数1~3)
    int e;//仮置き
    for (int n = cage[e][0],i; i < 7; i++)
    {
        cage[e][i] = cage[e][i + 1];
        cage[e][7] = n;
        n = cage[e][0];//1段全体的に1行ずらす
    }
    return 0;//cage;//変更後の盤面
};

void rotate_left(int ** cage){
    mem(cage);//記録
    for (int i = 0; i < 2; i++)//右回転
    {
        flip(cage);//3回ずらす
    }
    fallcube(cage);//重力
    return;//cage;//変更後の盤面
};

void rotate_right(int ** cage){
    mem(cage);//記録
    for (int i = 0; i < 6; i++)//左回転
    {
        flip(cage);//7回ずらす
    }
    fallcube(cage);//重力
    return;//cage;//変更後の盤面
};

void updown(int ** cage){
    mem(cage);//記録
    for (int t,e = 0; e < 8; e++)
    {
        t = cage[0][e];
        cage[0][e] = cage[2][e];
        cage[2][e] = t;//上下入れ替え
    }
    fallcube(cage);//重力
    return;//cage;//変更後の盤面提示
}

int reset(int ** cage){
    int reset_cage [3][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    };
    for (int e,i = 0; i < 3 ; i++)
    {
        for (e = 0; e < 8; e++) {reset_cage[i][e] = cage[i][e];}
    }
    return 0;
}

int ** reach(const int ** cage){

    return 0;
}

int ** to_canonical(const int ** cage){
    int min_cage[3][8]={
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    };
    for (int e,i = 0; i < 3 ; i++)
    {
        for (e = 0; e < 8; e++) {min_cage[i][e] = cage[i][e];}//コピー
    }
    for (int i = 0; i < 4; i++)//8状態を保存
    {
        /* code */
    }

    return 0;//min_cage;//標準形
}
