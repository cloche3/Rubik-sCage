#include "RubikCage.hpp"
#include <vector>
#include <map>

const int num_colors = 6 ; //色の数
const int cubes = 4 ; //1色あたりのキューブの数
const int first_player = 1; //先手番号
const int second_player = -1; //後手番号

using namespace std;

/**
 * 使う色とキューブ個数のvector
 * 戻り値：キューブのリスト[4,4,4,4,4,4] test_fin
 */
vector<int> color_palette(void){
    std::vector<int> color_set;
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

void make_all_state(int** cage){

}

int main(int argc, char *argv[]){
    int first_cage[3][8] = {
        {1, 2, 3, 4, 5, 6, 1, 2},
        {3, 4, 5, 6, 1, 2, 3, 4},
        {5, 6, 1, 2, 3, 4, 5, 0}
    };
    int **cage = make_cage(first_cage);
    print_cage(cage);

    // std::pair<bool, int> p = is_finished(cage);
    // std::cout << p.first << std::endl;
    // std::cout << p.second << std::endl;

    return 0;
}