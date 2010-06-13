parser grammar ComplexParser;

options {
    tokenVocab=ComplexLexer;
    output=AST;
    ASTLabelType=pANTLR3_BASE_TREE;
    language=C;
}

prog
    : expr EOF!
    ;

expr
  : bitor
  ;

bitor
  : bitxor ( BW_OR^ bitxor )*
  ;
  
bitxor
  : bitand ( BW_XOR^ bitand )*
  ;

bitand
  : bitshift ( BW_AND^ bitshift )*
  ;
  
bitshift
  : addition ( (BW_SHLEFT | BW_SHRIGHT)^ addition)*
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
    : MINUS atom    -> ^(UNARY MINUS atom)
    | PLUS atom     -> ^(UNARY PLUS atom)
    | BW_NOT atom   -> ^(UNARY BW_NOT atom)
    | atom
    ;

atom
    :  real_number                  -> ^(ATOM real_number)
    |  imaginary_number             -> ^(ATOM imaginary_number)
    |  real_number si_unit_ref      -> ^(ATOM real_number si_unit_ref)
    |  imaginary_number si_unit_ref -> ^(ATOM imaginary_number si_unit_ref)
    |  constant_ref                 -> ^(ATOM constant_ref)
    |  funct_ref1                   -> ^(ATOM funct_ref1)
    |  funct_ref2                   -> ^(ATOM funct_ref2)
    |  LEFT_PAREN expr RIGHT_PAREN  -> ^(ATOM expr)
    ;

funct_ref1
    : FN_SIN LEFT_PAREN expr RIGHT_PAREN   -> ^(FUNCTION FN_SIN expr)
    | FN_COS LEFT_PAREN expr RIGHT_PAREN   -> ^(FUNCTION FN_COS expr)
    | FN_TAN LEFT_PAREN expr RIGHT_PAREN   -> ^(FUNCTION FN_TAN expr)
    | FN_ASIN LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_ASIN expr)
    | FN_ACOS LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_ACOS expr)
    | FN_ATAN LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_ATAN expr)
    | FN_SINH LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_SINH expr)
    | FN_COSH LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_COSH expr)
    | FN_TANH LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_TANH expr)
    | FN_ASINH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ASINH expr)
    | FN_ACOSH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ACOSH expr)
    | FN_ATANH LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_ATANH expr)
    | FN_EXP LEFT_PAREN expr RIGHT_PAREN   -> ^(FUNCTION FN_EXP expr)
    | FN_LN LEFT_PAREN expr RIGHT_PAREN    -> ^(FUNCTION FN_LN expr)
    | FN_LOG10 LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_LOG10 expr)
    | FN_SQRT LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_SQRT expr)
    | FN_ABS LEFT_PAREN expr RIGHT_PAREN   -> ^(FUNCTION FN_ABS expr)
    | FN_RE LEFT_PAREN expr RIGHT_PAREN    -> ^(FUNCTION FN_RE expr)
    | FN_IM LEFT_PAREN expr RIGHT_PAREN    -> ^(FUNCTION FN_IM expr)
    | FN_ARG LEFT_PAREN expr RIGHT_PAREN   -> ^(FUNCTION FN_ARG expr)
    | FN_CONJ LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_CONJ expr)
    | FN_DEG LEFT_PAREN expr RIGHT_PAREN   -> ^(FUNCTION FN_DEG expr)
    | FN_RAD LEFT_PAREN expr RIGHT_PAREN   -> ^(FUNCTION FN_RAD expr)
    | FN_NORM LEFT_PAREN expr RIGHT_PAREN  -> ^(FUNCTION FN_NORM expr)
    | FN_POLAR LEFT_PAREN expr RIGHT_PAREN -> ^(FUNCTION FN_POLAR expr)
    ;
  
funct_ref2
    : FN_ATAN2 LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION FN_ATAN2 $a $b)
    | FN_POW LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION FN_POW $a $b)
    | BITWISE_FN_AND LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_AND $a $b)
    | BITWISE_FN_OR LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_OR $a $b)
    | BITWISE_FN_NOT LEFT_PAREN a = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_NOT $a)
    | BITWISE_FN_NAND LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_NAND $a $b)
    | BITWISE_FN_NOR LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_NOR $a $b)
    | BITWISE_FN_XOR LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_XOR $a $b)
    | BITWISE_FN_XNOR LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_XNOR $a $b)
    | BITWISE_FN_SHL LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_SHL $a $b)
    | BITWISE_FN_SHR LEFT_PAREN a = expr ARG_SEPARATOR b = expr RIGHT_PAREN    
        -> ^(FUNCTION BITWISE_FN_SHR $a $b)
    ;

constant_ref
    : CONSTANTS_PI  -> ^(CONSTANT_REF CONSTANTS_PI)
    | CONSTANTS_E   -> ^(CONSTANT_REF CONSTANTS_E)
    | CONSTANTS_ANS -> ^(CONSTANT_REF CONSTANTS_ANS)
    ;
  
si_unit_ref
    : SI_PREFIX_YOTTA -> ^(SI_CONVERT SI_PREFIX_YOTTA)
    | SI_PREFIX_ZETTA -> ^(SI_CONVERT SI_PREFIX_ZETTA)
    | SI_PREFIX_EXA   -> ^(SI_CONVERT SI_PREFIX_EXA)
    | SI_PREFIX_PETA  -> ^(SI_CONVERT SI_PREFIX_PETA)
    | SI_PREFIX_TERA  -> ^(SI_CONVERT SI_PREFIX_TERA)
    | SI_PREFIX_GIGA  -> ^(SI_CONVERT SI_PREFIX_GIGA)
    | SI_PREFIX_MEGA  -> ^(SI_CONVERT SI_PREFIX_MEGA)
    | SI_PREFIX_KILO  -> ^(SI_CONVERT SI_PREFIX_KILO)
    | SI_PREFIX_HECTO -> ^(SI_CONVERT SI_PREFIX_HECTO)
    | SI_PREFIX_DECA  -> ^(SI_CONVERT SI_PREFIX_DECA)
    | SI_PREFIX_DECI  -> ^(SI_CONVERT SI_PREFIX_DECI)
    | SI_PREFIX_CENTI -> ^(SI_CONVERT SI_PREFIX_CENTI)
    | SI_PREFIX_MILLI -> ^(SI_CONVERT SI_PREFIX_MILLI)
    | SI_PREFIX_MICRO -> ^(SI_CONVERT SI_PREFIX_MICRO)
    | SI_PREFIX_NANO  -> ^(SI_CONVERT SI_PREFIX_NANO)
    | SI_PREFIX_PICO  -> ^(SI_CONVERT SI_PREFIX_PICO)
    | SI_PREFIX_FEMTO -> ^(SI_CONVERT SI_PREFIX_FEMTO)
    | SI_PREFIX_ATTO  -> ^(SI_CONVERT SI_PREFIX_ATTO)
    | SI_PREFIX_ZEPTO -> ^(SI_CONVERT SI_PREFIX_ZEPTO)
    | SI_PREFIX_YOCTO -> ^(SI_CONVERT SI_PREFIX_YOCTO)
    | SI_PREFIX_KIBI  -> ^(SI_CONVERT SI_PREFIX_KIBI)
    | SI_PREFIX_MEBI  -> ^(SI_CONVERT SI_PREFIX_MEBI)
    | SI_PREFIX_GIBI  -> ^(SI_CONVERT SI_PREFIX_GIBI)
    | SI_PREFIX_TEBI  -> ^(SI_CONVERT SI_PREFIX_TEBI)
    | SI_PREFIX_PEBI  -> ^(SI_CONVERT SI_PREFIX_PEBI)
    | SI_PREFIX_EXBI  -> ^(SI_CONVERT SI_PREFIX_EXBI)
    | SI_PREFIX_ZEBI  -> ^(SI_CONVERT SI_PREFIX_ZEBI)
    | SI_PREFIX_YOBI  -> ^(SI_CONVERT SI_PREFIX_YOBI)
    ;

imaginary_number
    : real_number? COMPLEX_UNIT -> ^(IM real_number? COMPLEX_UNIT)
    ;

real_number 
    : dec_num | hex_num | oct_num | bin_num
    ;
    
dec_num : FLOAT_NUMBER  -> ^(RE FLOAT_NUMBER);
hex_num : HEX_NUMBER    -> ^(HEX HEX_NUMBER);
oct_num : OCTAL_NUMBER  -> ^(OCT OCTAL_NUMBER);
bin_num : BINARY_NUMBER -> ^(BIN BINARY_NUMBER);