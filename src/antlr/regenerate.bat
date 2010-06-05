del *.c
del *.h
del *.tokens

java org.antlr.Tool ComplexLexer.g
java org.antlr.Tool ComplexParser.g
java org.antlr.Tool ComplexEval.g