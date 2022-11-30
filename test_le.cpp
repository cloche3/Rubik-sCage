#include "aRubikCage.cpp"

int main(void) {
    int test[3][8] = {
        {3, 2, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int test2[3][8] = {
        {1, 2, 3, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int **test_cage_p = new int*[height];
    for (int i = 0; i < height; i++) {
        test_cage_p[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            test_cage_p[i][j] = test[i][j];
        }
    }

    int **test_cage_p2 = new int*[height];
    for (int i = 0; i < height; i++) {
        test_cage_p2[i] = new int[num_positions];
        for (int j = 0; j < num_positions; j++) {
            test_cage_p2[i][j] = test2[i][j];
        }
    }

    bool sita = le(test_cage_p, test_cage_p2);

    print_cage(test_cage_p);
    if(sita) {
        cout << "<" << endl;
    } else {
        cout << ">" << endl;
    }
    print_cage(test_cage_p2);


}