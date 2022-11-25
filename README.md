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