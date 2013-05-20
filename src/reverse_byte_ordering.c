/*
 ============================================================================
 Name        : reverse_byte_ordering.c
 Author      : William Wu (william.wu@themathpath.com)
 Version     : 1.0
 Date		 : May 20, 2013
 Copyright   : 2013
 Description : Reverses ordering of bytes in each block of n bytes.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 	// getopt
#include <sys/stat.h>	// file size

#define byte unsigned char
#define N_DEFAULT 2

/* FUNCTION PROTOTYPES */
void usage(void);
int get_file_size(const char *fpath);

int 
main (int argc, char* argv[]) {

	/* COMMAND-LINE PARAMETERS */
	int g;
	int iflag=0, oflag=0, nflag=0;
	int n = N_DEFAULT;
	char* input_filename = NULL;
	char* output_filename = NULL;
	FILE* ifp;
	FILE* ofp;
	while((g = getopt(argc, argv, "i:o:n:h")) != -1) {
		switch (g) {
			case 'i':
				iflag = 1;
				input_filename = optarg;
				if (NULL == (ifp = fopen(input_filename,"r"))) {
					printf("Cannot open input file %s to read.\n",input_filename);
					return 1;
				}					
				break;
			case 'o':
				oflag = 1;
				output_filename = optarg;
				if (NULL == (ofp = fopen(output_filename,"w"))) {
					printf("Cannot open output file %s to write.\n",output_filename);
					return 2;
				}					
				break;
			case 'n':
				nflag = 1;
				n = atoi(optarg);
				break;
			case 'h':
				usage();
				return 1;
				break;
			case '?':
				usage();
				return 1;
				break;
			default:
				usage();
				break;
		}
	}
	if (0==iflag || 0==oflag) {
		usage();
		return 3;
	}
	// print selected parameters
	printf("input: %s\n", input_filename);
	printf("output: %s\n", output_filename);
	printf("n: %d\n", n);

	// verify file size
	if (0 != get_file_size(input_filename) % n) {
		printf("Size of input file %s in bytes MUST be a multiple of %d.\n",input_filename, n);
		return 4;					
	}
	
	/* READ, REVERSE, AND WRITE */
	byte* buf = (byte*) malloc(sizeof(byte)*n);
	int count = 0;
	int i = 0;
	while(fread(buf, n, 1, ifp) == 1) { // read n bytes
		for(i=(n-1);i>=0;i--) {
			fwrite((buf+i),1,1,ofp); // write bytes in reversed order to disk
		}
		count += n;
	}	

	// reporting
	printf("%d bytes read from %s.\n",count,input_filename);
	printf("Applied byte order reversal to %d blocks, each %d bytes in size, and wrote to %s.\n",count/n,n,output_filename);

	// cleanup
	fclose(ofp);
	fclose(ifp);
	free(buf);

	return 0;
}

void
usage(void) {
	printf("Reverses the ordering of bytes in each block of n bytes, where n is user-specified.\n");
	printf("Usage:\n");
	printf("\treverse_byte_ordering -i [input_file] -o [output_file] -n [number_of_bytes_in_block]\n");	
	printf("\tNote: If -n is omitted, then it defaults to 2. Common use cases are 2 and 4.");
	printf("Example:\n");
	printf("\treverse_byte_ordering -i input_file -o output_file -n 4");
}

int 
get_file_size(const char *fpath)
{
    int ret = -1;
    struct stat* buf = (struct stat*)malloc(sizeof(struct stat));
    if(stat(fpath, buf) == 0) {
        ret = buf->st_size;
    }
    free(buf);
    return ret;
}
