
# 关于我们

我们是一个热爱密码学的研究团队，希望自己能在密码学的世界里贡献自己的一份力量。

同时写下这个博客，是为了能让更少的人走弯路。

![qrcode](images/qrcode.png)

最后送大家一段励志名言共勉：`Fdmh bxcwuh,Fdmh yvvngfb.`

**Ps.密文太短，可能解不出来~大家加油！！（解出来的欢迎下方留言）**

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