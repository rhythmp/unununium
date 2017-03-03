#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_NAME_SIZE 256
#define LEVEL_1 1
#define LEVEL_2	2
#define LEVEL_3	3
#define LEVEL_4	4

#define BIT0 ( 1UL << 0 )
#define BIT1 ( 1UL << 1 )
#define BIT2 ( 1UL << 2 )
#define BIT3 ( 1UL << 3 )
#define BIT4 ( 1UL << 4 )
#define BIT5 ( 1UL << 5 )
#define BIT6 ( 1UL << 6 )
#define BIT7 ( 1UL << 7 )
#define BIT8 ( 1UL << 8 )
#define BIT9 ( 1UL << 9 )
#define BIT10 ( 1UL << 10 )
#define BIT11 ( 1UL << 11 )
#define BIT12 ( 1UL << 12 )

#define BIT_A BIT12
#define BIT_D BIT1
#define BIT_F BIT2
#define BIT_P BIT3
#define BIT_S BIT4
#define BIT_H BIT5
#define BIT_U BIT6
#define BIT_G BIT7
#define BIT_CAPS_D 	BIT8
#define BIT_LONG_INODES BIT9
#define BIT_LONG_DEVICE BIT10
#define BIT_LONG_HELP 	BIT11
#define BIT_LONG_VERSION BIT12

static void usage();
static void print_version();
static void directory_traverse( DIR *, const char *, unsigned int );
//static int init_tree(int argc, char **argv);
