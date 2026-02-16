/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./parser/parser.y"

#include <cstdio>
#include "../ast/ast.hpp"
#include "../lexer/lexer.hpp"

SymbolTable st;
llvmSymbolTable new_st;
llvmFunctionTable new_ft;
std::string tabcount;
bool debug = 0;
bool optimization_enabled = false;
std::string program_name = "main";



#line 86 "./parser/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_PARSER_HPP_INCLUDED
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
    T_byte = 258,
    T_int = 259,
    T_if = 260,
    T_else = 261,
    T_true = 262,
    T_false = 263,
    T_proc = 264,
    T_reference = 265,
    T_return = 266,
    T_while = 267,
    T_id = 268,
    T_const = 269,
    T_char = 270,
    T_string = 271,
    T_equal = 272,
    T_notEq = 273,
    T_lessEq = 274,
    T_moreEq = 275
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 47 "./parser/parser.y"

    LocalDef *lcl_def;
    DefList *local_def_list;
    Fparlist *fpar_list;
    Fpar *fpar_def;
    Stmt *stmt;
    CompoundStmt *cmpdstmt;
    Func_call *func_call;
    ExprList *expr_list;
    Expr *expr;
    Lvalue *lvalue;
    Cond *cond ;

    RType rtype;
    std::string *var;
    int num;
    char character;
    char op;

#line 179 "./parser/parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_PARSER_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

#define YYUNDEFTOK  2
#define YYMAXUTOK   275


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,     2,     2,    29,    22,     2,
      31,    32,    27,    25,    34,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    37,
      24,    38,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,    21,    40,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    84,    84,    88,    89,    93,    94,    98,    99,   105,
     106,   110,   111,   115,   116,   120,   121,   125,   126,   131,
     132,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     149,   153,   154,   158,   159,   163,   164,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   183,
     184,   185,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"byte\"", "\"int\"", "\"if\"",
  "\"else\"", "\"true\"", "\"false\"", "\"proc\"", "\"reference\"",
  "\"return\"", "\"while\"", "T_id", "T_const", "T_char", "T_string",
  "\"==\"", "\"!=\"", "\"<=\"", "\">=\"", "'|'", "'&'", "'>'", "'<'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'('", "')'", "':'", "','",
  "'['", "']'", "';'", "'='", "'{'", "'}'", "$accept", "program",
  "func_def", "local_def_list", "fpar_list", "fpar_def", "data_type",
  "type", "r_type", "local_def", "var_def", "stmt", "compound_stmt",
  "compound_stmt_helper", "func_call", "expr_list", "expr", "l_value",
  "cond", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   124,    38,    62,    60,    43,    45,    42,    47,    37,
      33,    40,    41,    58,    44,    91,    93,    59,    61,   123,
     125
};
# endif

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -8,   -16,    18,   -94,     4,   -94,   -14,     8,    51,   -94,
      71,    83,    20,    12,   -94,   -94,   105,     0,   -94,   -94,
     -94,   -94,    83,   -94,   -94,    22,    -6,   -94,   -94,   151,
     -94,   -94,   -94,   -94,   -94,    -6,   105,    15,   -94,   164,
      37,   100,    53,   -23,   -94,   -94,   -94,   -94,   -94,    56,
      89,    90,   -94,    81,   -94,   -94,   108,   108,   108,   -94,
     -94,    73,   -94,    81,   104,   108,   -94,   108,    92,   -94,
     -94,    81,    81,   139,   -18,    21,    21,   161,   108,   108,
     108,   108,   108,   -94,    35,   -94,   168,   169,   149,   144,
      95,   -94,   123,    48,   108,   108,   108,   108,   108,   108,
      81,    81,    66,   -94,    21,    21,   -94,   -94,   -94,    66,
     -94,   108,   -94,   -94,   -94,   -94,   169,   169,   169,   169,
     169,   169,   116,   -94,   138,   -94,   169,    66,   -94
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     0,     0,     7,
       0,     0,     0,     0,    12,    11,     0,    13,    10,    16,
      15,     5,     0,     8,     9,     0,     0,     5,    14,     0,
      31,    17,     6,    18,     4,     0,     0,     0,     3,     0,
       0,     0,     0,    49,    51,    21,    30,    32,    23,     0,
       0,     0,    19,     0,    37,    38,     0,     0,     0,    28,
      41,     0,    39,     0,     0,     0,    24,     0,     0,    52,
      53,     0,     0,     0,     0,    42,    43,     0,     0,     0,
       0,     0,     0,    29,     0,    33,     0,    35,     0,     0,
       0,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,    44,    45,    46,    47,    48,     0,
      34,     0,    50,    22,    20,    54,    56,    57,    60,    61,
      59,    58,    63,    62,    25,    27,    36,     0,    26
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   145,   126,   -94,   141,     2,   163,   158,   -94,
     -94,   -93,    16,   -94,   -37,   -94,   -35,   -36,   -61
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    31,    26,     8,     9,    17,    18,    21,    32,
      33,    47,    48,    37,    60,    86,    73,    62,    74
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    50,    84,   100,   101,     1,    61,    29,    64,   124,
      91,    93,    65,    20,   102,     4,   125,     6,     5,    10,
      40,    75,    76,    77,    20,     6,    41,    42,    43,    87,
      88,    44,    89,    30,   128,    25,     7,    92,    39,   122,
     123,    11,    34,   104,   105,   106,   107,   108,    80,    81,
      82,    38,    45,    22,    30,    46,   100,   101,    28,   116,
     117,   118,   119,   120,   121,    49,    50,   109,    53,   100,
     101,    40,    49,    50,    14,    15,   126,    41,    42,    43,
     115,    16,    44,    12,    63,    13,    14,    15,    69,    70,
      49,    50,    19,    66,    43,    54,    55,    44,    78,    79,
      80,    81,    82,    45,    68,    30,    56,    57,    14,    15,
      83,    71,    72,    43,    54,    55,    44,    43,    54,    55,
      44,    43,    54,    55,    44,    56,    57,    67,    90,    56,
      57,    58,   114,    56,    57,    58,    85,    59,   101,    58,
      94,    95,    96,    97,   127,     3,    98,    99,    78,    79,
      80,    81,    82,    35,    23,   103,    94,    95,    96,    97,
       0,     0,    98,    99,    78,    79,    80,    81,    82,    78,
      79,    80,    81,    82,    78,    79,    80,    81,    82,    24,
      27,   113,     4,     0,    36,   112,    78,    79,    80,    81,
      82,     0,     0,   103,    78,    79,    80,    81,    82,    51,
     110,    52,   111
};

static const yytype_int8 yycheck[] =
{
      37,    37,    63,    21,    22,    13,    41,    13,    31,   102,
      71,    72,    35,    11,    32,    31,   109,    13,     0,    33,
       5,    56,    57,    58,    22,    13,    11,    12,    13,    64,
      65,    16,    67,    39,   127,    35,    32,    72,    36,   100,
     101,    33,    26,    78,    79,    80,    81,    82,    27,    28,
      29,    35,    37,    33,    39,    40,    21,    22,    36,    94,
      95,    96,    97,    98,    99,   102,   102,    32,    31,    21,
      22,     5,   109,   109,     3,     4,   111,    11,    12,    13,
      32,    10,    16,    32,    31,    34,     3,     4,     7,     8,
     127,   127,     9,    37,    13,    14,    15,    16,    25,    26,
      27,    28,    29,    37,    14,    39,    25,    26,     3,     4,
      37,    30,    31,    13,    14,    15,    16,    13,    14,    15,
      16,    13,    14,    15,    16,    25,    26,    38,    36,    25,
      26,    31,    37,    25,    26,    31,    32,    37,    22,    31,
      17,    18,    19,    20,     6,     0,    23,    24,    25,    26,
      27,    28,    29,    27,    13,    32,    17,    18,    19,    20,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    25,
      26,    27,    28,    29,    25,    26,    27,    28,    29,    16,
      22,    37,    31,    -1,    33,    36,    25,    26,    27,    28,
      29,    -1,    -1,    32,    25,    26,    27,    28,    29,    35,
      32,    37,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    13,    42,    43,    31,     0,    13,    32,    45,    46,
      33,    33,    32,    34,     3,     4,    10,    47,    48,     9,
      47,    49,    33,    46,    48,    35,    44,    49,    36,    13,
      39,    43,    50,    51,    53,    44,    33,    54,    53,    47,
       5,    11,    12,    13,    16,    37,    40,    52,    53,    55,
      58,    35,    37,    31,    14,    15,    25,    26,    31,    37,
      55,    57,    58,    31,    31,    35,    37,    38,    14,     7,
       8,    30,    31,    57,    59,    57,    57,    57,    25,    26,
      27,    28,    29,    37,    59,    32,    56,    57,    57,    57,
      36,    59,    57,    59,    17,    18,    19,    20,    23,    24,
      21,    22,    32,    32,    57,    57,    57,    57,    57,    32,
      32,    34,    36,    37,    37,    32,    57,    57,    57,    57,
      57,    57,    59,    59,    52,    52,    57,     6,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    47,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    58,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     8,     7,     0,     2,     1,     3,     4,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     4,
       7,     1,     4,     1,     2,     5,     7,     5,     2,     3,
       3,     0,     2,     3,     4,     1,     3,     1,     1,     1,
       3,     1,     2,     2,     3,     3,     3,     3,     3,     1,
       4,     1,     1,     1,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 84 "./parser/parser.y"
                {(yyvsp[0].lcl_def)->sem(); program_name = (yyvsp[0].lcl_def)->get_name() ;(yyvsp[0].lcl_def)->llvm_igen(optimization_enabled); }
#line 1451 "./parser/parser.cpp"
    break;

  case 3:
#line 88 "./parser/parser.y"
                                                                    { (yyval.lcl_def) = new Func_def((yyvsp[-7].var),(yyvsp[-5].fpar_list),(yyvsp[-2].rtype),(yyvsp[-1].local_def_list),(yyvsp[0].cmpdstmt)); }
#line 1457 "./parser/parser.cpp"
    break;

  case 4:
#line 89 "./parser/parser.y"
                                                         { (yyval.lcl_def) = new Func_def((yyvsp[-6].var),(yyvsp[-2].rtype),(yyvsp[-1].local_def_list),(yyvsp[0].cmpdstmt)); }
#line 1463 "./parser/parser.cpp"
    break;

  case 5:
#line 93 "./parser/parser.y"
                                { (yyval.local_def_list) = new DefList(); }
#line 1469 "./parser/parser.cpp"
    break;

  case 6:
#line 94 "./parser/parser.y"
                                { (yyvsp[-1].local_def_list)->append_def((yyvsp[0].lcl_def)); (yyval.local_def_list) = (yyvsp[-1].local_def_list); }
#line 1475 "./parser/parser.cpp"
    break;

  case 7:
#line 98 "./parser/parser.y"
                            { (yyval.fpar_list) = new Fparlist(); (yyval.fpar_list)->append_fpar((yyvsp[0].fpar_def)); }
#line 1481 "./parser/parser.cpp"
    break;

  case 8:
#line 99 "./parser/parser.y"
                            { (yyvsp[-2].fpar_list)->append_fpar((yyvsp[0].fpar_def)); (yyval.fpar_list) = (yyvsp[-2].fpar_list); }
#line 1487 "./parser/parser.cpp"
    break;

  case 9:
#line 105 "./parser/parser.y"
                                { (yyval.fpar_def) = new Fpar((yyvsp[-3].var),true,(yyvsp[0].rtype)); }
#line 1493 "./parser/parser.cpp"
    break;

  case 10:
#line 106 "./parser/parser.y"
                                { (yyval.fpar_def) = new Fpar((yyvsp[-2].var),false,(yyvsp[0].rtype)); }
#line 1499 "./parser/parser.cpp"
    break;

  case 11:
#line 110 "./parser/parser.y"
            { (yyval.rtype) = TYPE_int; }
#line 1505 "./parser/parser.cpp"
    break;

  case 12:
#line 111 "./parser/parser.y"
            { (yyval.rtype) = TYPE_char; }
#line 1511 "./parser/parser.cpp"
    break;

  case 13:
#line 115 "./parser/parser.y"
                        { (yyval.rtype) = (yyvsp[0].rtype); }
#line 1517 "./parser/parser.cpp"
    break;

  case 14:
#line 116 "./parser/parser.y"
                        { if ((yyvsp[-2].rtype) == TYPE_int) (yyval.rtype) = TYPE_int_array; else (yyval.rtype) = TYPE_char_array; }
#line 1523 "./parser/parser.cpp"
    break;

  case 15:
#line 120 "./parser/parser.y"
                { (yyval.rtype) = (yyvsp[0].rtype); }
#line 1529 "./parser/parser.cpp"
    break;

  case 16:
#line 121 "./parser/parser.y"
                { (yyval.rtype) = TYPE_void; }
#line 1535 "./parser/parser.cpp"
    break;

  case 17:
#line 125 "./parser/parser.y"
                { (yyval.lcl_def) = (yyvsp[0].lcl_def); }
#line 1541 "./parser/parser.cpp"
    break;

  case 18:
#line 126 "./parser/parser.y"
                { (yyval.lcl_def) = (yyvsp[0].lcl_def); }
#line 1547 "./parser/parser.cpp"
    break;

  case 19:
#line 131 "./parser/parser.y"
                                            { (yyval.lcl_def) = new Var_def((yyvsp[-3].var),(yyvsp[-1].rtype)); }
#line 1553 "./parser/parser.cpp"
    break;

  case 20:
#line 132 "./parser/parser.y"
                                            { (yyval.lcl_def) = new Var_def((yyvsp[-6].var),(yyvsp[-4].rtype),(yyvsp[-2].num)); }
#line 1559 "./parser/parser.cpp"
    break;

  case 21:
#line 137 "./parser/parser.y"
                                        { (yyval.stmt) = new NoOp(); }
#line 1565 "./parser/parser.cpp"
    break;

  case 22:
#line 138 "./parser/parser.y"
                                        { (yyval.stmt) = new Let((yyvsp[-3].lvalue),(yyvsp[-1].expr)); }
#line 1571 "./parser/parser.cpp"
    break;

  case 23:
#line 139 "./parser/parser.y"
                                        { (yyval.stmt) = (yyvsp[0].cmpdstmt); }
#line 1577 "./parser/parser.cpp"
    break;

  case 24:
#line 140 "./parser/parser.y"
                                        { (yyval.stmt) = (yyvsp[-1].func_call); }
#line 1583 "./parser/parser.cpp"
    break;

  case 25:
#line 141 "./parser/parser.y"
                                        { (yyval.stmt) = new If((yyvsp[-2].cond),(yyvsp[0].stmt)); }
#line 1589 "./parser/parser.cpp"
    break;

  case 26:
#line 142 "./parser/parser.y"
                                        { (yyval.stmt) = new If((yyvsp[-4].cond),(yyvsp[-2].stmt),(yyvsp[0].stmt)); }
#line 1595 "./parser/parser.cpp"
    break;

  case 27:
#line 143 "./parser/parser.y"
                                        { (yyval.stmt) = new While((yyvsp[-2].cond),(yyvsp[0].stmt)); }
#line 1601 "./parser/parser.cpp"
    break;

  case 28:
#line 144 "./parser/parser.y"
                                        { (yyval.stmt) = new Return(); }
#line 1607 "./parser/parser.cpp"
    break;

  case 29:
#line 145 "./parser/parser.y"
                                        { (yyval.stmt) = new Return((yyvsp[-1].expr)); }
#line 1613 "./parser/parser.cpp"
    break;

  case 30:
#line 149 "./parser/parser.y"
                                        { (yyval.cmpdstmt) = (yyvsp[-1].cmpdstmt); }
#line 1619 "./parser/parser.cpp"
    break;

  case 31:
#line 153 "./parser/parser.y"
                                        { (yyval.cmpdstmt) = new CompoundStmt(); }
#line 1625 "./parser/parser.cpp"
    break;

  case 32:
#line 154 "./parser/parser.y"
                                        { (yyvsp[-1].cmpdstmt)->append_stmt((yyvsp[0].stmt)); (yyval.cmpdstmt) = (yyvsp[-1].cmpdstmt); }
#line 1631 "./parser/parser.cpp"
    break;

  case 33:
#line 158 "./parser/parser.y"
                            { (yyval.func_call) = new Func_call((yyvsp[-2].var)); }
#line 1637 "./parser/parser.cpp"
    break;

  case 34:
#line 159 "./parser/parser.y"
                            { (yyval.func_call) = new Func_call((yyvsp[-3].var),(yyvsp[-1].expr_list)); }
#line 1643 "./parser/parser.cpp"
    break;

  case 35:
#line 163 "./parser/parser.y"
                        { (yyval.expr_list) = new ExprList(); (yyval.expr_list)->append_expr((yyvsp[0].expr)); }
#line 1649 "./parser/parser.cpp"
    break;

  case 36:
#line 164 "./parser/parser.y"
                        { (yyvsp[-2].expr_list)->append_expr((yyvsp[0].expr)); (yyval.expr_list) = (yyvsp[-2].expr_list); }
#line 1655 "./parser/parser.cpp"
    break;

  case 37:
#line 168 "./parser/parser.y"
                    { (yyval.expr) = new Const((yyvsp[0].num)); }
#line 1661 "./parser/parser.cpp"
    break;

  case 38:
#line 169 "./parser/parser.y"
                    { (yyval.expr) = new Character((yyvsp[0].character)); }
#line 1667 "./parser/parser.cpp"
    break;

  case 39:
#line 170 "./parser/parser.y"
                    { (yyval.expr) = (yyvsp[0].lvalue); }
#line 1673 "./parser/parser.cpp"
    break;

  case 40:
#line 171 "./parser/parser.y"
                    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1679 "./parser/parser.cpp"
    break;

  case 41:
#line 172 "./parser/parser.y"
                    { (yyval.expr) = (yyvsp[0].func_call); }
#line 1685 "./parser/parser.cpp"
    break;

  case 42:
#line 173 "./parser/parser.y"
                    { (yyval.expr) = new UnOp((yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1691 "./parser/parser.cpp"
    break;

  case 43:
#line 174 "./parser/parser.y"
                    { (yyval.expr) = new UnOp((yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1697 "./parser/parser.cpp"
    break;

  case 44:
#line 175 "./parser/parser.y"
                    { (yyval.expr) = new BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1703 "./parser/parser.cpp"
    break;

  case 45:
#line 176 "./parser/parser.y"
                    { (yyval.expr) = new BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1709 "./parser/parser.cpp"
    break;

  case 46:
#line 177 "./parser/parser.y"
                    { (yyval.expr) = new BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1715 "./parser/parser.cpp"
    break;

  case 47:
#line 178 "./parser/parser.y"
                    { (yyval.expr) = new BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1721 "./parser/parser.cpp"
    break;

  case 48:
#line 179 "./parser/parser.y"
                    { (yyval.expr) = new BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1727 "./parser/parser.cpp"
    break;

  case 49:
#line 183 "./parser/parser.y"
                        { (yyval.lvalue) = new Lvalue_id((yyvsp[0].var)); }
#line 1733 "./parser/parser.cpp"
    break;

  case 50:
#line 184 "./parser/parser.y"
                        { (yyval.lvalue) = new Lvalue_id((yyvsp[-3].var),(yyvsp[-1].expr)); }
#line 1739 "./parser/parser.cpp"
    break;

  case 51:
#line 185 "./parser/parser.y"
                        { (yyval.lvalue) = new Lvalue_string((yyvsp[0].var)); }
#line 1745 "./parser/parser.cpp"
    break;

  case 52:
#line 189 "./parser/parser.y"
                    { (yyval.cond) = new ConstBool(1); }
#line 1751 "./parser/parser.cpp"
    break;

  case 53:
#line 190 "./parser/parser.y"
                    { (yyval.cond) = new ConstBool(0); }
#line 1757 "./parser/parser.cpp"
    break;

  case 54:
#line 191 "./parser/parser.y"
                    { (yyval.cond) = (yyvsp[-1].cond); }
#line 1763 "./parser/parser.cpp"
    break;

  case 55:
#line 192 "./parser/parser.y"
                    { (yyval.cond) = new C_UnOp((yyvsp[-1].op), (yyvsp[0].cond)); }
#line 1769 "./parser/parser.cpp"
    break;

  case 56:
#line 193 "./parser/parser.y"
                    { (yyval.cond) = new C_BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1775 "./parser/parser.cpp"
    break;

  case 57:
#line 194 "./parser/parser.y"
                    { (yyval.cond) = new C_BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1781 "./parser/parser.cpp"
    break;

  case 58:
#line 195 "./parser/parser.y"
                    { (yyval.cond) = new C_BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1787 "./parser/parser.cpp"
    break;

  case 59:
#line 196 "./parser/parser.y"
                    { (yyval.cond) = new C_BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1793 "./parser/parser.cpp"
    break;

  case 60:
#line 197 "./parser/parser.y"
                    { (yyval.cond) = new C_BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1799 "./parser/parser.cpp"
    break;

  case 61:
#line 198 "./parser/parser.y"
                    { (yyval.cond) = new C_BiOp((yyvsp[-2].expr),(yyvsp[-1].op),(yyvsp[0].expr)); }
#line 1805 "./parser/parser.cpp"
    break;

  case 62:
#line 199 "./parser/parser.y"
                    { (yyval.cond) = new C_BiOp((yyvsp[-2].cond),(yyvsp[-1].op),(yyvsp[0].cond)); }
#line 1811 "./parser/parser.cpp"
    break;

  case 63:
#line 200 "./parser/parser.y"
                    { (yyval.cond) = new C_BiOp((yyvsp[-2].cond),(yyvsp[-1].op),(yyvsp[0].cond)); }
#line 1817 "./parser/parser.cpp"
    break;


#line 1821 "./parser/parser.cpp"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 204 "./parser/parser.y"


int main(int argc, char* argv[]) { 
    for (int i =1; i<argc; ++i){
        std::string arg = argv[i];
        if (arg == "-O") {
            optimization_enabled = true;
        }
    } 
    int result = yyparse();
    return result;
}
