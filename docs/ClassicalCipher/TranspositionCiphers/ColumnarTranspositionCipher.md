## 列换位密码简介

列换位密码是一种比较简单、易于实现的换位密码，通过一个简单地规则将明文打乱混合成密文。

虽然列换位密码本身很弱，但如果结合其他密码一起使用，例如替换密码，组合后的密码更难破解。

!!! Tip "例题"

	**下面我们以明文"The quick brown fox jumps over the lazy dog"**

	**密钥 how are u为例：**

填入5行7列表(事先约定填充的行列数，如果明文不能填充完表格可以约定使用某个字母进行填充)

![ColumnarTranspositionCipher-1](image/ColumnarTranspositionCipher-1.png)

按how are u在字母表中的出现的先后顺序进行编号，我们就有a为1,e为2，h为3，o为4，r为5，u为6，w为7，所以先写出a列，其次e列，以此类推写出的结果便是密文：

![ColumnarTranspositionCipher-2](image/ColumnarTranspositionCipher-2.png)

`密文： qoury inpho Tkool hbxva uwmtd cfseg erjez`

## 列换位密码的程序实现

在python中加密加密明文，可以使用pycipher模块（使用pip install pycipher安装）。

```python
>>>from pycipher import ColTrans
>>>ColTrans("HELLO").encipher('defend the east wall of the castle')
'ETSLELDDALHTFHTOCEEEWFANEATS'
>>>ColTrans("HELLO").decipher('ETSLELDDALHTFHTOCEEEWFANEATS')
'DEFENDTHEEASTWALLOFTHECASTLE'
```

## 列换位密码的密码分析

!!! Tip "强调"

	**如果使用长密钥（比如密钥长度为20），列换位密码是一种令人惊讶的安全密码。**

### 暴力破解

破解列换位密码的第一步就是暴力破解。我们可以在很短时间内遍历9位以下的密钥，我们看一下不同的密钥空间：

|Key Length|No. of permutations	|Examples|
|:-:|:-:|:-:|
|2|2|AB, BA|
|3|6|ABC, BAC, CBA, ...|
|4|24|ABCD, ABDC, ACBD, ...|
|5|120|ABCDE, ABCED, ...|
|6|720|ABCDEF, ABDCFE, ...|
|7|5,040|ABCDEFG, ABDCGEF, ...|
|8|40,320|ABCDEFGH, ...|
|9|362,880|ABCDEFGHI, ...|
|10|3,628,800|ABCDEFGHIJ, ...|
|11|39,916,800|ABCDEFGHIJK, ...|
|12|479,001,600|ABCDEFGHIJKL, ...|

可以看到密钥长度为9的时候，密钥空间仅为41万左右，计算机可以很快的遍历完。

### 字典攻击

如果爆破失败的话，我们可以使用字典攻击。列换位密码经常使用单词或短语，所以我们可以将常用词语作为字典进行破解.

我们在暴力破解中测试了较短的单词，所以只需要测试长度超过9的字典，包含地名，人名，历史名等。

但如果关键字是类似"THEBLOOMSINSEPTEMBER"这种的，那多强大的字典也没有用了....

### 爬山算法

此处的爬山算法和我们在替换密码中的爬山算法是类似的，我们首先假设密钥长度为10，然后选择此长度的随机父密钥，通过在父密钥中进行随机交换来生成子密钥，如果子密钥可读性更高，那我们就用子密钥代替父密钥。

在经过成百上千的循环后，我们可能会找到正确的密钥。如果找不到正确的密钥，我们可以增加密钥长度再执行爬山算法。

<p style="text-align:center;"><img width="300px" src="../image/hill.jpg" /></p>

但对于长度大于20以上的密钥来说，模拟退火算法可能是更好地选择。

!!! Tip "问题"

	**如果使用暴力破解攻击列换位密码，我们该如何判断密钥是否正确？**






















