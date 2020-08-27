## 简单替换密码简介

简单替换密码已经有数百年历史了。它基本上包括用每个明文字符替换一个不同的密文字符。它与Caesar密码的不同之处在于，简单替换密码的加密表不仅仅是简单移动字母表，而是完全混乱的字母表。

简单替换密码的密码表如下图所示：

<p style="text-align:center;"><img width="700px" src="../image/SimpleSubstitutionCipher-1.png" /></p>

将对应关系整理成更易读的形式：

<p style="text-align:center;"><img width="700px" src="../image/SimpleSubstitutionCipher-2.png" /></p>

而简单替换密码的密钥就是第二行的字母，即：

```
WYHFXUMTJVSGENBRDZLQAPCOKI
```

当然为了记忆简单，我们也可以这样设置密钥，首先写下一个有意义的单词（不包含重复字母）,然后将字母表中其余字母依次写入，例：

```
SIMPLEABCDFGHJKNOQRTUVWXYZ
------
```

**注意上方横线区域，此密码可简记为simple**

## 简单替换密码示例

!!! Tip "举例"

	**我们使用密钥: `phqgiumeaylnofdxjkrcvstzwb`，加密`defend the east wall of the castle`：**
	

首先写出密钥为1时明文和密文的对照表：

<p style="text-align:center;"><img src="../image/SimpleSubstitutionCipher-3.png" /></p>

对要加密的明文逐个查表替换：D替换为G、E替换为I... 依次类推，直到整段明文都被加密。

```
plaintext:  defend the east wall of the castle
ciphertext: giuifg cei iprc tpnn du cei qprcni
```

## 简单替换密码的程序实现

!!! Tip "注意"

	**程序可在python3下运行**

```python
>>>from pycipher import SimpleSubstitution
>>>ss = SimpleSubstitution('phqgiumeaylnofdxjkrcvstzwb')
>>>ss.encipher('defend the east wall of the castle')
'GIUIFGCEIIPRCTPNNDUCEIQPRCNI'
>>>ss.decipher('GIUIFGCEIIPRCTPNNDUCEIQPRCNI')
'DEFENDTHEEASTWALLOFTHECASTLE'
```

运行示例：

<p style="text-align:center;"><img width="600px" src="../image/SimpleSubstitutionCipher-4.png" /></p>

## 简单替换密码的密码分析

虽然简单替换密码的密钥空间很大（密钥数量约为2<sup>88.4</sup>），但是还是很容易被破解。因为在英语文本中有很多冗余或统计属性。

### 频率分析

频率分析方法像之前分析凯撒密码是一样的，自然英语每个字母出现的频率有着特殊的分布，所以我们首先计算密文中字母的频率分布。

下图为自然英语的字母频率：

<p style="text-align:center;"><img width="525px" src="../image/SimpleSubstitutionCipher-5.png" /></p>

下图为自然英语字母频率从最频繁到最不常见：

<p style="text-align:center;"><img width="525px" src="../image/SimpleSubstitutionCipher-6.png" /></p>

这说明'e'是最常见的字母，出现概率约为13%，而z出现的概率却小于1%。经过简单替换密码加密后不会改变这些字母的频率，只会使它们的对应关系变得杂乱无章。

在上一小节的示例中，'e'被加密为'i'，所以'i'在密文中变成了最常见的密文。密码分析人员必须通过这种方法，找到密文和明文中每个字符的映射关系。

比如我们将密文中最常见的字母替换为'e'，第二常见的字母替换为't'，以此类推。

---

对于短文本的破解，频率分析方法可能没有那么奏效。这时候我们就需要更多的英语知识：

依旧以`giuifg cei iprc tpnn du cei qprcni`为例，我们可以使用下列的规则猜测某些单词：

|       |                                    |
| ------------ | ------------------------------------------ |
| 常见的一个字母单词 | a, I.                                       |
| 常见的两个字母单词 | of, to, in, it, is, be, as, at, so, we, he, by, or, on, do, if, me, my, up, an, go, no, us, am  |
| 常见的三个字母单词 | the, and, for, are, but, not, you, all, any, can, had, her, was, one, our, out, day, get, has, him, his, how, man, new, now, old, see, two, way, who, boy, did, its, let, put, say, she, too, use                       |
| 常见的四个字母单词 | that, with, have, this, will, your, from, they, know, want, been, good, much, some, time |

**上表中的内容是从[Simon Singhs的网站](http://www.simonsingh.net/The_Black_Chamber/hintsandtips.htm)借来的**

### 爬山算法

简单替换密码比凯撒密码和仿射密码更为复杂，后者的密钥空间分别为25和311，我们还可以通过暴力破解去攻击。但是，简单替换密码的密钥空间为2<sup>88.4</sup>，用暴力破解显然不太现实。

为此我们引入一种新的算法--爬山算法来查找正确的密钥。这种方法的前提是我们可以确定一段文本与英文文本有多相似，并对这段文本进行评分。一段非常类似于英语的文本将获得高分，而一堆随机字符将获得低分。为此，我们将使用基于四字组统计量的适应性评分（[四元组统计教程](http://crypto-wiki.io/ClassicalCipher/Cryptanalysis/Quadgram/)）。 

举个例子：使用错误密钥解密出的消息可能包含序列"QKPC"，这在英语中非常罕见，这段文本就会被评一个较低的分数。通过这种方式，我们可以对使用不同密钥解密的文本进行排名，排名最高的可能就是正确的明文。

<p style="text-align:center;"><img width="525px" src="../image/SimpleSubstitutionCipher-7.png" /></p>

爬山算法的原理如下：

1. 生成一个parent随机密钥，使用parent密钥解密并评估分数，存储结果。
2. 随机更换密钥中的两个字符，使用新密钥解密文本并评估分数。
3. 如果新密钥分数较高，则将新密钥存储为parent密钥。
4. 回到2，如果在最近1000次迭代中评分没有发生显著性改善则回到1。

随着此循环的进行，解密后的文本变得越来越合适，密钥变的越来越好，直到出现真正的密钥或找不到密钥为止。

找不到密钥的情况往往说明爬山算法被卡在局部最大值中，在这种情况下，无法对密钥进行简单地更改以提高评估分数。此时就需要使用其他的parent密钥重新启动算法。

!!! Tip "举例"

	**我们有一段密文: `SOWFBRKAWFCZFSBSCSBQITBKOWLBFXTBKOWLSOXSOXFZWWIBICFWUQLRXINOCIJLWJFQUNWXLFBSZXFBTXAANTQIFBFSFQUFCZFSBSCSBIMWHWLNKAXBISWGSTOXLXTSWLUQLXJBUUWLWISTBKOWLSWGSTOXLXTSWLBSJBUUWLFULQRTXWFXLTBKOWLBISOXSSOWTBKOWLXAKOXZWSBFIQSFBRKANSOWXAKOXZWSFOBUSWJBSBFTQRKAWSWANECRZAWJ`**

首先我们生成一个随机密钥：

```
普通字母：ABCDEFGHIJKLMNOPQRSTUVWXYZ
密码字母：YBXONGSWKCPZFMTDHRQUJVELIA
```

并使用此密钥解密密文，得到：

```
GDHMBRIZHMJLMGBGJGBSYOBIDHXBMCOBIDHXGDCGDCMLHHYBYJMHTSXRCYEDJYUXHUMSTEHCXMBGLCMBOCZZEOSYMBMGMSTMJLMGBGJGBYNHQHXEIZCBYGHFGODCXCOGHXTSXCUBTTHXHYGOBIDHXGHFGODCXCOGHXBGUBTTHXMTXSROCHMCXOBIDHXBYGDCGGDHOBIDHXCZIDCLHGBMYSGMBRIZEGDHCZIDCLHGMDBTGHUBGBMRI
```

我们评估这段文本的分数为-2304.04，接下来通过交换密钥中的"Y"和"B"，然后再进行解密，我们得到的分数为-2002.78，这是一个改进！

但是这段文本还是不具有可读性，我们必须迭代执行此过程，直至没有办法得到更高的评估分数。

经过多次迭代，找到的最终密钥是：

```
XZTJWUMOBEPARIQKDLFSCHYGNV
```

解密出的文本可读性也很高：

```
THESIMPLESUBSTITUTIONCIPHERISACIPHERTHATHASBEENINUSEFORMANYHUNDREDSOFYEARSITBASICALLYCONSISTSOFSUBSTITUTINGEVERYPLAINTEXTCHARACTERFORADIFFERENTCIPHERTEXTCHARACTERITDIFFERSFROMCAESARCIPHERINTHATTHECIPHERALPHABETISNOTSIMPLYTHEALPHABETSHIFTEDITISCOMPLETELYJUMBLED
```

---
### 程序实现

!!! Tip "注意"

	**该程序需要配合密码分析文本表征中的ngram_score评分模块，以及quadgrams字典。请移步至[四元组统计](http://crypto-wiki.io/ClassicalCipher/Cryptanalysis/Quadgram/)。**


```python
# -*- coding: UTF-8 -*-
import random
from ngram_score import ngram_score
print("正在加载字典")
fitness = ngram_score('quadgrams.txt')
global parentkey
parentkey = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
parentscore = -99e9
maxscore = -99e9
Pcount = 0

class SimpleSub:

    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    def __init__(self, ciphertext):
        self.ciphertext = ciphertext

    def decipher(self, key):
        plaintext = ''
        key = ArrayToStr(key)
        for i in self.ciphertext:
            plaintext += self.alphabet[key.index(i)]
        return plaintext


def ArrayToStr(array):

    return ''.join(i for i in array)

ciphertext = input("请输入要破解的密文:")

DecipherObj = SimpleSub(ciphertext)

while True:
    random.shuffle(parentkey)
    plaintext = DecipherObj.decipher(parentkey)
    parentscore = fitness.score(plaintext)
    Pcount += 1
    Scount = 0
    while Scount < 1000:
        a = random.randint(0, 25)
        b = random.randint(0, 25)
        childkey = parentkey[:]
        childkey[a], childkey[b] = childkey[b], childkey[a]
        plaintext = DecipherObj.decipher(childkey)
        score = fitness.score(plaintext)
        if score > parentscore:
            # print score
            parentscore = score
            parentkey = childkey[:]
            Scount = 0
        Scount += 1
    if parentscore > maxscore:
        maxscore = parentscore
        print('current Key:' + ArrayToStr(parentkey))
        plaintext = DecipherObj.decipher(parentkey)
        print(plaintext)
        print(fitness.score(plaintext))
        print '------------------------------------------------------------'

```

运行结果：

<p style="text-align:center;"><img src="../image/SimpleSubstitutionCipher-8.png" /></p>



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




