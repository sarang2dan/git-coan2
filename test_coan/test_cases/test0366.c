/**ARGS: symbols --must -L --explain -DXX=A */
/**SYSCODE: = 3 */

#define YY XX
#define ZZ YY
#define BB A
#define A 1
#if YY == BB
#undef A
#else
#undef BB
#endif
