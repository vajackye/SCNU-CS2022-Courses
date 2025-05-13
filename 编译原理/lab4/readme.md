* exe执行程序从：[https://wwpw.lanzoub.com/ixsud2hcdreb](https://wwpw.lanzoub.com/ixsud2hcdreb)下载。exe打开后左上角菜单查看使用说明。
* 测试样例：
  ```c++
	样例1：S -> ( S ) S | @
	样例2：A -> ( A ) | a
	样例3：
	E -> E + T
	T -> a
  ```
* 注意的小bug：在**LR1**求解闭包部分`LR1GetClosure()`，求follow集合如果存在多重空@情况，多个follow元素的纠正。只需要修改10行以内的代码。请自行完成（已解决，忘更新了）。


* 2025.5.1做项目时发现bug：
* 对于LR0，LR1求解DFA时对于空的处理不正确（约要改少于10行代码）。对于空，直接将空判断归类到规约判断内。eg：
  ```c++
  if(item.dotpos == item.right.size() || item.right[0] == "@"){
  	//认为规约项目
  	continue;
  }
