#include "RubikCage.hpp"
#include <vector>
#include <map>

const int color = 6 ; //色の数
const int cubes = 4 ; //1色あたりのキューブの数

std::vector <int> color_palette(void){
    std::vector<int> color_palette;
    for (int t = 0; t < color; t++){
        color_palette.push_back(cubes);
    }
    return color_palette;
}

void first_win(int** cage, int player){
    std::vector<int> make_cage;

}

main(int argc, char *argv[]){
    vector<int> line = color_palette();
    for (int i = 0; i < line.size(); i++) {
        cout << line.at(i) << ", ";
    }
    cout << endl;

}