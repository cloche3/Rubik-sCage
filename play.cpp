#include "winline.cpp"

void R_test_func(void){
    int test[3][8] = {
        {1, 0, 0, 0, 1, 2, 3, 0},
        {1, 0, 0, 0, 2, 3, 4, 0},
        {0, 0, 0, 0, 0, 0, 3, 0}
    };
    int ** test_cage_p = make_cage(test);
    // int test2[3][8] = {
    //     {0, 0, 0, 0, 1, 2, 3, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0}
    // };

    printf("test_cage1\n");
    print_cage(test_cage_p);

    // printf("test_cage2\n");
    // print_cage(test_cage_p2);

    // test_cage_p = put(test_cage_p,1,1);
    // test_cage_p = clockwise(test_cage_p,0);
    // test_cage_p = counterclockwise(test_cage_p, 0);

    vector<pair<int, int> > p = putreach(test_cage_p);
    for (int i = 0; i < p.size(); i++){
        cout << p[i].first <<endl;
        cout << p[i].second <<endl;
    }

    // vector<int> line = three_cube_line(test_cage_p);
    // for (int i = 0; i < line.size(); i++) {
    //     cout << line.at(i) << ", ";
    // }
    // cout << endl;

    // bool sita = updownreach(test_cage_p);
    // printf("updownreach %d\n",sita);

    // bool sita = le(test_cage_p, test_cage_p2);
    // if(sita) {
    //     cout << "cage1 < cage2" << endl;
    // } else {
    //     cout << "cage1 > cage2" << endl;
    // }

    // to_canonical(test_cage_p);

    printf("result\n");
    print_cage(test_cage_p);
    delete [] test_cage_p;
    return;
}



int main (int argc, char *argv[]){

    // R_test_func();
    int first_cage[3][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int **cage = make_cage(first_cage);
    to_canonical(cage);
    print_cage(cage);
    int player = 1;

    // std::pair<bool, int> win_test = is_finished(cage);
    // cout << std::boolalpha << win_test.first;
    // cout << win_test.second <<endl;

    // // int **next_cage = put_rule(cage,color_palette(), player, 7);
    // print_cage(next_cage);

    // std:vector<int**>v;
    // v.push_back(cage);
    // if (!(different_board(v, cage)))
    // {
    //     cout << "false";
    // }

    std::pair<int, int> two_moves = std::make_pair(-1, -1);
    cout << "call winner(cage, player, two_moves); in play.cpp with" << endl;
    cout << winner(cage, player, two_moves);

    return 0;
}