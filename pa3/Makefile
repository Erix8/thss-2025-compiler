antlr:
	java -jar antlr-4.13.1-complete.jar -Dlanguage=Cpp -visitor -no-listener -o src/ SysYLexer.g4 SysYParser.g4

clean:
	rm -f src/SysYLexer.cpp src/SysYParser.cpp src/SysYLexer.h src/SysYParser.h  
	rm -f src/SysYParserBaseVisitor.h src/SysYParserVisitor.h
	rm -f src/SysYParserBaseVisitor.cpp src/SysYParserVisitor.cpp
	rm -f src/*.interp src/*.tokens

test:
	python3 run-test.py

.PHONY: antlr clean test
