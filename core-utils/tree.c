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
static unsigned int flags_option = 0;
static const char SINGLE_OPTION[] = "adDfgpshu";

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

static void print_version(){
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
	DIR *root_count = root;
	int Number_of_entries = 0;
	struct dirent **dirent_traverse = NULL;
	int loop_traverse = 0;
	unsigned int i;

	path = (char *) malloc(len + (sizeof(char)*(NAME_MAX + 1)));
	memset( (void *)path, '\0', len + (sizeof(char)*(NAME_MAX + 1)) );
	strcpy( path, path_to_root );

	// Counting the number of entries in the directory and then closing directory
	while( contents = readdir(root_count)){
		if( strcmp( contents->d_name, "." ) && strcmp( contents->d_name, ".." ) ){
			if( contents->d_name[0] == '.' )	// Can be hidden folder or file
				if(!(flags_option & BIT_A) )
					continue;
			Number_of_entries++;
		}
	}

	dirent_traverse = (struct dirent **) malloc(sizeof(struct dirent *) * Number_of_entries);
	closedir(root);
	printf("===> Number of entries = %d", Number_of_entries);

	// opening the directory for traversal
	root = opendir(path_to_root);

	// store all entries in an array
	while( contents = readdir(root) ){
		if( strcmp( contents->d_name, "." ) && strcmp( contents->d_name, ".." ) ){
			
			if( contents->d_name[0] == '.' )	// Can be hidden folder or file
				if(!(flags_option & BIT_A) )
					continue;
			dirent_traverse[loop_traverse] = contents;
			loop_traverse++;
		
		}
	}

	
	for( i = 0; i < loop_traverse; i++ ){
			printf("\n");
			name = dirent_traverse[i]->d_name;	
			//name = contents->d_name;
			for( loop = 0 ; loop < level_display; loop++ )
				printf("  |");
			printf("%s", name);

			if(strcmp (path_to_root, "/") )
				strcat( path, "/");
			strcat(path, name); //printf("   =====>>%d", contents->d_reclen);
			
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
			path[len] = '\0'; // resetting for other path traversal
		//	free(dirent_traverse[i]);		
		
	}
	fflush(stdout);
	free(dirent_traverse);
	free(path);
}

//static int init_tree(int argc, char **argv)
void main(int argc, char **argv)
{
	char 	*root = NULL;
	DIR 	*ent;
	int opt = 0;
	int long_index = 0;
	int number_of_options = 0;
	
/*	if( argc > 2 ){
		// CHANGE THE EXIT
		printf("\n\tError\n\n");
		exit(0);
	}

	else
*/

	static struct option long_options[] = {
		{"device",	no_argument,	0,	0},
		{"inodes",	no_argument,	0,	0},
		{"help",	no_argument,	0,	0},
		{"version",	no_argument,	0,	0},
		{0,		0,		0,	0  },
	};

	
	while((opt = getopt_long( argc, argv, SINGLE_OPTION, long_options, &long_index)) != -1 ){

		switch(opt){
			case 0:
//				printf("\n\t==%s", long_options[long_index].name);
				if(!strcmp (long_options[long_index].name, "device")){
					number_of_options++;
					flags_option |= BIT_LONG_DEVICE;
					printf("\n\t==%s", long_options[long_index].name);

				}else if(!strcmp (long_options[long_index].name, "inodes")){
					number_of_options++;
					flags_option |= BIT_LONG_INODES;
					printf("\n\t==%s", long_options[long_index].name);

				}else if(!strcmp (long_options[long_index].name, "help")){
					number_of_options++;
					flags_option |= BIT_LONG_HELP;
					printf("\n\t==%s", long_options[long_index].name);

				}else if(!strcmp (long_options[long_index].name, "version")){
					number_of_options++;
					flags_option |= BIT_LONG_VERSION;
					printf("\n\t==%s", long_options[long_index].name);

				}
				break;

			case 'a':
				number_of_options++;
				flags_option |= BIT_A;
				break;
			// break not included for debug
			case 'd':
				number_of_options++;
				flags_option |= BIT_A;
				break;
			case 'D':
				flags_option |= BIT_CAPS_D;
			case 'f':
				flags_option |= BIT_F;
			case 'g':
				flags_option |= BIT_G;
			case 'p':
				flags_option |= BIT_P;
			case 's':
				flags_option |= BIT_S;
			case 'h':
				flags_option |= BIT_H;
			case 'u':
				flags_option |= BIT_U;
				break;
	
			default:
				printf("\n\tDDDD");
				break;
		}
	}

	number_of_options = argc - number_of_options;
	if( number_of_options > 2 ){

	}	
	if( number_of_options == 2 ){
		int len = strlen( argv[argc - 1] );
		root = (char *)malloc( sizeof(char) * (len + 1 ));
		strcpy( root , argv[argc - 1] );
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


