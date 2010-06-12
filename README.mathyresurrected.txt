===========================================================================
                 MathyResurrected plugin for Launchy
===========================================================================

    MathyResurrected is advanced calculator plugin for excellent and
extremely useful program Launchy ( http://www.launchy.net/ ).

Author
======
Tomislav Adamić (a.k.a. El Gruñón) <tomislav.adamic@gmail.com>

About
=====

    Once upon a time there was a popular plugin for Launchy called Mathy.
It was powerful and slim. It was useful. But, those were the dark times,
and Launchy needed to overcome that. So, the version 2.0 came. Many plugins
followed this outbreak and from darkness came into the 2.0 light. But not
Mathy.

    Mathy was the sole purpose why many Launchy users didn't want to come
into the 2.0 light. Just to have their Mathy, they refused to take on new
Launchy. But this will be no more...

    MathyResurrected will try to replicate Mathy functionality.
MathyResurrected is starting from the scratch. Well, not trully. The idea
for it's sole existence came from Mathy's author. So, credit should be
given: thanks jiquera for your excellent idea and excellent plugin. I hope
MathyResurrected will be worthy successor.

Instalation
===========
    - Unzip dll into Launch plugins folder
    - Unzip icons into Launcy plugins/icons folder
    - restart Launchy
    - enable plugin in options. It is advised to disable calcy.

Support
=======
All questions regarding plugin should be asked at Sourceforge project site:

         http://sourceforge.net/projects/mathyresurrected/

Or at Launchy project site, "Plugins 2.0+" subforum:

         https://sourceforge.net/projects/launchy/

Features
========
    - complex number arithemtic
    - many built in math functions and operators (see the list below)
    - some predefined math constants (see the list below)
    - ignores space
    - Configurable decimal point separator and function argument separator
    - Configurable thousands separator
    - Configurable result format
    - SI and binary unit prefixes
    - binary, hexadecimal nad octal input and output

===========================================================================
                             Numeric input
===========================================================================

    All numbers are treated as complex numbers. It is allowed to use either
'i' or 'j' to write complex unit (sqrt(-1)). Assuming '.' as decimal
separator following are examples of supported numeric input:

      input            interpreted as
    12            =      12+0i
    12e12         =      12*10^12+0i
    12E+12        =      12*10^12+0i
    12e-12        =      12*10^(-12)+0i
    12.12         =      12.12+0i
    12.12E12      =      12.12*10^12+0i
    .12           =      0.12+0i
    -.12e-2       =      -0.12*10(-2)+0i
    12+3i         =      12+3i
    12-12E-12+i   =      12.12*10^(-12)+i
    i             =      0+i
    -i            =      0-i
    -12i          =      0-12i
    ...

===========================================================================
                             Operators
===========================================================================

    The following operators are available:

    Unary operators
    ===============
    Op        Name                Example
     +        plus                 +4, +i
     -        minus                -4, -i

    Binary operators
    ================
    Op        Name                Example
     +        plus                 6+4, 1+2
     -        minus                -4, 2-i
     *        multiply             6*4, 1*2
     /        divide               4/4, 2/i
     ^        to the power of      4^4, 2^i
     %        modulo               456%45
              NOTE: a%b=Re(a)%Re(b) if (Im{a}!=0 || Im{b}!=0)

    ()        brackets

    Bitwise operators (unary and binary)
    ====================================

    These operators operate on unsigned integer real part of operands.
This means that for any two complex numbers x and y, and binary bitwise
operator op

                    x op y = UInt{Re{x}} op UInt{Re{y}}

    symbol        name
       &         and
       |         or
       ×         xor
       ~         not
      ~&         nand
      ~|         nor
      ~×         xnor

===========================================================================
                       SI and binary unit prefixes
===========================================================================

    This is special functionality that allows you to write SI unit prefix
as a number suffix and that number is automatically converted into
base unit quantity. i.e.:

    2k = 2 * 1 0000 = 2.000
    2M = 2 * 1 000 000 = 2.000.000

but also

    2Ki = 2 * 1024 = 2048

Note that you can't write prefix alone (as you can with imaginary unit):
    k or 1*k
But number must be present and is implicitly multiplied:
    1k

SI SUFFIXES ARE CASE SENSITIVE!

Here is the list of all supported suffixes:

    Quantity    Prefix    Symbol
      10^24      yotta      Y
      10^21      zetta      Z
      10^18      exa        E
      10^15      peta       P
      10^12      tera       T
      10^9       giga       G
      10^6       mega       M
      10^3       kilo       k
      10^2       hecto      h
      10^1       deca      da

      10^-1      deci       d
      10^-2      centi      c
      10^-3      milli      m
      10^-6      micro      u
      10^-9      nano       n
      10^-12     pico       p
      10^-15     femto      f
      10^-18     atto       a
      10^-21     zepto      z
      10^-24     yocto      y

    Name    Symbol    Base 2    Base 1024
    kibi      Ki       2^10      1024^1
    mebi      Mi       2^20      1024^2
    gibi      Gi       2^30      1024^3
    tebi      Ti       2^40      1024^4
    pebi      Pi       2^50      1024^5
    exbi      Ei       2^60      1024^6
    zebi      Zi       2^70      1024^7
    yobi      Yi       2^80      1024^8

===========================================================================
                             Functions
===========================================================================

MathyResurrected has a set of built in functions. Function arguments are
separated by ';' or ':' depending on MathyResurrected setings.

Functions are case insensitive.

The following functions are supported:

Trigonometric functions
=======================

    sin(x)            complex sine of x
    cos(x)            complex cosine of x
    tan(x)            complex tangent of x

    asin(x)
    arcsin(x)        complex arc sine of x
    acos(x)
    arccos(x)        complex arc cosine of x
    atan(x)
    arctan(x)        complex arc tangent of x
    atan2(x, y)
    arctan2(x, y)    arc tangent of y/x, but uses the sign of both
                     arguments to determine the quadrant.
                     NOTE: atan2(a,b)=atan2(Re(a), Re(b))
                           if (Im{a}!=0 || Im{b}!=0)

Hyperbolic functions
====================

    sinh(x)       complex hyperbolic sine of x
    cosh(x)       complex hyperbolic cosine of x
    tanh(x)       complex hyperbolic tangent of x

    asinh(x)
    arcsinh(x)    complex inverse hyperbolic sine of x
    acosh(x)
    arccosh(x)    complex inverse hyperbolic cosine of x
    atanh(x)
    arctanh(x)    complex inverse hyperbolic tangent of x

Exponential and logarithmic functions
=====================================

    exp(x)        e (2.71828183... ) raised to the power of x
    ln(x)
    log(x)        natural logarithm of x
                  NOTE: ln(0)=NaN
    log10(x)      common logarithm of x
                  NOTE: log(0)=NaN

Power functions
===============

    sqrt(x)        square root of x
    pow(x, y)      x raised to the power of y

Miscellaneous functions
=======================

    abs(x)        absolute value of x
    re(x)         real part of x
    im(x)         imaginary part of x
    arg(x)        argument of x
                  NOTE: arg(0) is NaN
    conj(x)       complex conjugate
    min(x, y)     smallest of x and y
                  NOTE: min(a,b) = min(Re(a), Re(b)) if (Im{a}!=0 || Im{b}!=0)
    max(x, y)     biggest of x and y
                  NOTE: max(a,b)= max(Re(a), Re(b)) if (Im{a}!=0 || Im{b}!=0)

    deg(x)        for x radians returns number of degrees (0 <= deg(x) < 360)
                  NOTE: deg(x)=deg(Re(x)) if Im{x}!=0
    rad(x)        for x degrees returns number of radians (0 <= rad(x) < 2pi)
                  NOTE: rad(x)=rad(Re(x)) if Im{x}!=0

    norm(x)     norm of complex number
    polar(x)    creates complex number from polar components, where
                Re(x) = r and Im(x) = t;

Bitwise functions
=================

    All these functions are implemented to work with real part of expression only.
This means that for any function f from this group, f(x) = f(Re(x)) no matter what
the value of Im{x} is.

    and(x,y)    - bitwise and
    or(x,y)     - bitwse or
    not(x)      - bitwise not
    nand(x,y)   - bitwise nand: not(x and y)
    nor(x,y)    - bitwise nor: not(x or y)
    xor(x,y)    - bitwise exclusive or
    xnor(x,y)   - bitwise xnor: not(x xor y)

===========================================================================
                             Variables
===========================================================================

    Mathy supported variable expressions like this:

    g=3;1+12;myvar=3 //will return 3

    MathyResurrected currently doesn't support this and I have no plans
doing it, but that may cahnge in the future.

===========================================================================
                              Constants
===========================================================================

There are three predefined constants:

    pi    = 3.14159265...
    e     = 2.71828183...
    ans   = result of previous calculation.

Constants are case sensitive.

NOTE: With complex unit ('i' or 'j') it is allowed to write expressions like
this: 2i, 5.5j, etc... With other constants this is not allowed. So, if you
want for example double of pi, you must write 2*pi, not 2pi. If you're
wondering why is this so, try to interpret this expression: 12e+3. Is it
equal to 12*10^3 or is it 12*e+3? So, say once again with me: there is no
implicit multiplication with constants. On the other hand, it is allowed to
use constant alone instead of multiplying it with one, ie. 34+e, pi+25,
(instead of 34+1*e, 1*pi+25) etc...

===========================================================================
                    Binary, hexadecimal and octal numbers
===========================================================================

    All these bases are supported in input, but only as unsigned integers.
If present in output (which is configurable) these numbers represent
cut-off value of actual calculation which is done with floats.

When in input, numbers must be prefixed with their base prefix:

    "0b" or "0B"    - for binary numbers.         Example: 0b10001111
    "0x" or "0X"    - for hexadecimal numbers.    Example: 0x44AFF
    "0"             - for octal numbers           Example: 01557