/** \file
 *  This C header file was generated by $ANTLR version 3.2 Sep 23, 2009 12:02:23
 *
 *     -  From the grammar source file : ComplexParser.g
 *     -                            On : 2010-06-13 13:30:16
 *     -                for the parser : ComplexParserParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser ComplexParser has the callable functions (rules) shown below,
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
 * a parser context typedef pComplexParser, which is returned from a call to ComplexParserNew().
 *
 * The methods in pComplexParser are  as follows:
 *
 *  - ComplexParser_prog_return      pComplexParser->prog(pComplexParser)
 *  - ComplexParser_expr_return      pComplexParser->expr(pComplexParser)
 *  - ComplexParser_bitor_return      pComplexParser->bitor(pComplexParser)
 *  - ComplexParser_bitxor_return      pComplexParser->bitxor(pComplexParser)
 *  - ComplexParser_bitand_return      pComplexParser->bitand(pComplexParser)
 *  - ComplexParser_addition_return      pComplexParser->addition(pComplexParser)
 *  - ComplexParser_multiplication_return      pComplexParser->multiplication(pComplexParser)
 *  - ComplexParser_exponentiation_return      pComplexParser->exponentiation(pComplexParser)
 *  - ComplexParser_unary_return      pComplexParser->unary(pComplexParser)
 *  - ComplexParser_atom_return      pComplexParser->atom(pComplexParser)
 *  - ComplexParser_funct_ref1_return      pComplexParser->funct_ref1(pComplexParser)
 *  - ComplexParser_funct_ref2_return      pComplexParser->funct_ref2(pComplexParser)
 *  - ComplexParser_constant_ref_return      pComplexParser->constant_ref(pComplexParser)
 *  - ComplexParser_si_unit_ref_return      pComplexParser->si_unit_ref(pComplexParser)
 *  - ComplexParser_imaginary_number_return      pComplexParser->imaginary_number(pComplexParser)
 *  - ComplexParser_real_number_return      pComplexParser->real_number(pComplexParser)
 *  - ComplexParser_dec_num_return      pComplexParser->dec_num(pComplexParser)
 *  - ComplexParser_hex_num_return      pComplexParser->hex_num(pComplexParser)
 *  - ComplexParser_oct_num_return      pComplexParser->oct_num(pComplexParser)
 *  - ComplexParser_bin_num_return      pComplexParser->bin_num(pComplexParser)
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

#ifndef	_ComplexParser_H
#define _ComplexParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct ComplexParser_Ctx_struct ComplexParser, * pComplexParser;



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
typedef struct ComplexParser_prog_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_prog_return;

typedef struct ComplexParser_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_expr_return;

typedef struct ComplexParser_bitor_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_bitor_return;

typedef struct ComplexParser_bitxor_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_bitxor_return;

typedef struct ComplexParser_bitand_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_bitand_return;

typedef struct ComplexParser_addition_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_addition_return;

typedef struct ComplexParser_multiplication_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_multiplication_return;

typedef struct ComplexParser_exponentiation_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_exponentiation_return;

typedef struct ComplexParser_unary_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_unary_return;

typedef struct ComplexParser_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_atom_return;

typedef struct ComplexParser_funct_ref1_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_funct_ref1_return;

typedef struct ComplexParser_funct_ref2_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_funct_ref2_return;

typedef struct ComplexParser_constant_ref_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_constant_ref_return;

typedef struct ComplexParser_si_unit_ref_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_si_unit_ref_return;

typedef struct ComplexParser_imaginary_number_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_imaginary_number_return;

typedef struct ComplexParser_real_number_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_real_number_return;

typedef struct ComplexParser_dec_num_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_dec_num_return;

typedef struct ComplexParser_hex_num_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_hex_num_return;

typedef struct ComplexParser_oct_num_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_oct_num_return;

typedef struct ComplexParser_bin_num_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ComplexParser_bin_num_return;



/** Context tracking structure for ComplexParser
 */
struct ComplexParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;


     ComplexParser_prog_return (*prog)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_expr_return (*expr)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_bitor_return (*bitor)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_bitxor_return (*bitxor)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_bitand_return (*bitand)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_addition_return (*addition)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_multiplication_return (*multiplication)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_exponentiation_return (*exponentiation)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_unary_return (*unary)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_atom_return (*atom)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_funct_ref1_return (*funct_ref1)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_funct_ref2_return (*funct_ref2)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_constant_ref_return (*constant_ref)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_si_unit_ref_return (*si_unit_ref)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_imaginary_number_return (*imaginary_number)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_real_number_return (*real_number)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_dec_num_return (*dec_num)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_hex_num_return (*hex_num)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_oct_num_return (*oct_num)	(struct ComplexParser_Ctx_struct * ctx);
     ComplexParser_bin_num_return (*bin_num)	(struct ComplexParser_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct ComplexParser_Ctx_struct * ctx);
    /* @headerFile.members() */
    pANTLR3_BASE_TREE_ADAPTOR	adaptor;
    pANTLR3_VECTOR_FACTORY		vectors;
    /* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pComplexParser ComplexParserNew         (pANTLR3_COMMON_TOKEN_STREAM instream);
ANTLR3_API pComplexParser ComplexParserNewSSD      (pANTLR3_COMMON_TOKEN_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the parser will work with.
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
#define FN_POLAR      90
#define SI_PREFIX_TERA      36
#define EXPONENT      109
#define BITWISE_FN_SHR      99
#define MOD      20
#define SI_PREFIX_ZEPTO      50
#define BITWISE_FN_SHL      98
#define ARG_SEPARATOR      22
#define BITWISE_FN_NOR      95
#define BW_XOR      29
#define FN_MAX      85
#define LEXER_ERROR      112
#define BITWISE_FN_NOT      93
#define ATOM      9
#define EOF      -1
#define SI_CONVERT      6
#define SI_PREFIX_YOTTA      32
#define FN_TANH      69
#define BITWISE_FN_NAND      94
#define FN_COS      61
#define FN_ATAN      65
#define FN_ASIN      63
#define POW      21
#define SI_PREFIX_EXA      34
#define SI_PREFIX_ZETTA      33
#define FN_LOG10      75
#define SI_PREFIX_GIGA      37
#define SI_PREFIX_MILLI      44
#define FN_NORM      89
#define OCTAL_NUMBER      106
#define SI_PREFIX_MEGA      38
#define BW_SHLEFT      30
#define OTHER_CHAR      113
#define SI_PREFIX_FEMTO      48
#define FN_MIN      84
#define BW_SHRIGHT_OP      15
#define MULT      18
#define SI_PREFIX_PETA      35
#define FN_NRT      78
#define FN_ACOSH      71
#define FN_PROJ      88
#define OCT      13
#define BINARY_NUMBER      107
#define WS      111
#define FN_COSH      68
#define SI_PREFIX_YOCTO      51
#define FN_RAD      87
#define LEFT_PAREN      24
#define CONSTANT_REF      7
#define FN_SQRT      76
#define FN_POW      77
#define BW_AND      26
#define BW_OR      27
#define RE      5
#define SI_PREFIX_ZEBI      58
#define FN_ABS      79
#define FN_CONJ      83
#define BITWISE_FN_OR      92
#define FN_DEG      86
#define FN_EXP      73
#define SI_PREFIX_PICO      47
#define SI_PREFIX_YOBI      59
#define CONSTANTS_PI      100
#define SI_PREFIX_NANO      46
#define RIGHT_PAREN      25
#define FN_ACOS      64
#define BW_SHRIGHT      31
#define DECIMAL_POINT      23
#define IM      4
#define BITWISE_FN_AND      91
#define SI_PREFIX_GIBI      54
#define SI_PREFIX_PEBI      56
#define HEX      12
#define SI_PREFIX_HECTO      40
#define FN_TAN      62
#define PLUS      16
#define SI_PREFIX_ATTO      49
#define FN_SINH      67
#define FN_LN      74
#define UNARY      10
#define SI_PREFIX_DECA      41
#define CONSTANTS_ANS      102
#define SI_PREFIX_EXBI      57
#define FN_ASINH      70
#define FLOAT_NUMBER      110
#define SI_PREFIX_TEBI      55
#define SI_PREFIX_DECI      42
#define SI_PREFIX_KIBI      52
#define FN_ARG      82
#define BITWISE_FN_XOR      96
#define CONSTANTS_E      101
#define HEX_DIGIT      104
#define FN_IM      81
#define FN_SIN      60
#define SI_PREFIX_CENTI      43
#define MINUS      17
#define COMPLEX_UNIT      103
#define BW_SHLEFT_OP      14
#define FLOAT_MANTISSA      108
#define SI_PREFIX_MEBI      53
#define SI_PREFIX_MICRO      45
#define FN_ATAN2      66
#define SI_PREFIX_KILO      39
#define FN_RE      80
#define FN_ATANH      72
#define DIV      19
#define BW_NOT      28
#define HEX_NUMBER      105
#define BIN      11
#define BITWISE_FN_XNOR      97
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for ComplexParser
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
