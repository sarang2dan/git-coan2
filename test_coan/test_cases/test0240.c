/**ARGS: symbols -L -d -u --expand --must -DFOO -DSTR=string */
/**SYSCODE: = 2 */
#ifdef FOO
#define FOO 1
#define STR
#undef BAR
#else
#define BAR
#endif
