/**ARGS: symbols --locate -d -u --must -DFOO -UBAR */
/**SYSCODE: = 2 */
#ifdef FOO
#undef FOO
#else
#define FOO 1
#endif
#ifndef BAR
#define BAR 1
#else
#undef BAR 
#endif
