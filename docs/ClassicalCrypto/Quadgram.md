## 四元组统计简介

在尝试破解密码的时候，通常会使用不同的密钥进行解密，然后查看已解密的文本，如果文本看起来非常像英文，那我们认为这个密钥有可能是正确的。

**四元组统计（Quadgram Statistics）是一种确定一段文本与英文相似程度的方法。例如文本ATTACK中的四元组是ATTA、TTAC、TACK。**

要使用四元组统计来确定文本与英文的相似程度，首先我们要确定哪些四元组在英文中出现的频率高、哪些四元组在英文中出现的频率低。因此我们统计了托尔泰的《战争与和平》中的所有出现的四元组，再计算出每个四元组的概率。


|Quadgram|Count|LogProbability|
|:-:|:-:|:-:|
|AAAA|1|-6.40018764963|
|QKPC|0|-9.40018764963|
|YOUR|1132|-3.34634122278|
|TION|4694|-2.72864456437|
|ATTA|359|-3.84509320105|

四元组统计 english_quadgrams.txt 下载地址

!!! Tip "提示"

	**可以看出某些四元组的出现频率远高于其他四元组，这可用于确定特定文本片段与英语的相似程度。**


**这意味着，如果文本中包含QPKC则可能不是英语，如果包含TION，则很大程度可能是英语。**

要计算一段文本是英文的概率，我们必须提取出文本中所有的四元组，然后乘以每个四元组的概率。对于文本ATTACK，四元组是ATTA、TTAC和TACK，则总概率为：

<p style="text-align:center;"><img width="400px" src="../image/Quadgram-1.png" /></p>

例如：

<p style="text-align:center;"><img width="230px" src="../image/Quadgram-2.png" /></p>

在上面的等式中，count()是特定四元组出现的字数，N是训练样本中四元组的总数。

!!! Tip "提示"

	**太多的小数相乘时，浮点数有可能会造成数值下溢，因此对每个概率取对数。**

我们都知道 **log(a*b) = log(a)+log(b)** ，所以最终的公式为：

<p style="text-align:center;"><img width="650px" src="../image/Quadgram-3.png" /></p>

使用对数来计算一段文本的分数，数值越大意味着这段文本越可能是英文、数字越小意味着不太可能是英文。

## 四元组统计举例

!!! Tip "例子"

	计算明文文本 **ATTACK THE EAST WALL OF THE CASTLE AT DAWN** 的四元组统计分数

	以及经过凯撒加密后密文 **FYYFHP YMJ JFXY BFQQ TK YMJ HFXYQJ FY IFBS** 的四元组统计分数

通过在文本中提取四元组，然后使用公式计算四元组统计分数。明文文本分数为-129.24、加密后的文本分数为-288.10。很明显原始文本具有更高的分数，这正是我们想要的效果。

**明文文本分数较高的原因是因为像"EAST"和"OFTH"这样的四元组在英文中出现的频率更高，它们对总分数的贡献更大。而加密后文本中"FYYF"和"BFQQ"之类的四元组在英文中非常罕见，因此拉低了总分数。**

## 四元组统计的程序实现

```python
'''
fileName:ngram_score.py
Allows scoring of text using n-gram probabilities
17/07/12
'''
from math import log10

class ngram_score(object):
    def __init__(self,ngramfile,sep=' '):
        ''' load a file containing ngrams and counts, calculate log probabilities '''
        self.ngrams = {}
        for line in file(ngramfile):
            key,count = line.split(sep) 
            self.ngrams[key] = int(count)
        self.L = len(key)
        self.N = sum(self.ngrams.itervalues())
        #calculate log probabilities
        for key in self.ngrams.keys():
            self.ngrams[key] = log10(float(self.ngrams[key])/self.N)
        self.floor = log10(0.01/self.N)

    def score(self,text):
        ''' compute the score of text '''
        score = 0
        ngrams = self.ngrams.__getitem__
        for i in xrange(len(text)-self.L+1):
            if text[i:i+self.L] in self.ngrams: score += ngrams(text[i:i+self.L])
            else: score += self.floor          
        return score
```

使用方法：

```python
import ngram_score as ns
fitness = ns.ngram_score('quadgrams.txt')
print fitness.score('HELLOWORLD')
```


