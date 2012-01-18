#ifndef ENV_H
#define ENV_H

extern char **environ;

/* 
** returns:    -1 if s is null 
** returns:    -1 if s isn't found.
** returns: >= 0  if s is found, make v points to it
*/

extern int env_get(const char *s, char **v);

#endif
