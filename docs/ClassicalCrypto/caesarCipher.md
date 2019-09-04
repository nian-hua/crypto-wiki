## 凯撒密码简介

凯撒密码是历史上已知最早的密码之一。凯撒密码中的每个字母在字母表中“移动”了一定的位置。例如，如果密码为1，则A将替换为B，B将替换为C，依此类推。相传最早是凯撒大帝用来和将军进行秘密交流时所用的加密方法。

我们更加直观的了解一下凯撒加密，如果密码为3，则A被替换成D、B被替换成E，如下图所示

<p style="text-align:center;"><img width="500px" src="../image/Caesar-1.png" /></p>


## 凯撒密码示例

!!! Tip "举例"

	**我们使用密钥1来加密`defend the east wall of the castle`**

首先写出密钥为1时明文和密文的对照表：

<p style="text-align:center;"><img width="700px" src="../image/Caesar-2.jpg" /></p>

对要加密的明文逐个查表替换：D替换为E、E替换为F、F替换为G、E替换为F... 依次类推，直到整段明文都被加密。

```
plaintext:  defend the east wall of the castle
ciphertext: efgfoe uif fbtu xbmm pg uif dbtumf
```

## 凯撒密码的数学描述

首先，我们将所有字符翻译成数字，'a'= 0，'b'= 1，'c'= 2，...，'z'= 25。我们现在可以使用数学描述表示凯撒密码加密函数e(x)，其中x是我们要加密的字符，如：

<p style="text-align:center;"><img width="200px" src="../image/Caesar-3.png" /></p>

其中k是密钥（每次加密使用的位移）。使用这个公式加密后的结果为数字，我们需要再将其转换为字母。

解密的数学描述如下：

lll