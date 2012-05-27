del *.cpp
del *.c
del *.h
del *.tokens

java -jar antlr-3.2.jar ComplexLexer.g
java -jar antlr-3.2.jar ComplexParser.g
java -jar antlr-3.2.jar ComplexEval.g

ren ComplexLexer.c ComplexLexer.cpp
ren ComplexParser.c ComplexParser.cpp
ren ComplexEval.c ComplexEval.cpp