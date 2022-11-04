#include <stdio.h>
#include <dirent.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	DIR	*dir;
	struct dirent *dentry;
	printf("Nb arg = %d\n", argc);
	dir = opendir(argv[1]);
	if (dir != NULL)
	{
		dentry = readdir(dir);
		while (dentry)
		{
			if ((strcmp(dentry->d_name, ".") == 0 || strcmp(dentry->d_name, "..") == 0 || (*dentry->d_name) == '.'))
			{
			}
			else 
			{
				printf("%s",dentry->d_name);
				printf("\n");
			}
			dentry = readdir(dir);
		}
	
	}
	closedir(dir);
}
