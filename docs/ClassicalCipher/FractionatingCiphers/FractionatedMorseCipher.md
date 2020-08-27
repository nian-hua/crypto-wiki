## 分组摩斯密码简介

分组摩斯密码首先将明文转换为摩斯编码，然后将固定长度的摩斯码加密回字母。这意味着明文字母和密文字母已经不是一一对应的关系，比常见的替换密码更加安全。但就现在而言仍有方法对其进行破解。

## 分组摩斯密码示例

!!! Tip "举例"

	**使用密钥`ROUNDTABLECFGHIJKMPQSVWXYZ`加密`defend the east`**

首先将明文转换为摩斯码，字符之间使用`x`分割、单词之间使用`xx`分割。

```
明文: defend the east
摩斯: -..x.x..-.x.x-.x-..xx-x....x.xx.x.-x...x-x
```

现在根据密钥生成加密表：

```
R O U N D T A B L E C F G H I J K M P Q S V W X Y Z
. . . . . . . . . - - - - - - - - - x x x x x x x x
. . . - - - x x x . . . - - - x x x . . . - - - x x
. - x . - x . - x . - x . - x . - x . - x . - x . -
```

我们将摩斯码对应到加密表中，如前三个摩斯码为`-..`转换到密文为`E`，接下来的三个摩斯码为`x.x`转为到密文为`S`，依次类推得到所有密文`ESOAVVLJRSSTRX`。

## 分组摩斯密码的密码分析

分组摩斯密码的分析并不难，我们先看如下的摩斯分组加密表：

```
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
. . . . . . . . . - - - - - - - - - x x x x x x x x
. . . - - - x x x . . . - - - x x x . . . - - - x x
. - x . - x . - x . - x . - x . - x . - x . - x . -
```

通过上表，可以发现某些密文字母组合是不可能的，例如RS，RT，...，RZ。因为我们的明文摩斯编码后中不可能包含xxx。

同样不存在组合还有：IS，IT，IZ，CY，CZ，FY，FZ，OY，OZ等

未完待续...

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


