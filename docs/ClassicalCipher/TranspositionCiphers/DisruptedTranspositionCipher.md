## 中断换位密码简介

中断换位密码是其他换位密码的进一步复杂化。在中断换位密码中，所有行均以不规律方式填充。这导致了明文的转换异常复杂。

!!! Tip "例题"

	**下面我们以明文"we confirm the delivery of the documents and will send further instructions x"**

	**密钥 CONSPIRACY 为例：**

首先，我们确定要填充的行数和列数。接下来，我们填充一行，直到达到密钥中排位第一的字母序列，在下一行我们填充至密钥中的排位第二的字母序列。填充完最后一行后，我们再将每行中的空白位置进行填充。

![DisruptedTranspositionCipher-1](image/DisruptedTranspositionCipher-1.png)

接下来，我们在空白地方填充无意义字母即可。

![DisruptedTranspositionCipher-2](image/DisruptedTranspositionCipher-2.png)

`密文： RSVRHNWMTRECMZCHLJTFQLHFNCIEOOCNESHYDUENVETFBSIFIXGMOTDFDVTVBRKKQ`
















