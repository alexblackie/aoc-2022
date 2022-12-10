#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct DeviceFile
{
	struct DeviceFile *peer;
	size_t size;
	char *name;
};

struct DeviceDirectory
{
	struct DeviceDirectory *parent;
	struct DeviceDirectory *children;
	struct DeviceDirectory *peer;
	struct DeviceFile *files;
	char *name;
};

struct DeviceCommand
{
	char *executable;
	char *argument;
};

struct DeviceFile *init_device_file(char name[], size_t size);
struct DeviceDirectory *init_device_directory(char name[], struct DeviceDirectory *parent);
struct DeviceCommand *device_parse_cmd(char *line);
size_t device_dirsize(struct DeviceDirectory *dir, bool with_peers);
size_t device_sum_small_dirs(struct DeviceDirectory *root);
void device_execute_cd(char *dest, struct DeviceDirectory **pwd);
void device_discover_directory(char *src, struct DeviceDirectory *parent);
void device_discover_file(char *src, struct DeviceDirectory *parent);
void device_free_cmd(struct DeviceCommand *cmd);
void device_free_fs(struct DeviceDirectory *dir);
void device_crawl(FILE *fp, struct DeviceDirectory *root);
int day7(size_t *result);
