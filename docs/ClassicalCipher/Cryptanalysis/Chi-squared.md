## 卡方统计简介

卡方统计是衡量两种分类概率分布相似程度的指标，如果两种分类的分布相同则卡方统计为0，如果分布非常不同，则会产生更高的数值，公式如下：

<p style="text-align:center;"><img width="300px" src="../image/Chi-square-1.png" /></p>

其中，C<sub>A</sub>是字母A的计数（不是概率），E<sub>A</sub>是字母A的预期计数。 **卡方统计量是由每个字母实际出现次数和预期出现次数之差的平方除以预期出现次数的和。**

我们知道正常的英文文本中每个字符出现的概率，而卡方统计使用的是计数却不是概率，因此我们首先需要将概率转换为预期次数。下列表格为英文字母和它们在英文文本中出现的频率：

<p style="text-align:center;"><img width="350px" src="../image/Chi-square-3.png" /></p>

---

## 卡方统计举例

例如：正常英文文本中E的出现概率为0.127，那我们可以通过概率乘以密文长度计算出在100个英文文本中会出现12.7次字母E。

!!! Tip "例题"

	请计算以下文本中A的 **卡方统计量**：

	**aoljhlzhyjpwolypzvulvmaollhysplzaruvduhukzptwslzajpwoly**
	**zpapzhafwlvmzbizapabapvujpwolypudopjolhjoslaalypuaolwsh**
	**pualeapzzopmalkhjlyahpuubtilyvmwshjlzkvduaolhswohila**

	（共162个字符）

我们可以看到字母A出现了18次，如果它是英文，我们预计它会出现162 * 0.082 = 13.284次，根据公式我们可以计算出：

<p style="text-align:center;"><img width="300px" src="../image/Chi-square-2.png" /></p>

接下来再对其他字母执行此过程，然后将26个字母的卡方统计量相加。得到的结果是1634.09。

---

## 破解凯撒密码

凯撒密码密钥空间较小，只有26种可能，因此我们可以暴力破解凯撒加密。

!!! Tip "例题"

	请破解一段凯撒加密的密文：

	**aoljhlzhyjpwolypzvulvmaollhysplzaruvduhukzptwslzajpwoly**
	**zpapzhafwlvmzbizapabapvujpwolypudopjolhjoslaalypuaolwsh**
	**pualeapzzopmalkhjlyahpuubtilyvmwshjlzkvduaolhswohila**


我们首先计算使用密钥1的卡方统计量，依次类推、直到计算到密钥25，如下表所示：


```
decryption key        plaintext          chi-squared
-------------------------------------------------------------
0      AOLJHLZHYJPWOLYPZVULVMAOL ...    1634.09
1      ZNKIGKYGXIOVNKXOYUTKULZNK ...    3441.13
2      YMJHFJXFWHNUMJWNXTSJTKYMJ ...    2973.71
3      XLIGEIWEVGMTLIVMWSRISJXLI ...    1551.67
4      WKHFDHVDUFLSKHULVRQHRIWKH ...    1199.40
5      VJGECGUCTEKRJGTKUQPGQHVJG ...    1466.62
6      UIFDBFTBSDJQIFSJTPOFPGUIF ...    1782.26
7      THECAESARCIPHERISONEOFTHE ...      33.67
8      SGDBZDRZQBHOGDQHRNMDNESGD ...    1747.07
9      RFCAYCQYPAGNFCPGQMLCMDRFC ...    1386.62
10     QEBZXBPXOZFMEBOFPLKBLCQEB ...    3423.96
11     PDAYWAOWNYELDANEOKJAKBPDA ...     809.38
12     OCZXVZNVMXDKCZMDNJIZJAOCZ ...    4646.96
13     NBYWUYMULWCJBYLCMIHYIZNBY ...     724.11
14     MAXVTXLTKVBIAXKBLHGXHYMAX ...    2159.43
15     LZWUSWKSJUAHZWJAKGFWGXLZW ...    1787.26
16     KYVTRVJRITZGYVIZJFEVFWKYV ...    3527.17
17     JXUSQUIQHSYFXUHYIEDUEVJXU ...    2967.66
18     IWTRPTHPGRXEWTGXHDCTDUIWT ...    1368.70
19     HVSQOSGOFQWDVSFWGCBSCTHVS ...     929.17
20     GURPNRFNEPVCUREVFBARBSGUR ...     461.19
21     FTQOMQEMDOUBTQDUEAZQARFTQ ...    4395.68
22     ESPNLPDLCNTASPCTDZYPZQESP ...     703.43
23     DROMKOCKBMSZROBSCYXOYPDRO ...    1226.79
24     CQNLJNBJALRYQNARBXWNXOCQN ...    1817.85
25     BPMKIMAIZKQXPMZQAWVMWNBPM ...    2939.16
```

通过分析上表，可以看到密钥7的卡方统计量最接近0，因此推断出加密的密钥为7。

---


