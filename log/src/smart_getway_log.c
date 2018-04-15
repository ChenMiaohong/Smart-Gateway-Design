#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/stat.h>
#include <dirent.h>
#include <dirent.h>
#include <unistd.h>
#include "zlog.h"
#include "smart_getway_log.h"

int Init_LogDir()
{

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
	struct stat st = {0};
	char log_dir[1024] = {0};
	strcpy(log_dir, "/var");
	strcat(log_dir, "/smart_getway");

	if (stat(log_dir, &st) == -1)
	mkdir(log_dir, 0777);
	//EmptyDir(log_dir);
    if ((dp = opendir(log_dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", log_dir);
        return -1;
    }
    chdir(log_dir);
    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if (S_ISREG(statbuf.st_mode)) {
            remove(entry->d_name);
        }
    }
    return 0;
}
