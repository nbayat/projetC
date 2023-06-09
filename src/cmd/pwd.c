#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../noeud.h"
#include "../debug.h"

char *pwd(noeud *n)
{
    if (DEBUG)
    {
        printf("! DEBUG ! -> pwd");
        if (strcmp(n->nom, "") != 0)
        {
            printf(" depuis %s\n", n->nom);
        }
        else
        {
            printf(" depuis root\n");
        }
    }

    char *path = malloc(1000);
    while (n != n->racine)
    {
        char *tmp = malloc(100);
        strcpy(tmp, path);
        strcpy(path, "/");
        strcat(path, n->nom);
        strcat(path, tmp);
        free(tmp);
        if (n->pere != NULL)
        {
            n = n->pere;
        }
    }
    return path;
}