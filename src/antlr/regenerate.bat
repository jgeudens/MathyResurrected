del *.c
del *.h
del *.tokens

rem set CLASSPATH=%CLASSPATH%;antlr-3.2.jar

java org.antlr.Tool ComplexLexer.g
java org.antlr.Tool ComplexParser.g
java org.antlr.Tool ComplexEval.g