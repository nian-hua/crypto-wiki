## 四方密码简介

四方密码是由法国著名密码学家Felix Delastelle发明的，其本质上与二方密码类似。

四方密码使用了四个5x5的波利比奥斯方阵（因为每个方阵最多容纳5\*5=25个元素，所以我们需要将字母表中使用频率最少的i和j写在同一方格）。其中左上和右下方阵为纯文本方阵，右上和左下方阵为密钥方阵。


## 四方密码示例

!!! Tip "举例"

	**我们使用密钥`example`和`keyword`来加密`test plaintext`**

首先根据密钥生成四个密钥方阵，左上方和右下方分别为字母表，右上方和左下方分别为根据两个密钥生成的波利比奥斯方阵：

<p style="text-align:center;"><img width=50% src="../image/Four-SquareCipher-1.png" /></p>

接下来将明文拆分为二元组：

<p style="text-align:center;"><img width=40% src="../image/Four-SquareCipher-2.png" /></p>

### 加密过程

取出一个明文二元组，在左上方阵中找到第一个字母，右下方阵中找到第二个字母。此时，二元组形成一个相对角的矩形，将每个字母替换为与该字母同一行的矩阵角字母（请注意保持顺序）。

<p style="text-align:center;"><img width=65% src="../image/Four-SquareCipher-3.png" /></p>

最后密文为：

<p style="text-align:center;"><img width=40% src="../image/Four-SquareCipher-4.png" /></p>

### 解密过程

!!! Tip "举例"

	**我们使用密钥`zebra`和`coyote`来解密`NCZUB MKX`**

首先根据密钥生成四个密钥方阵，方法同加密过程：

<p style="text-align:center;"><img width=50% src="../image/Four-SquareCipher-5.png" /></p>

将密文拆分为二元组：

<p style="text-align:center;"><img width=23% src="../image/Four-SquareCipher-6.png" /></p>

在解密过程中，取出一个密文二元组，在右上方阵找到第一个字母，左下方阵中找到第二个字母。此时，二元组会形成一个相对角的矩形：

<p style="text-align:center;"><img width=65% src="../image/Four-SquareCipher-7.png" /></p>

将解密后的二元组拼接得到明文：

<p style="text-align:center;"><img width=23% src="../image/Four-SquareCipher-8.png" /></p>

## 四方密码的程序实现

```python
>>>from pycipher import Foursquare
>>>fs = Foursquare('zgptfoihmuwdrcnykeqaxvsbl','mfnbdcrhsaxyogvituewlqzkp')
>>>fs.encipher('defend the east wall of the castle')
'FBUMCNESFDPIKKZXCXMIUNZNQUNM'
>>>fs.decipher('FBUMCNESFDPIKKZXCXMIUNZNQUNM')
'DEFENDTHEEASTWALLOFTHECASTLE'
```

## 四方密码的密码分析

四方密码虽然比替换密码复杂很多，但在当前计算机强大的运算能力下还是很容易破解的。因为四方密码使用密文二元组替换明文二元组，所以隐藏了单个字母的频率信息，我们很难使用频率分析法破解四方密码。

!!! Warning "扩展"

	**更多关于模拟退火算法的信息，请移步至[普莱费尔密码的密码分析](../PlayfairCipher/#_10)**

像前文的普莱费尔密码分析一样，我们在破解四方密码时，使用的也是模拟退火算法：


```c
/*****************************************
* The author is practicalcryptography    *
* The author is practicalcryptography    *
*****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "scoreText.h"

#define TEMP 20
#define STEP 0.1
#define COUNT 10000

char *foursquareDecipher(char *key1,char *key2, char *in,char *out, int len);
float foursquareCrack(char *text,int len, char* maxKey1, char* maxKey2);
static char *shuffleKey(char *in);

int main(int argc, char *argv[])
{
    // THINGS TO ENSURE: CIPHER AND KEY MUST BE UPPERCASE, CONSISTING ONLY OF LETTERS A-Z, AND NO OTHERS. YOU CAN SPELL OUT NUMBERS IF YOU NEED TO.
    // NEITHER THE CIPHER OR THE KEY SHOULD HAVE THE LETTER 'J' IN IT. IT WILL CRASH IF YOU DO NOT DO THESE THINGS. THIS IS A PROOF OF CONCEPT ONLY.
    char cipher[]  = "HMMKEQESDTMDHLAWFWMNKSOSFOMRFNLWLKHNSQGGEKXEOLLVDXNRSQQGARTFKSAVNUDLFNDHESPZGQTWESAGPGSQSQSTPKUSBBQLQHESAGPGSQSQGXLNAVHTPMHMKKNYGSUGDMTPDGFNKYAVHXLWGEKRILESLZZOFNAVIHRHRKAGHSMYUGEGNSRGAVMVOQPRLNKRXLMYLQPXILESQYBNRHRKAGKYQXDIHMPGPYOERZOLBEZLURFWLWUOLDDPNSQYAGMUQPQWESBEZVEQESDTMDBQLWDIUSHB";
    int len = strlen(cipher);  
    char *out = malloc(sizeof(char)*(len+1));
    srand((unsigned)time(NULL)); // randomise the seed, so we get different results each time we run this program

    printf("Running foursquarecrack, this could take a few minutes...\n");

    char key1[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    char key2[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    int i=0;
    double score,maxscore=-99e99;
    // run until user kills it
    while(1){
        i++;
        score = foursquareCrack(cipher,len,key1,key2);
        if(score > maxscore){
            maxscore = score;
            printf("best score so far: %f, on iteration %d\n",score,i);
            printf("    Key: '%s','%s'\n",key1,key2);
            foursquareDecipher(key1,key2, cipher,out, len);
            printf("    plaintext: '%s'\n",out);
        }
    }
    free(out);
    return 0;
}

void exchange2letters(char *key){
    int i = rand()%25;
    int j = rand()%25;
    char temp = key[i];
    key[i]= key[j];
    key[j] = temp;
}

// this is the bit that implements the simulated annealing algorithm 
float foursquareCrack(char *text,int len, char* bestKey1, char* bestKey2){
    int i,j,count;
    float T;
    char temp, *deciphered = malloc(sizeof(char) * (len+1));
    char testKey1[26],testKey2[26];
    char maxKey1[26],maxKey2[26];
    double prob,dF,maxscore,score;
    double bestscore;
    strcpy(maxKey1,bestKey1);
    strcpy(maxKey2,bestKey2);
    foursquareDecipher(maxKey1,maxKey2,text,deciphered,len);
    maxscore = scoreTextQgram(deciphered,len);
    bestscore = maxscore;
    for(T = TEMP; T >= 0; T-=STEP){
        for(count = 0; count < COUNT; count++){ 
            strcpy(testKey1,maxKey1);
            strcpy(testKey2,maxKey2);
            if(count%2==0){
                exchange2letters(testKey1);    
            }else{
                exchange2letters(testKey2);    
            }
            foursquareDecipher(testKey1,testKey2,text,deciphered,len);
            score = scoreTextQgram(deciphered,len);
            dF = score - maxscore;
            if (dF >= 0){
                maxscore = score;
                strcpy(maxKey1,testKey1);
                strcpy(maxKey2,testKey2);
            }else if(T > 0){
                prob = exp(dF/T);
                if(prob > 1.0*rand()/RAND_MAX){
                    maxscore = score;
                    strcpy(maxKey1,testKey1);
                    strcpy(maxKey2,testKey2);
                }
            }
            // keep track of best score we have seen so far
            if(maxscore > bestscore){
                bestscore = maxscore;
                strcpy(bestKey1,maxKey1);
                strcpy(bestKey2,maxKey2);
            } 
        }
    }
    free(deciphered);
    return bestscore;
}


char *foursquareDecipher(char *key1,char *key2, char *text, char *result, int len){
    int i;
    char a,b; /* the digram we are looking at */
    int a_ind,b_ind;
    int a_row,b_row;
    int a_col,b_col;
    char alph[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    
    for (i = 0; i < len; i += 2){
        a = text[i];
        b = text[i+1];
        /*if (index(key,a) == NULL || index(key,b) == NULL) break;*/
        a_ind = (int)(strchr(key1,a) - key1);
        b_ind = (int)(strchr(key2,b) - key2);
        a_row = a_ind / 5;
        b_row = b_ind / 5;
        a_col = a_ind % 5;
        b_col = b_ind % 5;
        result[i] = alph[5*a_row + b_col];
        result[i+1] = alph[5*b_row + a_col];
    }
    result[i] = '\0';
    return result;
}

// do fisher yeates shuffle      
static char *shuffleKey(char *in){
    int i,j;
    char temp;
    for (i = 24; i >= 1; i--){
        j = rand() % (i+1);
        temp = in[j];
        in[j] = in[i];
        in[i] = temp;
    }
    return in;
} 
```

其他相关头文件下载：

[scoreText.c](./scoreText.c)

[scoreText.h](./scoreText.h)

[qgr.h.zip](./qgr.h.zip)

程序运行示例：

<p style="text-align:center;"><img src="../image/Four-SquareCipher-9.png" /></p>


<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/gitalk@1/dist/gitalk.css">
<div id="gitalk-container"></div>
<script src="https://cdn.jsdelivr.net/npm/gitalk@1/dist/gitalk.min.js"></script>
<script>
var str=location.pathname.slice(0,-1);
var obj=str.lastIndexOf("/");
var gitalk = new Gitalk({
  clientID: 'e85a79662384a39231e9',
  clientSecret: 'fb5aaa0a353e51ef239e5a6d4a9c05ab186af177',
  repo: 'crypto-wiki',
  owner: 'nian-hua',
  admin: ['nian-hua'],
  id: str.substr(obj+1),      // Ensure uniqueness and length less than 50
  distractionFreeMode: false  // Facebook-like distraction free mode
})
gitalk.render('gitalk-container')
console.log(str.substr(obj+1))
</script>


