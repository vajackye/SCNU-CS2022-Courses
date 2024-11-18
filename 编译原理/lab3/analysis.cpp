#include "analysis.h"
#include <QDebug>
using namespace std;

// 将符号与 TokenType 对应
unordered_map<string, TokenType> mp = {
    // 关键字
    {"if", IF},
    {"then", THEN},
    {"else", ELSE},
    {"endif", ENDIF},
    {"repeat", REPEAT},
    {"until", UNTIL},
    {"read", READ},
    {"write", WRITE},
    {"true", CONST}, //布尔常量
    {"false", CONST},
    {"for", FOR},
    {"endfor", ENDFOR},
    {"while", WHILE},
    {"endwhile", ENDWHILE},

    // 运算符
    {":=", ASSIGN},
    {"<", LT},
    {">", GT},
    {"<=", LE},
    {">=", GE},
    {"=", EQ},
    {"<>", NEQ},
    {"+", PLUS},
    {"-", MINUS},
    {"*", MUL},
    {"/", DIV},
    {"%", MOD},
    {"^", POW},
    {"++", INCREMENT},
    {"--", DECREMENT},

    // 正则符号
    {"::=", REG_ASSIGN},
    {"|", REG_OR},
    {"&", REG_AND},
    {"#", REG_HASH},
    {"?", REG_OPT},

    //通用左右括号
    {"(", LP},
    {")", RP},

    // 分隔符
    {";", SEP},
};

//-------------------------------------------------------------------
//测试函数--打印枚举名字
string getTokenTypeName(TokenType tokenType) {
    switch (tokenType) {
        // 关键字（KW）
    case IF: return "IF";
    case THEN: return "THEN";
    case ELSE: return "ELSE";
    case ENDIF: return "ENDIF";
    case REPEAT: return "REPEAT";
    case UNTIL: return "UNTIL";
    case READ: return "READ";
    case WRITE: return "WRITE";
    case TRUE: return "TRUE";
    case FALSE: return "FALSE";
    case FOR: return "FOR";
    case ENDFOR: return "ENDFOR";
    case WHILE: return "WHILE";
    case ENDWHILE: return "ENDWHILE";

        // 标识符常量
    case CONST: return "CONST";
    case ID: return "ID";

        // 运算符（OP）
    case ASSIGN: return "ASSIGN";
    case LT: return "LT";
    case GT: return "GT";
    case LE: return "LE";
    case GE: return "GE";
    case EQ: return "EQ";
    case NEQ: return "NEQ";
    case PLUS: return "PLUS";
    case MINUS: return "MINUS";
    case MUL: return "MUL";
    case DIV: return "DIV";
    case MOD: return "MOD";
    case POW: return "POW";
    case INCREMENT: return "INCREMENT";
    case DECREMENT: return "DECREMENT";

        // 正则符号（REG）
    case REG_ASSIGN: return "REG_ASSIGN";
    case REG_OR: return "REG_OR";
    case REG_AND: return "REG_AND";
    case REG_HASH: return "REG_HASH";
    case REG_OPT: return "REG_OPT";

        // 通用左右括号
    case LP: return "LP";
    case RP: return "RP";

        // 分隔符（SEP）
    case SEP: return "SEP";

        // 特殊符号
    case ERROR: return "ERROR";
    case ENDFILE: return "ENDFILE";

    default: return "UNKNOWN";
    }
}

//----------------------------------------------------------------




//初始化所有必要value
void Analysis::init() {
    this->InputCode = "";
    this->word = "";
    this->explain = false;
    this->isReg = false;
    this->lineNum = 0; //行号数目
    this->tkNow = 0; //目前遍历到的tokens
    this->ErrorLine.clear();
    this->Tokens.clear();
    this->token = {};

    //QT特色操作
    this->fileName.clear();
    this->errorList.clear();

    this->root = new Node("start"); //建树
}

//修改为QT格式
void Analysis::analysis(const QString &fileName) {
    QFile file(fileName);  // 打开文件
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file:" << fileName;
        return;
    }

    QTextStream in(&file);  // 绑定文件流
    string ss;
    init();

    while (!in.atEnd()) {  // 逐行读取文件
        QString line = in.readLine();  // 读取一行
        ss = line.toStdString();  // 转换为 std::string

        if (ss.empty()) continue;  // 跳过空行

        // 处理字符串，保存结果
        this->InputCode += ss + "\n";
        this->lineNum++;  // 行号 + 1

        wordKind(ss);  // 词法分析
    }

    file.close();  // 关闭文件

    // 语法分析
    LangAnaly();
}

//---------------------------------------------------------------词法分析部分--------------------------------------------------------------------
//
//先词法分析
string Analysis::wordKind(string ss) {
    for (int i = 0; i < ss.size(); i++)
    {
        bool flag = false; //一次只能执行一个东西
        while (isspace(ss[i])) i++;

        i = this->zhushi(ss, i, flag);
        if (flag) continue;
        i = this->keyW(ss, i, flag);
        if (flag) continue;
        i = this->digit(ss, i, flag);
        if (flag) continue;
        i = this->opera(ss, i, flag);
        if (flag) continue;
        i = this->regex(ss, i, flag);
        if (flag) continue;
        if (ss[i] == ';')
        {
            flag = true;
            this->Tokens.push_back({ ";", mp[";"] });
            this->ErrorLine.push_back({":", this->lineNum});
        }
        //分析报错
        if (!flag && i < ss.size() && !isspace(ss[i]))
        {
            cout << "error" << endl;
            return "error";
        }
    }
    return "";
}

//词法注释处理, 如何解决注释没有报错？
int Analysis::zhushi(string st, int index, bool &flag)
{
    int idx = index;
    //如果是注释,不参与语法分析
    if (st[index] == '{') this->explain = true;

    if (this->explain) {
        flag = true;
        while (idx < st.size()) {
            if (st[idx] == '}') {
                explain = false;
                break;
            }
            idx++;
        }
        return idx; //因为idx后自增，故返回idx。
    }
    return index; //不成功原路返回
}

//词法数字处理
int Analysis::digit(string st, int index, bool &flag)
{
    int idx = index;
    string bef = "";
    //如果是数字
    if (isdigit(st[idx])) {
        while (idx < st.size() && isdigit(st[idx])) {
            bef += st[idx++];
        }
        flag = true;
        this->Tokens.push_back({ bef,  CONST});
        this->ErrorLine.push_back({ bef, this->lineNum });
        return idx - 1; //判断到最后一个不是数字时，回溯到最后一个数字 : idx - 1。
    }
    return index; //不成功原路返回
}

//词法关键字或标识符处理
int Analysis::keyW(string st, int index, bool &flag)
{
    int idx = index;
    string bef = "";
    //如果是字母
    if (isalpha(st[idx])) {
        flag = true;
        while (idx < st.size() && isalpha(st[idx]))
            bef += st[idx++];

        if (mp.find(bef) != mp.end()) {  // 如果是关键字或者是BOOL
            this->Tokens.push_back({ bef, mp[bef] });
            this->ErrorLine.push_back({ bef, this->lineNum });

            //特判while和for的后面括号内容
            if (bef == "while" || bef == "for") {
                while (isspace(st[idx])) idx++;
                if (st[idx] == '(')
                {
                    this->Tokens.push_back({ "(", mp["("]});
                    this->ErrorLine.push_back({ "(", this->lineNum });
                    idx++;
                }
            }
        }
        else {  // 否则为标识符
            this->Tokens.push_back({ bef, ID });
            this->ErrorLine.push_back({ bef, this->lineNum });
        }
        return idx - 1; //判断到最后一个不是字母时，回溯到最后一个字母: idx - 1。
    }
    return index; //不成功原路返回
}

//词法操作数处理
int Analysis::opera(string st, int index, bool &flag)
{
    int idx = index;
    string bef = "";
    string now = "";
    //先判断赋值运算符
    if (st.substr(idx, 2) == ":=") {
        flag = true;
        this->Tokens.push_back({ ":=", mp[":="] });
        this->ErrorLine.push_back({ ":=", this->lineNum });
        return idx + 1;
    }
    //普通运算符,优化：可以枚举所有的符号，给每个标识符添加编号，即可缩短范围
    if (st[idx] == '+' || st[idx] == '-' || st[idx] == '*' || st[idx] == '/' || st[idx] == '%' || st[idx] == '^' || st[idx] == '<' || st[idx] == '>' || st[idx] == '=' || st[idx] == '(' || st[idx] == ')') {
        flag = true;
        //bool haveDone = false;
        while (idx <= st.size()) {
            now += st[idx];
            //说明该符号到头了
            if (mp.find(now) == mp.end()) {
                this->Tokens.push_back({ bef, mp[bef] });
                this->ErrorLine.push_back({ bef, this->lineNum });
                //haveDone = true;
                break;
            }
            //if (!haveDone)
            //{
            //    this->Tokens.push_back({ bef, mp[bef] });
            //    this->ErrorLine.push_back({ bef, this->lineNum });
            //}
            idx++;
            bef = now;
        }

        return idx - 1;
    }
    return index; //不成功原路返回
}

//词法正则处理
int Analysis::regex(string st, int index, bool &flag)
{
    int idx = index;
    //正则表达式的赋值运算符
    if (idx + 2 < st.size() && st.substr(idx, 3) == "::=")
    {
        flag = true;
        this->isReg = true;
        this->Tokens.push_back({ "::=", mp["::="] });
        this->ErrorLine.push_back({ "::=", this->lineNum });
        idx += 3; //刚好3个字符
    }

    if (!isReg) return index; //正则不能无端出现，必须有::=后才能出现

    //如果是普通正则表达式运算符
    //if (st[idx] == '|' || st[idx] == '&' || st[idx] == '#' || st[idx] == '?' || st[idx] == '(' || st[idx] == ')') {
    flag = true;
    //之所以在这里循环，是减轻调度次数。反正后面的所有都是正则，且都是“单字符”形式。不存在：abc|d，按实验要求一定是：a&b&c|d
    while (idx < st.size() && st[idx] != ';') {
        if (isspace(st[idx]))
        {
            idx++;
            continue;
        }
        if (isalpha(st[idx]))
        {
            this->Tokens.push_back({ string(1,st[idx]), ID});
            this->ErrorLine.push_back({ string(1,st[idx]), this->lineNum });
        }
        else if (isdigit(st[idx]))
        {
            this->Tokens.push_back({ string(1,st[idx]), CONST });
            this->ErrorLine.push_back({ string(1,st[idx]), this->lineNum });
        }
        else
        {
            this->Tokens.push_back({ string(1,st[idx]), mp[string(1,st[idx])] });
            this->ErrorLine.push_back({ string(1,st[idx]), this->lineNum });
        }
        idx++;
    }
    this->isReg = false;
    return idx - 1; //刚好返回到最后一个正则操作。

    //}
    //return index; //不成功原路返回
}

//打印词法分析结果
void Analysis::printWord()
{
    //cout << this->word;
    for (int i = 0; i < this->Tokens.size(); i++)
    {
        cout << getTokenTypeName(this->Tokens[i].second) << "\t" << this->Tokens[i].first<< endl;
        //cout << this->ErrorLine[i].second << "\t" << this->ErrorLine[i].first << endl<<endl;
    }
}


//---------------------------------------------------------------语法分析部分--------------------------------------------------------------------



//语法分析
Node* Analysis::LangAnaly(){

    //只能从这五个语句开始。
    getToken();
    this->root->child[this->root->SIZE++] = stmt_sequence();
//    printSyntaxTree(this->root, 0);
    return this->root;
}

TokenType Analysis::getToken() {
    if (tkNow < Tokens.size()) {
        token = Tokens[tkNow]; // 获取当前 token
        tkNow++; //继续到下一个token
        return token.second;
    }
    token = { "endfile",ENDFILE};
    return token.second;
}

// 用来匹配当前符号是否为预想的符号，如果是则前移，否则产生错误信息
// 传进来的是函数期望匹配的下一个token。token是Tokens序列中当前的位置的token
void Analysis::match(const TokenType& expectedToken) {
    //如果符合预期，则继续前移下一个token
    if (token.second == expectedToken) {

        getToken(); // 获取下一个符号
    }
    else {
        Error(2, ErrorLine[tkNow].second, expectedToken,token.second);
        getToken(); //报错后继续走，目的是获取所有的报错
    }
}

//语法出错分析
void Analysis::Error(int errorKind, const int& idx, const TokenType& expectedToken = ERROR, const TokenType& token = ERROR) {
    QString description;
    QString file = this->fileName;  // `fileName` 是当前文件名
    int line = idx;

    switch (errorKind) {
    case 1:
        description = QString("Unknown token: %1").arg(QString::fromStdString(Tokens[tkNow - 1].first));
        break;
    case 2:
        description = QString("Expected: %1, but got: %2")
                          .arg(QString::fromStdString(getTokenTypeName(expectedToken)))
                          .arg(QString::fromStdString(getTokenTypeName(token)));
        break;
    default:
        description = "Unknown error.";
        break;
    }

    // 存储错误信息到 vector
    errorList.emplace_back(description, file, line);
}


//清除语法树。
void Analysis::clear(Node* root)
{
    if (root == nullptr)
        return;

    // 递归删除所有子节点
    for (int i = 0; i < 4; i++) {
        if (root->child[i] != nullptr)
            clear(root->child[i]);
    }

    // 递归删除兄弟节点
    clear(root->sibling);

    // 删除当前节点
    delete root;
    root = nullptr;
}

//打印树
void Analysis::printSyntaxTree(Node* root, int depth){
    if (!root) return;

    for (int i = 0; i < depth; ++i) cout << "  "; // 缩进
    cout << root->ch << endl;

    for (int i = 0; i < root->SIZE; ++i) {
        printSyntaxTree(root->child[i], depth + 1);
    }

    if (root->sibling) {
        printSyntaxTree(root->sibling, depth);
    }
}

// 递归下降函数群
Node* Analysis::stmt_sequence() {
     //先开始
    Node* rt = statement();
    Node* p = rt;
    while (token.second != ENDFILE && token.second != ENDIF && token.second != ENDFOR && token.second != ENDWHILE && token.second != UNTIL && token.second != ELSE) {
        Node* q;
        match(token.second); //分隔符号
        if (token.second == ENDFILE || token.second == ENDIF || token.second == ENDFOR || token.second == ENDWHILE || token.second == UNTIL || token.second == ELSE)
            break;
        q = statement();
        if (q != nullptr){
            if (rt == nullptr) rt = p = q;
            else { //兄弟节点
                p->sibling = q;
                p = q;
            }
        }
    }
    return rt;
}
Node* Analysis::statement() {
    Node* rt = nullptr;
    switch (token.second) {
    case IF:
        rt = if_stmt();
        break;
    case REPEAT:
        rt = repeat_stmt();
        break;
    case ID:
        rt = assign_stmt();
        break;
    case READ:
        rt = read_stmt();
        break;
    case WRITE:
        rt = write_stmt();
        break;
    case WHILE:
        rt = while_stmt();
        break;
    case FOR:
        rt = for_stmt();
        break;
    case INCREMENT:
    case DECREMENT:
        rt = factor(); //自增自减直接在factor内操作
        break;
    default:
        Error(1, ErrorLine[tkNow-1].second); //报错，并展示错误行数
        break;
    }
    return rt;
}


Node* Analysis::if_stmt() {
    Node* rt = nullptr;
    rt = new Node("if");
    match(IF);
    match(LP);
    if(rt != nullptr)
        rt->child[rt->SIZE++] = exp();

    match(RP);
    if (rt != nullptr)
        rt->child[rt->SIZE++] = stmt_sequence();
    //可选
    if (token.second == ELSE) {
        match(ELSE);
        //Node* p = new Node("else");
        //if (rt != nullptr && p != nullptr)
        //{
        //    p->child[p->SIZE++] = stmt_sequence();
        //    rt->sibling = p; //挂载兄弟节点而不是儿子节点
        //}
        if(rt != nullptr)
            rt->child[rt->SIZE++] = stmt_sequence();
    }
    match(ENDIF);

    return rt;
}

Node* Analysis::repeat_stmt() {
    Node* rt = nullptr;
    rt = new Node("repeat");
    match(REPEAT);
    if (rt != nullptr)
        rt->child[rt->SIZE++] = stmt_sequence();
    match(UNTIL);
    if (rt != nullptr)
        rt->child[rt->SIZE++] = exp();

    return rt;
}

Node* Analysis::while_stmt() {
    Node* rt = nullptr;
    rt = new Node("while");
    match(WHILE);
    match(LP);
    rt->child[rt->SIZE++] = exp();
    match(RP);
    rt->child[rt->SIZE++] = stmt_sequence();

    match(ENDWHILE);

    return rt;
}

Node* Analysis::for_stmt() {
    Node* rt = nullptr;
    rt = new Node("for");
    match(FOR);
    match(LP);
    rt->child[rt->SIZE++] = assign_stmt();
    match(SEP);
    rt->child[rt->SIZE++] = exp();
    match(SEP);
    rt->child[rt->SIZE++] = factor();
    match(RP);
    rt->child[rt->SIZE++] = stmt_sequence();
    match(ENDFOR);
    return rt;
}

//read是叶子节点
Node* Analysis::read_stmt() {
    Node* rt = nullptr;
    match(READ);

    rt = new Node("read");
    match(ID); //下一个读取indentifier
    if (rt != nullptr)
        rt->ch += "(" + Tokens[tkNow-2].first + ")";

    return rt;
}

Node* Analysis::write_stmt() {
    Node* rt = nullptr;
    match(WRITE);

    rt = new Node("write");
    if (rt != nullptr)
        rt->child[rt->SIZE++] = exp(); //挂钩

    return rt;
}

Node* Analysis::assign_stmt() {
    Node* rt = nullptr;

    match(ID);
    switch (token.second) {
    //普通赋值运算
    case ASSIGN:
        match(ASSIGN);
        rt = new Node("assign");
        rt->ch += "(" + Tokens[tkNow - 3].first + ")"; //保证不会越界，前提是符合语法要求
        rt->child[rt->SIZE++] = exp();
        break;
    //正则赋值运算
    case REG_ASSIGN:
        match(REG_ASSIGN);
        rt = new Node("reg_assign");
        rt->ch += "(" + Tokens[tkNow - 3].first + ")"; //保证不会越界，前提是符合语法要求
        rt->child[rt->SIZE++] = regex_stmt();
        break;
    default:
        Error(1, ErrorLine[tkNow - 1].second);
        break;
    }
    return rt;
}

Node* Analysis::exp() {
    Node* rt = simple_exp();
    Node* p = nullptr;
    //可选的，如果都没有则跳过，等价于if(token.second==xxx)
    switch (token.second) {
    case LT:     // 小于 `<`
    case GT:     // 大于 `>`
    case EQ:     // 等于 `=`
    case LE:     // 小于等于 `<=`
    case GE:     // 大于等于 `>=`
    case NEQ:     // 不等于 `<>`
        p = new Node("op");
        p->ch += "(" + token.first + ")";
        if (p != nullptr){
            p->child[p->SIZE++] = rt; //操作符连接孩子
            rt = p; //指向父亲
        }
        match(token.second); // 匹配当前运算符
        if(rt != nullptr)
            rt->child[rt->SIZE++] = simple_exp(); // 处理右侧的 simple_exp连接
        break;
    default:
        // 如果不是合法运算符||不选择接下来的运算符也不选  [comparison-op simple-exp]
        break;
    }
    return rt;
}

Node* Analysis::simple_exp() {
    Node* rt = term();
    while (token.second == PLUS || token.second == MINUS) {
        Node* p = new Node("op");
        if (p != nullptr){
            p->ch += "(" + token.first +")";
            p->child[p->SIZE++] = rt;
            rt = p;
            match(token.second);
            rt->child[rt->SIZE++] = term();
        }
    }
    return rt;
}

Node* Analysis::term() {
    Node * rt = pow();
    while (token.second == MUL || token.second == DIV || token.second == MOD) {
        Node* p = new Node("op");
        if (p != nullptr) {
            p->ch += "(" + token.first + ")";
            p->child[p->SIZE++] = rt;
            rt = p;
            match(token.second);
            rt->child[p->SIZE++] = pow();

        }
    }
    return rt;
}

//有点疑惑，这个树也是这么建吗
Node* Analysis::pow() {
    Node* rt = factor();
    while (token.second == POW) {
        Node* p = new Node("op");
        if (p != nullptr) {
            p->ch += "(^)";
            p->child[p->SIZE++] = rt;
            match(POW);
            rt = p;
            rt->child[rt->SIZE++] = pow();

        }
    }
    return rt;
}

Node* Analysis::factor() {
    Node* rt = nullptr;
    Node* p = nullptr;
    switch (token.second) {
    case LP:
        match(LP);
        rt = exp(); //不是孩子了，factor已经是叶子节点。剩下的嵌套是下面的事。
        match(RP);
        break;
    case CONST:
        rt = new Node("const");
        if (rt != nullptr) {
            rt->ch += "(" + token.first + ")";
        }
        match(CONST);
        break;
    case ID:
        rt = new Node("id");
        if (rt != nullptr) {
            rt->ch += "(" + token.first + ")";
        }
        match(ID);
        break;
    //还有一个自增自减的
    case INCREMENT:
    case DECREMENT:
        p = new Node("op");
        if (p != nullptr) {
            p->ch += "(" + token.first + ")";
        }
        match(token.second);
        rt = new Node("id");
        rt->ch += "(" + token.first + ")";
        if (p != nullptr) {
            p->child[p->SIZE++] = rt;
            rt = p;
        }
        match(ID);
        break;
    default:
        Error(1, ErrorLine[tkNow - 1].second);
    }
    return rt;
}

Node* Analysis::regex_stmt() {
    Node* rt = andreg();
    while (token.second == REG_OR) {
        Node* p = new Node("reg_op");
        if (p != nullptr) {
            p->ch += "(|)";
            p->child[p->SIZE++] = rt;
            rt = p;
        }
        match(REG_OR);
        if(rt != nullptr)
            rt->child[rt->SIZE++] = andreg();
    }
    return rt;
}

Node* Analysis::andreg() {
    Node * rt = topreg();
    while (token.second == REG_AND) {
        Node* p = new Node("reg_op");
        if (p != nullptr) {
            p->ch += "(&)";
            p->child[p->SIZE++] = rt;
            rt = p;
        }
        match(REG_AND);
        if(rt != nullptr)
            rt->child[rt->SIZE++] = topreg();
    }
    return rt;
}

Node* Analysis::topreg() {
    Node* rt = reg_factor();
    while (token.second == REG_HASH || token.second == REG_OPT) {
        Node* p = new Node("reg_op");
        if (p != nullptr) {
            p->ch += "(" + token.first + ")";
            p->child[p->SIZE++] = rt;
            rt = p;
        }
        match(token.second);
    }
    return rt;
}

Node* Analysis::reg_factor() {
    Node* rt = nullptr;
    switch (token.second)
    {
    case LP:
        match(LP);
        rt = regex_stmt();
        match(RP);
        break;
    case ID:
        rt = new Node("id");
        if (rt != nullptr) {
            rt->ch += "(" + token.first + ")";
        }
        match(ID);
        break;
    case CONST:
        rt = new Node("const");
        if (rt != nullptr) {
            rt->ch += "(" + token.first + ")";
        }
        match(CONST);
        break;
    default:
        Error(1, ErrorLine[tkNow - 1].second);
        break;
    }
    return rt;
}


