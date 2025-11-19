antlr:
	java -jar antlr-4.13.1-complete.jar -Dlanguage=Cpp -visitor -no-listener -o src/antlr/ Calculator.g4

clean:
	rm src/antlr/*.cpp src/antlr/*.h 
	rm src/antlr/*.interp src/antlr/*.tokens

test: 
	python3 run-test.py

.PHONY: antlr clean test