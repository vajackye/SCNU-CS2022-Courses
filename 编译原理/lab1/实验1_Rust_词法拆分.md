* 关键字：

  ```yaml
  ---严格关键字
  
  KW_AS         : as
  KW_BREAK      : break
  KW_CONST      : const
  KW_CONTINUE   : continue
  KW_CRATE      : crate
  KW_ELSE       : else
  KW_ENUM       : enum
  KW_EXTERN     : extern
  KW_FALSE      : false
  KW_FN         : fn
  KW_FOR        : for
  KW_IF         : if
  KW_IMPL       : impl
  KW_IN         : in
  KW_LET        : let
  KW_LOOP       : loop
  KW_MATCH      : match
  KW_MOD        : mod
  KW_MOVE       : move
  KW_MUT        : mut
  KW_PUB        : pub
  KW_REF        : ref
  KW_RETURN     : return
  KW_SELFVALUE  : self
  KW_SELFTYPE   : Self
  KW_STATIC     : static
  KW_STRUCT     : struct
  KW_SUPER      : super
  KW_TRAIT      : trait
  KW_TRUE       : true
  KW_TYPE       : type
  KW_UNSAFE     : unsafe
  KW_USE        : use
  KW_WHERE      : where
  KW_WHILE      : while
  KW_ASYNC	  : async		(2018+)
  KW_AWAIT      : await		(2018+)
  KW_DYN        : dyn			(2018+)
  
  ---保留关键字
  KW_ABSTRACT   : abstract
  KW_BECOME     : become
  KW_BOX        : box
  KW_DO         : do
  KW_FINAL      : final
  KW_MACRO      : macro
  KW_OVERRIDE   : override
  KW_PRIV       : priv
  KW_TYPEOF     : typeof
  KW_UNSIZED    : unsized
  KW_VIRTUAL    : virtual
  KW_YIELD      : yield
  KW_TRY        : try			(2018+)
  
  ---弱关键字
  KW_UNION 	  : union
  KW_STATICLIFETIME : static
  KW_DYN 		  : dyn			(2015+)
  ```



* 标识符

  ```rust
  1.一个符合XID_Start规则字符开头，后可以跟多个XID_Continue规则字符；或者_后跟一或多个XID_continue规则字符
      
  let my_var = 10;      // 符合 XID_Start 和 XID_Continue
  let _tempValue = 20;  // 以 `_` 开头，但后面是合法的 XID_Continue 字符
  let x = 30;           // 简单的标识符
  let 东京 = 1;			//还能写中文...
  
  
  2.原始标识符使用 r# 前缀，允许使用保留关键字作为标识符，但是 r# 前缀不算在标识符本身！除了：crate, self, super, Self这些关键字
  
  let r#fn = 100;      // 'fn' 是保留关键字，但可以通过 r# 使用
  let r#true = false;  // 'true' 是关键字，但通过 r# 可以使用
  
  
  3.单个下划线_不能作为标识符。（单个下划线表示未使用的值）
  let _ = 200; //表示不关心这个值。
  
  
  4.不允许包含ZWNJ(零宽非连接符)和ZWJ(零宽连接符),需要手动插入，不必理会。
  
  
  5.只能用ASCII字符集得到情况：extern crate 声明，mod 声明...
  
  ```



* 注释：

  ```rust
  //行注释
  
  
  /*块注释，/*可以进行嵌套 */ */
  
  
  ///外部文档注释，用于给模块，函数，结构体等代码添加文档说明，通常用于生成API文档，以///开头，必须搭配程序项一起出现!
  /// 这是一个外部文档注释,生成文档时，rustdoc 工具会读取这些注释并生成相应的文档
  /// 它用于给 `add` 函数生成文档
  fn add(a: i32, b: i32) -> i32 {
      a + b
  }
  
  
  /**
  	外部块文档注释，用于长文档描述:/** */
  */
  
  
  //!内部文档注释，通常对模块或文件本身注释
  
  
  /*! 内部块文档注释，对模块详细说明 */
  ```



* 标点符号

  ```yaml
  +     Plus         算术加法, trait约束, 可匹配空的宏匹配器(Macro Kleene Matcher)
  -     Minus        算术减法, 取反
  *     Star         算术乘法, 解引用, 裸指针, 可匹配空的宏匹配器, use 通配符
  /     Slash        算术除法
  %     Percent      算术取模
  
  ^     Caret        位和逻辑异或
  !     Not          位和逻辑非, 宏调用, 内部属性, never型, 否定实现
  &     And          位和逻辑与, 借用, 引用, 引用模式
  |     Or           位和逻辑或, 闭包, match 中的模式, if let, 和 while let
  
  &&    AndAnd       短路与, 借用, 引用, 引用模式
  ||    OrOr         短路或, 闭包
  <<    Shl          左移位, 嵌套泛型
  >>    Shr          右移位, 嵌套泛型
  
  +=    PlusEq       加法及赋值
  -=    MinusEq      减法及赋值
  *=    StarEq       乘法及赋值
  /=    SlashEq      除法及赋值
  %=    PercentEq    取模及赋值
  ^=    CaretEq      按位异或及赋值
  &=    AndEq        按位与及赋值
  |=    OrEq         按位或及赋值
  <<=   ShlEq        左移位及赋值
  >>=   ShrEq        右移位及赋值, 嵌套泛型
  =     Eq           赋值, 属性, 各种类型定义
  
  ==    EqEq         等于
  !=    Ne           不等于
  >     Gt           大于, 泛型, 路径
  <     Lt           小于, 泛型, 路径
  >=    Ge           大于或等于, 泛型
  <=    Le           小于或等于
  
  @     At           子模式绑定
  _     Underscore   通配符模式, 自动推断型类型, 常量项中的非命名程序项, 外部 crate, 和 use 声明
  
  .     Dot          字段访问, 元组索引
  ..    DotDot       区间, 结构体表达式, 模式
  ...   DotDotDot    可变参数函数, 区间模式
  ..=   DotDotEq     闭区间, 区间模式
  
  ----分隔符
  
  ,     Comma        各种分隔符
  ;     Semi         各种程序项和语句的结束符, 数组类型
  :     Colon        各种分隔符
  ::    PathSep      [路径分隔符]路径
  
  ->    RArrow       函数返回类型, 闭包返回类型, 数组指针类型
  =>    FatArrow     匹配臂, 宏
  #     Pound        属性
  $     Dollar       宏
  ?     Question     问号运算符, 非确定性尺寸, 可匹配空的宏匹配器
  
  ---定界符
  {}	花/大括号
  []	方/中括号
  ()	圆/小括号
  ```



* 字面量

  ```rust
  对于原生字面量，两侧的#必须相同，如：r##"123"##
  	ASCII转义:
              \x41	7-bit 字符编码（2位数字，最大值为 0x7F）
              \n	换行符
              \r	回车符
              \t	制表符
              \\	反斜线
              \0	Null
  
  	unicode转义:\u{7FFF}	24-bit Unicode 字符编码（最多6个数字）
  
  	引导转义:	\'	单引号	\"	双引号
  	
  
  -----------------------------------我是分割线--------------------------------"\
  
  字符字面量(Unicode):
  	字符字面量用''包裹，内部不包含：'(可用\转义), space, \n, \r, \t。
  
  
  -----------------------------------我是分割线--------------------------------\
  
  字符串字面量(Unicode):可用\忽略换行符号，字符串字面量允许换行书写(需要r#)
  
      let a = "foobar";
      let b = "foo\
               bar";
  	let c = r#"
  			我
  			换!
  			"#
  
  	字符串字面量转义实例：
  	
      "foo"; r#"foo";                     // foo, "foo"
      "\"foo\""; r#""foo""#;             // "foo",包含双引号
  
      "foo #\"# bar";
      r##"foo #"# bar"##;                // foo #"# bar
  
      "\x52"; "R"; r"R";                 // R
      "\\x52"; r"\x52";                  // \x52
  
  
  -----------------------------------我是分割线--------------------------------\
  
  
  数字字面量：
  	整型字面量：
  		2进制：0b开头，后跟二进制数和下划线任意组合(至少一个数字)
  		8进制：0o开头，后跟八进制数和下划线任意组合(至少一个数字)
  		2进制：0x开头，后跟十六进制数和下划线任意组合(至少一个数字)
  		后跟的必须为以下整形后缀：u8、i8、u16、i16、u32、i32、u64、i64、u128、i128、usize 或 isize
                          123;                               // 类型 i32
                          123i32;                            // 类型 i32
                          123u32;                            // 类型 u32
                          123_u32;                           // 类型 u32
                          let a: u64 = 123;                  // 类型 u64
  
                          0xff;                              // 类型 i32
                          0xff_u8;                           // 类型 u8
  
                          0o70;                              // 类型 i32
                          0o70_i16;                          // 类型 i16
  
                          0b1111_1111_1001_0000;             // 类型 i32
                          0b1111_1111_1001_0000i64;          // 类型 i64
                          0b________1;                       // 类型 i32
  
                          0usize;                            // 类型 usize
  
  
  
  -----------------------------------我是分割线--------------------------------\
  
  	浮点型字面量：
  		10进制字面量.十进制数字[+/-E整数]
  		10进制字面量+/-E整数
  		
                          123.0f64;        					// 类型 f64
                          0.1f64;          					// 类型 f64
                          0.1f32;          					// 类型 f32
                          12E+99_f64;      					// 类型 f64
                          5f32;            					// 类型 f32
                          let x: f64 = 2.; 					// 类型 f64
  
  
  -----------------------------------我是分割线--------------------------------\
  		
  	布尔型字面量：true/false
  
  -----------------------------------我是分割线--------------------------------\
  字节字面量，字节串字面量没写，应该不用写吧。。
  还有元组索引:
  let example = ("dog", "cat", "horse");
  let dog = example.0;
  let cat = example.1;
  //非法案例：
  let cat = example.01;  // 错误：没有 `01` 字段
  let horse = example.0b10;  // 错误：没有 `0b10` 字段
  ```

  

* 循环标签和生存期

  ```rust
  循环标签:
  fn main() {
      'outer: // 外层循环标签
      for i in 0..3 {
          for j in 0..3 {
              if j == 1 {
                  break 'outer; // 跳出外层循环
              }
              println!("i = {}, j = {}", i, j);
          }
      }
      println!("Done!");
  }
  
  
  
  //生存期没看懂。。。
  ```

  
