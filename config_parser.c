#include<string.h>
#include<stdio.h>
#include <sys/types.h>
#include <regex.h>

/* like an example we can use PCRE - Perl-compatible regular expressions lib pcre.h*/

/*  config_parse() is
 * config.ini file format
 *
 *  [full]
 *  [files]
 *  file=
 *  file=
 *  file=mysql-incr-[1][0-4].tar.gz
 *
 *  [dirs]
 *  dir=
 *  [incremental]
 *  [files]
 *  file=
 *  [dirs]
 *  dir=
 *
 * [common]
 *  days=14
 *  number=3
 * //comment
 *
 */


int config_parser(char**, FILE*);
/* создать ассоциативный массив? */
/*int config_parser(char **array, FILE *f)
{

  array

  rewind(f);
  while(fgets)


  return 0;
}

typedef struct {
  char **array;
  unsigned int size ;


}__filenames;
typedef __filenames* filenames;
filenames init_filenames();
add_into_filenames();
remove_from_filenames();
void close_filenames(filenames);

*/
