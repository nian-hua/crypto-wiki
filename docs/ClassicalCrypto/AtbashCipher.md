## 埃特巴什码简介

埃特巴什码是一种固定密钥的替换密码，其明文字母表与密文字母表正好相反，即所有的A都会被替换成Z，所有的B都会被替换成Y，依次类推。

**埃特巴什码没有安全性可言，因为它的密钥是固定的。**

## 埃特巴什码的算法

埃特巴什码的替换规则是：

```
ABCDEFGHIJKLMNOPQRSTUVWXYZ
ZYXWVUTSRQPONMLKJIHGFEDCBA
```
如果要加密一段明文，我们首先在上面找到明文，然后使用第二行的字母代替当前的明文字母。

!!! Tip "举例"

	**请使用埃特巴什码加密ATTACK AT DAWN**

首先从明文字母表中寻找A，然后查看A对应的密文字母为Z，依次加密每个明文字母，最后我们得到加密后的密文

```
ZGGZXP ZG WZDM
```

解密消息的过程和加密的过程完全相同。

## 埃特巴什码的程序实现

```python
>>>from pycipher import Atbash
>>>Atbash().encipher('defend the east wall of the castle')
'wvuvmwgsvvzhgdzoolugsvxzhgov'
>>>Atbash().decipher('wvuvmwgsvvzhgdzoolugsvxzhgov')
'defendtheeastwallofthecastle'
```

## 埃特巴什码的密码分析

如果能确认一段密文是使用埃特巴什码加密，那就可以简单的解密它（密钥只有一种情况）。

