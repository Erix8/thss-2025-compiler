# PA1: 基于ANTLR4的词法分析器

## Soft Deadline

**2025 年 10 月 14 日 23：59**

## 实验描述

在《汇编与编译原理》的第一个PA (Programming Assignments) 中，你需要利用ANTLR4 **独立完成** 一个简易C语言（SysY语言）的词法分析器。

### Part1: 环境配置

在前两次PA中，我们不对环境配置做过多要求，但我们推荐将使用 Ubuntu22.04 系统作为你的开发环境。在Lab(大作业)中我们会详细讲解操作系统的选择以及环境配置。

我们推荐你用下面的两种方式安装`ANTLR4`:

- 方法一：使用`pip install` 安装：

  ```
  pip install antlr4-tools
  ```

  > 如果你希望快速开始，不想手动管理`.jar`文件并希望用 Python 语言完成大作业，我们推荐你采用这种方式安装。

- 方法二：手动下载`.jar`文件（以 Ubuntu22.04 操作系统为例）： `ANTLR`依赖 Java，所以你需要先安装 Java 环境。

  ```
  sudo apt-get update
  sudo apt-get install openjdk-11-jdk curl
  ```

  从官网下载 antlr-4.13.1 的 jar 包

  ```
  sudo curl -L -o /usr/local/lib/antlr-4.13.1-complete.jar https://www.antlr.org/download/antlr-4.13.1-complete.jar
  ```

  将下面的内容添加到`~/.bashrc`或`~/.zshrc`来设置环境变量和别名：

  ```
  export CLASSPATH=/usr/local/lib/antlr-4.13.1-complete.jar:.
  alias antlr4='java -jar /usr/local/lib/antlr-4.13.1-complete.jar'
  ```
  
  > 这种安装方式能严格固定 ANTLR 版本，保证你的实验代码能通过 Online Judge 的测试，如果你希望用 C++ / Java 完成大作业，我们推荐你采用这种方式安装。

### Part2: 编写g4文件

**ANTLR**（ANother Tool for Language Recognition）是一个强大的开源生成工具，支持生成词法分析器、解析器以及树解析器。通过定义语法规则(.g4文件)，ANTLR能自动生成解析器代码。

下面，我们通过 [ANTLR官网](https://www.antlr.org/) 的小例子来简单介绍一下ANTLR的使用以及`.g4`文件的编写。

**Expr.g4**

```
grammar Expr;
prog:   (expr NEWLINE)* ;
expr:   expr ('*'|'/') expr
    |   expr ('+'|'-') expr
    |   INT
    |   '(' expr ')'
    ;
NEWLINE : [\r\n]+ ;
INT     : [0-9]+ ;
```

- 第一行 `grammar Expr` 是一个语法名称声明, `grammar`关键字用于声明这是一个语法定义文件，`Expr`是语法名称，必须与文件名一致。

- 接下来是一系列规则，规则的基本格式是`规则名: 模式`，其中词法规则名的首字母必须大写。对于关键字、运算符，规则编写非常容易，例如：

  ```
  CONST : 'const';
  LE : '<=';
  ```

  

- 第二行的 prog 规则，表示`prog`可以匹配零个或多个 `expr NEWLINE` 序列，`(expr NEWLINE)*`表示 `expr` 后跟换行符的模式可以重复零次或多次。

- 第三行开始的的 expr 规则是一个递归定义的表达式规则，包含四种可能的匹配方式：

- `expr ('*'|'/') expr`: 乘法或除法表达式（优先级较高）, 竖线表示或

- `expr ('+'|'-') expr`: 加法或减法表达式（优先级较低）

- `INT`: 整数常量

- `'(' expr ')'`: 括号表达式

- 第八行开始是词法规则，也就是本次实验你需要完成的任务。`NEWLINE`规则表示匹配一个或多个回车`(\r)`或换行`(\n)`字符，`INT`规则表示匹配一个或多个数字字符，其中`[0-9]`表示数字0到9的范围。

除此之外，对于编程语言中复杂的组成单元，你可以先定义一些`fragment`,它本身不会生成独立的词法符号，可以用于定义可重用的词法规则片段。例如：

```
fragment digit : [0-9]; // fragment 规则，只能被其他规则引用

INT : digit+;           // 使用 fragment 定义整数
```

现在，你已经对 ANTLR 的 g4 文件有了一个初步的认识，请你进一步阅读助教编写的[ANTLR使用指南](http://166.111.80.114:8000/labs/antlr/)，学习ANTLR更多使用方法。

下面正式介绍本次实验的内容，你需要阅读下面简易C语言的词法规则，完成词法分析文件g4的编写，其中`IDENT`、`INTEGER_CONST`、`MULTILINE_COMMENT`需要你自行完成规则编写。你的文件需要命名为`SysYLexer.g4`, 并将`lexer grammar SysYLexer;`作为 g4 文件的第一行。

词法规则如下，请注意你的g4文件中的规则名请和下面的规则保持一致，否则可能无法通过OJ的测试：

**SysY语言词法规则**

```
CONST -> 'const';

INT -> 'int';

VOID -> 'void';

IF -> 'if';

ELSE -> 'else';

WHILE -> 'while';

BREAK -> 'break';

CONTINUE -> 'continue';

RETURN -> 'return';

PLUS -> '+';

MINUS -> '-';

MUL -> '*';

DIV -> '/';

MOD -> '%';

ASSIGN -> '=';

EQ -> '==';

NEQ -> '!=';

LT -> '<';

GT -> '>';

LE -> '<=';

GE -> '>=';

NOT -> '!';

AND -> '&&';

OR -> '||';

L_PAREN -> '(';

R_PAREN -> ')';

L_BRACE -> '{';

R_BRACE -> '}';

L_BRACKT -> '[';

R_BRACKT -> ']';

COMMA -> ',';

SEMICOLON -> ';';

IDENT : 以下划线或字母开头，仅包含下划线、英文字母大小写、阿拉伯数字
   ;

INTEGER_CONST : 数字常量，包含十进制数，0开头的八进制数，0x或0X开头的十六进制数
   ;

WS
   -> [ \r\n\t]+
   ;

LINE_COMMENT
   -> '//' .*? '\n'
   ;

MULTILINE_COMMENT : 同标准C语言，以'/*'开头，以'*/'结尾 
   ;
```

**注意，你的词法分析器无需输出注释相关的内容。**

### Part3: 生成词法分析器

PA1的任务其实很简单，你只需要运行下面的代码来自测自己的 g4 文件是否编写正确即可:

```
antlr4 SysYLexer.g4
javac SysYLexer.java
java org.antlr.v4.gui.TestRig SysYLexer tokens -tokens
```

当你输入下面的程序时：

```
int main() {
    int a1 = 1;
    int _b = 2;
    c = (a1 + _b) * 0x3f; 
    return c;
}
```

你的词法分析器应当输出下面的结果：

```
[@0,0:2='int',<'int'>,1:0]
[@1,4:7='main',<IDENT>,1:4]
[@2,8:8='(',<'('>,1:8]
[@3,9:9=')',<')'>,1:9]
[@4,11:11='{',<'{'>,1:11]
[@5,17:19='int',<'int'>,2:4]
[@6,21:22='a1',<IDENT>,2:8]
[@7,24:24='=',<'='>,2:11]
[@8,26:26='1',<INTEGER_CONST>,2:13]
[@9,27:27=';',<';'>,2:14]
[@10,33:35='int',<'int'>,3:4]
[@11,37:38='_b',<IDENT>,3:8]
[@12,40:40='=',<'='>,3:11]
[@13,42:42='2',<INTEGER_CONST>,3:13]
[@14,43:43=';',<';'>,3:14]
[@15,49:49='c',<IDENT>,4:4]
[@16,51:51='=',<'='>,4:6]
[@17,53:53='(',<'('>,4:8]
[@18,54:55='a1',<IDENT>,4:9]
[@19,57:57='+',<'+'>,4:12]
[@20,59:60='_b',<IDENT>,4:14]
[@21,61:61=')',<')'>,4:16]
[@22,63:63='*',<'*'>,4:18]
[@23,65:68='0x3f',<INTEGER_CONST>,4:20]
[@24,69:69=';',<';'>,4:24]
[@25,76:81='return',<'return'>,5:4]
[@26,83:83='c',<IDENT>,5:11]
[@27,84:84=';',<';'>,5:12]
[@28,86:86='}',<'}'>,6:0]
[@29,88:87='<EOF>',<EOF>,7:0]
```

当然，你也可以根据[ANTLR4使用指南](http://166.111.80.114:8000/labs/antlr/)中的内容自行编写应用程序来输出 token 流。

### 代码与测试

本次 PA 不提供框架代码，你需要自己新建`SysYLexer.g4`文件完成实验并自行编写测试用例测试你词法分析器的正确性。在 Online Judge 中，助教团队准备了若干简易C语言的测试用例来测试词法分析的正确性。你无需实现上述词法规则之外的C语言词法。本次实验代码量约50行。

### 提交与评分

**在 GradeScope 上提交实验代码：**

1. **注册账号**：请每位同学按照 [OJ使用方法](http://166.111.80.114:8000/pa/oj/) 中的指南注册账号。

2. **代码要求**： 提交ZIP文件，注意ZIP文件中只包含`SysYLexer.g4`一个文件，不要有子文件夹。

   项目结构如下：

   ```
   project.zip
   └── SysYLexer.g4
   ```

3. **查看反馈**：提交后耐心等待自动评分结果，Online Judge 会构建 Docker 对你项目进行自动测试，你可以多次提交。注意 GradeScope 可以选择你的历史提交分数，你应当选择你的历史最高分作为成绩。