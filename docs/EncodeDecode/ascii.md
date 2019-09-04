## ASCII简介

ASCII编码是美国信息交换标准代码，主要用于显示现代英语和其他西欧语言。

因为1位二进制数可以表示(2<sup>1</sup>)=2种状态：0、1；

而2位二进制数可以表示（2<sup>2</sup>）=4种状态：00、01、10、11；

依次类推，7位二进制 数可以表示(2<sup>7</sup>)=128种状态，每种状态都唯一地编为一个7位的二进制码，对应一个字符（或控制码），这些码可以排列成一个十进制序号0～127。

所以，7位ASCII码是用七位二进制数进行编码的，可以表示127个字符。

【其实每个人都可以约定一套自己的编码，但如果大家不想相互通信的时候造成混乱，那必须使用相同的编码规则】

## ASCII字符集

![ascii_code_chart](image/ascii_code_char.jpeg)

举个例子:

```
请解码以下ASCII：
102 108 97 103 123 97 115 99 105 105 95 105 115 95 111 107 125
```

**[点此进入ASCII在线工具](http://www.ab126.com/goju/1711.html)**

## Python编码解码ASCII

```
ascii_list = [102,108,97,103,123,97,115,99,105,105,95,105,115,95,111,107,125]
string = ''
for i in ascii_list:
	string += chr(i)
print string
ascii_list = []
for i in string:
	ascii_list.append(ord(i))
print ascii_list
```