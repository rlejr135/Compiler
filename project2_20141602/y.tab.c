/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 7 "cm.y" /* yacc.c:339  */

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName[5000]; /* for use in assignments */
static int savedLineNo[5000];  /* ditto */
static int savedSize;
static TreeNode * savedTree; /* stores syntax tree for later return */
static int now_level = 0;


#line 83 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ERROR = 258,
    COMERROR = 259,
    ELSE = 260,
    IF = 261,
    INT = 262,
    VOID = 263,
    WHILE = 264,
    RETURN = 265,
    ID = 266,
    NUM = 267,
    PLUS = 268,
    MINUS = 269,
    TIMES = 270,
    OVER = 271,
    LT = 272,
    LE = 273,
    GT = 274,
    GE = 275,
    EQ = 276,
    NE = 277,
    ASSIGN = 278,
    SEMI = 279,
    COMMA = 280,
    LPAREN = 281,
    RPAREN = 282,
    LSQUAREB = 283,
    RSQUAREB = 284,
    LCURLYB = 285,
    RCURLYB = 286,
    LOWER_THEN_ELSE = 287
  };
#endif
/* Tokens.  */
#define ERROR 258
#define COMERROR 259
#define ELSE 260
#define IF 261
#define INT 262
#define VOID 263
#define WHILE 264
#define RETURN 265
#define ID 266
#define NUM 267
#define PLUS 268
#define MINUS 269
#define TIMES 270
#define OVER 271
#define LT 272
#define LE 273
#define GT 274
#define GE 275
#define EQ 276
#define NE 277
#define ASSIGN 278
#define SEMI 279
#define COMMA 280
#define LPAREN 281
#define RPAREN 282
#define LSQUAREB 283
#define RSQUAREB 284
#define LCURLYB 285
#define RCURLYB 286
#define LOWER_THEN_ELSE 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 198 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   104

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    41,    41,    44,    57,    61,    63,    68,    67,    82,
      86,    81,   102,   106,   113,   112,   131,   133,   140,   154,
     160,   169,   168,   187,   195,   211,   214,   229,   232,   234,
     236,   238,   240,   244,   246,   250,   256,   267,   275,   277,
     284,   291,   295,   301,   300,   316,   323,   327,   329,   331,
     333,   335,   337,   341,   348,   352,   354,   358,   365,   369,
     371,   375,   377,   379,   381,   389,   388,   402,   405,   408,
     422
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERROR", "COMERROR", "ELSE", "IF", "INT",
  "VOID", "WHILE", "RETURN", "ID", "NUM", "PLUS", "MINUS", "TIMES", "OVER",
  "LT", "LE", "GT", "GE", "EQ", "NE", "ASSIGN", "SEMI", "COMMA", "LPAREN",
  "RPAREN", "LSQUAREB", "RSQUAREB", "LCURLYB", "RCURLYB",
  "LOWER_THEN_ELSE", "$accept", "program", "declaration_list",
  "declaration", "var_declaration", "$@1", "$@2", "$@3", "type_specifier",
  "fun_declaration", "$@4", "params", "param_list", "param", "$@5",
  "compound_stmt", "local_declarations", "statement_list", "statement",
  "expression_stmt", "selection_stmt", "iteration_stmt", "return_stmt",
  "expression", "var", "$@6", "simple_expression", "relop",
  "additive_expression", "addop", "term", "mulop", "factor", "call", "$@7",
  "args", "arg_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

#define YYPACT_NINF -90

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-90)))

#define YYTABLE_NINF -66

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      47,   -90,   -90,    12,    47,   -90,   -90,     4,   -90,   -90,
     -90,    -4,    -6,    -2,    13,   -90,    31,    49,   -90,    20,
      38,    26,    33,   -90,    32,    23,    43,    47,    50,    48,
     -90,   -90,   -90,   -90,    51,    47,   -90,   -90,    64,    -1,
      53,    52,    56,   -10,    14,   -90,   -90,    24,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,    55,    60,   -90,    46,    54,
     -90,   -90,    24,    24,   -90,    61,    59,    62,    57,   -90,
      24,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,    24,
      24,   -90,   -90,    24,    63,    65,   -90,    24,    24,   -90,
     -90,   -90,    58,    54,   -90,    22,    22,    66,   -90,    67,
      68,    72,   -90,   -90,   -90,    24,    22,   -90,   -90
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,     0,     2,     4,     5,     0,     6,     1,
       3,     7,     0,     0,     0,     8,     0,     0,    10,    13,
       0,     0,    16,    19,     0,    20,     0,     0,     0,     0,
      25,    15,    18,    11,     0,    27,    22,    24,     0,     0,
       7,     0,     0,     0,    42,    64,    34,     0,    23,    29,
      26,    28,    30,    31,    32,     0,    62,    41,    46,    54,
      58,    63,     0,     0,    38,     0,     0,     0,     0,    33,
       0,    55,    56,    48,    47,    49,    50,    51,    52,     0,
       0,    59,    60,     0,     0,     0,    39,     0,    68,    61,
      40,    62,    45,    53,    57,     0,     0,     0,    70,     0,
      67,    35,    37,    44,    66,     0,     0,    69,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -90,   -90,   -90,    82,    69,   -90,   -90,   -90,   -14,   -90,
     -90,   -90,   -90,    70,   -90,    73,   -90,   -90,   -89,   -90,
     -90,   -90,   -90,   -43,   -42,   -90,   -90,   -90,    10,   -90,
      11,   -90,    15,   -90,   -90,   -90,   -90
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,    13,    24,     7,     8,
      14,    21,    22,    23,    29,    49,    35,    39,    50,    51,
      52,    53,    54,    55,    56,    66,    57,    79,    58,    80,
      59,    83,    60,    61,    67,    99,   100
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      65,    44,    45,    20,    68,    41,   101,   102,    42,    43,
      44,    45,     9,    20,    64,    11,    47,   108,    15,    84,
      85,    38,   -14,    46,    -9,    47,    16,    90,    41,    30,
      48,    42,    43,    44,    45,    44,    45,    91,    91,    17,
     -65,    91,   -43,    18,    97,    98,    46,   -17,    47,    25,
      47,   -21,    30,    26,     1,     2,     1,    19,    27,    71,
      72,    28,   107,    73,    74,    75,    76,    77,    78,    81,
      82,    71,    72,    30,    33,    40,    34,   106,    62,    69,
      36,    -9,    63,    70,    89,    86,    10,    87,    88,    92,
      95,    93,    96,   105,   104,   103,     0,    32,    94,    31,
       0,     0,     0,     0,    37
};

static const yytype_int8 yycheck[] =
{
      43,    11,    12,    17,    47,     6,    95,    96,     9,    10,
      11,    12,     0,    27,    24,    11,    26,   106,    24,    62,
      63,    35,    26,    24,    28,    26,    28,    70,     6,    30,
      31,     9,    10,    11,    12,    11,    12,    79,    80,    26,
      26,    83,    28,    12,    87,    88,    24,    27,    26,    11,
      26,    28,    30,    27,     7,     8,     7,     8,    25,    13,
      14,    29,   105,    17,    18,    19,    20,    21,    22,    15,
      16,    13,    14,    30,    24,    11,    28,     5,    26,    24,
      29,    28,    26,    23,    27,    24,     4,    28,    26,    79,
      27,    80,    27,    25,    27,    29,    -1,    27,    83,    26,
      -1,    -1,    -1,    -1,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    34,    35,    36,    37,    41,    42,     0,
      36,    11,    38,    39,    43,    24,    28,    26,    12,     8,
      41,    44,    45,    46,    40,    11,    27,    25,    29,    47,
      30,    48,    46,    24,    28,    49,    29,    37,    41,    50,
      11,     6,     9,    10,    11,    12,    24,    26,    31,    48,
      51,    52,    53,    54,    55,    56,    57,    59,    61,    63,
      65,    66,    26,    26,    24,    56,    58,    67,    56,    24,
      23,    13,    14,    17,    18,    19,    20,    21,    22,    60,
      62,    15,    16,    64,    56,    56,    24,    28,    26,    27,
      56,    57,    61,    63,    65,    27,    27,    56,    56,    68,
      69,    51,    51,    29,    27,    25,     5,    56,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    38,    37,    39,
      40,    37,    41,    41,    43,    42,    44,    44,    45,    45,
      46,    47,    46,    48,    49,    49,    50,    50,    51,    51,
      51,    51,    51,    52,    52,    53,    53,    54,    55,    55,
      56,    56,    57,    58,    57,    59,    59,    60,    60,    60,
      60,    60,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    65,    65,    67,    66,    68,    68,    69,
      69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     0,     4,     0,
       0,     8,     1,     1,     0,     7,     1,     1,     3,     1,
       2,     0,     5,     4,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     2,     1,     5,     7,     5,     2,     3,
       3,     1,     1,     0,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     0,     5,     1,     0,     3,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 42 "cm.y" /* yacc.c:1646  */
    { savedTree = (yyvsp[0]);}
#line 1356 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 45 "cm.y" /* yacc.c:1646  */
    {
												TreeNode *t = (yyvsp[-1]);
												if (t != NULL){
															while (t->sibling != NULL)
																	t = t->sibling;
															t->sibling = (yyvsp[0]);
															(yyval) = (yyvsp[-1]);
												}
												else {
															(yyval) = (yyvsp[0]);
												}
										}
#line 1373 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 58 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 1379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 62 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 1385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 64 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 1391 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 68 "cm.y" /* yacc.c:1646  */
    { savedName[now_level] = copyString(beforeToken); 
											savedLineNo[now_level++] = lineno;
										}
#line 1399 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 72 "cm.y" /* yacc.c:1646  */
    { 
												TreeNode *new = newExpNode(IdK);

												(yyval) = newDecNode(IntK);
												(yyval)->child[0] = (yyvsp[-3]);
												new->attr.name = savedName[--now_level];
												new->lineno = savedLineNo[now_level];
												(yyval)->child[1] = new;
										}
#line 1413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 82 "cm.y" /* yacc.c:1646  */
    {	savedName[now_level] = copyString(beforeToken); 
											savedLineNo[now_level++] = lineno;
										}
#line 1421 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 86 "cm.y" /* yacc.c:1646  */
    { savedSize = atoi(tokenString); }
#line 1427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 88 "cm.y" /* yacc.c:1646  */
    {
												TreeNode *new = newExpNode (IdK);
												TreeNode *new2 = newExpNode(ConstK);

												(yyval) = newDecNode(ArrayK);
												(yyval)->child[0] = (yyvsp[-7]);
												new->attr.name = savedName[--now_level];
												new->lineno = savedLineNo[now_level];
												new2->attr.val = savedSize;
												(yyval)->child[1] = new;
												(yyval)->child[2] = new2;
										}
#line 1444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 103 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(TypeK);
										  (yyval)->type = Integer;
									 	}
#line 1452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 107 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(TypeK);
											(yyval)->type = Void;
										}
#line 1460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 113 "cm.y" /* yacc.c:1646  */
    { 
													savedName[now_level] = copyString(beforeToken);
													savedLineNo[now_level++] = lineno;
										}
#line 1469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 118 "cm.y" /* yacc.c:1646  */
    {
													TreeNode * t;
													t = newExpNode(IdK);
													(yyval) = newDecNode(FunK);
													(yyval)->child[0] = (yyvsp[-6]);
													(yyval)->child[2] = (yyvsp[-2]);
													(yyval)->child[3] = (yyvsp[0]);
													t->attr.name = savedName[--now_level];
													t->lineno = savedLineNo[now_level];
													(yyval)->child[1] = t;
										}
#line 1485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 132 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 134 "cm.y" /* yacc.c:1646  */
    {
													(yyval) = newExpNode(ParamK);
													(yyval)->type = Void;
										}
#line 1500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 141 "cm.y" /* yacc.c:1646  */
    {
													TreeNode *t = (yyvsp[-2]);
													if (t != NULL){
																while (t->sibling !=NULL){
																			t = t->sibling;
																}
																t->sibling = (yyvsp[0]);
																(yyval) = (yyvsp[-2]);
													}
													else{
																(yyval) = (yyvsp[0]);
													}
										}
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 155 "cm.y" /* yacc.c:1646  */
    { 
													(yyval) = (yyvsp[0]);
										}
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 161 "cm.y" /* yacc.c:1646  */
    {
													TreeNode *new = newExpNode(IdK);
													(yyval) = newExpNode(ParamK);
													(yyval)->child[0] = (yyvsp[-1]);
													(yyval)->child[1] = new;
													new->attr.name = copyString(beforeToken);
										}
#line 1538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 169 "cm.y" /* yacc.c:1646  */
    {
													savedName[now_level] = copyString(beforeToken);
													savedLineNo[now_level++] = lineno;
										}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 174 "cm.y" /* yacc.c:1646  */
    {
													TreeNode *new = newExpNode(IdK);
													TreeNode *new2 = newExpNode(ConstK);
													(yyval) = newExpNode(ParamK);
													(yyval)->child[0] = (yyvsp[-4]);
													(yyval)->child[1] = new;
													(yyval)->child[2] = new2;
													new->attr.name = savedName[--now_level];
													new->lineno = savedLineNo[now_level];
													new2->attr.val = 0;
										}
#line 1563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 188 "cm.y" /* yacc.c:1646  */
    {
													(yyval) = newStmtNode(CompoundK);
													(yyval)->child[0] = (yyvsp[-2]);
													(yyval)->child[1] = (yyvsp[-1]);
										}
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 196 "cm.y" /* yacc.c:1646  */
    {
													TreeNode *t = (yyvsp[-1]);
													(yyvsp[0])->kind.dec = LocalK;
													if (t != NULL){
																while (t->sibling != NULL){
																			t = t->sibling;
																}
																t->sibling = (yyvsp[0]);
																(yyval) = (yyvsp[-1]);
													}
													else{
																(yyval) = (yyvsp[0]);
													}
											}
#line 1592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 211 "cm.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 215 "cm.y" /* yacc.c:1646  */
    { 
													TreeNode *t = (yyvsp[-1]);
													if (t != NULL){
																while (t->sibling != NULL){
																			t = t->sibling;
																}
																t->sibling = (yyvsp[0]);
																(yyval) = (yyvsp[-1]);
													}
													else{
																(yyval) = (yyvsp[0]);
													}
											}
#line 1616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 229 "cm.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 233 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 1628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 235 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 1634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 237 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 239 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 241 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 245 "cm.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[-1]); }
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 247 "cm.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 251 "cm.y" /* yacc.c:1646  */
    {
														(yyval) = newStmtNode(SelectionK);
														(yyval)->child[0] = (yyvsp[-2]);
														(yyval)->child[1] = (yyvsp[0]);
											}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 257 "cm.y" /* yacc.c:1646  */
    {
														TreeNode *new = newStmtNode(ElseK);
														(yyval) = newStmtNode(SelectionK);
														(yyval)->child[0] = (yyvsp[-4]);
														(yyval)->child[1] = (yyvsp[-2]);
														(yyval)->child[2] = new;
														new->child[0] = (yyvsp[0]);
											}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 268 "cm.y" /* yacc.c:1646  */
    {
														(yyval) = newStmtNode(IterationK);
														(yyval)->child[0] = (yyvsp[-2]);
														(yyval)->child[1] = (yyvsp[0]);
											}
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 276 "cm.y" /* yacc.c:1646  */
    {	(yyval) = newStmtNode(ReturnK); }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 278 "cm.y" /* yacc.c:1646  */
    {
														(yyval) = newStmtNode(ReturnK);
														(yyval)->child[0] = (yyvsp[-1]);
											}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 285 "cm.y" /* yacc.c:1646  */
    { 
														(yyval) = newExpNode(AssignK);
														(yyval)->child[0] = (yyvsp[-2]);
														(yyval)->child[1] = (yyvsp[0]);
														(yyval)->attr.op = ASSIGN;
											}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 292 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 296 "cm.y" /* yacc.c:1646  */
    { 
														(yyval) = newExpNode(IdK);
														(yyval)->attr.name = copyString(beforeToken);
											}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 301 "cm.y" /* yacc.c:1646  */
    {
														savedName[now_level] = copyString(beforeToken);
														savedLineNo[now_level++] = lineno;
											}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 306 "cm.y" /* yacc.c:1646  */
    {
														TreeNode *new = newExpNode(IdK);
														(yyval) = newExpNode(IdarrayK);
														new->attr.name = savedName[--now_level];
														new->lineno = savedLineNo[now_level];
														(yyval)->child[0] = new;
														(yyval)->child[1] = (yyvsp[-1]);
											}
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 317 "cm.y" /* yacc.c:1646  */
    {
														(yyval) = newExpNode(OpK);
														(yyval)->child[0] = (yyvsp[-2]);
														(yyval)->child[1] = (yyvsp[0]);
														(yyval)->attr.op = (yyvsp[-1])->attr.op;
											}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 324 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 328 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = LE; }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 330 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = LT; }
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 332 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = GT; }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 334 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = GE; }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 336 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = EQ; }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 338 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = NE; }
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 342 "cm.y" /* yacc.c:1646  */
    { 
														(yyval) = newExpNode(OpK);
														(yyval)->child[0] = (yyvsp[-2]);
														(yyval)->child[1] = (yyvsp[0]);
														(yyval)->attr.op = (yyvsp[-1])->attr.op;
											}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 349 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 353 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = PLUS; }
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 355 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = MINUS; }
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 359 "cm.y" /* yacc.c:1646  */
    { 
														(yyval) = newExpNode(OpK);
														(yyval)->child[0] = (yyvsp[-2]);
														(yyval)->child[1] = (yyvsp[0]);
														(yyval)->attr.op = (yyvsp[-1])->attr.op;
											}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 366 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 370 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = TIMES; }
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 372 "cm.y" /* yacc.c:1646  */
    { (yyval) = newExpNode(OpK); (yyval)->attr.op = OVER; }
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 376 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 378 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 380 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 382 "cm.y" /* yacc.c:1646  */
    { 
														(yyval) = newExpNode(ConstK);
														(yyval)->attr.val = atoi(tokenString);
											}
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 389 "cm.y" /* yacc.c:1646  */
    {
														savedName[now_level] = copyString(beforeToken);
														savedLineNo[now_level++] = lineno;
											}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 394 "cm.y" /* yacc.c:1646  */
    {
														(yyval) = newExpNode(CallK);
														(yyval)->attr.name = savedName[--now_level];
														(yyval)->lineno = savedLineNo[now_level];
														(yyval)->child[0] = (yyvsp[-1]);
											}
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 403 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 405 "cm.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 409 "cm.y" /* yacc.c:1646  */
    {
														TreeNode *t = (yyvsp[-2]);
														if (t != NULL){
																	while(t->sibling != NULL){
																				t = t->sibling;
																	}
																	t->sibling = (yyvsp[0]);
																	(yyval) = (yyvsp[-2]);
														}
														else{
																	(yyval) = (yyvsp[0]);
														}
											}
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 423 "cm.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1954 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1958 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 427 "cm.y" /* yacc.c:1906  */


int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
	fprintf(listing, "before token : %s\n", beforeToken);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{
			TokenType token = getToken();

			if (token == ERROR){
						fprintf(listing,"Lexical anaylze error at line %d: %s", lineno, tokenString);
						Error = TRUE;
						return 0;
			}

			return token; 
}

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

