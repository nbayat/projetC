#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../noeud.h"
#include "path.h"

noeud *cd(char *path, noeud *dir)
{
    printf("path: %s\n", path);
    if (dir->fils == NULL && isRelative(path) && !isReturnToRoot(path) && !isCurrent(path) && !isLevelUp(path))
    {
        printf("This directory is empty\n");
        return dir;
    }
    if (isReturnToRoot(path))
    {
        dir = dir->racine;
        return dir;
    }
    if (isCurrent(path))
    {
        printf("You are already here\n");
        return dir;
    }
    if (isLevelUp(path))
    {
        if (dir->pere == NULL)
        {
            printf("You are already at the root\n");
            return dir;
        }
        dir = dir->pere;
        return dir;
    }
    // split path into tokens
    if (isRelative(path))
    {
        char *newPath = malloc(strlen(path) + 1);
        strcpy(newPath, path);
        char *token = strtok(newPath, "/");
        while (token != NULL)
        {
            if (isRelative(token))
            {
                dir = find_child(dir, token);
                if (dir == NULL)
                {
                    printf("No such file or directory\n");
                    return dir;
                }
                else if (!dir->est_dossier)
                {
                    printf("This is not a directory\n");
                    return NULL;
                }
            }
            token = strtok(NULL, "/");
        }
    }
    else if (!isRelative(path))
    {
        char *newPath = malloc(strlen(path) + 1);
        newPath = newPath + 1;
        strcpy(newPath, path);
        dir = dir->racine;
        char *token = strtok(newPath, "/");
        while (token != NULL)
        {
            if (isRelative(token))
            {
                dir = find_child(dir, token);
                if (dir == NULL)
                {
                    printf("No such file or directory\n");
                    return dir;
                }
            }
            token = strtok(NULL, "/");
        }
    }
    return dir;
}
