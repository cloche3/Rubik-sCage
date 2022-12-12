#include "RubikCage.cpp"
#include <vector>
#include <map>

const int num_colors = 6 ; //色の数
const int cubes = 4 ; //1色あたりのキューブの数
const int first_player = 1; //先手番号
const int second_player = -1; //後手番号

using namespace std;

/**
 * 使う色とキューブ個数のvector
 * 戻り値：キューブのリスト[0,4,4,4,4,4,4] test_fin
 */
vector<int> color_palette(void){
    std::vector<int> color_set = {0};
    for (int t = 0; t < num_colors; t++){
        color_set.push_back(cubes);
    }
    return color_set;
}

/**
 * 色 color が先手の色か後手の色かを判定
 * 戻り値：該当するプレーヤーの番号（先手：１、後手：－１） test_fin
*/
int color_2_player(int color) {
    return (color > num_colors / 2) ? -1 : 1;
}

/**
 * 盤面 cage  がゲーム終了状態化を調べる
 * 終了状態なら、pair の最初の値は true
 *                      ２番めの値は勝利したプレーヤー（1, -1, 0) (0は引き分け)　test_fin
*/
pair<bool, int> is_finished(int** cage) {
    std::vector<int> color_win = three_cube_line(cage); // 1直線にキューブが3個揃っているか

    // ３個揃った場合
    if (!color_win.empty()) {
        if (color_win.at(0) == color_win.at(color_win.size() - 1)) {
            return std::make_pair(true, color_2_player(color_win[0]));
        } else { // どちらも３個揃って引き分け
            return std::make_pair(true, 0);
        }
    }

    // ブロックがいっぱいの場合（引き分け）
    bool is_filled = true;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < num_positions; j++) {
            if (cage[i][j] == 0){
                is_filled = false;
                break;
            }
        }
    }
    if (is_filled){
        return std::make_pair(true, 0);
    }

    // いっぱいではなく、3個揃っていない場合
    return std::make_pair(false, 0);
}

/**
 * キューブを入れる時の優先ルール test_fin
 *
*/
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
                    break;
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
                    break;
                }
            }
        }
    }
}



/**
 * 勝ったplayerの出力
 * 引数:cage(盤面), player(どちらの手番か先手:1 後手:-1), last_two_moves(直前の2手)
 * 戻り値 勝ったplayer(先手:1 後手:-1 引き分け:0)
 * last_two_moves 0~2：回転した段数, 3：反転したかどうか,-1：前の手番に入れている
 */
int winner_old(int** cage, int player, pair<int, int> last_two_moves){
    std::pair<int, int> putwin; // 置いて勝つ場所と色
    std::vector<int>color_set = color_palette(); // キューブの個数と色 [0,4,4,4,4,4,4] 0:空 1~3:先手の色 4~6:後手の色

    for (;;){
        putwin = putreach(cage);// キューブを置いて勝つ盤面
        if (player == color_2_player(putwin.second)){ //手番の人の色かどうか
            if (color_set[putwin.second] > 0){ // 入れる色のキューブがあるのか
                return player; //その時のplayerの勝利
            }
        }

        for (int i = 0; i < height; i++){
            int** clockwise_cage = clockwise(cage, i); // 時計回り
            if((is_finished(clockwise_cage)).first){ //終了判定でtrueなら終了
                return (is_finished(clockwise_cage)).second; // 0で引きわけ
            }
        }
        for (int i = 0; i < height; i++){
            int** counterclockwise_cage = counterclockwise(cage, i); // 反時計回り
            if((is_finished(counterclockwise_cage)).first){ //終了判定でtrueなら終了
                return (is_finished(counterclockwise_cage)).second ; // 0で引きわけ
            }
        }
        int** updown_cage = updown(cage); // 反転
        if((is_finished(updown_cage)).first){ //終了判定でtrueなら終了
            return (is_finished(updown_cage)).second; // 0で引きわけ
        };

        if((is_finished(cage)).first){ //元の盤面 終了判定でtrueなら終了
            return (is_finished(cage)).second; // 0で引きわけ
        };

        // ここから先は優先手を指定

        if (last_two_moves.second >= 0){ // 前回の自分の番の時キューブを入れなかった時
            put_rule(cage, color_set, player);
            last_two_moves.first = -1;
        }
        if (player != color_2_player(putwin.second)){ // 自分の番に相手がリーチの場合
            /* code */
        }



        last_two_moves = std::make_pair(last_two_moves.second, last_two_moves.first); //pairの入れ替え
        winner(cage, (player* -1), last_two_moves); // 再帰
    }
    return -1; // 後手の勝利
}
/*
 * 勝った盤面保存
*/

// vector<int **> board(int** cage, int player, pair<int, int> last_two_moves){
//     std::vector<int **> win_board; //勝った盤面の保存
//     std::pair<int, int> putwin; // キューブを置いて勝つ盤面

//     for (;;){
//         if (player == color_2_player(putwin.second)){
//             std::pair<int, int> putwin = putreach(cage);
//             int ** win_cage = put(cage, (putwin.first), putwin.second);
//             board.push_back(win_cage);
//         }

//         if((is_finished(cage)).first){
//             break;
//         };
//     }
//     return win_board;
// }

int main(int argc, char *argv[]){
    int first_cage[3][8] = {
        {1, 2, 3, 4, 5, 6, 1, 2},
        {3, 4, 5, 6, 1, 2, 3, 4},
        {5, 6, 1, 2, 3, 4, 5, 0}
    };
    int **cage = make_cage(first_cage);
    print_cage(cage);

    std::pair<bool, int> p = is_finished(cage);
    std::cout << p.first << std::endl;
    std::cout << p.second << std::endl;

    vector<int> line = {0,0,0,0,0,0,1};
    put_rule(cage, line, -1);
    print_cage(cage);
}