
##分组密码简介

分组密码是一种拆解字母的方法，以便一个字母能被两个或多个符号表示。例如：a可以用01代替、b可以用02代替，依次类推我们得到加密表。

<p style="text-align:center;"><img src="../image/FractionatingCiphers-1.png" /></p>

!!! Tip "举例"

	**请加密文本`flee at once`**
	
通过查表，我们将每个字母转换为两位的数字得到：`06120505 0120 15140305`
	
显然，这段密文非常容易破解，但我们通过增加密钥复杂度来提高破解难度。除此之外，我们刚刚使用的简单分组密码还存在一个缺陷，它会受到频率分析的攻击。我们分析这段密文的时候不能对单个数字的分析，而是将两位数字看做一个整理，例如05在密文中出现的次数最多，而它的确是英文中频率最高的字母e。

虽然分组密码有这些缺陷，但它可以使其他密码更加安全。如将分组与列换位密码结合。

!!! Tip "举例"

	**请使用列换位密码（密钥：apple）和分组密码加密文本`flee at once`**

经过分组加密后的密文为：`06120505 0120 15140305`，我们再使用列换位密码对其进行加密：

<p style="text-align:center;"><img width="120px" src="../image/FractionatingCiphers-2.png" /></p>

得到密文`0524 0115 2050 6000 1513`

现在使用频率分析法也无法破解这段密文，因为其中的`50 60`为不可用状态。除非我们先进行列换位破解，再进行频率分析。

分组密码不仅能让我们将单词拆分，而且还能将字母拆分，允许我们使用较小的字符集表示一组字母（例如之前的例子我们使用0-9十个字符表示26个字母）。

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