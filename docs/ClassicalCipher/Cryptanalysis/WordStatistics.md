## 单词统计简介

在之前的章节中我们学习了如何使用四元组来确定一段文本和英文的相似程度，而本节主要通过分析一段文本中包含的英文单词来确定文本与英文的相似程度。

在这之前有一个前提：我们需要一个非常大的语料库，以便计算每个单词的出现次数，然后再计算每个单词的概率。为了准确的计算概率，我们需要使用谷歌的[trillion word database](http://googleresearch.blogspot.com.au/2006/08/all-our-n-gram-are-belong-to-you.html)数据库。

## 分词

为了计算一段文本与英文的相似程度，我们需要提取所有的单词，将所有的单词概率相乘得到文本的总概率。但是在破解的过程中，密文往往是未经过分词的一整段文本，如果我们对这段文本暴力分词，则可能会有2^(L-1)种分词情况。

幸运的是，Peter Norvig在《美丽的数据》一书中提出了一种优雅的解决方案，我们将其称之为momoized递归，有关于momoized的更多详细资料请阅读[Peter Norvig的网站](http://norvig.com/ngrams/)

## 单词统计的程序实现

[单词统计字典下载地址](地址)

python程序：

```python
from math import log10

class word_score(object):
    def __init__(self):
        ''' load a file containing ngrams and counts, calculate log probabilities '''
        self.Pw = {}
        for line in file('count_1w.txt'):
            key,count = line.split('\t') 
            self.Pw[key.upper()] = self.Pw.get(key.upper(), 0) + int(count)
        self.N = 1024908267229 ## Number of tokens
        #calculate first order log probabilities
        for key in self.Pw.keys():
            self.Pw[key] = log10(float(self.Pw[key])/self.N)
        #get second order word model 
        self.Pw2 = {}
        for line in file('count_2w.txt'):
            key,count = line.split('\t') 
            self.Pw2[key.upper()] = self.Pw2.get(key.upper(), 0) + int(count)
        #calculate second order log probabilities
        for key in self.Pw2.keys():
            word1,word2 = key.split()
            if word1 not in self.Pw: 
                self.Pw2[key] = log10(float(self.Pw2[key])/self.N)
            else: 
                self.Pw2[key] = log10(float(self.Pw2[key])/self.N) - self.Pw[word1]
        # precalculate the probabilities we assign to words not in our dict, L is length of word
        self.unseen = [log10(10./(self.N * 10**L)) for L in range(50)]        
        
    # conditional word probability    
    def cPw(self,word,prev='<UNK>'):
        if word not in self.Pw: 
            return self.unseen[len(word)]
        elif prev+' '+word not in self.Pw2: 
            return self.Pw[word]
        else: 
            return self.Pw2[prev+' '+word]
    
    def score(self,text,maxwordlen=20):
        prob = [[-99e99]*maxwordlen for _ in range(len(text))]
        strs = [['']*maxwordlen for _ in range(len(text))]
        for j in range(maxwordlen):
            prob[0][j] = self.cPw(text[:j+1])
            strs[0][j] = [text[:j+1]]
        for i in range(1,len(text)):
            for j in range(maxwordlen):
                if i+j+1 > len(text): break
                candidates = [(prob[i-k-1][k] + self.cPw(text[i:i+j+1],strs[i-k-1][k][-1]),
                               strs[i-k-1][k] + [text[i:i+j+1]] ) for k in range(min(i,maxwordlen))]
                prob[i][j], strs[i][j] = max(candidates)
        ends = [(prob[-i-1][i],strs[-i-1][i]) for i in range(min(len(text),maxwordlen))]
        return max(ends)
```
## 举例

!!! Tip "举例"

	**来尝试将句子`HELLOHOWAREYOUTODAY`分段，并计算分数**

```python
from word_score import word_score
fitness = word_score()
print fitness.score('HELLOHOWAREYOUTODAY')
```
程序的预期返回结果是：`(-15.227537974076597,['HELLO','HOW','ARE','YOU','TODAY'])`

!!! Warning "提示"
	**其中文本必须为大写程序才能正常工作**

