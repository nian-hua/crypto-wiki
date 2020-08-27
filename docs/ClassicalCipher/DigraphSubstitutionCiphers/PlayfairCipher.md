## 普莱费尔简介

普莱费尔密码是由惠斯通发明的一种有向图密码，该密码不像简单替换密码或维吉尼亚密码只加密单个字母，而是使用成对的字母（二元组）进行加密。因此在分析普莱费尔密码是，无法使用简单地频率分析，而是使用 **基于二元组的频率分析**。

如果基于二元组的频率分析，我们需要使用25\*25 = 625个有向图，也就是说要对625种频率状态进行排序，因此我们需要很长的密文才能使用这种方法。

除此之外，我们在破解简单替换密码时还使用了一种名为爬山算法的方法，而因为普莱费尔密码的复杂性使爬山算法有可能会使其陷入 **局部最大值**，所以我们使用 **模拟退火算法** 破解普莱费尔密码。

## 普莱费尔密码示例

使用普莱费尔密码之前，我们首先需要绘制一个波利比奥斯方阵。通常使用密钥来创建方阵（因为方阵最多容纳5\*5=25个元素，所以我们需要将字母表中使用频率最少的i和j写在同一方格）。

### 加密过程

加密规则如下：

1. 如果拆分明文二元组时同一个二元组内有两个相同的字母（或结尾处仅剩一个字母），则在相同字母之间（或末尾）插入"X"。

2. 如果二元组出现在方阵的同一行中，则将每个字母替换为当前行中右边的字母（遇到行尾从行首重新开始）。

3. 如果二元组出现在方框的同一列中，则将每个字母替换为当前列中下方的字母（遇到列尾从列首重新开始）。

4. 如果二元组形成一个相对角的矩形，则将每个字母替换为与该字母同一行的矩阵角字母（请注意保持顺序）。

!!! Tip "举例"

	**我们使用密钥`playfair`来加密`hide the gold in the tree stump`**

首先使用密钥生成波利比奥斯方阵（将i和j写在同一方格内）：

<p style="text-align:center;"><img width=20% src="../image/PlayfairCipher-1.png" /></p>

将明文拆分为二元组：

<p style="text-align:center;"><img width=70% src="../image/PlayfairCipher-2.png" /></p>

可以发现第十个二元组为"ee"，根据加密规则1插入"x"：

<p style="text-align:center;"><img width=70% src="../image/PlayfairCipher-3.png" /></p>

接下来根据加密规则，依次加密每个二元组：

<p style="text-align:center;"><img width=70% src="../image/PlayfairCipher-4.png" /></p>

拼接密文二元组得到密文：

<p style="text-align:center;"><img width=70% src="../image/PlayfairCipher-5.png" /></p>

最终得到密文为`BMODZBXDNABEKUDMUIXMMOUVIF`，或将其拆分为大小为5的块：`BMODZ BXDNA BEKUD MUIXM MOUVI F`，甚至可以仿照原始明文布局`BMOD ZBX DNAB EK UDM UIXMM OUVIF`。

### 解密过程

解密过程与加密过程几乎完全相同，除了在规则2、3中的取右边、下方的字母改为取左边、上方的字母。最后还要删除多余的"x"字符。

!!! Tip "举例"

	**我们使用密钥`example`来解密`UA ARBED EXAPO PR QNX AXANR`**

首先使用密钥生成波利比奥斯方阵（`字母i同j`）：

<p style="text-align:center;"><img width=20% src="../image/PlayfairCipher-6.png" /></p>

根据规则解密每个密文二元组：

<p style="text-align:center;"><img width=70% src="../image/PlayfairCipher-7.png" /></p>

将所有的二元组拼接到一起：

<p style="text-align:center;"><img width=70% src="../image/PlayfairCipher-8.png" /></p>

删除其中多余的x（exit中的x不用删除，因为x前后字母不相同），最终得到明文：`we will meet at the exit`。

## 普莱费尔密码的程序实现

```python
>>>from pycipher import Playfair
>>>Playfair('zgptfoihmuwdrcnykeqaxvsbl').encipher('defend the east wall of the castle')
'RKPAWRPMYSELZCLFXUZFRSNQBPSA'
>>>Playfair('zgptfoihmuwdrcnykeqaxvsbl').decipher('RKPAWRPMYSELZCLFXUZFRSNQBPSA')
'DEFENDTHEXASTWALLOFTHECASTLE'
```

运行示例：

<p style="text-align:center;"><img src="../image/PlayfairCipher-9.png" /></p>

## 普莱费尔密码的密码分析

### 普莱费尔密码的特征

1. 密文中包含偶数个字母。

2. 至多包含25个字母（不含字母J）

3. 如果出现长重复，那么他们的间隔只能是偶数个字符。

4. 密文中二元组内的元素不可能相同（例如密文二元组`EE`是不可能存在的）。

### 普莱费尔密码的频率分析攻击

在上一小节的解密过程中，我们可以发现密文中存在3个`XA`，而它们解密后都被还原为`ex`，这说明依然可以对普莱费尔密码进行频率分析，但前提是基于二元组。

如果存在一段很长的密文，完全满足英文的统计学规律，则我们还可以使用基于二元组的频率分析。

<p style="text-align:center;"><img src="../image/PlayfairCipher-10.png" /></p>

### 普莱费尔密码的已知明文攻击

在手工密码分析时，我们需要注意到以下技巧：

一个普莱费尔密文二元组及其逆向二元组（例如密文中的AB和BA），解密后的对应明文依旧是逆向关系（例如RE和ER）。

具体方法内容可以参见美军编写的"Field Manual"第7章"Solution to Polygraphic Substitution Systems"。

### 模拟退火算法

在破解简单替换密码，我们引入了爬山算法来攻击简单替换密码。首先我们来回顾一下简单替换算法。

简单替换密码的原理：

1. 生成一个parent随机密钥，使用parent密钥解密并评估分数，存储结果。

2. 随机更换密钥中的两个字符，使用新密钥解密文本并评估分数。

3. 如果新密钥分数较高，则将新密钥存储为parent密钥。

4. 回到2，如果在最近1000次迭代中评分没有发生显著性改善则回到1。

遗憾的是，爬山算法无法用来破解简单替换密码，因为爬山算法在破解过程中往往会卡在局部最大值,而不一定是全局最大值（也就说此时并不是真正的密钥，但是爬山算法简单地修改密钥并没有办法再提高文本的适应性）。

<p style="text-align:center;"><img width=525px src="../image/PlayfairCipher-11.png" /></p>

爬山法是完完全全的贪心法，每次都鼠目寸光的选择一个当前最优解，因此只能搜索到局部的最优值。**模拟退火** 其实也是一种贪心算法，但是它的搜索过程引入了 **随机因素**。模拟退火算法以一定的概率来 **接受一个比当前密钥要差的一个密钥**，因此有可能会跳出这个局部的最大值，达到全局的最大值。

<p style="text-align:center;"><img width=525px src="../image/PlayfairCipher-12.png" /></p>

如上图所示，模拟退火算法在搜索到局部最大值A后，会以一定的概率接受到E的移动。也许经过几次这样的不是局部最优的移动后会到达D点，于是就跳出了局部最大值A。

<p style="text-align:center;"><img src="../image/PlayfairCipher-x.gif" /></p>

模拟退火算法的原理：

1. 生成一个parent随机密钥，使用parent密钥解密。

2. 对解密后的文本评估分数，并存储结果。

3. 伪代码如下：

```python
for k in range(TEMP=10,TEMP>=0,TEMP=TEMP-STEP):
	for i in range(50000,0,-1):
		child = change(parent)        #稍微修改父密钥（例如随机交换密钥中的两个字符）得到子密钥，使用子密钥解密文本并评估分数
		set dF = (ChildFit-ParentFit) #计算子密钥和副密钥的评分差
		If dF > 0 :                   #子密钥的评分高于父密钥,总是接受该子密钥
			parent = child
		If dF < 0 && :                   #子密钥的评分低于父密钥
			parent = child            #以一定的概率接受移动，而且这个概率随着时间推移逐渐降低（逐渐降低才能趋向稳定）
```

这里的"一定概率"参考的是金属冶炼的退火过程，这也是模拟退火算法名称的由来。

根据热力学的原理，在温度为T时，出现能量差为dE的降温的概率为P(dE)，表示为：

$$P(dE) = exp(dE/(kT))$$

其中k是一个常数，exp表示自然指数，且dE<0。这条公式的意思是：温度越高，出现一次能量差为dE的降温的概率就越大；温度越低，则出现降温的概率就越小。又由于dE总是小于0（否则就不叫退火了），因此dE/kT < 0 ，所以P(dE)的函数取值范围是(0,1) 。

随着温度T的降低，P(dE)会逐渐降低。我们将一次向较差解的移动看做一次温度跳变过程，我们以概率P(dE)来接受这样的移动。

!!! Tip "注意"

	**该程序需要配合密码分析文本表征中的ngram_score评分模块，以及quadgrams字典。请移步至[四元组统计](http://crypto-wiki.io/ClassicalCipher/Cryptanalysis/Quadgram/)。**

```python
# Tuesday, December 10, 2019
# Author:nianhua
# Blog:https://github.com/nian-hua/
import random
import math
from ngram_score import ngram_score
from pycipher import Playfair
print("正在加载字典")
TEMP = 20
STEP = 0.2
COUNT = 10000
fitness = ngram_score('quadgrams.txt')


def playfairDecipher(ciphertext, key):
    return Playfair(key).decipher(ciphertext)


def exchange2letters(key):

    i = random.randint(0, 24)
    j = random.randint(0, 24)
    key = list(key)
    key[i], key[j] = key[j], key[i]
    return ''.join(key)


def swap2rows(key):
    i = random.randint(0, 4)
    j = random.randint(0, 4)
    newkey = ''
    for k in range(5):
        if k == i:
            newkey += key[j*5:j*5+5]
        elif k == j:
            newkey += key[i*5:i*5+5]
        else:
            newkey += key[k*5:k*5+5]
    return newkey


def transpkey(key):
    changekey = ''
    for k in range(5):
        for s in range(5):
            changekey += key[5*s+k:5*s+k+1]
    return changekey


def swap2cols(key):
    key = transpkey(key)
    key = swap2rows(key)
    key = transpkey(key)
    return key


def flashbackrows(key):
    newkey = ''
    for i in range(4, -1, -1):
        newkey += key[i*5:i*5+5]
    return newkey


def flashbackcols(key):
    key = transpkey(key)
    key = flashbackrows(key)
    key = transpkey(key)
    return key


def modifyKey(key):

    i = random.randint(0, 50)
    if i == 0:
        key = swap2rows(key)
    elif i == 1:
        key = swap2cols(key)
    elif i == 2:
        key = key[::-1]
    elif i == 3:
        key = flashbackrows(key)
    elif i == 4:
        key = flashbackcols(key)
    else:
        key = exchange2letters(key)
    return key


def playfairCrack(ciphertext, key):

    deciphered = playfairDecipher(ciphertext, key)
    maxscore = fitness.score(deciphered)
    maxkey = key
    bestscore = maxscore
    T = TEMP
    while T >= 0:
        T = round(T-STEP, 2)
        # print(T)
        # vss = 0
        for i in range(COUNT):
            testkey = modifyKey(maxkey)
            deciphered = playfairDecipher(ciphertext, testkey)
            score = fitness.score(deciphered)
            dF = score - maxscore
            if dF > 0:
                maxscore = score
                maxkey = testkey
            elif T > 0:
                prob = math.exp(dF/T)
                if prob > random.random():
                    vss += 1
                    maxscore = score
                    maxkey = testkey
            if maxscore > bestscore:
                # print(bestscore)
                bestscore = maxscore
                key = maxkey
        # print('vss:'+str(vss))
    return bestscore, key, playfairDecipher(ciphertext, key)


def main():
    score, maxscore = -99e99, -99e99
    ciphertext = "XZOGQRWVQWNROKCOAELBXZWGEQYLGDRZXYZRQAEKLRHDUMNUXYXSXYEMXEHDGNXZYNTZONYELBEUGYSCOREUSWTZRLRYBYCOLZYLEMWNSXFBUSDBORBZCYLQEDMHQRWVQWAEDPGDPOYHORXZINNYWPXZGROKCOLCCOCYTZUEUIICERLEVHMVQWLNWPRYXHGNMLEKLRHDUYSUCYRAWPUYECRYRYXHGNBLUYSCCOUYOHRYUMNUXYXSXYEMXEHDGN"
    key = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    Icount = 1
    while True:
        score, key, plaintext = playfairCrack(ciphertext, key)
        if score > maxscore:
            maxscore = score
            print("当前的轮次：" + str(Icount))
            print("最佳分数：" + str(maxscore))
            print("密钥：" + str(key))
            print("明文：" + str(plaintext))
        Icount += 1


if __name__ == '__main__':
    main()
```

程序运行示例：

<p style="text-align:center;"><img src="../image/PlayfairCipher-13.png" /></p>

!!! Warning "扩展"

	**更多关于模拟退火算法的信息，请访问[模拟退火算法](https://en.wikipedia.org/wiki/Simulated_annealing)**

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


