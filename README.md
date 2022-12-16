# Rubik's Cage

test

save code

bool updownreach(/*const*/ int ** cage){
    for (int t = 0; t < 8; t+=2){//1~4枚目
        if ((cage[0][0+t] == cage[1][1+t] == cage[0][((t+2) % 8)]) && cage[0][((2+t) % 8)] != 0 && (cage[1][0+t] == cage[1][((2+t) % 8)] == cage[2][1+t] == 0)){//山の形
            printf("1 %d\n",t);
            return true;
        }
        if ((cage[0][0+t] == cage[1][1+t] == cage[2][((2+t) % 8)]) && cage[2][((2+t) % 8)] != 0 && (cage[1][0+t] == cage[2][1+t] == 0)){//真ん中が高い山の形
            printf("2 %d\n",t);
            return true;
        }
        if ((cage[1][0+t] == cage[2][1+t] == cage[1][((2+t) % 8)]) && cage[1][((2+t) % 8)] != 0 && (cage[2][0+t] == cage[2][((2+t) % 8)]  == 0)){//1段目が埋まった山の形
            printf("3 %d\n",t);
            return true;
        }//失敗
        if ((cage[1][0+t] == cage[0][1+t] == cage[1][((2+t) % 8)]) && cage[1][((2+t) % 8)] != 0 && (cage[2][0+t] == cage[2][((2+t) % 8)] == cage[1][1+t] == 0)){//谷の形
            printf("4 %d\n",t);
            return true;
        }//miss
        if ((cage[2][0+t] == cage[0][1+t] == cage[2][((2+t) % 8)]) && cage[2][((2+t) % 8)] != 0 && (cage[1][1+t] == 0)){//真ん中が深い谷の形
            printf("5 %d\n",t);
            return true;
        }
        if ((cage[2][0+t] == cage[1][1+t] == cage[2][((2+t) % 8)]) && cage[2][((2+t) % 8)] != 0 && (cage[2][1+t] == 0)){//1段目が埋まった谷の形
            printf("6 %d\n",t);
            return true;
        }

        if ((cage[0][0+t] == cage[0][1+t] == cage[1][((2+t) % 8)]) && cage[1][((2+t) % 8)] != 0 && (cage[1][0+t] == cage[1][1+t] == cage[2][((2+t) % 8)] == 0)){//左寄りに2つ並び、1つ1段上にある形
            printf("7 %d\n",t);
            return true;
        }//miss
        if ((cage[0][0+t] == cage[0][1+t] == cage[2][((2+t) % 8)]) && cage[2][((2+t) % 8)] != 0 && (cage[1][0+t] == cage[1][1+t] == 0)){//左寄りに2つ並び、1つ2段上にある形（反転L字型）
            printf("8 %d\n",t);
            return true;
        }//miss
        if ((cage[1][0+t] == cage[1][1+t] == cage[2][((2+t) % 8)]) && cage[2][((2+t) % 8)] != 0 && (cage[2][0+t] == cage[2][1+t] == 0)){//1段目が埋まった左寄りに2つ並び、1つ上にある形
            printf("9 %d\n",t);
            return true;
        }//miss

        if ((cage[1][0+t] == cage[1][1+t] == cage[0][((2+t) % 8)]) && cage[0][((2+t) % 8)] != 0 && (cage[2][0+t] == cage[2][1+t] == cage[1][((2+t) % 8)] == 0)){//左寄りに2つ並び、1つ1段下にある形
            printf("10 %d\n",t);
            return true;
        }//miss

        if ((cage[2][0+t] == cage[2][1+t] == cage[0][((2+t) % 8)]) && cage[0][((2+t) % 8)] != 0 && (cage[1][((2+t) % 8)] == 0)){//左寄りに2つ並び、1つ2段下にある形
            printf("11 %d\n",t);
            return true;
        }//miss
        if ((cage[2][0+t] == cage[2][1+t] == cage[1][((2+t) % 8)]) && cage[1][((2+t) % 8)] != 0 && (cage[2][((2+t) % 8)] == 0)){//1段目が埋まった左寄りに2つ並び、1つ下にある形
            printf("12 %d\n",t);
            return true;
        }//miss
        if ((cage[1][0+t] == cage[0][1+t] == cage[0][((2+t) % 8)]) && cage[0][((2+t) % 8)] != 0 && (cage[2][0+t] == cage[1][1+t] == cage[1][((2+t) % 8)] == 0)){//右寄りに2つ並び1つ1段上にある形
            printf("13 %d\n",t);
            return true;
        }//miss
        if ((cage[2][0+t] == cage[0][1+t] == cage[0][((2+t) % 8)]) && cage[0][((2+t) % 8)] != 0 && (cage[1][1+t] == cage[1][((2+t) % 8)] == 0)){//右寄りに2つ並び1つ2段上にある形(L字型)
            printf("14 %d\n",t);
            return true;
        }//miss
        if ((cage[2][0+t] == cage[1][1+t] == cage[1][((2+t) % 8)]) && cage[1][((2+t) % 8)] != 0 && (cage[2][1+t] == cage[2][((2+t) % 8)] == 0)){//1段目が埋まった右寄りに2つ並び1つ上にある形
            printf("15 %d\n",t);
            return true;
        }//miss
        if ((cage[0][0+t] == cage[1][1+t] == cage[1][((2+t) % 8)]) && cage[1][((2+t) % 8)] != 0 && (cage[1][0+t] == cage[2][1+t] == cage[2][((2+t) % 8)] == 0)){//右寄りに2つ並び1つ1段下にある形
            printf("16 %d\n",t);
            return true;
        }//miss
        if ((cage[0][0+t] == cage[2][1+t] == cage[2][((2+t) % 8)]) && cage[2][((2+t) % 8)] != 0 && (cage[1][0+t] == 0)){//右寄りに2つ並び1つ2段下にある形
            printf("17 %d\n",t);
            return true;
        }
        if ((cage[1][0+t] == cage[2][1+t] == cage[2][((2+t) % 8)]) && cage[2][((2+t) % 8)] != 0 && (cage[2][0+t] == 0)){//1段目が埋まった右寄りに2つ並び1つ下にある形
            printf("18 %d\n",t);
            return true;
        }
        if ((cage[0][0+t] == cage[2][1+t] == cage[1][((2+t) % 8)]) && cage[1][((2+t) % 8)] != 0 && (cage[1][0+t] == cage[2][((2+t) % 8)] == 0)){//相手が（」）こんな形
            printf("19 %d\n",t);
            return true;
        }//miss
        if ((cage[1][0+t] == cage[2][1+t] == cage[0][((2+t) % 8)]) && cage[0][((2+t) % 8)] != 0 && (cage[2][0+t] == cage[1][((2+t) % 8)] == 0)){//相手が（反転」）こんな形
            printf("20 %d\n",t);
            return true;
        }//miss
    }
    return false;
}


// int** to_canonical_okamoto(int** cage){ //標準形
//     int** min_cage = copy(cage); // 最小盤面

//     int** rotate_cage_base = rotate_cage(cage); // 回転体

//     int count = 1; //test
//     for (int board = 0; board < 4; board++){ //8状態を保存

//         for (int i = 0; i < height; i++) { //鏡像
//             swap(cage[i][(7+board) % 8],cage[i][1+board]);
//             swap(cage[i][(6+board) % 8],cage[i][2+board]);
//             swap(cage[i][(5+board) % 8],cage[i][3+board]);
//         }

//         printf("mirror %d\n",count);
//         if (le(min_cage, cage)){// 大小比較
//             printf("true\n");
//         }
//         print_cage(cage);
//         count += 1;

//         if (le(min_cage, cage)){ // 大小比較
//             for (int i = 0; i < height; i++) {
//                 for (int j = 0; j < num_positions; j++) {
//                     min_cage[i][j] = cage[i][j];
//                 }
//             }
//         }
//         for (int i = 0; i < height; i++) { // 鏡像を戻す
//             swap(cage[i][(7+board) % 8], cage[i][1+board]);
//             swap(cage[i][(6+board) % 8], cage[i][2+board]);
//             swap(cage[i][(5+board) % 8], cage[i][3+board]);
//         }

//         rotate_cage(cage)

//         printf("rotate %d\n",count);
//         if (le(min_cage, rotate_cage)){
//             printf("true\n");
//         }
//         print_cage(rotate_cage);
//         count += 1;

//         if (le(min_cage, rotate_cage)){ // 大小比較
//             for (int i = 0; i < height; i++) {
//                 for (int j = 0; j < num_positions; j++) {
//                     min_cage[i][j] = rotate_cage[i][j];
//                 }
//             }
//         }
//     }
//     delete [] rotate_cage;
//     return min_cage;
// }


<!--
#include <iostream>
#include <vector>

// ルービックケージを表すクラス
class RubikCage {
 public:
  RubikCage() {}

  // 各面を回転させる関数
  void rotate(int face, bool clockwise) {
    // 回転処理を行う
  }

  // ケージの状態を表示する関数
  void display() const {
    // ケージの状態を表示する
  }

 private:
  // ケージの状態を表す変数など
};

int main() {
  // ルービックケージのインスタンスを生成
  RubikCage rc;

  // 各面を回転させる
  rc.rotate(0, true);  // 1面を時計回りに回転
  rc.rotate(1, false); // 2面を反時計回りに回転

  // ケージの状態を表示
  rc.display();

  return 0;
} -->

void put_rule(int** cage, vector<int> color_palette, int player){
    if (player == 1){
        for (int color = 1; color < 4; color++){ // 先手の色
            bool is_filled = true; // フラグ
            if (color_palette[color] > 0){ // 自分の色のキューブがあるかどうか
                for (int t = 0; t < 3; t++){
                    if (cage[0][t*2] == 0){ // 角が空である時
                        cage = put(cage, color, (t*2));
                        color_palette.at(color) = color_palette.at(color) - 1; // キューブの使用
                        is_filled = false;
                        break;
                    }else if (cage[0][(t*2)+1] != 0 && cage[1][(t*2)+1] == 0){ //中央が空である時
                        cage = put(cage, color, ((t*2)+1));
                        color_palette.at(color) = color_palette.at(color) - 1; // キューブの使用
                        is_filled = false;
                        break;
                    }else if (cage[0][(t*2)+1] != 0 && cage[1][(t*2)+1] == 0){ //2段目が空である時
                        cage = put(cage, color , (t+2));
                        color_palette.at(color) = color_palette.at(color) - 1; // キューブの使用
                        is_filled = false;
                        break;
                    }
                }
            }
            if (is_filled){
                if (color_palette[color] > 0){
                    for (int j = 0; j < num_positions; j++){
                        if (cage[2][j] == 0){
                            cage = put(cage, color, j);
                            color_palette.at(color) = color_palette.at(color) - 1; // キューブの使用
                            break;
                        }
                    }
                }
            }
        }
    }else{
        for (int color = 4; color < 7; color++){ // 後手の色 4,5,6
            bool is_filled = true; // フラグ
            if (color_palette[color] > 0){ // 自分の色のキューブがあるかどうか
                for (int t = 0; t < 3; t++){
                    if (cage[0][t*2] == 0){ // 角が空である時
                        cage = put(cage, color, (t*2));
                        color_palette.at(color) = color_palette.at(color) - 1; // キューブの使用
                        is_filled = false;
                        break;
                    }else if (cage[0][(t*2)+1] != 0 && cage[1][(t*2)+1] == 0){ //中央が空である時
                        cage = put(cage, color, ((t*2)+1));
                        color_palette.at(color) = color_palette.at(color) - 1; // キューブの使用
                        is_filled = false;
                        break;
                    }else if (cage[0][(t*2)+1] != 0 && cage[1][(t*2)+1] == 0){ //2段目が空である時
                        cage = put(cage, color , (t+2));
                        color_palette.at(color) = color_palette.at(color) - 1; // キューブの使用
                        is_filled = false;
                        break;
                    }
                }
            }
            if (is_filled){
                if (color_palette[color] > 0){
                    for (int j = 0; j < num_positions; j++){
                        if (cage[2][j] == 0){
                            cage = put(cage, color, j);
                            color_palette.at(color) = color_palette.at(color) - 1; // キューブの使用
                            break;
                        }
                    }
                }
            }
        }
    }
}

int first_cage[3][8] = {
        {0, 0, 0, 4, 3, 2, 1, 0},
        {0, 0, 0, 0, 0, 1, 4, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };