## ADFGX密码简介

ADFGX密码是德军在第一次世界大战期间使用的密码，它和ADFGVX十分相似。ADFGX密码也是一种分组密码，它将明文字符转换为`ADFGX`中的两个字符。`ADFGX`这五个字母并不是随意选择的，而是因为这五个字母在摩斯电码里听起来非常特殊，便于手抄员识别。

## ADFGX密码示例

首先构造密钥方阵：

```
    A D F G X
    ---------
A | p h q g m 
D | e a y n o 
F | f d x k r
G | c v s z w 
X | b u t i l
```

假设我们要加密字母`a`，先取出`a`同一行最左侧的字母`D`，在取出`a`同一列最顶部的字母`D`。依次类推，`attack`被加密为`DD XF XF DD GA FG`。现在它只是一个稍微特殊点的简单替换密码，使用爬山算法很容易破解。

接下来再使用密钥为`GERMAN`的[列换位密码](../../TranspositionCiphers/ColumnarTranspositionCipher/)对其再进行一次加密：

```
G E R M A N       --->      A E G M N R
-----------       --->      -----------
D D X F X F       --->      X D D F F X
D D G A F G       --->      F D D A G G
```

则加密后的密文为：`XF DD DD FA FG XG`

## ADFGX密码的程序实现

```
>>>from pycipher import ADFGX
>>>a = ADFGX('phqgmeaylnofdxkrcvszwbuti','HELLO')
>>>a.encipher('defend the east wall of the castle')
'FDFDDXGFDDGFDFDDGDAADXADAXAGADDDDDADGDGDGXAGGFXAAXDFGGGD'
>>>a.decipher(_)
'DEFENDTHEEASTWALLOFTHECASTLE'
```

## ADFGX密码的密码分析

在CRYPTO 84的密码学论文集《ADFGVX密码系统的密码分析》一文中讨论了ADFGVX密码的密码分析。但是，这篇论文并没有公开，此处会尽快更新。


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


