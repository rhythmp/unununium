/* LICENSE INFO: TBD*/

/* tiper - text editor */

/* */

//#include "utilbox.h"
#include "tree.h"

// NEED TO REMOVE THIS
#include<stdio.h>
#include<stdlib.h>


#define VERSION 0
#define REVISION 1
#define TOOL_NAME "tree"

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

	path = (char *) malloc(len + (sizeof(char)*MAX_NAME_SIZE));
	memset( (void *)path, '\0', len + (sizeof(char)*MAX_NAME_SIZE) );
	strcpy( path, path_to_root );

	while( contents = readdir(root) ){
		if( strcmp( contents->d_name, "." ) && strcmp( contents->d_name, ".." ) ){
			printf("\n");
			name = contents->d_name;
			for( loop = 1 ; loop < level; loop++ )
				printf("  |");
			printf("%s", name);

			//////////////////////////////////////////////////////////////////
			
			if(strcmp (path_to_root, "/") )
				strcat( path, "/");
			strcat(path, name);
			strcat( path, "/"); printf("   =====>>%s",path);
			
			/////////////////////////////////////////////////////////////////
			ent = opendir( path );
			printf(" %d", (int) ent);
			if( ent ){
				directory_traverse( ent, path, level+1 );
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
	
	if( argc > 2 ){
		// CHANGE THE EXIT
		printf("\n\tError\n\n");
		exit(0);
	}
	else
	if( argc == 2 ){
		int len = strlen( argv[1] );
		root = (char *)malloc( sizeof(char) * (len + 1 ));
		strcpy( root , argv[1] );
	}		
	else{
		root = (char *)malloc( sizeof(char) * 2 );
		root[0] = '/';
		root[1] = '\0';
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


