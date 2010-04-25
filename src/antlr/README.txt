
This folder contains ANTLR generated source files. Unless gramar files are
changed, these files should not be touched. 

ANTLR is modern, free lexer/parser generator. To learn more about ANTLR go 
here:

	- http://www.antlr.org/

How to regenerate these sources?
================================

To regenerate MathyResurrected parser source you will need ANTLR and Java.

	- http://www.antlr.org/download/antlr-3.2.jar

Recomended version ANTLR version is 3.2. Lower versions are not 
guaranteed to work. After that:

	- copy antlr-3.2.jar to this folder 
	- set java classpath variable. In windows Cmd this can be done like 
	  this:
	  
		set CLASSPATH=%CLASSPATH%;antlr-3.2.jar
		
	  In other shells (sh and similar) you will probably need to export 
	  CLASSPATH variable. See your specific shell documentation. 
	- now we are ready to go, execute these comands:
	
		java org.antlr.Tool ComplexLexer.g
		java org.antlr.Tool ComplexParser.g
		java org.antlr.Tool ComplexEval.g