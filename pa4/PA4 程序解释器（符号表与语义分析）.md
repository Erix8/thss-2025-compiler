# PA4: 程序解释器（符号表与语义分析）

## Soft Deadline

**2025 年 12 月 2 日 23：59**

本次作业为选做作业，完成本次作业会有少量加分，但 PA 和 Homework 两部分总分不超过25分。

开始之前

**请通过下面的命令获取 PA4 框架代码**（假设你已经按 PA2 的要求设置好 upstream 仓库）：

```
git fetch upstream
git checkout main       # 切换到你的本地分支
git merge upstream/main # 合并上游的变更
```

你也可以手动下载 [框架代码](https://github.com/Nboxff/thss-2025-compiler) 中的`pa4` 文件夹，将其复制到你的本地项目根目录中。



## 实验描述

程序的解释执行无需提前编译，而是由解释器逐行读取源代码，边解析边执行。这种方式启动速度快、跨平台性好，并且便于调试，但运行效率一般低于编译执行。Python、JavaScript 等语言常采用解释执行方式，适用于脚本开发、快速迭代或需要动态调整的场景，本质上是牺牲部分运行性能来换取更高的灵活性。

在 PA4 中，你需要实现一个简单的程序解释器，它需要支持以下功能：

1. **变量定义**：支持定义多个变量，例如`a = 1`, 并能在变量所在的作用域中使用这个变量。
2. **整数运算**：支持加（`+`）、减(`-`)、乘(`*`)、整除(`/`)、取余(`%`)五种基本的整数运算。
3. **打印语句**：支持使用`print`关键字打印变量或表达式的值。
4. **错误检查**：在对未定义变量的访问时，直接返回一个错误，不再执行下面的语句。

### Part0: 环境配置

本次实验环境配置与 PA3 完全相同。

### Part1: 程序解释器实现

在本次实验中，我们已为你提供描述本次语言的语法规则文件：

**Calculator.g4**

```
grammar Calculator;

program: statement+ EOF;

statement
    : assignment
    | block
    | printStmt
    ;

assignment: ID '=' expr ';';

block: '{' statement* '}';

printStmt: 'print' expr ';';

expr
    : '(' expr ')'                # parenExpr
    | ID                          # lvalExpr
    | INT                         # intExpr
    | expr (MUL | DIV | MOD) expr # mulExpr
    | expr (PLUS | MINUS) expr    # plusExpr
    ;


INT: [0-9]+;
ID: [a-zA-Z_][a-zA-Z0-9_]*;

MUL: '*';
DIV: '/';
MOD: '%';
PLUS: '+';
MINUS: '-';

WS: [ \t\r\n]+ -> skip;
COMMENT: '#' ~[\r\n]* -> skip;
```

在 PA4 框架代码中，我们已为大家实现好 g4 文件，并生成了对应的词法分析器和语法分析器代码。你可以修改 g4 文件并运行`make antlr`重新生成词法分析器和语法分析器代码。

程序输入是符合上述文法规则的一段代码，你需要输出每个`print`语句的结果，每个结果占一行。

下面特别介绍一下这个小语言的特点：

- 内层作用域可以访问外层作用域的变量，但不能修改外层作用域的变量。如果你试图在内层作用域修改外层作用域的变量，它会创建一个新的局部变量，这个变量的生命周期和这个作用域一致。
- 变量屏蔽：大家平时写的 C 语言一致，当外层作用域定义了一个变量，内层作用域也定义了同名变量时，在内层作用域中会暂时屏蔽外层作用域中的变量。
- 顺序执行：程序中的语句会按照它们出现的顺序执行。

#### 输入样例

```
a = 10;
{
    b = a + 5;
    print b;  # 输出15
    a = 20;
    print a;  # 输出20
}
print a;  # 输出10（内部作用域的修改不影响外部, 类似 Python 的函数作用域）
```

#### 输出样例

```
15
20
10
```

数据保证所有运算不会超出 int32 的范围。

#### Part1 实验指导

当你观察到上面的输入样例时，你应该意识到 PA4 的核心是要设计一个**符号表**，通过符号表来管理变量定义。具体地说，给定一个符号名，你需要获得符号对应的值。

符号表应当有以下两个功能：

- 填表：在定义一个新的符号的时候，你需要往符号表里添加这个符号名以及它对应的信息
- 查表：在使用一个符号的时候，你需要判断符号表中是否存有这个符号的信息，并且从符号表中得到这个符号的所有信息。

符号表中应该存储那些信息？

这取决于你本身，只要觉得方便，可以向符号表中填入任何内容。在编译器类型检查中，符号表中需要存储变量的类型信息；在 LLVM IR 生成中，符号表应当存储相应的 Value（具体为虚拟寄存器）。

在考虑符号的**作用域**时，请注意：每当进入一个新的代码块（block），就会开启一个新的作用域；而退出该代码块时，作用域将返回到之前的状态。

你可以根据你的需要创建新的`.h`和`.cpp`文件。完成 Part1 的任务，你可以获得 PA4 76% 的分数。

### Part2: 错误处理

在 Part 2 中，你需要处理对未定义变量的访问。当访问到符号不存在于符号表中，你需要返回一个错误，并停止执行。

你需要在 stdout 中输出一个错误信息，格式为：`Error: Undefined symbol 'symbol_name' at line xxx`。

#### 输入样例

```
a = 1;
print a;
a = b + 1;
print a;
```

#### 输出样例

```
1
Error: Undefined symbol 'b' at line 3
```

### 运行与测试

PA4采用 CMake 构建项目，你也可以自行编译所有的 .cpp 文件。下面以 CMake 构建为例，在项目根目录中执行下面的命令：

```
mkdir build
cd build
cmake ..
make -j4
```

此时，可以看到`build/`目录下生成了可执行文件`interpreter`，执行`./interpreter`运行程序解释器。

当然，你可以配置你的 Clion / VSCode 等现代编程工具，利用 GUI 图形界面完成构建与运行。

对于PA4，我们为大家提供了 3 个本地的测试用例，你可以在`pa4`目录运行`make test`来可视化测试结果。

![可视化测试结果](http://166.111.80.114:8000/pa/images/pa4-test.png)

本地测试通过不代表 OJ 测试通过，**当 OJ 中的隐藏用例不通过时，你需要自行设计测试用例进行调试**。

### 提交与评分

在项目根目录(pa4/)运行`python package.py`生成ZIP压缩包，将压缩包上传到 GradeScope 上。

压缩包预期的结构如下：

```
project.zip
├── CMakeLists.txt                  # CMake 文件
├── Calculator.g4                   # 文法规则文件
├── include                         # 头文件
│   ├── InterpreterVisitor.h        # Your Visitor 头文件
│   └── ...                         # 你自己定义的其他头文件
└── src     
    ├── InterpreterVisitor.cpp      # Your Visitor 实现文件
    ├── ...                         # 你自己定义的其他 .cpp 文件
    ├── antlr
    │   ├── Calculator.interp
    │   ├── Calculator.tokens
    │   ├── CalculatorBaseVisitor.cpp
    │   ├── CalculatorBaseVisitor.h
    │   ├── CalculatorLexer.cpp
    │   ├── CalculatorLexer.h
    │   ├── CalculatorLexer.interp
    │   ├── CalculatorLexer.tokens
    │   ├── CalculatorParser.cpp
    │   ├── CalculatorParser.h
    │   ├── CalculatorVisitor.cpp
    │   └── CalculatorVisitor.h
    └── main.cpp
```

提交后耐心等待自动评分结果，Online Judge 会构建 Docker 对你项目进行自动测试。你可以多次提交你的代码，请注意 GradeScope 可以选择你的历史提交分数，你应当选择你的历史最高分作为成绩。

------

写在最后，在完成 PA4 后，你已经基本学会了如何设计符号表和管理作用域。在完成 PA3 熟悉了 Visitor 模式后，PA4 应该还是比较轻松的。