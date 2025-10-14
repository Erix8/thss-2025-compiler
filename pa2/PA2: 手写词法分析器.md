# PA2: 手写词法分析器

## Soft Deadline

**2025 年 10 月 28 日 23：59**

## 实验描述

在PA1中，我们已经学习了ANTLR4 g4文件的写法，并利用ANTLR4自动化生成了词法分析器。而在本次PA中，我们希望同学们用 C++ 语言，自行实现一个简单的词法分析器。

为什么要手写词法分析器？

同学们可能有疑问，明明在PA1中我们已经能自动化生成词法分析器了，为什么还要手写一个呢？事实上，手写一个词法分析器并不复杂，而且手写词法分析器可以针对特定场景优化。在 gcc 等编译器中，开发人员仍会选择自己手写词法分析器。

在开始本次实验前，请确保你已配置好 C++17 开发环境（需安装 CMake，推荐使用 VSCode 或 CLion 作为 IDE），此外，你还需要安装 Python3，用于将代码打包为 ZIP 压缩包并上传至 GradeScope。

如果你使用 Ubuntu22.04, 可以通过下面的方式配置环境：

```
sudo apt update
sudo apt install build-essential cmake git python3
```

**为了锻炼你的编程能力，请不要直接使用大语言模型来完成代码编写**，但询问大语言模型 C++17 语法、g4 文件的含义是被允许的。

### 词法规则描述

为了降低大家的任务量，我们选择了改编自龙书的一段词法规则 **DragonLexerGramar** 作为本次实验需要解析的词法规则。我们采用g4文件的形式给出DragonLexer的词法。

**DragonLexerGrammar.g4**

```
lexer grammar DragonLexerGrammar;

WS : [ \t\r\n]+ -> skip;

IF : 'if' ;
ELSE : 'else' ;
ID : LETTER (LETTER | DIGIT)* ;

INT : DIGITS ;

EQ : '=' ;
NE : '<>' ;
LT : '<' ;
LE : '<=' ;
GT : '>' ;
GE : '>=' ;

DOT : '.' ;
POS : '+' ;
NEG : '-' ;
SQUOTE : '\'' ;

REAL : DIGITS ('.' DIGITS)? ;
SCI : DIGITS ('.' DIGITS)? ([eE] [+-]? DIGITS)? ;

fragment DIGIT :  [0-9] ;
fragment DIGITS : [0-9] ('\''? [0-9])* ;
fragment LETTER : [a-zA-Z] ;
```

**注意**：当有多个规则可匹配时，ANTLR4会选择最先定义的规则，例如`123`会被识别成`INT`而不是`SCI`，你的词法分析器也要遵循相同的原则。此外，词法分析器应当总是尝试匹配尽可能长的字符串。

### 输入输出要求

程序输入是一段符合DragonLexerGramar词法的一段程序，你需要在标准输出(stdout)中输出词法分析的结果，每个词法单元(token)占一行，格式为：

```
TOKEN类型 TOKEN内容 at Line 行数.
```

这一部分的内容已经在框架代码中为你写好，你无需改动。本次OJ采用标准输入输出进行测试，忽略行尾空格和结尾换行。

#### 输入样例

```
123
0543
123+xyz
3<=4
3abc3
123.45E-67
123.45-67
123.45E-
123'123'
123.4'56
```

#### 输出样例

```
INT 123 at Line 1.
INT 0543 at Line 2.
INT 123 at Line 3.
PLUS + at Line 3.
IDENT xyz at Line 3.
INT 3 at Line 4.
LE <= at Line 4.
INT 4 at Line 4.
INT 3 at Line 5.
IDENT abc3 at Line 5.
SCI 123.45E-67 at Line 6.
REAL 123.45 at Line 7.
MINUS - at Line 7.
INT 67 at Line 7.
REAL 123.45 at Line 8.
IDENT E at Line 8.
MINUS - at Line 8.
INT 123'123 at Line 9.
SQUOTE ' at Line 9.
REAL 123.4'56 at Line 10.
```

### Part1: 框架代码导读

你需要使用`git`下载实验的框架代码，具体步骤如下：

**方法一**:

- 访问 [GitHub-thss-2025-compiler](https://github.com/Nboxff/thss-2025-compiler) 仓库，点击右上角的 fork 按钮，创建一个同名的仓库。
- 克隆你 fork 的仓库，`git clone https://github.com/YourName/thss-2025-compiler.git`
- 在项目根目录执行`cd pa2`进入本次实验的目录。

注意：在实验结束前，请不要公开你的作业代码，即你不应该将你的代码推送到公共仓库。

**方法二**:

创建一个你自己的仓库（若在 GitHub 创建请将权限设置为 private ）。执行下面的代码：

```
git clone <YourRepo> # 如果在GitHub创建

git remote add upstream https://github.com/Nboxff/thss-2025-compiler.git

git fetch upstream
git merge upstream/main --allow-unrelated-histories

git push origin main
```

在框架代码中， `main`函数是整个程序的入口，将用户输入的C程序交由词法分析器`lexer`进行解析，之后每次读取一个 token，输出 token 类型、token 内容以及所在行号。

**main.cpp**

```
int main() {
  std::ostringstream ss;
  ss << std::cin.rdbuf();
  std::string input = ss.str();

  DragonLexer lexer(input);
  while (true) {
    Token t = lexer.nextToken();
    if (t.type == TokenType::WS) {
      continue;
    } else if (t.type == TokenType::EOF_T) {
      break;
    } else {
      std::string typ = tokenTypeToString(t.type);
      std::cout << typ << " " << t.text << " at Line " << t.line << "." << std::endl;
    }
  }
  return 0;
}
```

- `Token.hpp`和`Token.cpp`定义了所有token的类型以及token对应的字符串，当需要添加新的token类型时，你需要修改这两个文件。
- `KeywordTable.hpp`和`KeywordTable.cpp`这两个文件保存了词法规则中的关键字，你需要调用`KeywordTable`类中的方法来区分关键字和普通的变量名。
- 在`Lexer.hpp`和`Lexer.cpp`中，`Lexer`类是词法分析器的基类，保存了当前处理的位置、字符、行数等信息，并提供了`nextToken() -> Token`纯虚函数，交由派生类来实现。
- `DragonLexer.hpp`和`DragonLexer.cpp`中实现了本次实验具体的词法分析器，负责实现每个词法单元的解析。

框架代码能解析的词法规则比`DragonLexerGrammar.g4`文件中描述的词法要多，你可以仔细阅读框架代码，了解框架代码的设计是如何支持软件的可扩展性的。

### Part2: 完善词法分析器

在本任务中，你首先需要在`Token.hpp`和`Token.cpp`中添加一个框架代码中为实现的 token 类型：`SQUOTE`(单引号)。

接着，你需要补全`Lexer.cpp`和`DragonLexer.cpp`两个文件。你可以修改框架代码中的其他文件，但请保证不要改变输入输出的格式。

我们在你需要完成代码编写的地方增加了`TODO`注释，如果你使用 VSCode 进行编程，你可以安装 **TODO Highlight** 这个插件来查看 TODO。本次实验代码量约 120 行。

### 运行与测试

PA2采用 CMake 构建项目，你也可以自行编译所有的 .cpp 文件。下面以 CMake 构建为例，在项目根目录中执行下面的命令：

```
mkdir build
cd build
cmake ..
make -j4
```

此时，可以看到`build/`目录下生成了可执行文件`dragon_lexer`或`dragon_lexer.exe`(Windows)，执行`./dragon_lexer`运行词法分析器。

当然，你可以配置你的 Clion / VSCode 等现代编程工具，利用 GUI 图形界面完成构建与运行。

对于PA2，我们只提供上面的样例，不提供具体的测试数据，你需要自行编写测试用例进行测试。

### 提交与评分

在项目根目录运行`python package.py`生成ZIP压缩包，将压缩包上传到 GradeScope 上。

压缩包预期的结构如下：

```
project.zip
├── CMakeLists.txt
└── src
    ├── DragonLexer.cpp
    ├── DragonLexer.hpp
    ├── KeywordTable.cpp
    ├── KeywordTable.hpp
    ├── Lexer.cpp
    ├── Lexer.hpp
    ├── Token.cpp
    ├── Token.hpp
    └── main.cpp
```

GradeScope上共有 12 个测试用例，其中 10 个测试用例不涉及数值中的单引号。提交后耐心等待自动评分结果，Online Judge 会构建 Docker 对你项目进行自动测试。你可以多次提交你的代码，请注意 GradeScope 可以选择你的历史提交分数，你应当选择你的历史最高分作为成绩。