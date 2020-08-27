## 培根密码简介

培根密码是弗朗西斯·培根在1605年设计的消息编码方式。培根密码将消息隐藏到文本的表现方式中，而不是文本的内容中。

为了对消息进行编码，需要将明文中的每个字母按照下方的编码表进行编码。明文中的每个字母都会转换成一组5个的a/b字母。

<p style="text-align:center;"><img width="400px" src="../image/BaconCipher-1.png" /></p>

除此之外，还有第二种编码表，与第一种编码表不同的是，在第二种编码表里I与J、U与V皆有不同编号。

<p style="text-align:center;"><img width="400px" src="../image/BaconCipher-2.png" /></p>

加密者需使用两种不同字体，分别代表A和B。准备好一篇包含相同AB字数的假信息后，按照密文格式化假信息，即依密文中每个字母是A还是B分别套用两种字体。

解密时，将上述方法倒转。所有字体一转回A，字体二转回B，以后再按上表拼回字母。

法兰西斯·培根另外准备了一种方法，其将大小写分别看作A与B，可用于无法使用不同字体的场合（例如只能处理纯文本时）。但这样比起字体不同更容易被看出来，而且和语言对大小写的要求也不太兼容。

培根密码本质上是将二进制信息通过样式的区别，加在了正常书写之上。培根密码所包含的信息可以和用于承载其的文章完全无关。

## 培根密码示例

!!! Tip "举例"

	**使用培根密码加密单词：`civilizations`**

首先根据对照表写出明文对应的AB字母：

```
AAABA ABAAA BABAB ABAAA ABABB ABAAA BBAAB AAAAA BAABB ABAAA ABBBA ABBAB BAABA
```

将B转换为小写:

```
AAAbA AbAAA bAbAb AbAAA AbAbb AbAAA bbAAb AAAAA bAAbb AbAAA AbbbA AbbAb bAAbA
```

此时任意选取一段英文句子，由于培根密码是1个字母对应5个字母（比方说A对应aaaaa）所以要求句子的字母总个数为明文个数的五倍，即所选句子要和上面AB字符串长度相同

例如明文：civilizations有13个字母，所以选取的句子为`13*5=65`个字母长度。

此时我们选取了句子（载体）：`my interest is in the future because i am going to spend the rest of my life ttere`

再将AB字符串附加到句子上（呈现方式为大小写）：`MY InTErEST iS iN tHe FUTUrE beCaUSE i aM GoING TO sPEnd ThE RESt of MY liFe tTErE`

!!! Tip "注意"

	**在本例中，仅使用了大小写来表现培根密码中的A和B，其实我们也可以使用不同的字体，是否加粗来表现。**
	
	**例如：** 
	
	<p style="text-align:center;"><img width="650px" src="../image/BaconCipher-3.png" /></p>