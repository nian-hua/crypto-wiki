## 仿射密码简介

仿射密码是一种单字母替换密码的特例。

该密码不如简单替换密码安全，因为它不仅容易受到针对替代密码的所有攻击方法，而且还存在其他缺点。其主要缺点来自以下方面：如果密码分析者可以发现（通过频率分析，暴力破解，猜测或其他方式）两个密文字符对应的明文，则可以通过联立方程组来求解密钥。

## 仿射密码的数学描述

仿射密码的"密钥"由2个数字组成，我们将其称为a和b。以下讨论假定使用26个字符的字母（m = 26）。a应该选择为相对于m素数（即a应该没有与m相同的公因数<除1以外>）。例如15和26没有公因数(除1以外)，因此15是可以用来加密的值，然而12和26具有相同公因数（例如2），这样12不能被用于加密。加密时，我们首先将所有字母转换为数字（'a'= 0，'b'= 1，...，'z'= 25）。

对于密文c，给定任意的p（p是代表字母的数字），有：

<p style="text-align:center;"><img width="400px" src="../image/AffineCipher-1.png" /></p>

解密的公式为：

<p style="text-align:center;"><img width="200px" src="../image/AffineCipher-2.png" /></p>

其中a<sup>-1</sup>是a的乘法逆元，为了找到a的乘法逆元，我们需要假定数字x满足：

<p style="text-align:center;"><img width="135px" src="../image/AffineCipher-3.png" /></p>

如果我们发现x使得等式成立，那么X就是a的逆元，我们称之为a<sup>-1</sup>。

解决此方程式最简单的方法是遍历1到25个数字，然后看哪个满足该方程式。

如果您想要更严谨的解决方案，可以使用matlab查找x：

```matlab
> [g,x,d] = gcd(a,m);    % we can ignore g and d, we dont need them
> x = mod(x,m);     
```

则x和a相乘并对26求余的结果为1。(以上都是定义，记住即可。)

!!! Tip "注意"

	**m的值并非总是26，如果你的字母表中含有大写字母、小写字母、以及空格，那么m值为53**
	
## 仿射密码示例

!!! Tip "举例"

	**令密钥a=5且b=7，加密`defend the east wall of the castle`**

我们将第一个字母'd'转换为数字3（'a'= 0，'b'= 1，...，'z'= 25）并将其代入等式中：

<p style="text-align:center;"><img width="400px" src="../image/AffineCipher-4.png" /></p>

因为'w'= 22，所以使用密钥a=5和b=7将'd'转换为'w'。以此类推，我们得到密文：

```
wbgbuwyqbbhtynhkkzgyqbrhtykb
```

接下来进行解密，通过计算知5<sup>-1</sup>=21，即5\*21=1(mod 26)，解密的公式如下：

<p style="text-align:center;"><img width="420px" src="../image/AffineCipher-5.png" /></p>

显而易见，我们可以依次得到明文：

```
defendtheeastwallofthecastle
```

## 仿射密码的程序实现

!!! Tip "注意"

	**可以使用`pip install pycipher`安装pycipher模块**

```python
>>>from pycipher import Affine
>>>Affine(a=5,b=9).encipher('defend the east wall of the castle')
'YDIDWYASDDJVAPJMMBIASDTJVAMD'
>>>Affine(a=5,b=9).decipher('YDIDWYASDDJVAPJMMBIASDTJVAMD')
'DEFENDTHEEASTWALLOFTHECASTLE'
```

运行示例：

<p style="text-align:center;"><img width="500px" src="../image/AffineCipher-6.png" /></p>

## 仿射密码的密码分析

仿射密码比凯撒密码稍微复杂一些，但并没有提供更多的安全性。其密钥空间仅为311（12\*26-1），对于计算机而言，很容易通过遍历所有的密钥来进行解密，并找到最佳密钥。

因此我们使用暴力破解，必须尝试使用每个密钥解密，然后每段解密后文本的可读性。

仿射密码有两个密钥，a和b。b的范围可从0~25，a的值可以为：`1,3,5,7,9,11,15,17,19,21,23,25`,我们遍历所有的组合，通过评分模块最后选择最有可能的密钥。

!!! Tip "注意"

	**该程序需要配合密码分析文本表征中的ngram_score评分模块，以及quadgrams字典。请移步至[四元组统计](http://crypto-wiki.io/ClassicalCipher/Cryptanalysis/Quadgram/)。**

```python
from ngram_score import *

fitness = ngram_score('quadgrams.txt')
alphabetb = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alphabets = "abcdefghijklmnopqrstuvwxyz"
scoretmp = []
newliste = []
ciphertext = input("请输入要破解的密码:")


def affine(a,b):

    plaintext =""
    for j in ciphertext:
        if 64 < ord(j) < 91:
            plaintext += alphabetb[(alphabetb.find(j)*a+b)%len(alphabetb)]
        elif 96 < ord(j) <123:
            plaintext += alphabets[(alphabets.find(j)*a+b)%len(alphabets)]
        else:
            plaintext += j
    return plaintext



def main():
    i = 0
    for a in [1,3,5,7,9,11,15,17,19,21,23,25]:
        for b in range(26):
            scoretmp.append([])
            plaintext = affine(a,b)
            scoretmp[i].append(i)
            scoretmp[i].append(plaintext)
            scoretmp[i].append(fitness.score(''.join(list(filter(str.isalpha,plaintext))).upper()))
            i = i+1
    for i in range(5):
        scorevi = -99e9
        goodvi = 0
        for j in scoretmp:
            if j[2] > scorevi:
                scorevi = j[2]
                goodvi = j[0]
        newliste.append(scoretmp[goodvi][:])
        scoretmp[goodvi][2] = -99e9
        print("%2d:%4.2f:%s"%(newliste[i][0],newliste[i][2],newliste[i][1]))

if "__main__" == __name__:

    main()
```

运行示例：

<p style="text-align:center;"><img src="../image/AffineCipher-7.png" /></p>

除了暴力破解之外，仿射密码的另一个缺陷是：已知任意两个密文对应的明文字符，则可以通过联立方程组来求解密钥。

假设我们有一段密文。如果密文中统计量最多的两个字符是"h"和"q"，那么我们可以假定它们对应于明文中的"e"和"t"。

此时，我们可以联立一个方程组（'h'->'e'和'q'->'t'），以下两个方程是我们已知的仿射密码中明文字符和对应的密文字符，但并不知道a和b（在以下等式中，字母已经被转换为数字，'e'= 4，'h'= 7，'q'= 16，'t'= 19）：

<p style="text-align:center;"><img width="230px" src="../image/AffineCipher-8.png" /></p>

此处我们使用通用方程组化简：

<p style="text-align:center;"><img width="210px" src="../image/AffineCipher-9.png" /></p>

现在我们已知`p q r s`，求a和b。首先我们必须找到`d=p-q`以及d<sup>-1</sup>。现在我们就可以求解a、b，如下图所示：

<p style="text-align:center;"><img width="250px" src="../image/AffineCipher-10.png" /></p>

继续刚刚的例子，令`p=4，r=7，q=19，s=16`。则`D = p-q = -15 = 11(mod 26)`。显然，D<sup>-1</sup> = 19。因此：

<p style="text-align:center;"><img width="580px" src="../image/AffineCipher-11.png" /></p>

故，`a=11，b=15`。

我们再将a和b代入解密程序，查看解密得到的文本是否包含正确的消息。