#include "scoreText.h"
#include "qgr.h"

extern float qgram[];

// assumes that text consists only of uppercase letters(no punctuation or spaces)
double scoreTextQgram(char *text,int len){
    int i;
    char temp[4];
    double score = 0;
    for (i=0;i<len-3;i++){
        temp[0]=text[i]-'A';
        temp[1]=text[i+1]-'A';
        temp[2]=text[i+2]-'A';
        temp[3]=text[i+3]-'A';
        // we have to index into the correct part of the array
        score += qgram[17576*temp[0] + 676*temp[1] + 26*temp[2] + temp[3]];
    }
    return score;
}