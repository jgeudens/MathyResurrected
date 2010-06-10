/** \file
 *  This C header file was generated by $ANTLR version 3.2 Sep 23, 2009 12:02:23
 *
 *     -  From the grammar source file : ComplexLexer.g
 *     -                            On : 2010-06-10 23:34:17
 *     -                 for the lexer : ComplexLexerLexer *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer ComplexLexer has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pComplexLexer, which is returned from a call to ComplexLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 * * The methods in pComplexLexer are  as follows:
 *
 *  -  void      pComplexLexer->PLUS(pComplexLexer)
 *  -  void      pComplexLexer->MINUS(pComplexLexer)
 *  -  void      pComplexLexer->MULT(pComplexLexer)
 *  -  void      pComplexLexer->DIV(pComplexLexer)
 *  -  void      pComplexLexer->MOD(pComplexLexer)
 *  -  void      pComplexLexer->POW(pComplexLexer)
 *  -  void      pComplexLexer->ARG_SEPARATOR(pComplexLexer)
 *  -  void      pComplexLexer->DECIMAL_POINT(pComplexLexer)
 *  -  void      pComplexLexer->LEFT_PAREN(pComplexLexer)
 *  -  void      pComplexLexer->RIGHT_PAREN(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_YOTTA(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_ZETTA(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_EXA(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_PETA(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_TERA(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_GIGA(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_MEGA(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_KILO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_HECTO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_DECA(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_DECI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_CENTI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_MILLI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_MICRO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_NANO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_PICO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_FEMTO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_ATTO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_ZEPTO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_YOCTO(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_KIBI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_MEBI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_GIBI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_TEBI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_PEBI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_EXBI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_ZEBI(pComplexLexer)
 *  -  void      pComplexLexer->SI_PREFIX_YOBI(pComplexLexer)
 *  -  void      pComplexLexer->FN_SIN(pComplexLexer)
 *  -  void      pComplexLexer->FN_COS(pComplexLexer)
 *  -  void      pComplexLexer->FN_TAN(pComplexLexer)
 *  -  void      pComplexLexer->FN_ASIN(pComplexLexer)
 *  -  void      pComplexLexer->FN_ACOS(pComplexLexer)
 *  -  void      pComplexLexer->FN_ATAN(pComplexLexer)
 *  -  void      pComplexLexer->FN_ATAN2(pComplexLexer)
 *  -  void      pComplexLexer->FN_SINH(pComplexLexer)
 *  -  void      pComplexLexer->FN_COSH(pComplexLexer)
 *  -  void      pComplexLexer->FN_TANH(pComplexLexer)
 *  -  void      pComplexLexer->FN_ASINH(pComplexLexer)
 *  -  void      pComplexLexer->FN_ACOSH(pComplexLexer)
 *  -  void      pComplexLexer->FN_ATANH(pComplexLexer)
 *  -  void      pComplexLexer->FN_EXP(pComplexLexer)
 *  -  void      pComplexLexer->FN_LN(pComplexLexer)
 *  -  void      pComplexLexer->FN_LOG10(pComplexLexer)
 *  -  void      pComplexLexer->FN_SQRT(pComplexLexer)
 *  -  void      pComplexLexer->FN_POW(pComplexLexer)
 *  -  void      pComplexLexer->FN_NRT(pComplexLexer)
 *  -  void      pComplexLexer->FN_ABS(pComplexLexer)
 *  -  void      pComplexLexer->FN_RE(pComplexLexer)
 *  -  void      pComplexLexer->FN_IM(pComplexLexer)
 *  -  void      pComplexLexer->FN_ARG(pComplexLexer)
 *  -  void      pComplexLexer->FN_CONJ(pComplexLexer)
 *  -  void      pComplexLexer->FN_MIN(pComplexLexer)
 *  -  void      pComplexLexer->FN_MAX(pComplexLexer)
 *  -  void      pComplexLexer->FN_DEG(pComplexLexer)
 *  -  void      pComplexLexer->FN_RAD(pComplexLexer)
 *  -  void      pComplexLexer->FN_PROJ(pComplexLexer)
 *  -  void      pComplexLexer->FN_NORM(pComplexLexer)
 *  -  void      pComplexLexer->FN_POLAR(pComplexLexer)
 *  -  void      pComplexLexer->BINARY_FN_AND(pComplexLexer)
 *  -  void      pComplexLexer->BINARY_FN_OR(pComplexLexer)
 *  -  void      pComplexLexer->BINARY_FN_NOT(pComplexLexer)
 *  -  void      pComplexLexer->BINARY_FN_NAND(pComplexLexer)
 *  -  void      pComplexLexer->BINARY_FN_NOR(pComplexLexer)
 *  -  void      pComplexLexer->BINARY_FN_XOR(pComplexLexer)
 *  -  void      pComplexLexer->BINARY_FN_XNOR(pComplexLexer)
 *  -  void      pComplexLexer->CONSTANTS_PI(pComplexLexer)
 *  -  void      pComplexLexer->CONSTANTS_E(pComplexLexer)
 *  -  void      pComplexLexer->CONSTANTS_ANS(pComplexLexer)
 *  -  void      pComplexLexer->COMPLEX_UNIT(pComplexLexer)
 *  -  void      pComplexLexer->HEX_NUMBER(pComplexLexer)
 *  -  void      pComplexLexer->HEX_DIGIT(pComplexLexer)
 *  -  void      pComplexLexer->OCTAL_NUMBER(pComplexLexer)
 *  -  void      pComplexLexer->BINARY_NUMBER(pComplexLexer)
 *  -  void      pComplexLexer->FLOAT_NUMBER(pComplexLexer)
 *  -  void      pComplexLexer->FLOAT_MANTISSA(pComplexLexer)
 *  -  void      pComplexLexer->EXPONENT(pComplexLexer)
 *  -  void      pComplexLexer->WS(pComplexLexer)
 *  -  void      pComplexLexer->LEXER_ERROR(pComplexLexer)
 *  -  void      pComplexLexer->OTHER_CHAR(pComplexLexer)
 *  -  void      pComplexLexer->Tokens(pComplexLexer)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD licence"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_ComplexLexer_H
#define _ComplexLexer_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

	#include "math_bridge_API.h"

 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct ComplexLexer_Ctx_struct ComplexLexer, * pComplexLexer;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/** Context tracking structure for ComplexLexer
 */
struct ComplexLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;


     void (*mPLUS)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mMINUS)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mMULT)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mDIV)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mMOD)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mPOW)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mARG_SEPARATOR)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mDECIMAL_POINT)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mLEFT_PAREN)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mRIGHT_PAREN)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_YOTTA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_ZETTA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_EXA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_PETA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_TERA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_GIGA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_MEGA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_KILO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_HECTO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_DECA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_DECI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_CENTI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_MILLI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_MICRO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_NANO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_PICO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_FEMTO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_ATTO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_ZEPTO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_YOCTO)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_KIBI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_MEBI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_GIBI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_TEBI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_PEBI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_EXBI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_ZEBI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mSI_PREFIX_YOBI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_SIN)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_COS)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_TAN)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ASIN)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ACOS)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ATAN)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ATAN2)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_SINH)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_COSH)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_TANH)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ASINH)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ACOSH)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ATANH)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_EXP)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_LN)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_LOG10)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_SQRT)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_POW)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_NRT)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ABS)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_RE)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_IM)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_ARG)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_CONJ)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_MIN)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_MAX)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_DEG)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_RAD)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_PROJ)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_NORM)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFN_POLAR)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mBINARY_FN_AND)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mBINARY_FN_OR)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mBINARY_FN_NOT)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mBINARY_FN_NAND)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mBINARY_FN_NOR)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mBINARY_FN_XOR)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mBINARY_FN_XNOR)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mCONSTANTS_PI)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mCONSTANTS_E)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mCONSTANTS_ANS)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mCOMPLEX_UNIT)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mHEX_NUMBER)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mHEX_DIGIT)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mOCTAL_NUMBER)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mBINARY_NUMBER)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFLOAT_NUMBER)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mFLOAT_MANTISSA)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mEXPONENT)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mWS)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mLEXER_ERROR)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mOTHER_CHAR)	(struct ComplexLexer_Ctx_struct * ctx);
     void (*mTokens)	(struct ComplexLexer_Ctx_struct * ctx);    const char * (*getGrammarFileName)();
    void	    (*free)   (struct ComplexLexer_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pComplexLexer ComplexLexerNew         (pANTLR3_INPUT_STREAM instream);
ANTLR3_API pComplexLexer ComplexLexerNewSSD      (pANTLR3_INPUT_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the lexer will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define FUNCTION      8
#define BINARY_FN_XNOR      89
#define EXPONENT      99
#define SI_PREFIX_TERA      28
#define FN_POLAR      82
#define MOD      18
#define SI_PREFIX_ZEPTO      42
#define ARG_SEPARATOR      20
#define BINARY_FN_NAND      86
#define FN_MAX      77
#define LEXER_ERROR      102
#define ATOM      9
#define SI_CONVERT      6
#define EOF      -1
#define SI_PREFIX_YOTTA      24
#define FN_TANH      61
#define FN_COS      53
#define FN_ATAN      57
#define FN_ASIN      55
#define POW      19
#define SI_PREFIX_EXA      26
#define SI_PREFIX_ZETTA      25
#define FN_LOG10      67
#define SI_PREFIX_GIGA      29
#define SI_PREFIX_MILLI      36
#define FN_NORM      81
#define OCTAL_NUMBER      96
#define SI_PREFIX_MEGA      30
#define OTHER_CHAR      103
#define BINARY_FN_NOR      87
#define SI_PREFIX_FEMTO      40
#define BINARY_FN_NOT      85
#define FN_MIN      76
#define BINARY_FN_OR      84
#define MULT      16
#define SI_PREFIX_PETA      27
#define FN_ACOSH      63
#define FN_NRT      70
#define FN_PROJ      80
#define OCT      13
#define BINARY_NUMBER      97
#define WS      101
#define FN_COSH      60
#define SI_PREFIX_YOCTO      43
#define FN_RAD      79
#define LEFT_PAREN      22
#define CONSTANT_REF      7
#define FN_SQRT      68
#define FN_POW      69
#define RE      5
#define SI_PREFIX_ZEBI      50
#define FN_ABS      71
#define FN_CONJ      75
#define BINARY_FN_AND      83
#define FN_DEG      78
#define FN_EXP      65
#define SI_PREFIX_PICO      39
#define SI_PREFIX_YOBI      51
#define CONSTANTS_PI      90
#define SI_PREFIX_NANO      38
#define RIGHT_PAREN      23
#define FN_ACOS      56
#define DECIMAL_POINT      21
#define IM      4
#define SI_PREFIX_GIBI      46
#define SI_PREFIX_PEBI      48
#define HEX      12
#define SI_PREFIX_HECTO      32
#define FN_TAN      54
#define SI_PREFIX_ATTO      41
#define PLUS      14
#define FN_SINH      59
#define FN_LN      66
#define UNARY      10
#define BINARY_FN_XOR      88
#define SI_PREFIX_DECA      33
#define CONSTANTS_ANS      92
#define SI_PREFIX_EXBI      49
#define FN_ASINH      62
#define FLOAT_NUMBER      100
#define SI_PREFIX_TEBI      47
#define SI_PREFIX_DECI      34
#define SI_PREFIX_KIBI      44
#define FN_ARG      74
#define CONSTANTS_E      91
#define HEX_DIGIT      94
#define FN_IM      73
#define SI_PREFIX_CENTI      35
#define FN_SIN      52
#define COMPLEX_UNIT      93
#define MINUS      15
#define FLOAT_MANTISSA      98
#define SI_PREFIX_MEBI      45
#define SI_PREFIX_MICRO      37
#define FN_ATAN2      58
#define SI_PREFIX_KILO      31
#define FN_RE      72
#define DIV      17
#define FN_ATANH      64
#define HEX_NUMBER      95
#define BIN      11
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for ComplexLexer
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
