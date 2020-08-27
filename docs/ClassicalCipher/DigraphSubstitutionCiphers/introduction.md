
##有向图密码简介

有向图密码类似于替换密码，只不过在替换时不是单个字母替换，而是将相邻两个字母合并为二元组一起进行替换。

我们来看一个最简单的有向图密码：

<p style="text-align:center;"><img src="../image/DigraphSubstitutionCiphers-1.png" /></p>

假设我们要加密的二元组为`he`。则在上表顶部查找`h`、在上表左侧查找`e`，在这两行(列)的交叉位置得到密文二元组为`NY`。

!!! Tip "举例"

	**请加密明文`simple examplex`**
	
首先需要将明文拆分为明文二元组：`si mp le ex am pl e`，因为最后一个二元组只有一位，所以需要使用`x`填充：`si mp le ex am pl ex`。

按照上述加密方法，依次加密每个明文二元组得到：

<p style="text-align:center;"><img width=60% src="../image/DigraphSubstitutionCiphers-2.png" /></p>
	
显然，字母频率分析法对这种加密方式无效。但是我们现在的密钥方阵太过于庞大，不管对于加密方还是解密方都不便使用，所以我们在有向图密码一章中详细介绍了其他方法来生成密钥方阵。

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