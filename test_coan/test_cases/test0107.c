/**ARGS: source -DFOO1 -UFOO2 */
/**SYSCODE: = 1 | 16 */
#if defined(FOO2) || 1
KEEP ME
#else
DELETE ME
#endif
