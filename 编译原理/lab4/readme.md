* exe执行程序从：[https://wwpw.lanzoub.com/ixsud2hcdreb](https://wwpw.lanzoub.com/ixsud2hcdreb)下载。exe打开后左上角菜单查看使用说明。
* 测试样例：
  ```c++
	样例1：S -> ( S ) S | @
	样例2：A -> ( A ) | a
	样例3：
	E -> E + T
	T -> a
  ```
* 注意的小bug：在**LR1**求解闭包部分`LR1GetClosure()`，求follow集合如果存在多重空@情况，多个follow元素的纠正。只需要修改10行以内的代码。请自行完成。

