/**ARGS: symbols --locate --undefs --cant -DFOO -UBAR */
/**SYSCODE: = 2 */
#ifdef FOO
#define FOO 1
#else
#undef FOO
#endif
#ifndef BAR
#define BAR 1
#else
#undef BAR 
#endif
