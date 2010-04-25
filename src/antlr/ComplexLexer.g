lexer grammar ComplexLexer;

options {
	language=C;
}

tokens {
  IM;
  RE;
  SI_CONVERT;
  CONSTANT_REF;
  FUNCTION;
  ATOM;
  UNARY;
}

@lexer::includes {
	#include "math_bridge_API.h"
}

PLUS : '+';
MINUS  : '-';
MULT : '*';
DIV : '/';
MOD : '%';
POW  : '^';
ARG_SEPARATOR : '#';
DECIMAL_POINT : '.';
LEFT_PAREN : '(';
RIGHT_PAREN : ')';

SI_PREFIX_YOTTA  :'Y';
SI_PREFIX_ZETTA  :'Z';
SI_PREFIX_EXA    :'E';
SI_PREFIX_PETA   :'P';
SI_PREFIX_TERA   :'T';
SI_PREFIX_GIGA   :'G';
SI_PREFIX_MEGA   :'M';
SI_PREFIX_KILO   :'k';
SI_PREFIX_HECTO  :'h';
SI_PREFIX_DECA   :'da';
SI_PREFIX_DECI   :'d';
SI_PREFIX_CENTI  :'c';
SI_PREFIX_MILLI  :'m';
SI_PREFIX_MICRO  :'u';
SI_PREFIX_NANO   :'n';
SI_PREFIX_PICO   :'p';
SI_PREFIX_FEMTO  :'f';
SI_PREFIX_ATTO   :'a';
SI_PREFIX_ZEPTO  :'z';
SI_PREFIX_YOCTO  :'y';
SI_PREFIX_KIBI   :'Ki';
SI_PREFIX_MEBI   :'Mi';
SI_PREFIX_GIBI   :'Gi';
SI_PREFIX_TEBI   :'Ti';
SI_PREFIX_PEBI   :'Pi';
SI_PREFIX_EXBI   :'Ei';
SI_PREFIX_ZEBI   :'Zi';
SI_PREFIX_YOBI   :'Yi';

FN_SIN    : (('s'|'S')('i'|'I')('n'|'N'));
FN_COS    : (('c'|'C')('o'|'O')('s'|'S'));
FN_TAN    : (('t'|'T')('a'|'A')('n'|'N'));
FN_ASIN   : (('a'|'A')('s'|'S')('i'|'I')('n'|'N'))
    | (('a'|'A')('r'|'R')('c'|'C')('s'|'S')('i'|'I')('n'|'N'));
FN_ACOS   : (('a'|'A')('c'|'C')('o'|'O')('s'|'S'))
    | (('a'|'A')('r'|'R')('c'|'C')('c'|'C')('o'|'O')('s'|'S'));
FN_ATAN   : (('a'|'A')('t'|'T')('a'|'A')('n'|'N'))
    | (('a'|'A')('r'|'R')('c'|'C')('t'|'T')('a'|'A')('n'|'N'));
FN_ATAN2  : (('a'|'A')('t'|'T')('a'|'A')('n'|'N')'2')
    | (('a'|'A')('r'|'R')('c'|'C')('t'|'T')('a'|'A')('n'|'N')'2');
FN_SINH   : (('s'|'S')('i'|'I')('n'|'N')('h'|'H'));
FN_COSH   : (('c'|'C')('o'|'O')('s'|'S')('h'|'H'));
FN_TANH   : (('t'|'T')('a'|'A')('n'|'N')('h'|'H'));
FN_ASINH  : (('a'|'A')('s'|'S')('i'|'I')('n'|'N')('h'|'H'))
    | (('a'|'A')('r'|'R')('c'|'C')('s'|'S')('i'|'I')('n'|'N')('h'|'H'));
FN_ACOSH  : (('a'|'A')('c'|'C')('o'|'O')('s'|'S')('h'|'H'))
    | (('a'|'A')('r'|'R')('c'|'C')('c'|'C')('o'|'O')('s'|'S')('h'|'H'));
FN_ATANH  : (('a'|'A')('t'|'T')('a'|'A')('n'|'N')('h'|'H'))
    | (('a'|'A')('r'|'R')('c'|'C')('t'|'T')('a'|'A')('n'|'N')('h'|'H'));
FN_EXP    : (('e'|'E')('x'|'X')('p'|'P'));
FN_LN   : (('l'|'L')('n'|'N'))
    | (('l'|'L')('o'|'O')('g'|'G'));
FN_LOG10  : (('l'|'L')('o'|'O')('g'|'G')'10');
FN_SQRT   : (('s'|'S')('q'|'Q')('r'|'R')('t'|'T'));
FN_POW    : (('p'|'P')('o'|'O')('w'|'W'));
FN_NRT    : (('n'|'N')('r'|'R')('t'|'T'));
FN_ABS    : (('a'|'A')('b'|'B')('s'|'S'));
FN_RE   : (('r'|'R')('e'|'E'));
FN_IM   : (('i'|'I')('m'|'M'));
FN_ARG    : (('a'|'A')('r'|'R')('g'|'G'));
FN_CONJ   : (('c'|'C')('o'|'O')('n'|'N')('j'|'J'));
FN_MIN    : (('m'|'M')('i'|'I')('n'|'N'));
FN_MAX    : (('m'|'M')('a'|'A')('x'|'X'));
FN_DEG    : (('d'|'D')('e'|'E')('g'|'G'));
FN_RAD    : (('r'|'R')('a'|'A')('d'|'D'));
FN_PROJ   : (('p'|'P')('r'|'R')('o'|'O')('j'|'J'));
FN_NORM   : (('n'|'N')('o'|'O')('r'|'R')('m'|'M'));
FN_POLAR  : (('p'|'P')('o'|'O')('l'|'L')('a'|'A')('r'|'R'));

CONSTANTS_PI  : 'pi';
CONSTANTS_E : 'e';

COMPLEX_UNIT  : 'i' | 'j';

FLOAT_NUMBER  
	: FLOAT_MANTISSA EXPONENT?
	;

fragment DEC_DIGIT
    : '0'..'9' 
    ;

fragment FLOAT_MANTISSA
    : DEC_DIGIT+ 
	    ( DECIMAL_POINT
	    	(
	    		DEC_DIGIT+
	    		|
	    		{ 
					$type = LEXER_ERROR;
					collectlexerError(GETCHARINDEX()-1, LEX_ERR_MALFORMED_MANTISSA); 
				}
	    	)
	    )? 
	| DECIMAL_POINT (
		DEC_DIGIT+
		|
		{ 
			$type = LEXER_ERROR;
			collectlexerError(GETCHARINDEX()-1, LEX_ERR_MALFORMED_MANTISSA); 
		}
	)
    ;

fragment EXPONENT
    : ('e' | 'E') (PLUS | MINUS)? (
		DEC_DIGIT+
		|   
		{ 
			$type = LEXER_ERROR;
			collectlexerError(GETCHARINDEX()-1, LEX_ERR_MALFORMED_EXPONENT); 
		}
    )
	;
	
/* Ignore white spaces */
WS    :  (' '|'\r'|'\t'|'\u000C'|'\n') { $channel=HIDDEN; }; 

fragment LEXER_ERROR : ;

/* Match anything that hasn't been mathced. Issue lexer error about 
illegal input */
OTHER_CHAR 
	:. {
		$type = LEXER_ERROR;
		collectlexerError(GETCHARINDEX()-1, LEX_ERR_BAD_INPUT); 
	};