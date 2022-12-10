#include "day7.h"
#include <string.h>

/**
 * Allocates and initializes a DeviceDirectory struct.
 */
struct DeviceDirectory *init_device_directory(char name[], struct DeviceDirectory *parent)
{
	struct DeviceDirectory *d = malloc(sizeof(struct DeviceDirectory));
	d->children = NULL;
	d->files = NULL;
	d->peer = NULL;
	d->parent = parent;
	d->name = strdup(name);
	return d;
}

/**
 * Allocates and initializes a DeviceFile struct.
 */
struct DeviceFile *init_device_file(char name[], size_t size)
{
	struct DeviceFile *f = malloc(sizeof(struct DeviceFile));
	f->peer = NULL;
	f->size = size;
	f->name = strdup(name);
	return f;
}

/**
 * Calculate the total size of the given directory, including its descendants.
 */
size_t device_dirsize(struct DeviceDirectory *dir, bool with_peers)
{
	size_t size = 0;

	struct DeviceFile *f = dir->files;
	while (f)
	{
		size += f->size;
		f = f->peer;
	}

	if (dir->children != NULL)
		size += device_dirsize(dir->children, true);

	if (with_peers && dir->peer != NULL)
		size += device_dirsize(dir->peer, true);

	return size;
}

/**
 * Recursively finds directories under 100_000 bytes and returns the sum of all
 * their sizes.
 */
size_t device_sum_small_dirs(struct DeviceDirectory *root)
{
	size_t size = 0;

	size_t my_size = device_dirsize(root, false);
	if (my_size <= 100000)
		size += my_size;

	if (root->peer != NULL)
		size += device_sum_small_dirs(root->peer);

	if (root->children != NULL)
		size += device_sum_small_dirs(root->children);

	return size;
}

char *_strip_newline(char *s)
{
	for (size_t i = 0; i < strlen(s); i++)
		if (s[i] == '\n')
			s[i] = '\0';
	return s;
}

/**
 * Parse a command line string into a populated `DeviceCommand` struct.
 */
struct DeviceCommand *device_parse_cmd(char *src)
{
	struct DeviceCommand *cmd = malloc(sizeof(struct DeviceCommand));
	cmd->executable = NULL;
	cmd->argument = NULL;

	char *cursor, *line, *start;
	start = line = strdup(src);

	strsep(&line, " "); /* Skip the starting '$' */
	cursor = strsep(&line, " ");

	cmd->executable = _strip_newline(strdup(cursor));
	if ((cursor = strsep(&line, " ")))
		cmd->argument = _strip_newline(strdup(cursor));

	free(start);
	return cmd;
}

/**
 * Frees both the DeviceCommand struct and its string pointers.
 */
void device_free_cmd(struct DeviceCommand *cmd)
{
	if (cmd->argument != NULL)
		free(cmd->argument);
	free(cmd->executable);
	free(cmd);
}

/**
 * Recursively frees all child directory and file structs for the given root.
 */
void device_free_fs(struct DeviceDirectory *root)
{
	if (root->files != NULL)
	{
		struct DeviceFile *tmp = NULL;
		struct DeviceFile *f = root->files;
		while (f)
		{
			tmp = f->peer;
			free(f->name);
			free(f);
			f = tmp;
		}
	}

	if (root->peer != NULL)
		device_free_fs(root->peer);

	if (root->children != NULL)
		device_free_fs(root->children);

	if (root->name != NULL)
		free(root->name);

	free(root);
}

/**
 * Sets the pwd pointer to a pointer to the new directory, dest, if it is found
 * as a peer of the current directory's children.
 */
void device_execute_cd(char *dest, struct DeviceDirectory **pwd)
{
	if (strcmp(dest, "..") == 0)
	{
		*pwd = (*pwd)->parent;
		return;
	}

	struct DeviceDirectory *d = (*pwd)->children;
	while (d != NULL)
	{
		if (strcmp(d->name, dest) == 0)
		{
			*pwd = d;
			break;
		}
		else
		{
			d = d->peer;
		}
	}
}

/**
 * Checks if a directory already exists under the given parent.
 */
bool device_dir_exists(char *dest, struct DeviceDirectory *pwd)
{
	struct DeviceDirectory *check = pwd;
	device_execute_cd(dest, &check);
	return check != pwd;
}

/**
 * Checks if a file already exists under the given parent.
 */
bool device_file_exists(char *dest, struct DeviceDirectory *pwd)
{
	struct DeviceFile *f = pwd->files;
	while (f)
	{
		if (strcmp(f->name, dest) == 0)
			return true;
		f = f->peer;
	}
	return false;
}

/**
 * Take the given command and takes action based on it.
 */
void execute_command(struct DeviceCommand *cmd, struct DeviceDirectory **pwd)
{
	if (strcmp(cmd->executable, "cd") == 0)
	{
		device_execute_cd(cmd->argument, pwd);
	}
}

/**
 * Parse a directory line from the output of `ls` into a `DeviceDirectory` and
 * attach it to the `pwd`, its parent.
 */
void device_discover_directory(char *src, struct DeviceDirectory *parent)
{
	char *cursor, *line, *start;
	start = line = strdup(src);

	strsep(&line, " "); /* Skip the starting 'dir' token */
	cursor = strsep(&line, " ");

	char *name = _strip_newline(cursor);
	if (!device_dir_exists(name, parent))
	{
		struct DeviceDirectory *dir = init_device_directory(name, parent);
		if (parent->children != NULL)
			dir->peer = parent->children;
		parent->children = dir;
	}

	free(start);
}

/**
 * Parse a line of output from `ls` as a `DirectoryFile` and attach it to the
 * current directory node.
 */
void device_discover_file(char *src, struct DeviceDirectory *parent)
{
	char *cursor, *line, *start;
	start = line = strdup(src);

	cursor = strsep(&line, " ");
	size_t size = atoi(cursor);
	cursor = strsep(&line, " ");

	char *name = _strip_newline(cursor);
	if (!device_file_exists(name, parent))
	{
		struct DeviceFile *f = init_device_file(name, size);
		if (parent->files != NULL)
			f->peer = parent->files;
		parent->files = f;
	}

	free(start);
}

/**
 * Parse an input file line-by-line and build the filesystem hierarchy.
 */
void device_crawl(FILE *fp, struct DeviceDirectory *root)
{
	struct DeviceDirectory *pwd = root;
	struct DeviceCommand *cmd = NULL;
	char *line_buf = NULL;
	size_t line_bufsize = 0;
	while (getline(&line_buf, &line_bufsize, fp) != -1)
	{
		if (line_buf[0] == '$')
		{
			if (cmd != NULL)
				device_free_cmd(cmd);
			cmd = device_parse_cmd(line_buf);
			execute_command(cmd, &pwd);
			continue;
		}
		if (strcmp(cmd->executable, "ls") == 0)
		{
			if (line_buf[0] == 'd')
				device_discover_directory(line_buf, pwd);
			else
				device_discover_file(line_buf, pwd);
		}
	}
	device_free_cmd(cmd);
	free(line_buf);
}

void _device_debug_print_tree(struct DeviceDirectory *root, unsigned int indent)
{
	struct DeviceDirectory *d = root;
	while (d)
	{
		for (unsigned int x = 0; x < indent; x++)
			printf("\t");
		printf("%s/\n", d->name);

		if (d->files)
		{
			struct DeviceFile *f = d->files;
			while (f)
			{
				for (unsigned int x = 0; x <= indent; x++)
					printf("\t");
				printf("%s (%ld)\n", f->name, f->size);
				f = f->peer;
			}
		}

		if (d->children)
			_device_debug_print_tree(d->children, indent + 1);

		d = d->peer;
	}
}

int day7(size_t *result)
{
	FILE *fp = fopen("inputs/day7.txt", "r");
	if (fp == NULL)
		return -1;

	struct DeviceDirectory *root = init_device_directory("/", NULL);
	device_crawl(fp, root);

	*result = device_sum_small_dirs(root);

	/* _device_debug_print_tree(root, 0); */

	fclose(fp);
	device_free_fs(root);
	return 0;
}
