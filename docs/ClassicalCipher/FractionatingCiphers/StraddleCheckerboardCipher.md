## 跨棋盘密码简介

跨棋盘密码(Straddle Checkerboard Cipher)是一种替换密码，当这种密码在结合其他加密方式，加密效果会更好。

## 跨棋盘密码示例

!!! Tip "举例"

	**使用密钥`fkmcpdyehbigqrosazlutjnwvx`及数字`3、7`作为密钥加密`DEFEND THE EAST WALL OF THE CASTLE`**
	```
	   0 1 2 3 4 5 6 7 8 9
	   -------------------
	   f k m   c p d   y e
	3: h b i g q r o s a z
	7: l u t j n w v x    
	```

我们在设置密钥矩阵的时候在第一行的3、7列留空，这是为了防止解密时出现二义性。

加密过程：

```
D E F E N  D T  H  E E A  S  T  W  A  L  L  O  F T  H  E C A  S  T  L  E
6 9 0 9 74 6 72 30 9 9 38 37 72 75 38 70 70 36 0 72 30 9 4 38 37 72 70 9
```

得到密文：`690975672309938377275387070360723094383772709`，此时这个密文可以直接发送给接收方，但是为了使其更加安全，往往需要引入第二阶段加密（如替换加密或换位密码）。

此处举个简单地例子：我们第二阶段的加密为一种加法（密钥为83729）

```
  837298372983729837298372983729837298372983729
+ 690974672309938377275387070360723094383772709
= 427162944282657104463659953089550282655655428
```

最后再使用密钥矩阵还原为字符：

```
427162944282657104463659953089550282655655428
CMU DMECCMYMDPU FCCDO PEEPH YEPPFMYMDPPDPPCMY
```

我们得到了最终的密文：`CMUDMECCMYMDPUFCCDOPEEPHYEPPFMYMDPPPPDPPCMY`。解密只是加密的逆过程，尽管密文长度发生了改变，但不影响正常解密过程。因为遇到`3、7`数字时，它需要使用连续两个数字来还原一个字母。

## 跨棋盘密码密码分析

假设一段加密后的密文为：`6909746723099383772753870703607230943837727093872638757438333832743772974928387272384175943874720383270`

假设一个加密密钥矩阵如下：

```
   0 1 2 3 4 5 6 7 8 9
   -------------------
   f k m   c p d   y e
3: h b i g q r o s a z
7: l u t j n w v x    
```

**注意图中的空白位置，总共有四个空白处。为了破解跨棋盘密码，需要找到这四个空白位置，然后将其作为替换密码破解即可。**

现在我们要破解通过加密密钥矩阵生成的密文，首先生成一个随机密钥矩阵：

```
   0 1 2 3 4 5 6 7 8 9
   -------------------
   a b c   d e f   g h
3: i j k l m n o p q r
7: a t u v w x y z    
```

我们将密钥矩阵写为`abc.def.ghijklmnopqrstuvwxyz..`。使用此矩阵加密的密文不可能会出现38、39、78或79等密文，因此可以丢弃部分密钥矩阵。

由于密钥矩阵的前10个字符中必须有2个空格，所以我们只有45种密钥矩阵情况，例如：

```
..abcdefghijklmnopqrstuvwxyz..
.a.bcdefghijklmnopqrstuvwxyz..
.ab.cdefghijklmnopqrstuvwxyz..
...
...
```

程序代码如下：

```python
''' Code by James Lyons for practicalcryptography.com 2016
All code is released under MIT licence '''
import random
from ngram_score import ngram_score
import re
import sys
from itertools import combinations

''' decrypt a straddle checkerboard cipher using the provided key
The first return value is an integer, 0 if the key is invalid, 1
if the key is valid. output is the decrypted text.'''
def scdecrypt(ctext,key):
    dotpos = []
    for i,k in enumerate(key): 
        if k == '.': dotpos.append(i)
    output = ""        
    flag = 0 
    for cc in ctext:
        c = int(cc)
        if key[c] != '.' and flag == 0: 
            output += key[c]
        elif flag == 1: 
            if key[10+c] == '.': return 0,""
            output += key[10+c]
            flag = 0
        elif flag == 2: 
            if key[20+c] == '.': return 0,""        
            output += key[20+c]
            flag = 0
        elif c == dotpos[0]: flag = 1     
        elif c == dotpos[1]: flag = 2
        else: 
            return 0,output
    return 1,output
        
''' compute the index of coincidence for a piece of text '''
def ic(text):
    freq = {}
    for letter in text:
        if letter in freq: freq[letter] += 1.
        else: freq[letter] = 1.
    freqsum = 0.
    for letter in freq.keys():    
        freqsum += freq[ letter ] * ( freq[ letter ] - 1 )
    N = len(text)
    IC = freqsum / ( N*(N-1) )    
    return IC

# get a list of all possible dot positions
first10 = combinations(range(10),2)
all_dot_positions = [[i[0],i[1],28,29] for i in first10]
        
ctext = '6909746723099383772753870703607230943837727093872638757438333832743772974928387272384175943874720383270'        
# we have all possible dot positions, try decrypting with each and see if we can discard any
texts = []
for d in all_dot_positions:
    key = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
    for pos in d: key.insert(pos,'.')
    # see if each key can be used to decrypt the ciphertext, keep it if yes
    valid,ptext = scdecrypt(ctext,key)
    if valid == 0: # shuffle the dots till it works
      for p3,p4 in combinations(range(10,30),2):
        key = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
        d = [d[0],d[1],p3,p4]
        for pos in d: key.insert(pos,'.')
        valid,ptext = scdecrypt(ctext,key)
        if valid == 1: break
    if valid==0: continue # we couldn't find any valid keys for this one
    texts.append((ic(ptext),ptext,''.join(key)))

# print the IC, text, and decryption key for all the candidates
texts.sort()
for i,j in enumerate(range(len(texts))):
    print '%0.3f' % texts[j][0],texts[j][1],'\t',texts[j][2]
```


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


