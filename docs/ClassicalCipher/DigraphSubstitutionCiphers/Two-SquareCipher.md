## 二方密码简介

二方密码又称为双普莱费尔密码，其安全性高于普莱费尔密码，但是操作方法并没有麻烦很多。它与普莱费尔密码的不同之处在于使用了两个混合方块。消除了普莱费尔密码的主要特征，因为在二方密码中字母可以自己加密自己，并且也可以出现双字母。

使用频率分析方法来攻击二方密码难度非常大，因为有676个二元组需要分析，这必须得基于大量的密文。

## 二方密码示例

!!! Tip "举例"

	**我们使用密钥`example`和`keyword`来加密`help me obi wan kenobi`**

要使用二方密码加密，首先要使用不同密钥准备两个波利比奥斯方阵。根据方阵的位置不同，二方密码可以分为两种加密方式，如下所示：

<p style="text-align:center;"><img width=85% src="../image/Two-SquareCipher-1.png" /></p>

接下来将明文拆分为二元组：

<p style="text-align:center;"><img src="../image/Two-SquareCipher-2.png" /></p>

### 加密过程

我们分别使用密钥横向和密钥竖向两种方法来进行加密。

#### 横向密钥方阵

对于使用横向密钥方阵加密方式来说，需要在左侧的方阵中找到明文二元组中的第一个字母，在右侧方阵中找到明文二元组的第二个字母，将每个字母替换为与该字母同一列的矩阵角字母。如图所示：

<p style="text-align:center;"><img width=70% src="../image/Two-SquareCipher-3.png" /></p>

最终加密后的结果为：

<p style="text-align:center;"><img src="../image/Two-SquareCipher-4.png" /></p>

#### 竖向密钥方阵

如果使用竖向密钥方阵，我们需要在上方的方阵中找到明文二元组中的第一个字母，在下方的方阵中找到明文二元组中的第二个字母，将每个字母替换为与该字母同一行的矩阵角字母。如图所示：

<p style="text-align:center;"><img width=50% src="../image/Two-SquareCipher-5.png" /></p>

最终加密后的结果为：

<p style="text-align:center;"><img src="../image/Two-SquareCipher-6.png" /></p>

### 解密过程

由于密码的对称性，二方密码的加密步骤和解密步骤完全相同，请自行尝试解密。

## 二方密码的密码分析

其实我们应该发现：有部分明文加密后却依旧与明文相同，如竖向密钥方阵将`he`加密为`HE`，因为两个字母位于同一行。这种情况在密码学中被称之为透明性（transparency）。

许多密码的缺点是字符加密后不可能为本身，大大减小了密码分析者需要考虑的情况。而透明性的存在则可以消除这个缺点。

但是因为二方密码中有大概20%的二元组被加密后与明文相同，所以这不再是一种优点，而是一种致命的缺陷。

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


