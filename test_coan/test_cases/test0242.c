/**ARGS: defs --once-only --cant -DFOO */
/**SYSCODE: = 2 */
#ifdef FOO
#define /* comment */ B /* comment */ " Definition  1 " // Comment
#else
#define /* comment */ B /* comment */ " Definition 2 " // Comment
#endif
