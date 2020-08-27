密码学是研究如何隐密地传递信息的学科，可分为古典密码学和现代密码学。

古典密码学主要关注信息的保密书写和传递，以及与其相对应的破译方法。

而现代密码学不只关注信息保密问题，还同时涉及信息完整性验证（消息验证码）、信息发布的不可抵赖性（数字签名）、以及在分布式计算中产生的来源于内部和外部的攻击的所有信息安全问题。


crypto-wiki中主要包括了CTF中常见的编解码方式、加解密方式以及攻击方法。

其中，古典密码主要包含以下两个方面:

- 替换密码
- 代换密码

而现代密码学可包括:

- 对称加密
- 非对称加密
- 哈希函数
- 数字签名

攻击类型可分为:

| 攻击类型     | 说明                                       |
| ------------ | ------------------------------------------ |
| 唯密文攻击   | 只拥有密文                                 |
| 已知明文攻击 | 拥有密文与对应的明文                       |
| 选择明文攻击 | 拥有加密权限，能够对明文加密后获得相应密文 |
| 选择密文攻击 | 拥有解密权限，能够对密文解密后获得相应明文 |


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