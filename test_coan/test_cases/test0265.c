/**ARGS: source -DX=A */
/**SYSCODE: = 0 */
#if X == 0
KEEP ME
#endif
#if 0 == X
KEEP ME
#endif
#if (X == 0)
KEEP ME
#endif
#if (X + 1) < 3
KEEP ME
#endif
#if (X + 1) == X
KEEP ME
#endif

