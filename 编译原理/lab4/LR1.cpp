#include "LR1.h"

using namespace std;

//unordered_map<string, vector<vector<string>>> langMp;//存储文法。格式如下：<规则左部,规则右部或的每一条规则<每一条或的规则的具体细化>
//vector<string> lgName; //所有非终结符的文法记载
//unordered_map<string, unordered_set<string>> firstSet; //每个非终结符的first集合
//unordered_map<string, unordered_set<string>> followSet;//每个非终结符的follow集合
//unordered_map<int, unordered_set<Item>> LR0DfaStates;//每个状态对应的项目集
//unordered_map<int, unordered_map<string, int>>LR0TransTable; //状态转移表，每个状态通过不同操作符跳到对应下一个状态


void LR1::init()
{
	langMp.clear(); //存储每一条文法
	lgName.clear(); //所有非终结符的文法记载
	firstSet.clear(); //每个非终结符的first集合
	followSet.clear(); //每个非终结符的follow集合
	LR0StateID = 0; //LR0的最大状态编号
}

void LR1::analysis()
{
	string ss;
	bool flag = true; //用来标记是否是第一条文法

	while (getline(cin, ss)) {
		if (ss.size() <= 0) break;
		string lrname = splitLang(ss);
		if (flag) {
			flag = false;
			this->startLang = lrname; //存储文法开始符号
		}
		lgName.push_back(lrname); //存储所有非终结符
	}
	//getline(cin, ss);
	//splitLang(ss);
	//printLang();
	getFirstSet();
	getFollowSet();
	//printLang();
	bool ok = judgeDieFirst();
	if (ok) {
		cout << "存在死递归" << endl;
		return ;
	}
	//先判定是否需要修改文法开始符号
	newStart();


	DfaLR0();

	bool isSR = IsSLR1();
	if (!isSR) cout << "非SLR1文法" << endl;

	return ;
}

//分解文法
string LR1::splitLang(string lang) {
	vector<string> tmp;
	int idx = 0;
	string lrgName = "";
	string rrgName = "";
	for (int i = 0; i < lang.size(); i++) {
		if (lang[i] == '-') {
			idx = i + 2;//直接跳到下一个规则
			break;
		}
		if (isspace(lang[i])) continue;
		lrgName += lang[i];
	}

	//分割右部
	for (int i = idx; i < lang.size(); i++) {
		//说明是下一个字符，加一个特判。避免: A | B 或后有空格
		if (isspace(lang[i]) && rrgName.size() > 0) {
			//存入
			tmp.push_back(rrgName);
			rrgName.clear();
			continue;
		}
		// 说明是本条文法下一个规则，待会处理 需要修改。
		if (lang[i] == '|') {
			if (rrgName.size() > 0) {
				tmp.push_back(rrgName);
				rrgName.clear();
			}
			langMp[lrgName].push_back(tmp);
			tmp.clear();
			continue;
		}
		if (!isspace(lang[i])) rrgName += lang[i];
		if (i == lang.size() - 1) {
			if (rrgName.size() > 0) {
				tmp.push_back(rrgName);
				rrgName.clear();
			}
			langMp[lrgName].push_back(tmp);
		}
	}
	return lrgName;
}

//求first集合
void LR1::getFirstSet()
{
	bool changed = true; //检查first集合是否还有变化
	while (changed) {
		changed = false;
		for (const auto & name: lgName) { //遍历每一条文法
			const auto& gram = langMp[name];
			string gramName = name; //获取该文法的左部
			int befSize = firstSet[gramName].size(); //先获取该文法左部的first集合先前元素个数
			for (const auto& line : gram) { //遍历该文法的右部的 或(|) 的每一个规则。
				int isEmp = 0; //判断最后该规则是否含有空
				for (int i = 0; i < line.size(); i++) {  //遍历其中每一个子规则下的每一个符号
					const auto& reg = line[i]; //字符
					
					if (langMp.find(reg) == langMp.end()) { //说明是终结符号
						firstSet[gramName].insert(reg);
						if(firstSet[gramName].size() != befSize) //如果不等于先前的元素个数，说明新加入的元素个数
							changed = true;
						break;
					}
					else { //说明是非终结符号
						unordered_set<string> tmpSet = firstSet[reg]; //获取该非终结符号的first集合
						if (tmpSet.find("@") != tmpSet.end()) { //如果该非终结符号包含空
							//如果不是最后一个非终结符。即：ABc,c是终结符，而非：ABC,C是非终结符
							tmpSet.erase("@"); //剔除空，如果是最后一个非终结符，则不剔除。
							firstSet[gramName].insert(tmpSet.begin(), tmpSet.end());
							isEmp += 1; //含空非终结符号 + 1
							if (befSize != firstSet[gramName].size()) //说明元素有变动
								changed = true;
							continue; //非终结符且包含空，则继续遍历该条规则的下一个字符
						}
						//如果该非终结符是不包含空的@
						firstSet[gramName].insert(tmpSet.begin(), tmpSet.end());
						if (firstSet[gramName].size() != befSize)
							changed = true;
						break; //非空则结束
					}
				}
				//如果该规则包含的非终结字符都含空，则加入空
				if (isEmp == line.size())
					firstSet[gramName].insert("@");
			}
		}
	}
	
}

//判断first集合是否存在死递归
bool LR1::judgeDieFirst(){
	for (const auto& value : firstSet) {
		if (value.second.size() == 0) //确实有死递归。
			return true;
	}
	return false;
}

//求follow集合
void LR1::getFollowSet(){
	//先初始化开始符号
	followSet[startLang].insert("$");
	bool changed = true; //检查follow集合是否还有变化
	while (changed) {
		changed = false;
		for (const auto& notFinal : lgName) { //遍历每一条文法
			const auto& gram = langMp[notFinal]; //获取非终结符的文法
			for (const auto& line : gram) {//获取每一条规则
				for (int i = 0; i < line.size(); i++) {
					const auto& reg = line[i]; //获取每一个字符
					if (langMp.find(reg) == langMp.end()) //说明求得是终结符号follow集，跳过
						continue;

					int befSize = followSet[reg].size(); //获取原先的follow集合大小
					//下面是求非终结符号follow集合
					int nextIdx = i + 1;
					//当前要求follow的非终结符号已经是最后一个
					if (nextIdx == line.size()) { //如果该非终结字符在最后一个，则加入follow(notFinal)，即文法左部的follow()
						followSet[reg].insert(followSet[notFinal].begin(), followSet[notFinal].end());
						if (befSize != followSet[reg].size()) //集合元素有变化
							changed = true;
						break; 
					}
					string nextReg; //下一个字符
					//下一个是非终结字符
					for (; nextIdx < line.size(); nextIdx++) {
						nextReg = line[nextIdx];
						//下一个是终结字符
						if (firstSet.find(nextReg) == firstSet.end()) { 
							followSet[reg].insert(nextReg);
							if (befSize != followSet[reg].size()) //如果follow集合大小有变化
								changed = true;
							break;
						}
						//下一个是非终结字符
						if (firstSet.find(nextReg) != firstSet.end()) { 
							const auto& nowFtSet = firstSet[nextReg];
							if(nowFtSet.find("@") == nowFtSet.end()) { //说明下一个字符first集不存在空，存储并结束寻找
								followSet[reg].insert(nowFtSet.begin(), nowFtSet.end()); //加入其后first集合
								if (befSize != followSet[reg].size()) //如果大小发生改变
									changed = true;
								break;
							}
							//如果存在空，继续下一个。
							followSet[reg].insert(nowFtSet.begin(), nowFtSet.end());
							followSet[reg].erase("@");
							if (nextIdx == line.size() - 1) { //已经是最后一个非终结符号，则要加入
								followSet[reg].insert(followSet[notFinal].begin(), followSet[notFinal].end());
								if (befSize != followSet[reg].size()) //如果大小发生改变
									changed = true;
								break;
							}
						}
					}
				}
			}
		}
	}
}

//判断文法开始符号是否需要更改
void LR1::newStart()
{
	if (langMp[startLang].size() > 1) {
		string nStart = startLang + "'";
		vector<string> tmp = { startLang };
		langMp[nStart].push_back(tmp);
		firstSet[nStart].insert(firstSet[startLang].begin(), firstSet[startLang].end());
		followSet[nStart].insert("$");
		startLang = nStart;
	}
}

/*-------------------------------- - 判断是否为LR0-----------------------------------------*/
//计算每个项目集的规则闭包，即能推导的情况的项目集
void LR1::getClosureLR0(unordered_set<ItemLR0>& items)
{
	bool changed = true;
	while (changed) {
		changed = false;

		unordered_set<ItemLR0> newItems = items; // 创建新集合，存放当前闭包状态

		for (const auto& item : items) {
			if (item.dotPos < item.right.size()) { //检查点是否在末尾
				string symbol = item.right[item.dotPos]; //点后的符号
				if (langMp.find(symbol) != langMp.end()) { //如果是非终结符号
					for (const auto& rule : langMp[symbol]) { //遍历该符号的每一条规则
						ItemLR0 newItem = { symbol,rule, 0};// 创建新项目，点位置在开头
						if (newItems.find(newItem) == newItems.end()) { //如果该状态内无该项目，则新增
							newItems.insert(newItem);
							changed = true;
						}
					}
				}
			}
		}
		items.insert(newItems.begin(), newItems.end()); //更新闭包状态
	}
}

// GOTOLR0 函数：从状态出发，按符号移进生成新状态
//对每个状态进行符号移进的操作，生成新状态，并进行状态合并
unordered_set<ItemLR0> LR1::GotoLR0(const unordered_set<ItemLR0>& state, const string& symbol) {
	if (symbol == "@") { //前面判断有问题，误入，则弹回去
		cout << "GotoLR0出现了@空" << endl;
		return {};
	}
	unordered_set<ItemLR0>nextState; //下一个状态表

	//遍历目前状态进行移进
	for (const auto& item : state) {
		if (item.dotPos < item.right.size() && item.right[item.dotPos] == symbol) { //判断是不是目标下一个要移动的符号
			//移动点的位置
			ItemLR0 movedItem = item;
			movedItem.dotPos++;
			nextState.insert(movedItem);
		}
	}

	//计算闭包
	getClosureLR0(nextState);

	return nextState;
}

//求LR0的DFA图
void LR1::DfaLR0()
{
	//初始化状态集合
	unordered_set<ItemLR0> startState; //本状态内项目集
	startState.insert({ startLang, langMp[startLang][0], 0 }); // 添加起始项目：（左部符号, 右部规则, 点位置）
	getClosureLR0(startState); //对该状态项目进行求闭包，求出下一步非终结字符包含的项目。
	int stateId = 0; //状态ID

	
	queue<pair<unordered_set<ItemLR0>, int>> stateQueue; //存储状态集合
	stateQueue.push({ startState ,stateId });
	LR0DfaStates[stateId] = startState ;//将每个状态的状态集合存储。dfaState+LR0TransTable刚好组成：每个状态的项目集 + 该状态的项目集通过符号k抵达下一个状态编号


	unordered_map<unordered_set<ItemLR0>, int, hash<unordered_set<ItemLR0>>> StateToId; //用于判断是否是新的状态集合
	StateToId[startState] = stateId++; //起始状态集合

	while (!stateQueue.empty()) {
		pair<unordered_set<ItemLR0>, int> tmp = stateQueue.front();

		unordered_set<ItemLR0> currentState = tmp.first; //当前状态集
		int currentId = tmp.second; //当前状态标号

		stateQueue.pop();

		//收集当前项目集在该LR位置(.)下一个是可移进的符号集合。
		unordered_set<string> symbols;
		for (const auto& item : currentState) {
			if (item.right.size() == 1&& item.right[0] == "@") continue; //空@
			if (item.dotPos < item.right.size()) {
				symbols.insert(item.right[item.dotPos]);
			}
		}

		//开始对每个可移进符号进行该状态项目集合的遍历，当前下一个移进符号为symbol时，则新状态。
		for (const auto& symbol : symbols) {
			unordered_set<ItemLR0> nextState = GotoLR0(currentState, symbol); //通过gotolr0函数求解下一个状态的项目集

			if (nextState.empty()) continue; //无法移进。不存在下一个状态

			//判断是否为新的状态集合
			if (StateToId.find(nextState) == StateToId.end()) {
				StateToId[nextState] = stateId; //存入状态记录
				LR0DfaStates[stateId] = nextState; //状态表记录
				LR0TransTable[currentId][symbol] = stateId; //更新状态转移表
				stateQueue.push({ nextState, stateId });
				stateId++;
			}
			else { //不是新集合也要更新状态转换表
				if(LR0TransTable[currentId].find(symbol) == LR0TransTable[currentId].end()) //保证无重复id转移出现
					LR0TransTable[currentId][symbol] = StateToId[nextState]; //更新状态转移表
			}
		}
	}
	LR0StateID = stateId - 1;
}

/*-------------------------------- - 判断是否为SLR1-----------------------------------------*/
//判断是否为SLR1文法
//核心：判断follow集合是否有移进-规约冲突，规约-规约冲突。
bool LR1::IsSLR1()
{
	bool isSlr1 = true; //假定是slr1文法

	//unordered_map<int, unordered_set<Item>> LR0DfaStates;
	for (const auto& state : LR0DfaStates) { //遍历每一个状态（项目集）
		int stateId = state.first;
		unordered_set<ItemLR0> items = state.second; //当前项目状态集

		unordered_set<string> finalFolSet; //存储规约项目左部对应的 follow 集合
		unordered_set<string> shiftFirstSet; //存储移进项目对应的first集合。如果二者有交集，说明有移进-规约冲突
		
		//遍历当前状态的每个项目
		for (const auto& item : items) {
			if(item.dotPos == item.right.size()) {//归约项
				if (item.right.size() == 1 && item.right[0] == "@") continue; //虽然@项目永远不会执行item.dotPos == size()，因为没有移进

				const auto& follow = followSet[item.left];
				
				// 检查插入规约项的 Follow 集是否存在冲突
				for (const auto& symbol : follow) {
					if (symbol == "@") continue;
					if (finalFolSet.count(symbol)) { // 非空符号的冲突检查
						cout << "规约-规约冲突：状态 " << stateId << " 符号 " << symbol << endl;
						isSlr1 = false;
					}
					finalFolSet.insert(symbol); // 插入 Follow 集,follow集合都是终结符号来的
				}
			}
			else { //移进项
				string nextSymbol = item.right[item.dotPos];

				if (nextSymbol == "@") continue; //空不行

				if (firstSet.find(nextSymbol) != firstSet.end()) { //如果是非终结符号
					shiftFirstSet.insert(firstSet[nextSymbol].begin(), firstSet[nextSymbol].end());
				}
				else {
					shiftFirstSet.insert(nextSymbol);
				}
			}
		}

		//检查移进-规约冲突
		for (const auto& symbol : shiftFirstSet) {
			if (symbol != "@" && finalFolSet.count(symbol)) { //有交集
				cout << "在状态:"<< stateId <<" ,存在移进-规约冲突，符号为:" << symbol << endl;
				isSlr1 = false;
			}
		}

	}
	return isSlr1;
}


/*----------------------------------LR1部分------------------------------------------------ - */
//计算每个项目集的规则闭包，即能推导的情况的项目集，这里是LR1的。冗余代码，修改新增了lookahead
void LR1::getClosureLR1(unordered_set<ItemLR1>& items)
{
	bool changed = true;
	while (changed) {
		changed = false;

		unordered_set<ItemLR1> newItems = items; // 创建新集合，存放当前闭包状态

		//开始进行闭包扩展
		for (const auto& item : items) {
			if (item.dotPos < item.right.size()) { //检查点是否在末尾
				string symbol = item.right[item.dotPos]; //点后的符号
				unordered_set<string> ahead; //计算该符号的follow集合，用于lookahead
				if (item.dotPos + 1 == item.right.size()) { //刚好是符号末尾了，则继承原先的ahead
					ahead = item.lookahead;
				}
				else if (langMp.find(item.right[item.dotPos + 1]) != langMp.end()) { //如果下一个是非终结符号，则求其first集合
					ahead.insert(item.lookahead.begin(), item.lookahead.end());
				}
				else { //如果下一个就是终结符号
					ahead.insert(item.right[item.dotPos + 1]);
				}

				if (langMp.find(symbol) != langMp.end()) { //如果下一个符号是非终结符号，则需要求闭包
					for (const auto& rule : langMp[symbol]) { //遍历该符号的每一条规则
						ItemLR1 newItem = { symbol,rule, 0 };// 创建新项目，点位置在开头
						newItem.lookahead = ahead; //这里新增前面求的lookahead项目
						if (newItems.find(newItem) == newItems.end()) { //如果该状态内无该项目，则新增
							newItems.insert(newItem);
							changed = true;
						}
					}
				}
			}
		}
		items.insert(newItems.begin(), newItems.end()); //更新闭包状态
	}
}

//这里是LR1的，对每个状态进行符号移进的操作，生成新状态，并进行状态合并。冗余代码没有任何修改的地方。（除了getClosureLR1）
unordered_set<ItemLR1> LR1::GotoLR1(const unordered_set<ItemLR1>& state, const string& symbol) {
	unordered_set<ItemLR1> nextState;

	for (const auto& item : state) {
		if (item.dotPos < item.right.size() && item.right[item.dotPos] == symbol) {
			ItemLR1 movedItem = item;
			movedItem.dotPos++;
			nextState.insert(movedItem);
		}
	}
	getClosureLR1(nextState);//对移进后结果进行求闭包（扩展规则)处理，同时处理lookahead。

	return nextState;
}

//建立LR1的DFA图
void LR1::DfaLR1()
{
	unordered_set<ItemLR1> startState;
	startState.insert({ startLang, langMp[startLang][0], 0, {"$"} }); // 初始项目集，$ 为 lookahead
	getClosureLR1(startState); //计算起始状态闭包

	int stateId = 0;
	queue<pair<unordered_set<ItemLR1>, int>> stateQueue; //存储：<项目集，状态编号>
	stateQueue.push({ startState, stateId });
	LR1DfaStates[stateId] = startState; //存储LR1的状态项目集

	unordered_map<unordered_set<ItemLR1>, int, hash<unordered_set<ItemLR1>>> stateToId; //用于判断是否有新的状态项目集产生
	stateToId[startState] = stateId++;

	//开始bfa遍历文法，增补状态
	while (!stateQueue.empty()) {
		const auto& tmp = stateQueue.front();
		unordered_set<ItemLR1> currentState = tmp.first; //当前状态集
		int currentId = tmp.second; //当前状态ID

		stateQueue.pop();

		unordered_set<string> symbols; //收集当前项目集在该LR位置(.)下一个是可移进的符号集合。
		for (const auto& item : currentState) {
			if (item.right.size() == 1 && item.right[0] == "@") continue; //空@
			if (item.dotPos < item.right.size()) {
				symbols.insert(item.right[item.dotPos]);
			}
		}

		//开始进行移进操作，对每一种符号进行移进，lookahead在求解闭包时处理。因为是在原地进行扩展，期望符号。移进仅仅是符合某个符号则移进
		for (const auto& symbol : symbols) {
			unordered_set<ItemLR1> nextState = GotoLR1(currentState, symbol); //进行简单移进操作，内部包含求闭包处理
			
			if (nextState.empty()) continue; //同理的，进行一下预防错误处理。

			if (stateToId.find(nextState) == stateToId.end()) {//是新状态，则加入状态项目表，并赋予状态Id
				stateToId[nextState] = stateId;
				LR1DfaStates[stateId] = nextState; //存储状态项目
				LR1TransTable[currentId][symbol] = stateId; //记录状态项目通过什么符号进行转移到下一个项目
				stateQueue.push({ nextState, stateId });
				stateId++;
			}
			else { //即使是就状态，也应该加入状态转换表，记录状态项目通过什么符号进行（转移到已存在的状态）
				LR1TransTable[currentId][symbol] = stateToId[nextState]; //当前状态项目集的currentId通过symbol符号转移到已有下一个状态Id
			}
		}

	}

}


