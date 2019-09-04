## 频率分析简介

频率分析是指研究字母或者字母组合在文本中出现的频率，使用频率分析可以破解部分古典密码。频率分析基于如下原理：在任何一种书面语言中，不同的字母或字母组合出现的频率各不相同。而且，对于以这种语言书写的任意一段文本，都具有大致相同的特征字母分布。比如，在英语中，字母E出现的频率很高，而X则出现得较少。

英语中出现频率最高的12个字母可以简记为“ETAOIN SHRDLU”，如下图所示为英文的字母概率分布。

<p style="text-align:center;"><img width="500px" src="../image/frequencyAnalysi-1.png" /></p>

## 频率分析举例

我们以凯撒加密来举例，使用频率分析来破解凯撒密码：

!!! Tip "例题"

	**Eve截获了Alice和Bob的通讯，这段密文使用了凯撒。**
	
	```
	if mjlft ufmmjoh mjft pof ebz if xbout up nblf gvo pg uif gbsnfst tp if tipvut  xpmg xpmg xpmg jt dpnjoh  
	uif ljoe gbsnfst bsf xpsljoh jo uif gjfme uifz ifbs uif tipvu boe ivssz up ifmq uif cpz  uifsf jto u b x
	pmg j n kpljoh uif gbsfst bsf bohsz boe hp cbdl up uifjs gjfme bgufs b xijmf uif cjz tipvut bhbjo  xpmg 
	xpmg xpmg jt dpnjoh  boe uif gbsnfst dpnf boe bsf difbufe bhbjo uif cpz mbvhit boe mbvhit uifz tbz  zpv 
	ufmm mjft xf xjmm opu cfmjfwf zpv mbufs b xpmg sfbmmz dpnft uif cpz jt wfsz tdbsfe  xpmg xpmg xpmg jt dp
	njoh  uif cpz tipvut boe tipvut  ifmq ifmq
	```
我们首先使用频率分析，对密文中的每个字母出现的次数进行统计：

<p style="text-align:center;"><img width="600px" src="../image/frequencyAnalysi-2.png" /></p>

接下来对照一下正常的英文频率，如图：

<p style="text-align:center;"><img width="600px" src="../image/frequencyAnalysi-3.png" /></p>

通过分析频率图我们可以发现，我们如果将加密后的所有字母向前移动一位即可得到明文，使用密钥1对凯撒加密进行解密：

<p style="text-align:center;"><img width="800px" src="../image/frequencyAnalysi-4.jpg" /></p>

!!! Tip "注意"

	**关于加密算法的问题，请移步至凯撒加密**

!!! Warning "扩展"

	**除了分析单一字母的频率外，我们还可以分析双字母的频率以及三字母的频率**
