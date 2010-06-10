tree grammar ComplexEval;

options {
	tokenVocab=ComplexParser;
	ASTLabelType=pANTLR3_BASE_TREE;
	language=C;
}

@includes {
	#include "math_bridge_API.h"
}

prog returns [mrComplex_ptr compl_retv]
    : expr { $compl_retv = $expr.compl_retv; };

expr returns [mrComplex_ptr compl_retv]
    : ^(PLUS a = expr b = expr) { $compl_retv = mr_binary_operator(MR_PLUS, $a.compl_retv, $b.compl_retv); }
    | ^(MINUS a = expr b = expr) { $compl_retv = mr_binary_operator(MR_MINUS, $a.compl_retv, $b.compl_retv); }
    | ^(MULT a = expr b = expr) { $compl_retv = mr_binary_operator(MR_MULTI, $a.compl_retv, $b.compl_retv); }
    | ^(DIV a = expr b = expr) { $compl_retv = mr_binary_operator(MR_DIV, $a.compl_retv, $b.compl_retv); }
    | ^(MOD a = expr b = expr) { $compl_retv = mr_binary_operator(MR_MOD, $a.compl_retv, $b.compl_retv); }
    | ^(POW a = expr b = expr) { $compl_retv = mr_binary_operator(MR_POW, $a.compl_retv, $b.compl_retv); }
	| unary  { $compl_retv =  $unary.compl_retv; }
	;

unary returns [mrComplex_ptr compl_retv]
@init {
  int negate_flag = 0;
  mrComplex_t tmp1, tmp2;
  tmp1.real = -1; tmp1.imag = 0;
}
    : ^(UNARY (MINUS { negate_flag = 1; })? expr) {  
   		if (negate_flag == 1) {
   			tmp2.real = $expr.compl_retv->real; 
			tmp2.imag = $expr.compl_retv->imag;
			$compl_retv = mr_binary_operator(MR_MULTI, &tmp1, &tmp2);
   		} else {
   			$compl_retv = $expr.compl_retv;
   		}
   	}
    | atom {
      $compl_retv = $atom.compl_retv;
    }
   ;

atom returns [mrComplex_ptr compl_retv]
@init {
	mrComplex_t tmp1, tmp2;
    int negate_flag = 0;
	tmp1.real = -1; tmp1.imag = 0;
}
	: ^(ATOM (MINUS { negate_flag = 1; })? real_number) {  
   		if (negate_flag == 1) {
   			tmp2.real = $real_number.compl_retv->real;
			tmp2.imag = $real_number.compl_retv->imag;
			$compl_retv = mr_binary_operator(MR_MULTI, &tmp1, &tmp2);
   		} else {
   			$compl_retv = $real_number.compl_retv;
   		}
   	}
	| ^(ATOM (MINUS { negate_flag = 1; })? imaginary_number) {  
   		if (negate_flag == 1) {
   			tmp2.real = $imaginary_number.compl_retv->real;
			tmp2.imag = $imaginary_number.compl_retv->imag;
			$compl_retv = mr_binary_operator(MR_MULTI, &tmp1, &tmp2);
   		} else {
   			$compl_retv = $imaginary_number.compl_retv;
   		}
   	}
	| ^(ATOM (MINUS { negate_flag = 1; })? si_unit_ref) {  
   		if (negate_flag == 1) {
			tmp2.real = $si_unit_ref.compl_retv->real;
			tmp2.imag = $si_unit_ref.compl_retv->imag;
			$compl_retv = mr_binary_operator(MR_MULTI, &tmp1, &tmp2);
   		} else {
   			$compl_retv = $si_unit_ref.compl_retv;
   		}
   	}
	| ^(ATOM (MINUS { negate_flag = 1; })? constant_ref) {  
   		if (negate_flag == 1) {
			tmp2.real = $constant_ref.compl_retv->real;
			tmp2.imag = $constant_ref.compl_retv->imag;
			$compl_retv = mr_binary_operator(MR_MULTI, &tmp1, &tmp2);
   		} else {
   			$compl_retv = $constant_ref.compl_retv;
   		}
   	}
	| ^(ATOM (MINUS { negate_flag = 1; })? funct_ref1) {  
   		if (negate_flag == 1) {
			tmp2.real = $funct_ref1.compl_retv->real;
			tmp2.imag = $funct_ref1.compl_retv->imag;
			$compl_retv = mr_binary_operator(MR_MULTI, &tmp1, &tmp2);
   		} else {
   			$compl_retv = $funct_ref1.compl_retv;
   		}
   	}
	| ^(ATOM (MINUS { negate_flag = 1; })? funct_ref2) {  
   		if (negate_flag == 1) {
			tmp2.real = $funct_ref2.compl_retv->real;
			tmp2.imag = $funct_ref2.compl_retv->imag;
			$compl_retv = mr_binary_operator(MR_MULTI, &tmp1, &tmp2);
   		} else {
   			$compl_retv = $funct_ref2.compl_retv;
   		}
   	}
	;

funct_ref1 returns [mrComplex_ptr compl_retv]
	: ^(FUNCTION FN_SIN expr) {		
		$compl_retv = mr_sin ($expr.compl_retv); }
	| ^(FUNCTION FN_COS expr) {		
		$compl_retv = mr_cos ($expr.compl_retv); }
	| ^(FUNCTION FN_TAN expr) {		
		$compl_retv = mr_tan ($expr.compl_retv); }
	| ^(FUNCTION FN_ASIN expr) {		
		$compl_retv = mr_asin ($expr.compl_retv); }
	| ^(FUNCTION FN_ACOS expr) {		
		$compl_retv = mr_acos ($expr.compl_retv); }
	| ^(FUNCTION FN_ATAN expr) {		
		$compl_retv = mr_atan ($expr.compl_retv); }
	| ^(FUNCTION FN_SINH expr) {		
		$compl_retv = mr_sinh ($expr.compl_retv); }
	| ^(FUNCTION FN_COSH expr) {		
		$compl_retv = mr_cosh ($expr.compl_retv); }
	| ^(FUNCTION FN_TANH expr) {
		$compl_retv = mr_tanh ($expr.compl_retv); }
	| ^(FUNCTION FN_ASINH expr) {		
		$compl_retv = mr_asinh ($expr.compl_retv); }
	| ^(FUNCTION FN_ACOSH expr) {		
		$compl_retv = mr_acosh ($expr.compl_retv); }
	| ^(FUNCTION FN_ATANH expr) {		
		$compl_retv = mr_atanh ($expr.compl_retv); }
	| ^(FUNCTION FN_EXP expr) {		
		$compl_retv = mr_exp ($expr.compl_retv); }
	| ^(FUNCTION FN_LN expr) {		
		$compl_retv = mr_log ($expr.compl_retv); }
	| ^(FUNCTION FN_LOG10 expr) {		
		$compl_retv = mr_log10 ($expr.compl_retv); }
	| ^(FUNCTION FN_SQRT expr) {		
		$compl_retv = mr_sqrt ($expr.compl_retv); }
	| ^(FUNCTION FN_ABS expr) {		
		$compl_retv = mr_abs ($expr.compl_retv); }
	| ^(FUNCTION FN_RE expr) {		
		$compl_retv = mr_re ($expr.compl_retv); }
	| ^(FUNCTION FN_IM expr) {		
		$compl_retv = mr_im ($expr.compl_retv); }
	| ^(FUNCTION FN_ARG expr) {		
		$compl_retv = mr_arg ($expr.compl_retv); }
	| ^(FUNCTION FN_CONJ expr) {		
		$compl_retv = mr_conj ($expr.compl_retv); }
	| ^(FUNCTION FN_DEG expr) {		
		$compl_retv = mr_deg ($expr.compl_retv); }
	| ^(FUNCTION FN_RAD expr) {		
		$compl_retv = mr_rad ($expr.compl_retv); }
	| ^(FUNCTION FN_NORM expr) {		
		$compl_retv = mr_norm ($expr.compl_retv); }
	| ^(FUNCTION FN_POLAR expr) {		
		$compl_retv = mr_polar($expr.compl_retv); }
	;

funct_ref2 returns [mrComplex_ptr compl_retv]
	: ^(FUNCTION FN_ATAN2 a=expr b=expr) {
		$compl_retv = mr_atan2($a.compl_retv, $b.compl_retv); 
	}
	| ^(FUNCTION FN_POW a=expr b=expr) {
		$compl_retv = mr_binary_operator(MR_POW, $a.compl_retv, $b.compl_retv); 
	}
	| ^(FUNCTION BINARY_FN_AND a=expr b=expr) {
		$compl_retv = mr_binary_operator(MR_BITWISE_AND, $a.compl_retv, $b.compl_retv); 
	}
	| ^(FUNCTION BINARY_FN_OR a=expr b=expr) {
		$compl_retv = mr_binary_operator(MR_BITWISE_OR, $a.compl_retv, $b.compl_retv); 
	}
	| ^(FUNCTION BINARY_FN_NOT a=expr) {
		$compl_retv = mr_unary_operator(MR_BITWISE_NOT, $a.compl_retv); 
	}
	| ^(FUNCTION BINARY_FN_NAND a=expr b=expr) {
		$compl_retv = mr_binary_operator (MR_BITWISE_NAND, $a.compl_retv, $b.compl_retv); 
	}
	| ^(FUNCTION BINARY_FN_NOR a=expr b=expr) {
		$compl_retv = mr_binary_operator(MR_BITWISE_NOR, $a.compl_retv, $b.compl_retv); 
	}
	| ^(FUNCTION BINARY_FN_XOR a=expr b=expr) {
		$compl_retv = mr_binary_operator(MR_BITWISE_XOR, $a.compl_retv, $b.compl_retv); 
	}
	| ^(FUNCTION BINARY_FN_XNOR a=expr b=expr) {
		$compl_retv = mr_binary_operator(MR_BITWISE_XNOR, $a.compl_retv, $b.compl_retv); 
	}
	;

constant_ref returns [mrComplex_ptr compl_retv]
	: ^(CONSTANT_REF CONSTANTS_PI) {
		$compl_retv = newMrComplex(); 
		$compl_retv->imag=0.0; 
		$compl_retv->real = mr_pi();
    	}
	| ^(CONSTANT_REF CONSTANTS_E) {
		$compl_retv = newMrComplex(); 
		$compl_retv->imag=0.0; 
		$compl_retv->real = mr_e();
    	}
    | ^(CONSTANT_REF CONSTANTS_ANS) {
		$compl_retv = getAns();
    	}
    	;

si_unit_ref returns [mrComplex_ptr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
	$compl_retv->imag = 0.0; 
}
	: ^(SI_CONVERT real_number SI_PREFIX_YOTTA) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_YOTTA);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_ZETTA) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_ZETTA);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_EXA) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_EXA);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_PETA) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_PETA);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_TERA) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_TERA);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_GIGA) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_GIGA);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_MEGA) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_MEGA);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_KILO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_KILO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_HECTO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_HECTO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_DECA) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_DECA);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_DECI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_DECI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_CENTI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_CENTI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_MILLI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_MILLI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_MICRO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_MICRO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_NANO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_NANO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_PICO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_PICO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_FEMTO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_FEMTO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_ATTO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_ATTO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_ZEPTO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_ZEPTO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_YOCTO) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_YOCTO);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_KIBI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_KIBI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_MEBI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_MEBI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_GIBI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_GIBI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_TEBI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_TEBI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_PEBI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_PEBI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_EXBI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_EXBI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_ZEBI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_ZEBI);
	}
	| ^(SI_CONVERT real_number SI_PREFIX_YOBI) {
		$compl_retv->real = si_calc ($real_number.compl_retv->real, 
			MR_MATH_SI_PREFIX_YOBI);
	}
	;

imaginary_number returns [mrComplex_ptr compl_retv]
@init {
	mrNumeric_t numb = 0;
	char num_present = 0;
	$compl_retv = newMrComplex();
	$compl_retv->real = 0;
}
	: ^(IM (
			real_number {
				 numb = $real_number.compl_retv->real;
				 num_present = 1;
			}
		)? COMPLEX_UNIT)
	{
		if (num_present == 0) {
			$compl_retv->imag = 1.0;
		} else {
			$compl_retv->imag = numb;
		}
    }
    ;

real_number returns [mrComplex_ptr compl_retv]
	:	 dec_num { $compl_retv =  $dec_num.compl_retv; }
	|	 hex_num { $compl_retv =  $hex_num.compl_retv; }
	|	 oct_num { $compl_retv =  $oct_num.compl_retv; }
	|	 bin_num { $compl_retv =  $bin_num.compl_retv; }
	;
	
dec_num returns [mrComplex_ptr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
	$compl_retv->imag = 0.0; 
}
    : ^(RE FLOAT_NUMBER) {
    	$compl_retv->real = parse_mrNumeric_t ($FLOAT_NUMBER->getText($FLOAT_NUMBER));
    };
	
hex_num returns [mrComplex_ptr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
	$compl_retv->imag = 0.0; 
}
    : ^(HEX HEX_NUMBER) {
    	$compl_retv->real = parse_hex_mrNumeric_t ($HEX_NUMBER->getText($HEX_NUMBER));
    };
	
oct_num returns [mrComplex_ptr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
	$compl_retv->imag = 0.0; 
}
    : ^(OCT OCTAL_NUMBER) {
    	$compl_retv->real = parse_oct_mrNumeric_t ($OCTAL_NUMBER->getText($OCTAL_NUMBER));
    };
	
bin_num returns [mrComplex_ptr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
	$compl_retv->imag = 0.0; 
}
    : ^(BIN BINARY_NUMBER) {
    	$compl_retv->real = parse_bin_mrNumeric_t ($BINARY_NUMBER->getText($BINARY_NUMBER));
    };