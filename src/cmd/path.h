#ifndef PATH_H
#define PATH_H

#include "../noeud.h"

// les commandes sont explicites

bool isCurrent(char *path);
bool isLevelUp(char *path);
bool isRelative(char *path);
bool isReturnToRoot(char *path);
bool isValidPath(char *path, noeud *dir);
char *extract_last_word_from_path(char *path);
char *exclude_last_word_from_path(char *path);
bool is_one_word(char *path);
bool isSubPath(char *path, char *subPath);

#endif