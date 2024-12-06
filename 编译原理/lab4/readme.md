* exe执行程序从：[byyl4](https://wwpw.lanzoub.com/ixsud2hcdreb)下载。exe打开后左上角菜单查看使用说明。
* 测试样例：
  ```c++
	样例1：S -> ( S ) S | @
	样例2：A -> ( A ) | a
	样例3：
	E -> E + T
	T -> a
  ```
* 上传的是第一版，注意的小bug：在**LR1**求解闭包部分`LR1GetClosure()`，求follow集合如果存在多重空@情况，多个follow元素的纠正。只需要修改10行以内的代码。请自行完成。
* 头文件不上传，QT版本不上传，部分头文件的定义见下面：

```c++
//LR0中每一个规则存储结构
struct ItemLR0 {
	string left; //规则左部
	vector<string> right; //规则右部
	int dotPos = 0; //点的位置

	//比较两个Item是否相同
	bool operator==(const ItemLR0& other) const {
		return left == other.left && right == other.right && dotPos == other.dotPos;
	}

};

//....其他部分

unordered_map<string, vector<vector<string>>> langMp;//存储文法。格式如下：<规则左部,规则右部或的每一条规则<每一条或的规则的具体细化>
vector<string> lgName; //所有非终结符的文法记载
unordered_map<string, unordered_set<string>> firstSet; //每个非终结符的first集合
unordered_map<string, unordered_set<string>> followSet;//每个非终结符的follow集合

//LR0的存储结构
//对于LR0TransTable，仅仅是为了在QT上展示关系罢了。否则都不需要开这个存储结构
unordered_map<int, unordered_set<ItemLR0>> LR0DfaStates;//LR0每个状态对应的项目集
unordered_map<int, unordered_map<string, int>>LR0TransTable; //LR0状态转移表，每个状态通过不同操作符跳到对应下一个状态

//....其他部分
```
