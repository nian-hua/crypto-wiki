### 简介

XXencode将输入文本以每三个字节为单位进行编码。如果最后剩下的资料少于三个字节，不够的部份用零补齐。这三个字节共有24个Bit，以6bit为单位分为4个组，每个组以十进制来表示所出现的数值只会落在0到63之间。以所对应值的位置字符代替。它所选择的可打印字符是：+-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz，一共64个字符。跟base64打印字符相比，就是UUencode多一个“-” 字符，少一个”/” 字符。

![XXencode.png](image/XXencode.png)

### 扩展
每60个编码输出（相当于45个输入字节）将输出为独立一行，每行的开头会加上长度字符，除了最后一行之外，长度字符都应该是h这个字符（45，刚好是64字母表中第45位h字符），最后一行的长度字符为剩下的字节数目在64字符中位值所代表的字符。

在线[XXencode](http://web.chacuo.net/charsetxxencode)编码解码。