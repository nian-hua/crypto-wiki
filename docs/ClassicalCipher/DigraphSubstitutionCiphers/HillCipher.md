## 希尔密码简介

希尔密码是一种运用基本矩阵论原理的有向图密码，由Lester S. Hill在1929年发明。

希尔首先将字母转换为数字（A=0, B=1, C=2...），一串字母当成n维向量，跟一个n×n的矩阵相乘，再将得出的结果模26。

需要注意的是用来加密的密钥矩阵必须是可逆的。

## 希尔密码示例

!!! Tip "举例"

	**我们使用密钥`BACKUP`来加密`retreat now`**

### 加密过程

因为密钥长度太短，无法填充3×3矩阵，所以我们这里使用`ABC`来补空。

<p style="text-align:center;"><img width=15% src="../image/HillCipher-1.png" /></p>

将字母转换为数字：

<p style="text-align:center;"><img src="../image/HillCipher-2.png" /></p>

则密钥矩阵为：

<p style="text-align:center;"><img width=20% src="../image/HillCipher-3.png" /></p>

现在我们将明文拆分为长度为3的列向量，`x`为我们填充的内容。

<p style="text-align:center;"><img width=25% src="../image/HillCipher-4.png" /></p>

将字母列向量转换为数字列向量：

<p style="text-align:center;"><img width=25% src="../image/HillCipher-5.png" /></p>

执行矩阵乘法：

<p style="text-align:center;"><img width=50% src="../image/HillCipher-6.png" /></p>

对明文列向量组依次操作，得到最终密文：`DPQRQ EVKPQ LR`。

### 解密过程

要解密哈希密文，必须找到加密密钥的逆矩阵，找到逆矩阵之后，解密过程和加密过程完全相同。计算逆矩阵的一般方法如下：

<p style="text-align:center;"><img width=30% src="../image/HillCipher-7.png" /></p>

首先找出密钥矩阵行列式的值并对26求余：

<p style="text-align:center;"><img width=50% src="../image/HillCipher-8.png" /></p>

继续求得行列式值模26的乘法逆元为19：

<p style="text-align:center;"><img width=30% src="../image/HillCipher-9.png" /></p>

再求得密钥矩阵的伴随矩阵为：

<p style="text-align:center;"><img width=50% src="../image/HillCipher-10.png" /></p>

最后将行列式值的乘法逆元与伴随矩阵相乘得到逆矩阵（**如果矩阵可逆，那么它的逆矩阵和它的伴随矩阵之间只差一个系数。**）：

<p style="text-align:center;"><img width=70% src="../image/HillCipher-11.png" /></p>

现在我们有了逆矩阵，将其与密文列向量相乘，即可得到明文:

<p style="text-align:center;"><img width=50% src="../image/HillCipher-12.png" /></p>

对密文列向量组依次操作，得到最终明文：`RETREAT NOW XX`。

!!! Tip "注意"

	**并不是每个矩阵都有逆矩阵。所以在选择密钥矩阵时，一定要保证密钥矩阵行列式值非零。**

## 希尔密码的密码分析

密码分析是破解密码的艺术，频率分析法对于希尔密码来说并没有用。但是希尔密码容易受到已知明文攻击（即知道明文及对应密文），因为希尔密码是完全线性的，所以根据已知的明文/密文可以构建线性方程组，进而求解方程组恢复密钥。

### 约束滑动算法

因为希尔密码是线性的，所以我们只需要找到2个二元组对应关系即可确定密钥矩阵（矩阵大小为`2×2`）。例如我们已知"th"被加密为"gk"，"er"被加密为"bd"，则通过求解一组线性方程组，恢复密钥矩阵。

!!! Tip "例题"

	**假设有一段密文为`fupcmtgzkyukbqfjhuktzkkixtta`（矩阵大小为`2×2`）**
	
并且我们通过其他方式得知密文中有一段明文文本为`of the`，则可能的情况为：

```
fu pc mt gz ky uk bq fj hu kt zk ki xt ta
-----------------------------------------
of th e. .. .. .. .. .. .. .. .. .. .. ..
.o ft he .. .. .. .. .. .. .. .. .. .. ..
.. of th e. .. .. .. .. .. .. .. .. .. ..
.. .o ft he .. .. .. .. .. .. .. .. .. ..
.. .. of th e. .. .. .. .. .. .. .. .. ..
.. .. .o ft he .. .. .. .. .. .. .. .. ..
.. .. .. of th e. .. .. .. .. .. .. .. ..
...
```
此时我们假设第二行为正确的结果，可知`"PC"`被加密为`"FT"`、`"MT"`被加密为`"HE"`，构建线性方程组（D为密钥矩阵）：

<p style="text-align:center;"><img src="../image/HillCipher-13.png" /></p>

<p style="text-align:center;"><img src="../image/HillCipher-14.png" /></p>

将以上两个方程合为一个方程：

<p style="text-align:center;"><img src="../image/HillCipher-15.png" /></p>

移项得求解密钥矩阵的方程：

<p style="text-align:center;"><img src="../image/HillCipher-16.png" /></p>

令P为我们要求逆的矩阵，d为P的行列式，求得d=|P|=1，则d<sup>-1</sup>=1 (1=1 mod 26)，又P的伴随矩阵为：

<p style="text-align:center;"><img src="../image/HillCipher-17.png" /></p>

因此可知P的逆矩阵为：

<p style="text-align:center;"><img src="../image/HillCipher-18.png" /></p>

所以密钥矩阵为：

<p style="text-align:center;"><img src="../image/HillCipher-19.png" /></p>

我们尝试使用密钥矩阵还原密文：

```
frfthezyssqyvfetlvbafvaconfz
```

显然，这不是正确答案，这意味着之前我们的假设错误。通过多次尝试，最终发现当`"KT"`被加密为`"FT"`、`"ZK"`被加密为`"HE"`时，还原的明文是有意义的文本。

此时的密钥矩阵为：

<p style="text-align:center;"><img src="../image/HillCipher-20.png" /></p>

解密后的文本为：

```
defendtheeastwallofthecastle
```

!!! Warning "约束滑动算法"

	**约束滑动算法是指通过在密文上滑动已知明文块，逐次求解加密密钥，并还原明文（通过评分判断是否为正确密钥，例如四元组统计法）。**

### 唯密文攻击

如果仅知加密后的密文（矩阵大小为`2×2`），则我们可以尝试使用最常见的四元组作为已知明文块进行约束滑动攻击，例如：我们使用英文中最常见的四元组`"THAT"`进行约束滑动攻击，然后尝试英文中第二常见的四元组`"THER"`，以此类推，直到还原出来的明文是一段正确的英文。

### 约束滑动算法的程序实现

**等待补充**

### `3×3`矩阵

现阶段无法完成`3×3`密钥矩阵的希尔密码唯密文攻击，有想法的童鞋可以留言呀。

## 希尔密码的总结

虽然我们无法破解`3×3`密钥矩阵的希尔密码，但是它的确是一种不安全的加密方法。我们可以将希尔密码与其他非线性运算（例如S盒）相结合来增强安全性，因为矩阵乘法可以提高密文的扩散性。很多现代密码（如AES和Twofish）也使用矩阵乘法来增加扩展性。

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


