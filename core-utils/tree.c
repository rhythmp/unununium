/* LICENSE INFO: TBD*/

/* tree - display directories in tree */

//#include "utilbox.h"
#include "tree.h"

// NEED TO REMOVE THIS
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<limits.h>
#include<getopt.h>

//#define DEBUG_TREE

#define VERSION 0
#define REVISION 1
#define TOOL_NAME "tree"

#define OPT_HELP 1
#define OPT_VERSION (1 << 1)

static FILE *stream;
static unsigned int maxrow, maxcol;
static unsigned int row, col;

/* TODO Change this */

/*TODO Test this*/
/*#ifndef CTRL
#define CTRL(x) ((x) & 0x1f)
#endif*/

static void usage()
{
	printf("tiper:\n");
	printf("Usage: "
		"./tiper [OPTIONS] [FILE]\n"
		"OPTIONS:\n"
		"-h - Usage\n"
		"-v - Version\n"); 
}

static void print_version()
{
	printf("%s version:%d.%d\n",TOOL_NAME, VERSION, REVISION);
}

static void directory_traverse( DIR *root , const char *path_to_root, unsigned int level ){
	struct dirent *contents;
	DIR *ent;
	int loop;
	char *name = NULL;
	char *path = NULL;
	int len = strlen(path_to_root);
	unsigned int level_display = level;// % 8;
	struct stat sb;

	path = (char *) malloc(len + (sizeof(char)*(NAME_MAX + 1)));
	memset( (void *)path, '\0', len + (sizeof(char)*(NAME_MAX + 1)) );
	strcpy( path, path_to_root );

	while( contents = readdir(root) ){
		if( strcmp( contents->d_name, "." ) && strcmp( contents->d_name, ".." ) ){
			printf("\n");
			name = contents->d_name;
			for( loop = 0 ; loop < level_display; loop++ )
				printf("  |");
			printf("%s", name);

			if(strcmp (path_to_root, "/") )
				strcat( path, "/");
			strcat(path, name);// printf("   =====>>%s",path);
			
			ent = opendir( path );

			#ifdef DEBUG_TREE
			printf(" %d", (int) ent);
			#endif
			if( ent ){
				lstat(path, &sb);
			
				if( !S_ISLNK(sb.st_mode) ){
					directory_traverse( ent, path, level+1 );
				}
				closedir(ent);
			}
			else{
				#ifdef DEBUG_TREE
				if( !strcmp( "Too many open files" , strerror(errno) ) )
				{printf(" error: %s %d", strerror(errno), level);	fflush(stdout);while(1);}
				#endif
			}
			path[len] = '\0';
				
		}
	}
	fflush(stdout);
	free(path);
}

//static int init_tree(int argc, char **argv)
void main(int argc, char **argv)
{
	char 	*root = NULL;
	DIR 	*ent;
	int opt = 0;
	int long_index = 0;
	int flags = 0;
	
/*	if( argc > 2 ){
		// CHANGE THE EXIT
		printf("\n\tError\n\n");
		exit(0);
	}

	else
*/

	static struct option long_options[] = {
		{"help",	no_argument,	0,	0},
		{"version",	no_argument,	0,	0},
		{0,		0,		0,	0  },
	};

	
	while((opt = getopt_long( argc, argv, "vf", long_options, &long_index)) != -1 ){

		switch(opt){
			case 0:
				printf("\n\t%s", long_options[long_index].name);
	
				break;
			case 'v':
				printf("\n\tvvvv");
				break;
			case 'f':
				printf("\n\tffff");
				break;
	
			default:
				printf("\n\tDDDD");
				break;
		}
	}
	
	/*while( (opt = getopt_long( argc, argv, "", long_options, &long_index)) != -1){
		switch(opt) {
			case 'v':
				printf("\n\tVersion...");
				flags = OPT_VERSION;
				fflush(stdout);
				while(1);
				break;
			case 'h':
				printf("\n\tHELP...");
				flags = OPT_HELP;
				fflush(stdout);
				while(1);
				break;
			default:
				break;
		}
	}

	while ((opt = getopt(argc, argv, "vf")) != -1) {
		switch (opt) {
		
		case 'v':
		//	flags = OPT_VERSION;
			printf("\n\tVvvvv...");
			fflush(stdout);
			while(1);
			break;
		case 'f':
		//	flags = OPT_VERSION;
			printf("\n\tfff...");
			fflush(stdout);
			while(1);
			break;
		default:
		//	flags |= OPT_HELP;
			printf("\n\tDddd...");
			fflush(stdout);
			while(1);
			break;
		}
	}*/
	
		 

	if( argc >2 ){

	}	
	if( argc == 2 ){
		int len = strlen( argv[1] );
		root = (char *)malloc( sizeof(char) * (len + 1 ));
		strcpy( root , argv[1] );
	}		
	else{
		root = (char *)malloc( sizeof(char) * PATH_MAX );
		if( getcwd( root, PATH_MAX) == NULL){
		}
	}

	ent = opendir(root);

	if( !ent ){
 		// CHANGE THE EXIT
		free(root);
		printf("\n\tError in ent\n\n");
		exit(0);
	}

	directory_traverse( ent, root, LEVEL_1 );
	printf("\n");

	free(root);
	//return 0;
}


