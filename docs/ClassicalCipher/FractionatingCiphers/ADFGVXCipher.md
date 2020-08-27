## ADFGVX密码简介

ADFGVX密码是对ADFGX密码的扩展，它将改良后的波利比奥斯方阵与列换位密码相结合。该密码使用了`ADFGVX`这六个字母，这些字母是故意选择的，它们在摩斯电码里听起来非常特殊，便于手抄员识别。

## ADFGVX密码示例

首先构造密钥方阵：

```
    A D F G V X
    -----------
A | p h 0 q g 6
D | 4 m e a 1 y
F | l 2 n o f d
G | x k r 3 c v
V | s 5 z w 7 b
X | j 9 u t i 8
```

显然，`attack`被加密为`DG XG XG DG GV GD`。现在它只是一个稍微特殊点的简单替换密码，使用爬山算法很容易破解。

接下来再使用密钥为`GERMAN`的[列换位密码](../../TranspositionCiphers/ColumnarTranspositionCipher/)对其再进行一次加密：

```
G E R M A N       --->      A E G M N R
-----------       --->      -----------
D G X G X G       --->      X G D G G X
D G G V G D       --->      G G D V D G
```

则加密后的密文为：`XG GG DD GV GD XG`。

下面我们再来举个简单的例子:

!!! Tip "举例"

	**使用如下的密钥矩阵加密`DEFEND THE EAST WALL OF THE CASTLE`**
	```
		A D F G V X
		-----------
	A | p h 0 q g 6
	D | 4 m e a 1 y
	F | l 2 n o f d
	G | x k r 3 c v
	V | s 5 z w 7 b
	X | j 9 u t i 8
	```

首先按照密钥方阵对明文进行加密得到`FXDFFVDFFFFXXGADDFDFDGVAXGVGDGFAFAFGFVXGADDFGVDGVAXGFADF`。接下来使用`GERMAN`进行列换位加密。

```
G E R M A N       --->      A E G M N R
-----------       --->      -----------
F X D F F V       --->      F X F F V D
D F F F F X       --->      F F D F X F
X G A D D F       --->      D G X D F A
D F D G V A       --->      V F D G A D
X G V G D G       --->      D G X G G V
F A F A F G       --->      F A F A G F
F V X G A D       --->      A V F G D X
D F G V D G       --->      D F D V G G
V A X G F A       --->      F A V G A X
D F               --->        F D 
```

最终密文为：`FFDVDFADFXFGFGAVFAFFDXDXFFDVDFFDGGAGVGVXFAGGDGADFADVFXGX`。

## ADFGVX密码的程序实现

```
>>>from pycipher import ADFGVX
>>>a = ADFGVX('ph0qg64mea1yl2nofdxkr3cvs5zw7bj9uti8','HELLO')
>>>a.encipher('defend the east wall of the castle')
'XDXDGVAFDDGFVFDDGFGAVXFDFXFVGFVDGFFFGDADAXFVAFFAFXGFGGAD'
>>>a.decipher(_)
'DEFENDTHEEASTWALLOFTHECASTLE'
```

## ADFGVX密码的密码分析

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


