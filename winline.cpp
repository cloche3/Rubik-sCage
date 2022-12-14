#include "RubikCage.cpp"
#include <vector>
#include <map>

using namespace std;

const int num_colors = 6 ; // 色の数
const int cubes = (24/num_colors) ; // 1色あたりのキューブの数
const int first_player = 1; // 先手番号
const int second_player = -1; // 後手番号
const bool allow_flip = true; // 上下反転を認めるかどうか
const vector<int> allow_rotate = {1, 1, 1}; // 回転する段を設定する。1の時回転できる

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
 * キューブを入れる時の条件
 * 引数　cage:盤面, color_palette:現在所持している色のキューブ, player:先手か後手か, j: 入れる箇所
 *
*/

int ** put_rule(int** cage, vector<int> color_palette, int player, int j){
    if (player == 1){
        for (int color = 1; color < (num_colors/2+1); color++){ // 先手の色 1, 2, 3
            if (color_palette.at(color) > 0){ // 自分の色のキューブがあるかどうか
                if (cage[2][j] == 0){ //キューブを入れられるかどうか
                    return put(cage, color, j);
                }
            }
        }
    }else{
        for (int color = (num_colors/2+1); color < (num_colors+1); color++){ // 後手の色 4, 5, 6
            if (color_palette.at(color) > 0){ // 自分の色のキューブがあるかどうか
                if (cage[2][j] == 0){
                    return put(cage, color, j);
                }
            }
        }
    }
    return 0;
}


/**
 * 勝ったplayerの出力
 * 引数:cage(盤面), player(どちらの手番か先手:1 後手:-1), last_two_moves(直前の2手)
 * 戻り値 勝ったplayer(先手:1 後手:-1 引き分け:0)
 * last_two_moves 0~2：回転した段数, 3：反転したかどうか,-1：前の手番に入れている
 */
int winner(int** cage, int player, pair<int, int> last_two_moves){
    vector<pair<int, int> > putwin; // 置いて勝つ色と場所
    std::vector<int>color_set = color_palette(); // キューブの個数と色 [0,4,4,4,4,4,4] 0:空 1~3:先手の色 4~6:後手の色
    std::vector<int **>next_cage; // 次の盤面の保存

    if((is_finished(cage)).first){ //元の盤面に3つキューブが揃っているか 終了判定でtrueなら終了
        return (is_finished(cage)).second; // 1:先手の勝利, -1:後手の勝利, 0:引きわけ
    };

    putwin = putreach(cage);// キューブを置いて勝つ盤面（リーチ
    if (player == -1){ // 後手の時
        std::sort(putwin.rbegin(), putwin.rend()); // 色を降順にする
    }
    for (int line = 0; line < putwin.size(); line++){
        if (player == color_2_player(putwin[line].first)){ //手番の人の色がリーチの場合
            if (color_set[putwin[line].first] > 0){ // 入れる色のキューブがあるのか
                return player; //その時のplayerの勝利
            }
        }
        if ( (player*-1) == color_2_player(putwin[line].first)) { //相手の色がリーチの場合
            if (player == 1){ // 先手の時
                for (int color = (num_colors/2); color > 1; color--){ // 先手の色 3, 2, 1
                    if (color_set[color] > 0){ // 自分の色のキューブがあるかどうか
                        if (cage[2][putwin[line].second] == 0){ //キューブを入れられるかどうか
                            cage = put(cage, color, (putwin[line].second));
                            break;
                        }
                    }
                }
            }else{ //後手の時
                for (int color = num_colors; color > (num_colors/2+1); color--){ // 後手の色 4, 5, 6
                    if (color_set[color] > 0){ // 自分の色のキューブがあるかどうか
                        if (cage[2][putwin[line].second] == 0){
                            cage = put(cage, color, (putwin[line].second));
                            break;
                        }
                    }
                }
            }
        }
    }

    // ここから先は次の盤面生成
    // キューブを入れた時の盤面の格納
    for (int j = 0; j < num_positions; j++){
        int** put_new_cage = put_rule(cage, color_set, player, j);
        if (put_new_cage == 0){
            break;
        }
        next_cage.push_back(put_new_cage);
    }

    // 盤面を回転した時
    for (int i = 0; i < height; i++) {
        if (allow_rotate.at(i) == 1){ // 回転を許可するかどうか
            next_cage.push_back(clockwise(cage, i)); // 時計回り
            next_cage.push_back(counterclockwise(cage, i)); // 反時計回り
        }
    }
    // 上下反転した時
    if (allow_flip){ //　上下反転を許可するかどうか
        next_cage.push_back(updown(cage));
        last_two_moves.first = 3;
    }

    // 再帰開始
    int all = 1;
    for (int t = 0; t < next_cage.size(); t++){
        last_two_moves = std::make_pair(last_two_moves.second, last_two_moves.first); //pairの入れ替え
        int result = winner(next_cage.at(t), (player* -1), last_two_moves); // 再帰
        if (result == player){
            return player;
        }else{
            all *= result;
        }
    }
    return (all == 0) ? 0 : -player;
}

int main(int argc, char *argv[]){
    int first_cage[3][8] = {
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int **cage = make_cage(first_cage);


    int player = 1;
    std::pair<int, int> two_moves = std::make_pair(-1, -1);

        cout << winner(cage, player, two_moves);


}