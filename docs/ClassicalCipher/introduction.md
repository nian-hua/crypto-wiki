
!!! Tip "注意"

	**虽然古典密码在现实生活中已经很少被使用，但古典密码学的密码分析方法值得我们借鉴学习**

古典密码学是密码学中的一个类型，其大部分加密方式都是利用置换式密码或代换式密码，有时则是两者的混合。

古典密码在历史中经常使用，但现代已经很少使用，大部分的已经不再安全了。一般而言，古典密码是基于一个拼音字母（像是 A-Z）、动手操作或是简单的设备。

经典密码通常很容易被破解。许多经典密码可单单经由密文而破解，所以它们容易受到唯密文攻击。

有些经典密码（像是凯撒密码）的密钥个数有限，所以这类密码可以暴力破解尝试所有的密钥。

![intro](image/introduction/intro.jpg)

代换式密码有比较大的密钥数，但是容易被频率分析，因为每个密码字母各代表了一个明文字母。

多字母代换式密码（像是维吉尼亚密码）使用多个替换防止了简单的频率分析，然而我们可以使用更先进的卡西斯基测试来破解这类密码。

![kasiski](image/introduction/kasiski.jpg)

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