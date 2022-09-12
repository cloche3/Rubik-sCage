#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <map>
#include <stack>

using namespace std;
signed char Mycolor= -1;
signed char Setcolor[6] = {1,2,3,4,5,6};
int BaseCage[3][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
    };
int NextCage [3][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
    };
int Stack[] = {};
int NextStack[] = {};   


/*
int set_color(void){    
    map<signed char, string> colorbase;
    colorbase[-1] = "null";
    colorbase[1] = "red";
    colorbase[2] = "blue";
    colorbase[3] = "orange";
    colorbase[4] = "green";
    colorbase[5] = "yellow";
    colorbase[6] = "white";
};
*/

int update(){
    for (int e,n,t=0; t < 8 ; t++)
    {
        for (n = 0; n < 2; n++)
        {
            for (e = 0; e < 2; e++)
            {
                BaseCage[e][t] == -1 && (BaseCage[e][t] = BaseCage[e + 1][t], BaseCage[e + 1][t] = -1), NextCage[e][t] == -1 && (NextCage[e][t] = NextCage[e + 1][t], NextCage[e + 1][t] = -1);
            }
        }
    }

};

int mem(){
    //std::stack<int> Stack;
    //std::stack<int> Nextstack;
    for (int e,
    N[3][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
    },
    S [3][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
    }, i = 0; i < 3 ; i++)
    {
        for (e = 0; e < 8; e++) N[i][e] = BaseCage[i][e], S[i][e] = NextCage[i][e];
    Stack[8](N), Nextstack(S);
    }
    
};

int put(int e){
    if (BaseCage[2][e -1] != -1 || Mycolor == -1)
    {
        return 0;
    };
    mem();
    BaseCage[2][e - 1] = Mycolor;
    NextCage[2][e - 1] = stack.length; 
    update();
};

int shift_left(int e){
    for (int n = BaseCage[e][0],i; i < 7; i++)
    {
        BaseCage[e][i] = BaseCage[e][i + 1];
        BaseCage[e][7] = n;
        n = BaseCage[e][0];
    }
    for (int n = BaseCage[e][0],i ; i < 7; i++)
    {
        NextCage[e][i] = NextCage[e][i + 1];
        NextCage[e][7] = n ;
    }    
};

int rotate_left(int e){
    mem();
    for (int i = 0; i < 2; i++)
    {
        shift_left(e);
    }
};

int rotate_right(int e){
    mem();
    for (int i = 0; i < 6; i++)
    {
        shift_left(e);
    }
};

int updown(){
    mem();
    for (int t,e = 0; e < 8; e++)
    {
        t = BaseCage[0][e];
        BaseCage[0][e] = BaseCage[2][e];
        BaseCage[2][e] = t;
        t = NextCage[0][e];
        NextCage[0][e] = NextCage[2][e];
        NextCage[2][e] = t;
    }
    update();    
}

int reset(){
    int BaseCage[3][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
    };
    int NextCage [3][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
    };
    int Stack[] = {};
    int NextStack[] = {};
    update();   
}

int reach(){

}

int to_canonical(){
    

}