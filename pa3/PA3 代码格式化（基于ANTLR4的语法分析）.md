# PA3: 代码格式化（基于ANTLR4的语法分析）

## Soft Deadline

**2025 年 11 月 4 日 23：59**

## 前置要求

✅ 完成PA1: 基于ANTLR4的词法分析器

开始之前

**请通过下面的命令获取 PA3 框架代码**（假设你已经按 PA2 的要求设置好 upstream 仓库）：

```
git fetch upstream
git checkout main       # 切换到你的本地分支
git merge upstream/main # 合并上游的变更
```

你也可以手动下载 [框架代码](https://github.com/Nboxff/thss-2025-compiler) 中的`pa3` 文件夹，将其复制到你的本地项目根目录中。



## 实验描述

代码格式化(Code format)是指按照统一的风格规范对源代码进行重新排版的过程，目的是提高代码的可读性、一致性和可维护性，而不改变代码的实际功能和行为。现代的 IDE（如 CLion、VSCode）都具备代码格式化功能，而且大多数开源项目在合并 PR 之前，也通常会要求提交的代码已经过格式化处理。

在PA1中，你已经使用ANTLR4构建了一个词法分析器，能够识别 SysY 语言（简化的 C 语言）代码的基本词法单元。在本实验中，你将基于 ANTLR4 的语法分析能力，构建一个代码格式化工具，能够对输入的无语法错误的 SysY 语言代码进行自动格式化，使其符合指定的代码风格规范。

### Part0: 环境配置

在本次实验中，你需要在 Ubuntu 22.04 系统中完成实验。

- 对于Windows用户，推荐使用 WSL2 或 Docker 作为开发环境，也可以安装虚拟机。
- 对于MacOS用户，推荐使用 Docker 作为开发环境或者安装虚拟机。
- 对于其他 Linux 发行版的用户，你需要自己注意和 Ubuntu 22.04 系统的差异。

本次实验使用 C++ 17 编写，使用 CMake 作为构建工具。请通过下面的命令安装必要的依赖：

```
sudo apt update
sudo apt install build-essential cmake git pkg-config python3 openjdk-11-jdk curl
```

使用 C++ 需要额外安装 ANTLR4-Cpp 运行时，我们已在框架代码中为大家提供，你无需额外操作。

### Part1: 编写SysYParser.g4文件

在进行代码格式化任务之前，你需要完成`SysYParser.g4`文件的编写，以完成对 SysY 语言的语法分析。为了保证你的代码能通过 GradeScope 的评测，请将`SysYLexer.g4`和`SysYParser.g4`文件放在`pa3/`项目根目录中。完成g4文件的编写，你可以获得25%的分数。

#### SysY语法规则介绍

在本次PA中，我们采用扩展的 Backus 范式（EBNF，Extended Backus-Naur Form），来表示SysY语言的语法规则，其中：

- 符号`[...]`表示方括号内包含的为可选项
- 符号`{...}`表示花括号内包含的为可重复 0 次或多次的项
- 终结符或者是由单引号括起的串，或者是 Ident、InstConst 这样的记号

SysY 语法规则如下：

```
CompUnit       ->     [CompUnit] (Decl | FuncDef)
Decl           ->     ConstDecl | VarDecl
ConstDecl      ->     'const' BType ConstDef { ',' ConstDef } ';'
BType          ->     'int'
ConstDef       ->     Ident { '[' ConstExp ']' } '=' ConstInitVal
ConstInitVal   ->     ConstExp 
                      | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
VarDecl        ->     BType VarDef { ',' VarDef } ';'
VarDef         ->     Ident { '[' ConstExp ']' } 
                      | Ident { '[' ConstExp ']' } '=' InitVal
InitVal        ->     Exp | '{' [ InitVal { ',' InitVal } ] '}'
FuncDef        ->     FuncType Ident '(' [ FuncFParams ] ')' Block
FuncType       ->     'void' | 'int'
FuncFParams    ->     FuncFParam { ',' FuncFParam }
FuncFParam     ->     BType Ident [ '[' ']' { '[' Exp ']' } ]
Block          ->     '{' { BlockItem } '}'
BlockItem      ->     Decl | Stmt
Stmt           ->     LVal '=' Exp ';' | [ Exp ] ';' | Block 
                      | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] 
                      | 'while' '(' Cond ')' Stmt 
                      | 'break' ';' | 'continue' ';' 
                      | 'return' [ Exp ] ';'
Exp            ->     AddExp
Cond           ->     LOrExp
Lval           ->     Ident {'[' Exp ']'}
PrimaryExp     ->     '('Exp')'|LVal|Number
Number         ->     IntConst
UnaryExp       ->     PrimaryExp | Ident '('[FuncRParams]')' | UnaryOp UnaryExp
UnaryOp        ->     '+' | '−' | '!'
FuncRParams    ->     Exp { ',' Exp }
MulExp         ->     UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
AddExp         ->     MulExp | AddExp ('+' | '−') MulExp
RelExp         ->     AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
EqExp          ->     RelExp | EqExp ('==' | '!=') RelExp
LAndExp        ->     EqExp | LAndExp '&&' EqExp
LOrExp         ->     LAndExp | LOrExp '||' LAndExp
ConstExp       ->     AddExp 
```

请注意，OJ 测试程序中会调用`CompUnit`作为入口，因此，在`SysYParser.g4`文件中，你必须要有一个名为`compUnit`的语法规则。

#### Part1 实验指导

只要能满足上面的语法规则，你可以自由地编辑 ANTLR4 的文件，包括不限于添加一些语法规则节点、添加注释等。

注意：g4文件中的注释是对代码编写有实际影响的，你可以回顾 [ANTLR4使用指南](http://166.111.80.114:8000/labs/antlr/) 中的内容。

在 PA3 中，你首先需要拷贝在 PA1 中已经实现的词法规则文件，并在`SysYParser.g4`中引用它，就像使用 C 语言中的`include`语句。

**SysYParser.g4**

```
parser gramar SysYParser;

options {
    tokenVoval = SysYLexer;
}
```

接下来，你需要正式编写 SysY 语言的语法规则了。你有没有发现上面的语法规则的写法有点“反人类”？例如：

```
AddExp -> MulExp | AddExp ('+' | '−') MulExp
```

当你看到这样的语法时一定会发出疑问：这是什么鬼写法。实际上，这个语法规则并不是为 ANTLR4 准备的，ANTLR 的强大之处就在于它能够自己处理左递归和优先级关系（通过先后顺序，越靠前的优先级越高）。

所以，下面我们要做一件和课程所学的知识相反的事情————**改成左递归**！

例如，我们可以将上面的一部分文法改成下面的样子，这样更直观也更便于后续语法树的遍历：

```
exp : L_PAREN exp R_PAREN
   | lVal
   | number
   | IDENT L_PAREN funcRParams? R_PAREN
   | unaryOp exp
   | exp (MUL | DIV | MOD) exp
   | exp (PLUS | MINUS) exp

cond
   : exp
   | cond (LT | GT | LE | GE) cond
   | cond (EQ | NEQ) cond
   | cond AND cond
   | cond OR cond
   ;
```

当你完成 g4 文件的编写，你可以运行下面的命令来生成词法分析器和语法分析器代码

```
antlr4 -Dlanguage=Cpp -visitor -no-listener -o src/ SysYLexer.g4 SysYParser.g4
```

你也可以直接利用框架代码中的`Makefile`来生成词法分析器和语法分析器，你只需要在项目根目录(pa3)运行：

```
make antlr
```

此时，你的项目结构应当是这样的：

```
pa3/
├── CMakeLists.txt                  # CMake 文件
├── Makefile                        # Makefile 文件
├── SysYLexer.g4                    # 词法规则文件
├── SysYParser.g4                   # 语法规则文件
├── antlr-4.13.1-complete.jar       # antlr jar 包
├── include                         # 头文件
│   └── SysYFormatter.h
├── src                             # 源文件
│   ├── SysYFormatter.cpp
│   ├── SysYLexer.cpp
│   ├── SysYLexer.h
│   ├── SysYLexer.interp
│   ├── SysYLexer.tokens
│   ├── SysYParser.cpp
│   ├── SysYParser.h
│   ├── SysYParser.interp
│   ├── SysYParser.tokens
│   ├── SysYParserBaseVisitor.cpp
│   ├── SysYParserBaseVisitor.h
│   ├── SysYParserVisitor.cpp
│   ├── SysYParserVisitor.h
│   └── main.cpp
└── third_party                     # 第三方库
    └── antlr4-runtime
```

下面，让我们正式开始代码格式化任务的编程吧。完成 Part1 的任务，你可以获得 PA3 25% 的分数。GradeScope 上 Part1 的测试较弱，通过 Part1 全部测试用例不代表 g4 文件完全正确。



### Part2: 代码格式化

在 Part 2 中，你需要完成代码格式化的任务，格式化要求如下：

1. 注释规则：

   - 你需要删除源代码中所有的注释信息和`EOF`标识符

2. 换行规则：

   - 每一条语句(decl/stmt)独占一行
   - 左花括号`{`采用 K&R 风格，即不换行，且`{`前有一个空格
   - 对于单独存在的代码块，左花括号独占一行，且前面没有额外的空格
   - 右花括号`}`另起一行
   - 除第一行外，每个函数前有一个空行
   - 每个声明语句独占一行，声明语句之间没有空行
   - 每条声明语句中的花括号都在同一行，即使它们存在嵌套关系（如`{{1, 2, 3}, {1, 2, 3}}`;）

3. 缩进规则：

   - 初始情况（最外层）不需要缩进
   - 每一级缩进使用2个空格
   - 语句块(block)内缩进一层，即每进入一个block，缩进两个空格
   - if、else、while等语句下无花括号包裹的语句，也要缩进一层
   - 形如`else if (cond) block`的情况，`else if`在同一行，且block缩进保持不变，block内缩进正常+1

4. 空格规则：

   - 下列关键字后面需要添加一个空格：

     ```
     const, int, void, if, else, while, return
     ```

     注：

     ```
     return
     ```

     后面跟分号的时候不需要加空格。

   - 二元运算符的两侧均有一个空格，注意比较运算符、部分逻辑运算符也是二元运算符

   - 一元运算符的两侧不需要加空格

   - 函数定义部分，其返回值和函数名之间有一个空格

   - 每行的末尾不要加额外的空格

   - 逗号的后面有一个空格，即对于函数形参、函数实参、初始化列表等情况有多于一个项的时候，用于分隔它们的逗号后面有一个空格，逗号前面没有空格

   - 除缩进以外，两个词法单元之间不会出现连续的多个空格

#### 输入样例

本次实验中，我们要求你实现文件读入，即通过`./sysy_formatter <input_file>`获取输入文件，并格式化输出到标准输出中。

**格式化前的代码**

```
const int a=1; int b= 2;
int arr[10]={1,2,3};

int plus(int x, int y) 
{
return x + y;
}

void print() {}

int main() 
{
  int c;
  {
    int  cond=1;
    if (cond == 1) 
    {
        c=a+b;
    } 
    else if (cond==2) 
    {
        c=a-b;
    }
    else c=a*b;
  }
  print();   return 0;
}
```

#### 输出样例

**格式化后的代码**

```
const int a = 1;
int b = 2;
int arr[10] = {1, 2, 3};

int plus(int x, int y) {
  return x + y;
}

void print() {
}

int main() {
  int c;
  {
    int cond = 1;
    if (cond == 1) {
      c = a + b;
    }
    else if (cond == 2) {
      c = a - b;
    }
    else
      c = a * b;
  }
  print();
  return 0;
}
```

你需要实现一个`SysYFormatter`类，继承自`SysYParserBaseVisitor`类，作为语法分析器的访问者。你需要补全`main.cpp`，在`main`函数中创建一个`SysYFormatter`对象，并调用`visit`方法，将语法分析树传入。

#### Part2 实验指导

PA3 的 Part 2 还是有一定代码量的，与其说是实现了代码格式化的工具，不如说我们按照特定格式，重新生成了一份代码。

##### 如何使用词法和语法分析器：main.cpp

在`main.cpp`中使用ANTLR4生成的语法分析结果：

需要导入头文件：

```
#include "SysYLexer.h"
#include "SysYParser.h"
#include "SysYFormatter.h"
```



引入命名空间：

```
using namespace antlr4;
```



创建 SysYLexer 对象和 SysYParser 对象，获取语法分析树，并创建 Visitor 对象并调用 visit 方法：

**main.cpp**

```
std::ifstream stream;
stream.open(argv[1]);
ANTLRInputStream input(stream);   // 创建 ANTLRInputStream 对象

SysYLexer lexer(&input);          // 创建 SysYLexer 对象
CommonTokenStream tokens(&lexer); // 创建 CommonTokenStream 对象
SysYParser parser(&tokens);       // 创建 SysYParser 对象

tree::ParseTree* tree = parser.compUnit(); // 获取语法分析树

SysYFormatter formatter;
std::string formatted = std::any_cast<std::string>(formatter.visit(tree));
```

##### 如何遍历语法树：Visitor 设计模式

ANTLR4已经为我们生成了语法分析树，你需要利用 [Visitor 设计模式](https://refactoringguru.cn/design-patterns/visitor) 来遍历这棵语法分析树并生成代码。

![Visitor 设计模式](http://166.111.80.114:8000/pa/images/visitor-pattern.png)

##### SysYFormatter类

你需要自己定义一个`SysYFormatter`类，继承自`SysYParserBaseVisitor`类，并实现具体的`visit`方法。Visitor默认将对语法树进行深度优先遍历，你可以重写基类的方法来自定义遍历顺序。

**SysYFormatter.h**

```
class SysYFormatter : public SysYParserBaseVisitor {
  // 更多方法略去
  std::any visitVarDecl(SysYParser::VarDeclContext *ctx) override;
  std::any visitVarDef(SysYParser::VarDefContext *ctx) override;
}
```

- 每个语法规则都对应一个具体的visit方法，例如`visitVarDecl`，你需要重写这些函数实现语法树的打印。
- 你需要定义一些变量/数据结构来存储生成的格式化代码。

下面是一个具体的`visitVarDecl`方法，你可以根据你自己的设计进行修改，助教的示例代码只是一个参考：



**SysYFormatter.cpp**

```
// varDecl
//   : bType varDef (COMMA varDef)* SEMICOLON
//   ;
std::any SysYFormatter::visitVarDecl(SysYParser::VarDeclContext *ctx) {
  // 你需要考虑添加缩进
  visit(ctx->bType());
  // 输出一个空格

  bool isFirstVarDef = true;
  for (auto *def : ctx->varDef()) {
    if (!isFirstVarDef) {
      // 输出 ", "
    }
    isFirstVarDef = false;
    visit(def);
  }

  // 输出一个分号，你也可以用 ctx->SEMICOLON()->getText()) 来获得分号
  // 输出一个换行符
  return nullptr;
}
```

更多用法请大家自行研究IDE的代码提示、ANTLR4 文档或询问大语言模型。



##### 如何处理缩进

- 你需要定义一个变量`indentLevel`，记录当前缩进级别，当访问`if`、`block`等节点时，增加缩进级别，访问完节点后，减少缩进级别。
- 你需要根据当前的缩进级别输出对应数量的空格。

### 运行与测试

PA3采用 CMake 构建项目，你也可以自行编译所有的 .cpp 文件。下面以 CMake 构建为例，在项目根目录中执行下面的命令：

```
mkdir build
cd build
cmake ..
make -j4
```

此时，可以看到`build/`目录下生成了可执行文件`sysy_formatter`，执行`./sysy_formatter ../test.c`运行代码格式化工具。

当然，你可以配置你的 Clion / VSCode 等现代编程工具，利用 GUI 图形界面完成构建与运行。

对于PA3，我们为大家提供了 5 个本地的测试用例，你可以在`pa3`目录运行`make test`来可视化测试结果。

![可视化测试结果](http://166.111.80.114:8000/pa/images/pa3-test.png)

本次测试通过不代表 OJ 测试通过，**当 OJ 中的隐藏用例不通过时，你需要自行设计测试用例进行调试**。

### 提交与评分

在项目根目录(pa3/)运行`python package.py`生成ZIP压缩包，将压缩包上传到 GradeScope 上。

压缩包预期的结构如下：

```
project.zip
├── CMakeLists.txt                  # CMake 文件, 最好不要修改
├── SysYLexer.g4                    # 词法规则文件
├── SysYParser.g4                   # 语法规则文件
├── include                         # 头文件
│   └── SysYFormatter.h
└── src                             # 源文件
    ├── SysYFormatter.cpp
    ├── SysYLexer.cpp
    ├── SysYLexer.h
    ├── SysYLexer.interp
    ├── SysYLexer.tokens
    ├── SysYParser.cpp
    ├── SysYParser.h
    ├── SysYParser.interp
    ├── SysYParser.tokens
    ├── SysYParserBaseVisitor.cpp
    ├── SysYParserBaseVisitor.h
    ├── SysYParserVisitor.cpp
    ├── SysYParserVisitor.h
    └── main.cpp
```

提交后耐心等待自动评分结果，Online Judge 会构建 Docker 对你项目进行自动测试。你可以多次提交你的代码，请注意 GradeScope 可以选择你的历史提交分数，你应当选择你的历史最高分作为成绩。

------

写在最后，在完成 PA3 后，你已经基本学会了 ANTLR4 的使用方法。大作业的核心也是利用 Visitor 模式遍历语法树来生成 LLVM IR 代码，当然你还需要考虑软件设计、类型系统、符号表、基本块组织等细节内容。

（大作业还没设计好， 敬请期待， 我们保留更换大作业选题的权力）

写完 PA3 大家辛苦了，希望大家能认真回顾这份代码，为大作业做好准备。