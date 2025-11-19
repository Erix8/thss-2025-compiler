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