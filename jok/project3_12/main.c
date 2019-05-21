#include "globals.h"

/*
 *	if no USE_PARSE			: scanner-only
 *	if no USE_PARSE			: parse-only
 *	if no USE_GENERATE_CODE	: does not generate code
 */

#define USE_PARSE			TRUE
#define USE_ANALYZE			TRUE
#define USE_GENERATE_CODE	FALSE

#include "util.h"

#if !USE_PARSE
#include "scan.h"
#else
	#include "parse.h"
	#if USE_ANALYZE
		#include "analyze.h"
	#if USE_CODE
		#include "cgen.h"
	#endif
	#endif
#endif

/* allocate global variables */
int lineno = 0;
FILE *source;
FILE *listing;
FILE *code;

/* allocate and set tracing flags */
int TraceScan		= FALSE;
int TraceParse		= FALSE;
int TraceAnalyze	= TRUE;
int TraceCode		= FALSE;

int Error = FALSE;

int main(int argc, char * argv[])
{
	int i;
	TreeNode *syntaxTree;
	char sourceFileName[120]; /* source code file name */

	if(argc != 2)
	{
		fprintf(stderr,"usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	strcpy(sourceFileName,argv[1]);
	if(strchr (sourceFileName, '.') == NULL) strcat(sourceFileName, ".tny");

	source = fopen(sourceFileName, "r");
	if(source == NULL)
	{
		fprintf(stderr, "File %s not found\n", sourceFileName);
		exit(1);
	}

	listing = stdout; /* send listing to screen */

#if !USE_PARSE
	fprintf(listing, "	 line number\t\ttoken\t\tlexeme\n");
	for(i = 0; i < 60; ++i) fprintf(listing, "-");
	fprintf(listing, "\n");

	while(getToken() != ENDFILE);
#else
	syntaxTree = parse();
	if(TraceParse && !Error)
	{
		fprintf(listing,"\nSyntax tree:\n");
		printTree(syntaxTree);
	}

	#if USE_ANALYZE
	if(!Error)
	{
		if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
		buildSymtab(syntaxTree);

		if(!Error)
		{
			if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
			typeCheck(syntaxTree);
			if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
		}
	}

		#if USE_GENERATE_CODE
		if(!Error)
		{
			char *codefile;
			int fnlen = strcspn(sourceFileName, ".");

			codefile = (char *)calloc(fnlen + 4, sizeof(char));
			strncpy(codefile, sourceFileName, fnlen);
			strcat(codefile, ".tm");
			code = fopen(codefile, "w");

			if(code == NULL)
			{
				printf("Unable to open %s\n", codefile);
				exit(1);
			}

			codeGen(syntaxTree, codefile);
			fclose(code);
		}
		#endif
	#endif
#endif

	fclose(source);
	return 0;
}

