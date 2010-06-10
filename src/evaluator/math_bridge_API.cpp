/*
* Copyright (C) 2009, 2010
* Tomislav Adamic <tomislav.adamic@gmail.com>
*
* This file is part of MathyResurrected - Launchy advanced calculator plugin
*
* MathyResurrected is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by the
* Free Software Foundation, either version 3 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with MathyResurrected. If not, see <http://www.gnu.org/licenses/>.
*/

#include <antlr3.h>
#include <cmath>
#include <complex>
#include <boost/math/complex.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/dynamic_bitset.hpp>
#include <string>
#include "MathyResurrectedExceptions.h"
#include "math_bridge_API.h"
#include "math_bridge_globals.h"
#include "MathEvaluator.h"

using namespace boost;
using namespace boost::math;
using namespace std;
using namespace mathy_resurrected;

typedef std::complex<mrNumeric_t> mr_StdComplex_t;
typedef const mrComplex_t* const mrComplex_const_ptr;

/*! Converts between tree parser return value and std::complex<T> */
inline void MRCOMPLEX_2_STDCOMPLEX(mr_StdComplex_t& compl, mrComplex_const_ptr mrretv) {
	compl.real(mrretv->real);
	compl.imag(mrretv->imag);
}

/*! Converts between tree parser return value and std::complex<T> */
inline void STDCOMPLEX_2_MRCOMPLEX(mrComplex_ptr mrretv, const mr_StdComplex_t& compl) {
	mrretv->real = compl.real();
	mrretv->imag = compl.imag();
}

/** Global data used by bridge API. Although this doesn't make this API much
tread safer than before, at leaset this "unsafety" has been localized and 
modulatized. */
BridgeAPIGlobals* globalData = 0;

void init_bridge_API (BridgeAPIGlobals* globs) {
	if(globs == 0) {
		throw invalid_argument("Null pointer not allowed!");
	}
	globalData = globs;
}

mrComplex_ptr newMrComplex() {
	mrComplex_ptr p = new mrComplex_t;
	p->real = 0; p->imag = 0;
	boost::shared_ptr< mrComplex_t > sp(p);
	globalData->complexFactoryData.push_back(sp);
	return p;
}

/*! Collects lexer errors during lexing phase so they can be used
to check for things like unmatched parentheses, illegal input etc... */
void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_code) {
	BridgeAPIGlobals::mr_LexerErrorPair p;
	p.char_index = char_index;
	p.err_type = err_code;
	globalData->lexerErrorsCollection.push_back(p);
}

void setAns(mrNumeric_t real, mrNumeric_t imag) {
	globalData->ans.real = real;
	globalData->ans.imag = imag;
}

mrComplex_ptr getAns() {
	return &(globalData->ans);
}

mrNumeric_t mr_pi() {
	static const mrNumeric_t 
		piVal = atan2((mrNumeric_t)(0.0), static_cast<mrNumeric_t>(-1.0));
	return piVal;
}

mrNumeric_t mr_e() {
	static const mrNumeric_t eVal = exp((mrNumeric_t)(1.0));
	return eVal;
}

mrNumeric_t si_calc(mrNumeric_t multipl, MR_MATH_SI_PREFIXES si_prefix) {
	mrNumeric_t suff_val, retv;

	switch (si_prefix) {
		case MR_MATH_SI_PREFIX_YOTTA:
			suff_val = 1e24;
			break;
		case MR_MATH_SI_PREFIX_ZETTA:
			suff_val = 1e21;
			break;
		case MR_MATH_SI_PREFIX_EXA:
			suff_val = 1e18;
			break;
		case MR_MATH_SI_PREFIX_PETA:
			suff_val = 1e15;
			break;
		case MR_MATH_SI_PREFIX_TERA:
			suff_val = 1e12;
			break;
		case MR_MATH_SI_PREFIX_GIGA:
			suff_val = 1e9;
			break;
		case MR_MATH_SI_PREFIX_MEGA:
			suff_val = 1e6;
			break;
		case MR_MATH_SI_PREFIX_KILO:
			suff_val = 1e3;
			break;
		case MR_MATH_SI_PREFIX_HECTO:
			suff_val = 1e2;
			break;
		case MR_MATH_SI_PREFIX_DECA:
			suff_val = 1e1;
			break;
		case MR_MATH_SI_PREFIX_DECI:
			suff_val = 1e-1;
			break;
		case MR_MATH_SI_PREFIX_CENTI:
			suff_val = 1e-2;
			break;
		case MR_MATH_SI_PREFIX_MILLI:
			suff_val = 1e-3;
			break;
		case MR_MATH_SI_PREFIX_MICRO:
			suff_val = 1e-6;
			break;
		case MR_MATH_SI_PREFIX_NANO:
			suff_val = 1e-9;
			break;
		case MR_MATH_SI_PREFIX_PICO:
			suff_val = 1e-12;
			break;
		case MR_MATH_SI_PREFIX_FEMTO:
			suff_val = 1e-15;
			break;
		case MR_MATH_SI_PREFIX_ATTO:
			suff_val = 1e-18;
			break;
		case MR_MATH_SI_PREFIX_ZEPTO:
			suff_val = 1e-21;
			break;
		case MR_MATH_SI_PREFIX_YOCTO:
			suff_val = 1e-24;
			break;
		case MR_MATH_SI_PREFIX_KIBI:
			suff_val = pow (static_cast<double>(2), 10);
			break;
		case MR_MATH_SI_PREFIX_MEBI:
			suff_val = pow (static_cast<double>(2), 20);
			break;
		case MR_MATH_SI_PREFIX_GIBI:
			suff_val = pow (static_cast<double>(2), 30);
			break;
		case MR_MATH_SI_PREFIX_TEBI:
			suff_val = pow (static_cast<double>(2), 40);
			break;
		case MR_MATH_SI_PREFIX_PEBI:
			suff_val = pow (static_cast<double>(2), 50);
			break;
		case MR_MATH_SI_PREFIX_EXBI:
			suff_val = pow (static_cast<double>(2), 60);
			break;
		case MR_MATH_SI_PREFIX_ZEBI:
			suff_val = pow (static_cast<double>(2), 70);
			break;
		case MR_MATH_SI_PREFIX_YOBI:
			suff_val = pow (static_cast<double>(2), 80);
			break;
	}

	retv = suff_val * multipl;
	return retv;
}

mrComplex_ptr mr_sin(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::sin(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_cos(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::cos(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_tan(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::tan(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_asin(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = boost::math::asin(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_acos(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = boost::math::acos(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_atan(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = boost::math::atan(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_sinh(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::sinh(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_cosh(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::cosh(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_tanh(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::tanh(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_asinh(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = boost::math::asinh(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_acosh(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = boost::math::acosh(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_atanh(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = boost::math::atanh(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_exp(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::exp(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_log(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::log(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_log10(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::log10(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_sqrt(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::sqrt(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_abs(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::abs(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_re(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	retv->real = x->real; retv->imag = 0.0;
	return retv;
}

mrComplex_ptr mr_im(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	retv->imag = x->imag; retv->real = 0.0;
	return retv;
}

mrComplex_ptr mr_arg(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::arg(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_conj(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::conj(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_deg(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();

	retv->real = fmod(x->real * 180 / mr_pi(), 360);
	retv->imag = 0;

	return retv;
}

mrComplex_ptr mr_rad(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();

	retv->real = fmod(x->real * mr_pi() / 180, 2*mr_pi());
	retv->imag = 0;

	return retv;
}

mrComplex_ptr mr_norm(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg_c, x);
	retv_c = std::norm(arg_c);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_polar(mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t retv_c;

	retv_c = std::polar(x->real, x->imag);
	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_atan2 (mrComplex_ptr x, mrComplex_ptr y) {
	mrComplex_ptr retv = newMrComplex();
	retv->real = std::atan2(x->real, y->real);
	return retv;
}

mrComplex_ptr mr_pow (mrComplex_ptr x, mrComplex_ptr y) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t arg1_c, arg2_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg1_c, x);
	MRCOMPLEX_2_STDCOMPLEX(arg2_c, y);

	retv_c = std::pow(arg1_c, arg2_c);

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);

	return retv;
}

mrComplex_ptr mr_add (mrComplex_ptr lv, mrComplex_ptr rv) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t rv_c, lv_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(rv_c,rv);
	MRCOMPLEX_2_STDCOMPLEX(lv_c,lv);

	retv_c = lv_c + rv_c;

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);
	return retv;
}

mrComplex_ptr mr_substract (mrComplex_ptr lv, mrComplex_ptr rv) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t rv_c, lv_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(rv_c,rv);
	MRCOMPLEX_2_STDCOMPLEX(lv_c,lv);

	retv_c = lv_c - rv_c;

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);
	return retv;
}

mrComplex_ptr mr_multiply (mrComplex_ptr lv, mrComplex_ptr rv) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t rv_c, lv_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(rv_c,rv);
	MRCOMPLEX_2_STDCOMPLEX(lv_c,lv);

	retv_c = lv_c * rv_c;

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);
	return retv;
}

mrComplex_ptr mr_divide (mrComplex_ptr lv, mrComplex_ptr rv) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t rv_c, lv_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(rv_c,rv);
	MRCOMPLEX_2_STDCOMPLEX(lv_c,lv);

	retv_c = lv_c / rv_c;

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);
	return retv;
}

mrComplex_ptr mr_modulo (mrComplex_ptr lv, mrComplex_ptr rv) {
	mrComplex_ptr retv = newMrComplex();
	mr_StdComplex_t retv_c;

	retv_c.imag(0);
	retv_c.real(static_cast<mrNumeric_t>(fmod(lv->real, rv->real)));

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);
	return retv;
}

mrComplex_ptr mr_and (mrComplex_ptr x, mrComplex_ptr y) {
	mrComplex_ptr retv = newMrComplex();

	retv->imag = 0;
	//retv->real = x->real & y->real;

	return retv;
}

mrComplex_ptr mr_or (mrComplex_ptr x, mrComplex_ptr y) {
	mrComplex_ptr retv = newMrComplex();

	retv->imag = 0;
	//retv->real = x->real | y->real;

	return retv;
}

mrComplex_ptr mr_not (mrComplex_ptr x) {
	mrComplex_ptr retv = newMrComplex();

	retv->imag = 0;
	//retv->real = ~(x->real);

	return retv;
}

mrComplex_ptr mr_nand (mrComplex_ptr x, mrComplex_ptr y) {
	mrComplex_ptr retv = newMrComplex();

	retv->imag = 0;
	//retv->real = !(x->real & y->real);

	return retv;
}

mrComplex_ptr mr_nor (mrComplex_ptr x, mrComplex_ptr y) {
	mrComplex_ptr retv = newMrComplex();

	retv->imag = 0;
	//retv->real = ~(x->real | y->real);

	return retv;
}

mrComplex_ptr mr_xor (mrComplex_ptr x, mrComplex_ptr y) {
	mrComplex_ptr retv = newMrComplex();

	retv->imag = 0;
	//retv->real = x->real ^ y->real;

	return retv;
}

mrComplex_ptr mr_xnor (mrComplex_ptr x, mrComplex_ptr y) {
	mrComplex_ptr retv = newMrComplex();

	retv->imag = 0;
	//retv->real = ~(x->real ^ y->real);

	return retv;
}

/*! Parsing of numeric types. */
mrNumeric_t parse_mrNumeric_t (pANTLR3_STRING strin) {
	string str;
	ANTLR3_UINT32 len = strin->len;

	/*! This naive implementation works only if str contains
	just digits, dot as decimal separator, sign and 'e' or 'E'.
	For other possibilities (for example, Arabic decimal separator)
	it will not work. This is inherent limitation of
	ANTLR3_STRING which could be overcome by looking into input
	stream directly, while using position of token that ANTLR
	provides, thus avoiding ANTLR3_STRING completely.

	Instead of doing this complicated implementation, input preprocessor
	will be implemented that will replace all locale specific characters
	with internal representation, before input is handed to parser. 
	This replacement will occur somewhere high in application so that
	parser and lexer will always get clear string expressions in which
	decimal separator will always be '.' */

	char removeCh = MathEvaluator::internalDecimalPoint().toAscii();
	char current;
	for (ANTLR3_UINT32 i = 0; i < len; ++i) {
		current = static_cast<char>(strin->charAt(strin, i));
		if (current == removeCh) {
			str += '.';
		} else {
			str += current;
		}
	}

	mrNumeric_t retv;
	try {
		retv = numeric_cast<mrNumeric_t>(lexical_cast<mrNumeric_t, string>(str));
	}
	catch (bad_lexical_cast&) {
		throw NumericConversionError("Range error: " + str);
	}
	catch (bad_numeric_cast&) {
		throw NumericConversionError("Range error: " + str);
	}
 
	return retv;
}

mrNumeric_t parse_hex_mrNumeric_t (pANTLR3_STRING strin) {
	ANTLR3_UINT32 len = strin->len;
	string str;
	for (ANTLR3_UINT32 i = 0; i < len; ++i) {
		str += static_cast<char>(strin->charAt(strin, i));;
	}

	mrNumeric_t retv;

	std::stringstream convertor;
	convertor << str;
	unsigned long int result;
	if (!(convertor >> std::hex >> result) || !convertor.eof()) {
		throw NumericConversionError("Range error: " + str);
	}

	retv = result;
	return retv;
}

mrNumeric_t parse_oct_mrNumeric_t (pANTLR3_STRING strin) {
	ANTLR3_UINT32 len = strin->len;
	string str;
	for (ANTLR3_UINT32 i = 0; i < len; ++i) {
		str += static_cast<char>(strin->charAt(strin, i));;
	}

	mrNumeric_t retv;

	std::stringstream convertor;
	convertor << str;
	long int result;
	if (!(convertor >> std::oct >> result) || !convertor.eof()) {
		throw NumericConversionError("Range error: " + str);
	}

	retv = result;
	return retv;
}

mrNumeric_t parse_bin_mrNumeric_t (pANTLR3_STRING strin) {
	ANTLR3_UINT32 len = strin->len;
	string tmpS;
	for (ANTLR3_UINT32 i = 2; i < len; ++i) { // Skipping "0b"
		char digit = static_cast<char>(strin->charAt(strin, i));
		tmpS.push_back(digit);
	}

	mrNumeric_t retv;
	long int result;
	dynamic_bitset<> set(tmpS);
	result = set.to_ulong();
	retv = result;
	return retv;
}