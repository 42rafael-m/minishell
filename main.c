#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	(void)argc;
	dir_stream = NULL;
	dir_stream = opendir(argv[1]);
	if (!dir_stream)
    {
        perror("opendir");
        return (1);
    }
	dir = readdir(dir_stream);
	if (dir)
		printf("dir->d_name = %s\n", dir->d_name);
	while (dir)
	{
		dir = readdir(dir_stream);
		if (dir)
			printf("dir->d_name = %s\n", dir->d_name);
	}
	if (dir_stream)
		closedir(dir_stream);
}