parser grammar ComplexParser;

options {
	tokenVocab=ComplexLexer;
	output=AST;
	ASTLabelType=pANTLR3_BASE_TREE;
	language=C;
}

@parser::includes {
	#include "math_bridge_API.h"
}

prog
  : expr EOF!
  ;

expr
  : addition
  ;

addition
  : multiplication ( (PLUS|MINUS)^ multiplication )*
  ;

multiplication
  : exponentiation ( (MULT|DIV|MOD)^ exponentiation )*
  ;

exponentiation
  : unary ( POW^ exponentiation )?
  ;

unary
  : MINUS? LEFT_PAREN expr RIGHT_PAREN -> ^(UNARY MINUS? expr)
  | atom
  ;
  
atom
  : MINUS? real_number -> ^(ATOM MINUS? real_number)
  | MINUS? imaginary_number -> ^(ATOM MINUS? imaginary_number)
  | MINUS? si_unit_ref -> ^(ATOM MINUS? si_unit_ref)
  | MINUS? constant_ref -> ^(ATOM MINUS? constant_ref)
  | MINUS? funct_ref1 -> ^(ATOM MINUS? funct_ref1)
  | MINUS? funct_ref2 -> ^(ATOM MINUS? funct_ref2)
  ;

funct_ref1
  : FN_SIN LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_SIN expr)
  | FN_COS LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_COS expr)
  | FN_TAN LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_TAN expr)
  | FN_ASIN LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ASIN expr)
  | FN_ACOS LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ACOS expr)
  | FN_ATAN LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ATAN expr)
  | FN_SINH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_SINH expr)
  | FN_COSH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_COSH expr)
  | FN_TANH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_TANH expr)
  | FN_ASINH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ASINH expr)
  | FN_ACOSH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ACOSH expr)
  | FN_ATANH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ATANH expr)
  | FN_EXP LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_EXP expr)
  | FN_LN LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_LN expr)
  | FN_LOG10 LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_LOG10 expr)
  | FN_SQRT LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_SQRT expr)
  | FN_ABS LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ABS expr)
  | FN_RE LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_RE expr)
  | FN_IM LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_IM expr)
  | FN_ARG LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ARG expr)
  | FN_CONJ LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_CONJ expr)
  | FN_DEG LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_DEG expr)
  | FN_RAD LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_RAD expr)
  | FN_NORM LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_NORM expr)
  | FN_POLAR LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_POLAR expr)
  ;
  
funct_ref2
  : FN_ATAN2 LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN -> ^(FUNCTION FN_ATAN2 $a $b)
  | FN_POW LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN -> ^(FUNCTION FN_POW $a $b)
  ;

constant_ref
  : CONSTANTS_PI -> ^(CONSTANT_REF CONSTANTS_PI)
  | CONSTANTS_E -> ^(CONSTANT_REF CONSTANTS_E)
  | CONSTANTS_ANS -> ^(CONSTANT_REF CONSTANTS_ANS)
  ;

si_unit_ref
  : real_number SI_PREFIX_YOTTA -> ^(SI_CONVERT real_number SI_PREFIX_YOTTA)
  | real_number SI_PREFIX_ZETTA -> ^(SI_CONVERT real_number SI_PREFIX_ZETTA)
  | real_number SI_PREFIX_EXA -> ^(SI_CONVERT real_number SI_PREFIX_EXA)
  | real_number SI_PREFIX_PETA -> ^(SI_CONVERT real_number SI_PREFIX_PETA)
  | real_number SI_PREFIX_TERA -> ^(SI_CONVERT real_number SI_PREFIX_TERA)
  | real_number SI_PREFIX_GIGA -> ^(SI_CONVERT real_number SI_PREFIX_GIGA)
  | real_number SI_PREFIX_MEGA -> ^(SI_CONVERT real_number SI_PREFIX_MEGA)
  | real_number SI_PREFIX_KILO -> ^(SI_CONVERT real_number SI_PREFIX_KILO)
  | real_number SI_PREFIX_HECTO -> ^(SI_CONVERT real_number SI_PREFIX_HECTO)
  | real_number SI_PREFIX_DECA -> ^(SI_CONVERT real_number SI_PREFIX_DECA)
  | real_number SI_PREFIX_DECI -> ^(SI_CONVERT real_number SI_PREFIX_DECI)
  | real_number SI_PREFIX_CENTI -> ^(SI_CONVERT real_number SI_PREFIX_CENTI)
  | real_number SI_PREFIX_MILLI -> ^(SI_CONVERT real_number SI_PREFIX_MILLI)
  | real_number SI_PREFIX_MICRO -> ^(SI_CONVERT real_number SI_PREFIX_MICRO)
  | real_number SI_PREFIX_NANO -> ^(SI_CONVERT real_number SI_PREFIX_NANO)
  | real_number SI_PREFIX_PICO -> ^(SI_CONVERT real_number SI_PREFIX_PICO)
  | real_number SI_PREFIX_FEMTO -> ^(SI_CONVERT real_number SI_PREFIX_FEMTO)
  | real_number SI_PREFIX_ATTO -> ^(SI_CONVERT real_number SI_PREFIX_ATTO)
  | real_number SI_PREFIX_ZEPTO -> ^(SI_CONVERT real_number SI_PREFIX_ZEPTO)
  | real_number SI_PREFIX_YOCTO -> ^(SI_CONVERT real_number SI_PREFIX_YOCTO)
  | real_number SI_PREFIX_KIBI -> ^(SI_CONVERT real_number SI_PREFIX_KIBI)
  | real_number SI_PREFIX_MEBI -> ^(SI_CONVERT real_number SI_PREFIX_MEBI)
  | real_number SI_PREFIX_GIBI -> ^(SI_CONVERT real_number SI_PREFIX_GIBI)
  | real_number SI_PREFIX_TEBI -> ^(SI_CONVERT real_number SI_PREFIX_TEBI)
  | real_number SI_PREFIX_PEBI -> ^(SI_CONVERT real_number SI_PREFIX_PEBI)
  | real_number SI_PREFIX_EXBI -> ^(SI_CONVERT real_number SI_PREFIX_EXBI)
  | real_number SI_PREFIX_ZEBI -> ^(SI_CONVERT real_number SI_PREFIX_ZEBI)
  | real_number SI_PREFIX_YOBI -> ^(SI_CONVERT real_number SI_PREFIX_YOBI)
  ;

imaginary_number
    : real_number? COMPLEX_UNIT -> ^(IM real_number? COMPLEX_UNIT)
	;

real_number : FLOAT_NUMBER -> ^(RE FLOAT_NUMBER);