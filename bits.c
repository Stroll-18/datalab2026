/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    return !((x >> 31) ^ (y >> 31)) && !(!x ^ !y);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int s;
    int res = 0;

    s = (v > 65535) << 4;
    res |= s;
    v >>= s;

    s = (v > 255) << 3;
    res |= s;
    v >>= s;

    s = (v > 15) << 2;
    res |= s;
    v >>= s;

    s = (v > 3) << 1;
    res |= s;
    v >>= s;

    res |= (v > 1);

    return res;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n_shift = n << 3;
    int m_shift = m << 3;
    int bn = (x >> n_shift) & 0xFF;
    int bm = (x >> m_shift) & 0xFF;
    int mask = ((0xFF << n_shift) | (0xFF << m_shift));
    int res = (x & ~mask) | (bm << n_shift) | (bn << m_shift);
    return res;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v >> 16) & 0x0000FFFF) | ((v << 16) & 0xFFFF0000);
    v = ((v >> 8)  & 0x00FF00FF) | ((v << 8)  & 0xFF00FF00);
    v = ((v >> 4)  & 0x0F0F0F0F) | ((v << 4)  & 0xF0F0F0F0);
    v = ((v >> 2)  & 0x33333333) | ((v << 2)  & 0xCCCCCCCC);
    v = ((v >> 1)  & 0x55555555) | ((v << 1)  & 0xAAAAAAAA);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~((1 << 31) >> n << 1);
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y = ~x;
    int pos = 0;
    int cond;

    cond = !!(y >> 16);
    pos += cond << 4;
    y >>= cond << 4;

    cond = !!(y >> 8);
    pos += cond << 3;
    y >>= cond << 3;

    cond = !!(y >> 4);
    pos += cond << 2;
    y >>= cond << 2;

    cond = !!(y >> 2);
    pos += cond << 1;
    y >>= cond << 1;

    cond = !!(y >> 1);
    pos += cond;

    return 32 + !y + ~pos;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign, frac, exp, tmp;
    int shift;
    unsigned abs_x;
    if (x == 0) return 0;
    sign = x >> 31;
    if (x < 0)
        abs_x = -x;
    else
        abs_x = x;
    tmp = abs_x;
    shift = 0;
    while(tmp >> 1)
    {
        tmp >>= 1;
        shift++;
    }
    exp = shift + 127;
    abs_x <<= (31 - shift);
    frac = (abs_x >> 8) & ((1U <<23)-1);
    unsigned round = abs_x & 0xff;

    if(round > 0x80)
    {
        frac++;
    }
    else
    {
        if(round == 0x80)
        {
            if(frac & 1)
            {
                frac++;
            }
        }
    }
    if(frac >> 23)
    {
        exp++;
        frac = frac & ((1U <<23)-1);
    }
    return (sign <<31) | (exp <<23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp  = (uf & 0x7F800000) >> 23;
    unsigned frac = uf & 0x007FFFFF;

    if (exp == 0xFF)
    {
        return uf;
    }

    if (exp == 0)
    {
        frac = frac << 1;
        return sign | frac;
    }

    exp = exp + 1;

    if (exp == 0xFF)
    {
        frac = 0;
    }
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 & 0x7FF00000) >> 20;
    unsigned fracHi = uf2 & 0x000FFFFF;
    unsigned fracLo = uf1;
    int E = exp - 1023;

    if (E < 0)
    {
        return 0;
    }
    if (E >= 31)
    {
        return 0x80000000;
    }

    unsigned fullHi = (1 << 20) | fracHi;
    unsigned intHi;

    intHi = (fullHi << E) | (fracLo >> (32 - E));

    int result = intHi >> 20;

    if (sign)
    {
        result = -result;
    }
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127)
    {
        return 0x7F800000;
    }
    if (x < -149)
    {
        return 0;
    }
    if (x >= -126)
    {
        unsigned exp = x + 127;
        return exp << 23;
    }
    unsigned shift = x + 149;
    return 1U << shift;
}
