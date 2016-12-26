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

static void usage();
static void print_version();
static void directory_traverse( DIR *, const char *, unsigned int );
//static int init_tree(int argc, char **argv);
