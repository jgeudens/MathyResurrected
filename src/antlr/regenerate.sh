rm *.c
rm *.cpp
rm *.h
rm *.tokens

java -jar antlr-3.2.jar ComplexLexer.g
java -jar antlr-3.2.jar ComplexParser.g
java -jar antlr-3.2.jar ComplexEval.g

mv ComplexLexer.c ComplexLexer.cpp
mv ComplexParser.c ComplexParser.cpp
mv ComplexEval.c ComplexEval.cpp