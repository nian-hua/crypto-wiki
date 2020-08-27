## 维吉尼亚密码简介

维吉尼亚密码是一种多字母替换密码，可以将其看做一系列凯撒密码组成密码字母表的加密算法。

维吉尼亚密码以其简单易用而著称，同时初学者通常难以破解，因而又被称为“不可破译的密码”。这也让很多人使用维吉尼亚密码来加密的目的就是为了将其破解。


## 维吉尼亚密码示例

在一个凯撒密码中，字母表中的每一字母都会作一定的偏移，例如偏移量为3时，A就转换为了D、B转换为了E……而维吉尼亚密码则是由一些偏移量不同的恺撒密码组成。

为了生成密码，需要使用表格法。这一表格包括了26行字母表，每一行都由前一行向左偏移一位得到。具体使用哪一行字母表进行编译是基于密钥进行的，在过程中会不断地变换。

<p style="text-align:center;"><img width="550px" src="../image/VigenereCipher-0.png" /></p>

!!! Tip "例题"

	**请使用关键词`LEMON`加密`ATTACKATDAWN`**

因为关键词的长度没有密文长，所以重复关键词得到密钥，即：

```
LEMONLEMONLE
```

对于明文的第一个字母A，对应密钥的第一个字母L，于是使用表格中L行字母表进行加密，得到密文第一个字母L。类似地，明文第二个字母为T，在表格中使用对应的E行进行加密，得到密文第二个字母X。以此类推，可以得到：

```
明文：ATTACKATDAWN
密钥：LEMONLEMONLE
密文：LXFOPVEFRNHR
```

解密的过程则与加密相反。例如：根据密钥第一个字母L所对应的L行字母表，发现密文第一个字母L位于A列，因而明文第一个字母为A。密钥第二个字母E对应E行字母表，而密文第二个字母X位于此行T列，因而明文第二个字母为T。以此类推便可得到明文。

用数字0-25代替字母A-Z，维吉尼亚密码的加密文法可以写成同余的形式：

<p style="text-align:center;"><img width="180px" src="../image/VigenereCipher-1.png" /></p>

解密方法则能写成：

<p style="text-align:center;"><img width="180px" src="../image/VigenereCipher-2.png" /></p>

## 维吉尼亚密码的变体

### Gronsfeld密码

Gronsfeld密码与维吉尼亚密码完全相同，只是使用数字作为密钥而不是字母，数字的选择可以从斐波那契数列或伪随机数序列中生成。


## 维吉尼亚密码的程序实现

!!! Tip "注意"

	**程序可在python3下运行**

维吉尼亚密码的程序实现：
```python
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
plaintext = ""
keyt = ""

def Scanf():
    global plaintext,keyt
    plaintext = input("请输入明文:")
    keyt = input("请输入密钥:")

def AlphaMove(alpha,drift):
    return(alphabet[(alphabet.find(alpha)+drift)%26])

def EnCryption():
    for i in range(len(plaintext)):
        print (AlphaMove(plaintext[i],alphabet.find(keyt[i%len(keyt)])),end="")
    print("")

def main():
    Scanf()
    EnCryption()

if "__main__" == __name__:
    main()

```

运行示例：

<p style="text-align:center;"><img width="350px" src="../image/VigenereCipher-3.png" /></p>

## 维吉尼亚密码的密码分析

尽管现在我们已经知道维吉尼亚密码是不安全的，但是如果维吉尼亚密码使用一个很长的随机密钥，我们也有可能无法破解。

维吉尼亚密码的破解可以分为两个步骤：确定密码的周期（密钥长度），然后找到正确的密钥。确定密钥长度时我们使用基于[重合指数](../../../ClassicalCipher/Cryptanalysis/IndexofCoincidence/)的检验，使用[卡方统计](../../../ClassicalCipher/Cryptanalysis/Chi-squared/)找到正确的密钥。

!!! Tip "例题"

	**请破解：`vptnvffuntshtarptymjwzirappljmhhqvsubwlzzygvtyitarptyiougxiuydtgzhhvvmumshwkzgstfmekvmpkswdgbilvjljmglmjfqwioiivknulvvfemioiemojtywdsajtwmtcgluysdsumfbieugmvalvxkjduetukatymvkqzhvqvgvptytjwwldyeevquhlulwpkt`**

!!! Warning "提示"

	**此方法无法保证我们找到的密钥就是正确的密钥，密文长度越长，可能性越大**

### 确定密钥长度

维吉尼亚密码将不同密钥的凯撒密码应用于连续的字母上，如果密钥是"PUB"，则第一个字母使用密钥为16的凯撒密码（P是第16个字母）进行加密，第二个字母用另一个密钥进行加密，第三个字母用再一个密钥进行加密。当我们到达第四个字母时，它使用与字母1相同的密码进行加密。因此，如果我们收集字母1，4，7，10，...，我们应该得到一个字符序列，所有这些字符都是使用相同密钥的凯撒密码进行加密。字符2，5，8，11，...和3，6，9，12，...的序列也将使用其自己的凯撒密码进行加密。当然，确切的顺序将取决于密码的周期，即密钥长度。

重合指数（IC）是一种统计技术，可以指示一段文本像英语的程度。该技术的有用特性之一是，如果使用替换密码加密文本，则IC的结果不会改变。这是因为IC基于字母频率，并且替换密码不会修改各个字母频率。如果文本与英语相似，则IC约为0.06；如果字符分布均匀，则IC接近0.03-0.04。

为了确定维吉尼亚密码的周期，我们首先假定密钥长度为2。我们从密文中提取两个序列1，3，5，7，...和2，4，6，8，...。使用我们刚举的例子，我们得到以下结果（注意：IC是使用整个序列计算的，而不止是显示的部分）

```
                                                            重合指数
密文:         vptnvffuntshtarptymjwzirappljmhhqvsubw...      0.049
如果密钥长度为2:                                            
sequence 1:  v t v f n s t r t m w i a p j h q s b ...      0.049
sequence 2:   p n f u t h a p y j z r p l m h v u w...      0.046
                                                  平均分:    0.048
如果密钥长度为3:                                            
sequence 1:  v  n  f  t  t  p  m  z  a  l  h  v  b ...      0.049
sequence 2:   p  v  u  s  a  t  j  i  p  j  h  s  w...      0.046
sequence 3:    t  f  n  h  r  y  w  r  p  m  q  u  ...      0.046
                                                  平均分:    0.047
```

我们可以假设密钥的长度为2~15，求出所有子序列重合指数的平均值，如下表所示： 

```
密钥长度         重合指数
-----------------------
1 :     0.0449443523561
2 :     0.0457833618884
3 :     0.0435885364312
4 :     0.0474962292609
5 :     0.0393612078978
6 :     0.0471437059672
7 :     0.0909922589726
8 :     0.0461858974359
9 :     0.0407804755631
10:     0.0361152882206
11:     0.0491603339901
12:     0.0512663398693
13:     0.0446886446886
14:     0.0988487702773
15:     0.0334554334554 
```

从表中可以看出在密钥长度为7和14时重合指数较高，这说明密钥长度可能为7，也可能为14。这两种密钥长度都应该尝试进一步破解，下表可能更直观。

<p style="text-align:center;"><img width="500px" src="../image/VigenereCipher-4.png" /></p>

### 查找密钥

现在我们可以大胆假设密钥长度为7，也就是说我们有7个凯撒密码要破解。我们使用卡方统计来找到正确的密钥：

提取密文中所有使用第一个密钥加密的密文（也就是第1，8，15，...个字母），得到第一个序列`VURZJUGRGGUGVGJQKEOAGUGKKQVWQP`，这是使用同一个密钥加密的凯撒密文。

如果想破解这个密钥，[卡方统计](../../../ClassicalCipher/Cryptanalysis/Chi-squared/)在这个页面有详细的描述。从本质上讲，我们尝试使用25种可能的密钥解密该序列，然后将解密后的文本频率分布与英文的频率分布进行比较，正确的密钥有着较低卡方统计量。

<pre>  密钥               解密文本                卡方统计
--------------------------------------------------
  0      VURZJUGRGGUGVGJQKEOAGUGKKQVWQP     595.42
  1      UTQYITFQFFTFUFIPJDNZFTFJJPUVPO     466.86
<span style="background-color:yellow;">  2      TSPXHSEPEESETEHOICMYESEIIOTUON      41.22</span>
  3      SROWGRDODDRDSDGNHBLXDRDHHNSTNM      67.73
  4      RQNVFQCNCCQCRCFMGAKWCQCGGMRSML     642.37
  5      QPMUEPBMBBPBQBELFZJVBPBFFLQRLK     451.49
  6      POLTDOALAAOAPADKEYIUAOAEEKPQKJ     121.97
  7      ONKSCNZKZZNZOZCJDXHTZNZDDJOPJI    2441.20
  8      NMJRBMYJYYMYNYBICWGSYMYCCINOIH     190.46
  9      MLIQALXIXXLXMXAHBVFRXLXBBHMNHG    1142.90
  10     LKHPZKWHWWKWLWZGAUEQWKWAAGLMGF     358.87
  11     KJGOYJVGVVJVKVYFZTDPVJVZZFKLFE     962.13
  12     JIFNXIUFUUIUJUXEYSCOUIUYYEJKED     354.18
  13     IHEMWHTETTHTITWDXRBNTHTXXDIJDC     241.97
  14     HGDLVGSDSSGSHSVCWQAMSGSWWCHICB     107.36
  15     GFCKUFRCRRFRGRUBVPZLRFRVVBGHBA     136.40
  16     FEBJTEQBQQEQFQTAUOYKQEQUUAFGAZ    1801.65
  17     EDAISDPAPPDPEPSZTNXJPDPTTZEFZY     531.22
  18     DCZHRCOZOOCODORYSMWIOCOSSYDEYX     247.66
  19     CBYGQBNYNNBNCNQXRLVHNBNRRXCDXW     377.60
  20     BAXFPAMXMMAMBMPWQKUGMAMQQWBCWV     489.12
  21     AZWEOZLWLLZLALOVPJTFLZLPPVABVU     815.45
  22     ZYVDNYKVKKYKZKNUOISEKYKOOUZAUT     648.33
  23     YXUCMXJUJJXJYJMTNHRDJXJNNTYZTS    1476.11
  24     XWTBLWITIIWIXILSMGQCIWIMMSXYSR     279.93
  25     WVSAKVHSHHVHWHKRLFPBHVHLLRWXRQ     158.53
</pre>

通过分析，我们得到了该密钥的第一个字母'C'（A = 0，B = 1，C = 2，...）。以此类推，分析剩下的六个密钥我们会得到序列：2，8，0，7，4，17，18，这意味着密钥是：`CIAHERS`，但很遗憾，答案错误。

这恰恰说明了除非有长密文，否则该方法未必可靠。正确的密钥是`CIPHERS`。

### 另辟蹊径

!!! Tip "注意"

	**这种方法需要我们能确定一段文本与英文的相似度，详见[四元组统计](../../../ClassicalCipher/Cryptanalysis/Quadgram/)**
	
因为我们不知道密钥长度，所以我们需要假设密钥长度为3、密钥长度为4....密钥长度为20。为了测试密钥的准确性，可以使用四元组统计的方法来评估解密文本的分数。例如，我们当前的密钥为CHIPAAA，我们只搜索了7位密钥中的前四位，我们再评估分数的时候也只评估前四位的分数，即：

当前密钥: **`CIPH`**`AAA`**`CIPH`**`AAA`**`CIPH`**`AAA`**`CIPH`**`AAA`

加密密文: `FMUL RUL JMTH WKO CTAV JKZ GKPZ XCW`

解密之后: **`DEFE`**`RUL`**`HEEA`**`WKO`**`ALL`**`OJKZ`**`ECAS`**`XCW`

我们仅会计算阴影部分的四元组统计分数，可以降低其他未正确解密区域对总体评分的影响。

!!! Tip "注意"

	**我们不会搜索所有的密钥（大概是26<sup>N</sup>次方个密钥 N是密钥长度），这显然不太现实，我们在破解密钥的时候将各位密钥独立开来破解，这样可以将搜索密钥的数量降低为26\*N。**

```python
from ngram_score import ngram_score
from itertools import permutations
from pycipher import Vigenere
import re

# 设置密文
ciphertext = 'kiqpbkxspshwehospzqhoinlgapp'
ciphertext = re.sub(r'[^A-Z]', '', ciphertext.upper())
# 加载字典
print('正在加载字典....')
qgram = ngram_score('quadgrams.txt')
tgram = ngram_score('trigrams.txt')
# 设置列表最大长度
N = 100
# 设置字母表
Alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


class OptativeStore(object):
    def __init__(self, store_length=1000):
        self.store = []
        self.store_length = store_length

    def append(self, item):
        self.store.append(item)
        self.store.sort(reverse=True)
        self.store = self.store[:self.store_length]

    def __getitem__(self, K):
        return self.store[K]

    def __len__(self):
        return len(self.store)


def ProcessTriGram(KLEN):

    oTable = OptativeStore(N)
    for i in permutations(Alphabet, 3):
        partkey = ''.join(i)
        fullkey = partkey + 'A' * (KLEN - 3)
        plaintext = Vigenere(fullkey).decipher(ciphertext)
        score = 0
        for j in range(0, len(plaintext), KLEN):
            score += tgram.score(plaintext[j:j + 3])
        oTable.append((score, partkey,  plaintext[:30]))
    return oTable


def SolveVirginia(KLEN):

    assert(KLEN > 2)
    best = ProcessTriGram(KLEN)
    nextbest = OptativeStore(N)
    for i in range(0, KLEN - 3):
        # print(i)
        for j in range(N):
            for k in Alphabet:
                partkey = best[j][1] + k
                # print(KLEN,len(partkey))
                fullkey = partkey + ('A' * (KLEN - len(partkey)))
                # print(fullkey)
                plaintext = Vigenere(fullkey).decipher(ciphertext)
                score = 0
                for l in range(0, len(ciphertext), KLEN):
                    score += qgram.score(plaintext[l:l + KLEN])
                nextbest.append((score, partkey, plaintext[:30]))
        best = nextbest
        nextbest = OptativeStore(N)
    return best


def main():
    for i in range(3, 20):
        bestkey = SolveVirginia(i)[0][1]
        plaintext = Vigenere(bestkey).decipher(ciphertext)
        bestscore = qgram.score(plaintext)
        print("Vigenere key length is %2d : %4d %20s %s" %
              (i, bestscore, bestkey, plaintext))


if __name__ == '__main__':
    main()

```

运行结果：

<p style="text-align:center;"><img src="../image/VigenereCipher-5.png" /></p>


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
