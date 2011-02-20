tree grammar ComplexEval;

options {
	tokenVocab=ComplexParser;
	ASTLabelType=pANTLR3_BASE_TREE;
	language=C;
}

@includes {
	#define INCLUDED_FROM_ANTLR_GENERATED_CODE
	#include "MathEvaluator.h"
	#undef INCLUDED_FROM_ANTLR_GENERATED_CODE
}

prog returns [ComplexPtr compl_retv]
    : expr { $compl_retv = $expr.compl_retv; }
	;

expr returns [ComplexPtr compl_retv]
    : ^(BW_AND a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_AND, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_AND2 a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_AND, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_OR a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_OR, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_OR2 a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_OR, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_XOR a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_XOR, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_XOR2 a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_XOR, $a.compl_retv, $b.compl_retv);
	}	
	| ^(BW_NAND a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_NAND, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_NOR a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_NOR, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_XNOR a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_XNOR, $a.compl_retv, $b.compl_retv);
	}	
	| ^(BW_SHLEFT a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_SHL, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_SHLEFT2 a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_SHL, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_SHRIGHT a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_SHR, $a.compl_retv, $b.compl_retv);
	}
	| ^(BW_SHRIGHT2 a = expr b = expr) {
		$compl_retv = mr_binary_bitwise_operator(MR_BITWISE_SHR, $a.compl_retv, $b.compl_retv);
	}
	| ^(PLUS a = expr b = expr) {
		$compl_retv = mr_binary_operator(MR_PLUS, $a.compl_retv, $b.compl_retv);
	}
	| ^(MINUS a = expr b = expr) {
		$compl_retv = mr_binary_operator(MR_MINUS, $a.compl_retv, $b.compl_retv);
	}
	| ^(MULT a = expr b = expr) {
		$compl_retv = mr_binary_operator(MR_MULTI, $a.compl_retv, $b.compl_retv);
	}
	| ^(DIV a = expr b = expr) {
		$compl_retv = mr_binary_operator(MR_DIV, $a.compl_retv, $b.compl_retv);
	}
	| ^(MOD a = expr b = expr) {
		$compl_retv = mr_binary_operator(MR_MOD, $a.compl_retv, $b.compl_retv);
	}
	| ^(POW a = expr b = expr) {
		$compl_retv = mr_binary_operator(MR_POW, $a.compl_retv, $b.compl_retv);
	}
	| unary {
		$compl_retv = $unary.compl_retv;
	}
	;
	
unary returns [ComplexPtr compl_retv]
  : ^(UNARY MINUS atom) {
		$compl_retv = mr_unary_operator(MR_UNARY_MINUS, $atom.compl_retv); 
    }
  | ^(UNARY PLUS atom) {
		$compl_retv = $atom.compl_retv;
    }
  | ^(UNARY BW_NOT atom) {
        $compl_retv = mr_unary_operator(MR_BITWISE_NOT, $atom.compl_retv); 
  }
  | atom {
		$compl_retv = $atom.compl_retv;
    }
  ;

atom returns [ComplexPtr compl_retv]
  :  ^(ATOM real_number) {
		$compl_retv = $real_number.compl_retv;
	}
  |  ^(ATOM imaginary_number) {
		$compl_retv = $imaginary_number.compl_retv;
	}
  |  ^(ATOM real_number si_unit_ref) {
		$compl_retv = mr_binary_operator(MR_MULTI, $real_number.compl_retv, $si_unit_ref.compl_retv);
	}
  |  ^(ATOM imaginary_number si_unit_ref) {
		$compl_retv = mr_binary_operator(MR_MULTI, $imaginary_number.compl_retv, $si_unit_ref.compl_retv);
	}
  |  ^(ATOM constant_ref) {
		$compl_retv = $constant_ref.compl_retv;
	}
  |  ^(ATOM funct_ref1) {
		$compl_retv = $funct_ref1.compl_retv;
	}
  |  ^(ATOM funct_ref2) {
		$compl_retv = $funct_ref2.compl_retv;
	}
  |  ^(ATOM expr) {
		$compl_retv = $expr.compl_retv;
	}
  ;

funct_ref1 returns [ComplexPtr compl_retv]
	: ^(FUNCTION FN_SIN expr) {		
		$compl_retv = mr_unary_function (MR_FUN_SIN, $expr.compl_retv); }
	| ^(FUNCTION FN_COS expr) {		
		$compl_retv = mr_unary_function (MR_FUN_COS, $expr.compl_retv); }
	| ^(FUNCTION FN_TAN expr) {		
		$compl_retv = mr_unary_function (MR_FUN_TAN, $expr.compl_retv); }
	| ^(FUNCTION FN_ASIN expr) {		
		$compl_retv = mr_unary_function (MR_FUN_ASIN, $expr.compl_retv); }
	| ^(FUNCTION FN_ACOS expr) {		
		$compl_retv = mr_unary_function (MR_FUN_ACOS, $expr.compl_retv); }
	| ^(FUNCTION FN_ATAN expr) {		
		$compl_retv = mr_unary_function (MR_FUN_ATAN, $expr.compl_retv); }
	| ^(FUNCTION FN_SINH expr) {		
		$compl_retv = mr_unary_function (MR_FUN_SINH, $expr.compl_retv); }
	| ^(FUNCTION FN_COSH expr) {		
		$compl_retv = mr_unary_function (MR_FUN_COSH, $expr.compl_retv); }
	| ^(FUNCTION FN_TANH expr) {
		$compl_retv = mr_unary_function (MR_FUN_TANH, $expr.compl_retv); }
	| ^(FUNCTION FN_ASINH expr) {		
		$compl_retv = mr_unary_function (MR_FUN_ASINH, $expr.compl_retv); }
	| ^(FUNCTION FN_ACOSH expr) {		
		$compl_retv = mr_unary_function (MR_FUN_ACOSH, $expr.compl_retv); }
	| ^(FUNCTION FN_ATANH expr) {		
		$compl_retv = mr_unary_function (MR_FUN_ATANH, $expr.compl_retv); }
	| ^(FUNCTION FN_EXP expr) {		
		$compl_retv = mr_unary_function (MR_FUN_EXP, $expr.compl_retv); }
	| ^(FUNCTION FN_LN expr) {		
		$compl_retv = mr_unary_function (MR_FUN_LOG, $expr.compl_retv); }
	| ^(FUNCTION FN_LOG10 expr) {		
		$compl_retv = mr_unary_function (MR_FUN_LOG10, $expr.compl_retv); }
	| ^(FUNCTION FN_SQRT expr) {		
		$compl_retv = mr_unary_function (MR_FUN_SQRT, $expr.compl_retv); }
	| ^(FUNCTION FN_ABS expr) {		
		$compl_retv = mr_unary_function (MR_FUN_ABS, $expr.compl_retv); }
	| ^(FUNCTION FN_RE expr) {		
		$compl_retv = mr_unary_function (MR_FUN_RE, $expr.compl_retv); }
	| ^(FUNCTION FN_IM expr) {		
		$compl_retv = mr_unary_function (MR_FUN_IM, $expr.compl_retv); }
	| ^(FUNCTION FN_ARG expr) {		
		$compl_retv = mr_unary_function (MR_FUN_ARG, $expr.compl_retv); }
	| ^(FUNCTION FN_CONJ expr) {		
		$compl_retv = mr_unary_function (MR_FUN_CONJ, $expr.compl_retv); }
	| ^(FUNCTION FN_DEG expr) {		
		$compl_retv = mr_unary_function (MR_FUN_DEG, $expr.compl_retv); }
	| ^(FUNCTION FN_RAD expr) {		
		$compl_retv = mr_unary_function (MR_FUN_RAD, $expr.compl_retv); }
	| ^(FUNCTION FN_NORM expr) {		
		$compl_retv = mr_unary_function (MR_FUN_NORM, $expr.compl_retv); }
	| ^(FUNCTION FN_POLAR expr) {		
		$compl_retv = mr_unary_function (MR_FUN_POLAR, $expr.compl_retv); }
	;

funct_ref2 returns [ComplexPtr compl_retv]
	: ^(FUNCTION FN_ATAN2 a=expr b=expr) {
		$compl_retv = mr_binary_function(MR_FUN2_ATAN2, $a.compl_retv, $b.compl_retv); 
	}
	| ^(FUNCTION FN_POW a=expr b=expr) {
		$compl_retv = mr_binary_operator(MR_POW, $a.compl_retv, $b.compl_retv); 
	}
	;

constant_ref returns [ComplexPtr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
}
	: ^(CONSTANT_REF CONSTANTS_PI) {
		mr_pi($compl_retv);
    	}
	| ^(CONSTANT_REF CONSTANTS_E) {
		mr_e($compl_retv);
    	}
    | ^(CONSTANT_REF CONSTANTS_ANS) {
		getAns($compl_retv);
    	}
    	;

si_unit_ref returns [ComplexPtr compl_retv]
@init { 
	$compl_retv = newMrComplex();
}
	: ^(SI_CONVERT SI_PREFIX_YOTTA) {
		si_ref(MR_MATH_SI_PREFIX_YOTTA, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_ZETTA) {
		si_ref(MR_MATH_SI_PREFIX_ZETTA, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_EXA) {
		si_ref(MR_MATH_SI_PREFIX_EXA, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_PETA) {
		si_ref(MR_MATH_SI_PREFIX_PETA, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_TERA) {
		si_ref(MR_MATH_SI_PREFIX_TERA, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_GIGA) {
		si_ref(MR_MATH_SI_PREFIX_GIGA, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_MEGA) {
		si_ref(MR_MATH_SI_PREFIX_MEGA, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_KILO) {
		si_ref(MR_MATH_SI_PREFIX_KILO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_HECTO) {
		si_ref(MR_MATH_SI_PREFIX_HECTO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_DECA) {
		si_ref(MR_MATH_SI_PREFIX_DECA, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_DECI) {
		si_ref(MR_MATH_SI_PREFIX_DECI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_CENTI) {
		si_ref(MR_MATH_SI_PREFIX_CENTI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_MILLI) {
		si_ref(MR_MATH_SI_PREFIX_MILLI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_MICRO) {
		si_ref(MR_MATH_SI_PREFIX_MICRO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_NANO) {
		si_ref(MR_MATH_SI_PREFIX_NANO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_PICO) {
		si_ref(MR_MATH_SI_PREFIX_PICO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_FEMTO) {
		si_ref(MR_MATH_SI_PREFIX_FEMTO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_ATTO) {
		si_ref(MR_MATH_SI_PREFIX_ATTO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_ZEPTO) {
		si_ref(MR_MATH_SI_PREFIX_ZEPTO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_YOCTO) {
		si_ref(MR_MATH_SI_PREFIX_YOCTO, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_KIBI) {
		si_ref(MR_MATH_SI_PREFIX_KIBI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_MEBI) {
		si_ref(MR_MATH_SI_PREFIX_MEBI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_GIBI) {
		si_ref(MR_MATH_SI_PREFIX_GIBI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_TEBI) {
		si_ref(MR_MATH_SI_PREFIX_TEBI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_PEBI) {
		si_ref(MR_MATH_SI_PREFIX_PEBI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_EXBI) {
		si_ref(MR_MATH_SI_PREFIX_EXBI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_ZEBI) {
		si_ref(MR_MATH_SI_PREFIX_ZEBI, $compl_retv);
	}
	| ^(SI_CONVERT SI_PREFIX_YOBI) {
		si_ref(MR_MATH_SI_PREFIX_YOBI, $compl_retv);
	}
	;

imaginary_number returns [ComplexPtr compl_retv]
@init {
	ComplexPtr numb;
	char num_present = 0;
	$compl_retv = newMrComplex();
}
	: ^(IM (
			real_number {
				 numb = $real_number.compl_retv;
				 num_present = 1;
			}
		)? COMPLEX_UNIT)
	{
		if (num_present == 0) {
			mpfr_set_ui(mpc_imagref($compl_retv), 1, MPFR_RNDN);
		} else {
			mpfr_set(mpc_imagref($compl_retv), mpc_realref(numb), MPFR_RNDN);
		}
    }
    ;

real_number returns [ComplexPtr compl_retv]
	:	 dec_num { $compl_retv = $dec_num.compl_retv; }
	|	 hex_num { $compl_retv = $hex_num.compl_retv; }
	|	 oct_num { $compl_retv = $oct_num.compl_retv; }
	|	 bin_num { $compl_retv = $bin_num.compl_retv; }
	|    dec_num_percent { $compl_retv = $dec_num_percent.compl_retv; }
	|    hex_num_percent { $compl_retv = $hex_num_percent.compl_retv; }
	|    oct_num_percent { $compl_retv = $oct_num_percent.compl_retv; }
	|    bin_num_percent { $compl_retv = $bin_num_percent.compl_retv; }
	;
	
dec_num_percent returns [ComplexPtr compl_retv]
    : ^(PERCENT dec_num) {
        $compl_retv = $dec_num.compl_retv;
		mpc_div_ui($compl_retv, $compl_retv, 100, MPC_RNDNN);
    };
	
hex_num_percent returns [ComplexPtr compl_retv]
    : ^(PERCENT hex_num) {
        $compl_retv = $hex_num.compl_retv;
		mpc_div_ui($compl_retv, $compl_retv, 100, MPC_RNDNN);
    };
	
oct_num_percent returns [ComplexPtr compl_retv]
    : ^(PERCENT oct_num) {
        $compl_retv = $oct_num.compl_retv;
		mpc_div_ui($compl_retv, $compl_retv, 100, MPC_RNDNN);
    };
	
bin_num_percent returns [ComplexPtr compl_retv]
    : ^(PERCENT bin_num) {
        $compl_retv = $bin_num.compl_retv;
		mpc_div_ui($compl_retv, $compl_retv, 100, MPC_RNDNN);
    };

dec_num returns [ComplexPtr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
}
    : ^(RE FLOAT_NUMBER) {
		strToReal ($FLOAT_NUMBER->getText($FLOAT_NUMBER), mpc_realref($compl_retv));
    };
	
hex_num returns [ComplexPtr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
}
    : ^(HEX HEX_NUMBER) {
    	strHexToReal ($HEX_NUMBER->getText($HEX_NUMBER), mpc_realref($compl_retv));
    };
	
oct_num returns [ComplexPtr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
}
    : ^(OCT OCTAL_NUMBER) {
    	strOctToReal ($OCTAL_NUMBER->getText($OCTAL_NUMBER), mpc_realref($compl_retv));
    };
	
bin_num returns [ComplexPtr compl_retv]
@init { 
	$compl_retv = newMrComplex(); 
}
    : ^(BIN BINARY_NUMBER) {
    	strBinToReal ($BINARY_NUMBER->getText($BINARY_NUMBER), mpc_realref($compl_retv));
    };