/** \file
 *  This C header file was generated by $ANTLR version 3.2 Sep 23, 2009 12:02:23
 *
 *     -  From the grammar source file : ComplexEval.g
 *     -                            On : 2010-06-11 19:56:02
 *     -           for the tree parser : ComplexEvalTreeParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The tree parser ComplexEval has the callable functions (rules) shown below,
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
 * a parser context typedef pComplexEval, which is returned from a call to ComplexEvalNew().
 *
 * The methods in pComplexEval are  as follows:
 *
 *  - mrComplex_ptr      pComplexEval->prog(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->expr(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->unary(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->atom(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->funct_ref1(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->funct_ref2(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->constant_ref(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->si_unit_ref(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->imaginary_number(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->real_number(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->dec_num(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->hex_num(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->oct_num(pComplexEval)
 *  - mrComplex_ptr      pComplexEval->bin_num(pComplexEval)
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

#ifndef	_ComplexEval_H
#define _ComplexEval_H
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
typedef struct ComplexEval_Ctx_struct ComplexEval, * pComplexEval;



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

/** Context tracking structure for ComplexEval
 */
struct ComplexEval_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_TREE_PARSER	    pTreeParser;


     mrComplex_ptr (*prog)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*expr)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*unary)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*atom)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*funct_ref1)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*funct_ref2)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*constant_ref)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*si_unit_ref)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*imaginary_number)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*real_number)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*dec_num)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*hex_num)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*oct_num)	(struct ComplexEval_Ctx_struct * ctx);
     mrComplex_ptr (*bin_num)	(struct ComplexEval_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct ComplexEval_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pComplexEval ComplexEvalNew         (pANTLR3_COMMON_TREE_NODE_STREAM instream);
ANTLR3_API pComplexEval ComplexEvalNewSSD      (pANTLR3_COMMON_TREE_NODE_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the tree parser will work with.
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
#define EOF      -1
#define SI_CONVERT      6
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

/* End of token definitions for ComplexEval
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
