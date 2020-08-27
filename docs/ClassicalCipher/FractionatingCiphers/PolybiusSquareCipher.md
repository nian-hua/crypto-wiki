## 波利比奥斯方阵密码简介

波利比奥斯方阵密码在本质上与替换密码相同，但是每个明文字符均被加密为两个密文字符。该密码的安全性较低，当明文长度大于100字符时，甚至可以使用手动进行破解。

## 波利比奥斯方阵密码示例

!!! Tip "举例"

	**使用如下的密钥矩阵加密`defend the east wall of the castle`**
	```
	   A B C D E
	   - - - - -
	A| p h q g m
	B| e a y l n
	C| o f d x k
	D| r c v s z
	E| w b u t i
	```
加密过程：

```
明文:  d e f e n d  t h e  e a s t  w a l l  o f  t h e  c a s t l e 
密文:  CCBACBBABECC EDABBA BABBDDED EABBBDBD CACB EDABBA DBBBDDEDBDBA
```

加密过程显而易见，每个明文字母均被替换为当前行首和列首的两个密文字符，如`d->CC`

!!! Tip "举例"

	**如果像上文一样生成密钥矩阵，则我们需要记住25个字母。为了简化记忆，我们可以选取一个密钥，然后将其余字母按字母表顺序排列。如密钥为`zebra`,则可以将密钥扩展为：`zebracdfghiklmnopqstuvwxy`**

依次取密钥中五个字符为一行，生成密钥矩阵即可。

## 波利比奥斯方阵密码的程序实现

```python
>>>from pycipher import PolybiusSquare
>>>p = PolybiusSquare('phqgiumeaylnofdxkrcvstzwb',5,'ABCDE')
>>>p.encipher('defend the east wall of the castle')
'CEBCCDBCCBCEEBABBCBCBDEAEBEDBDCACACCCDEBABBCDDBDEAEBCABC'
>>>p.decipher('CEBCCDBCCBCEEBABBCBCBDEAEBEDBDCACACCCDEBABBCDDBDEAEBCABC')
'DEFENDTHEEASTWALLOFTHECASTLE'
```

运行示例：

<p style="text-align:center;"><img src="../image/PolybiusSquareCipher-1.png" /></p>

## 波利比奥斯方阵密码的密码分析

因为波利比奥斯方阵密码只是一种替换密码的变形，所以很容易被破解。此处可以参考简单替换密码的密码分析。

**有什么疑惑欢迎下方留言呀！**
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


