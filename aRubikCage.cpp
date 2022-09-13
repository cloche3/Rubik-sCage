#include <iostream>
#include <limits.h>
#include <map>
#include <stack>

//using namespace std;


signed char mycolor= 0;
signed char setcolor[6] = {1,2,3,4,5,6};
int cage[3][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    };
int cage_n [3][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    };
int stack[] = {};
int nextStack[] = {};
int length;


/*
int set_color(void){
    map<signed char, string> colorbase;
    colorbase[0] = "null";
    colorbase[1] = "red";
    colorbase[2] = "blue";
    colorbase[3] = "orange";
    colorbase[4] = "green";
    colorbase[5] = "yellow";
    colorbase[6] = "white";
};
*/

void fallcube(int **cage){
    for (int e,n,t=0; t < 8 ; t++)
    {
        for (n = 0; n < 2; n++)
        {
            for (e = 0; e < 2; e++)
            {
                cage[e][t] == 0 && (cage[e][t] = cage[e + 1][t], cage[e + 1][t] = 0);
                cage_n[e][t] == 0 && (cage_n[e][t] = cage_n[e + 1][t], cage_n[e + 1][t] = 0);
            }
        }
    }
    return;
};

int mem(){
    //std::stack<int> stack;
    //std::stack<int> Nextstack;
    for (int e,
    N[3][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    },
    S [3][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    }, i = 0; i < 3 ; i++)
    {
        for (e = 0; e < 8; e++) N[i][e] = cage[i][e], S[i][e] = cage_n[i][e];
    //stack[null](N), nextStack(S);
    }
    return;
};

int put(int e){
    if (cage[2][e -1] != -1 || mycolor == -1)
    {
        return 0;
    };
    mem();
    cage[2][e - 1] = mycolor;
    cage_n[2][e - 1] = length;
    fallcube();
    return 0;
};

int shift_left(int e){
    for (int n = cage[e][0],i; i < 7; i++)
    {
        cage[e][i] = cage[e][i + 1];
        cage[e][7] = n;
        n = cage[e][0];
    }
    for (int n = cage[e][0],i ; i < 7; i++)
    {
        cage_n[e][i] = cage_n[e][i + 1];
        cage_n[e][7] = n ;
    }
    return 0;
};

int rotate_left(int e){
    mem();
    for (int i = 0; i < 2; i++)
    {
        shift_left(e);
    }
    return 0;
};

int rotate_right(int e){
    mem();
    for (int i = 0; i < 6; i++)
    {
        shift_left(e);
    }
    return 0;
};

int updown(){
    mem();
    for (int t,e = 0; e < 8; e++)
    {
        t = cage[0][e];
        cage[0][e] = cage[2][e];
        cage[2][e] = t;
        t = cage_n[0][e];
        cage_n[0][e] = cage_n[2][e];
        cage_n[2][e] = t;
    }
    fallcube();
    return void;
}

int reset(){
    int cage[3][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int cage_n [3][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int stack[] = {};
    int nextStack[] = {};
    fallcube();
    return;
}

int reach(){
    return 0;
}

int to_canonical(){
    return 0;
}
