#include "../src/day7.h"
#include "greatest/greatest.h"

void _device_fs_fixture(struct DeviceDirectory *root)
{
	FILE *fp = fopen("test/fixtures/day7.txt", "r");
	if (fp == NULL)
	{
		printf("Failed to open fixture!");
		return;
	}
	device_crawl(fp, root);
	fclose(fp);
}

TEST test_device_dirsize()
{
	struct DeviceFile *root_file = init_device_file("r.txt", 256);
	struct DeviceDirectory *root = init_device_directory("/", NULL);
	root->files = root_file;
	struct DeviceFile *child_file = init_device_file("a.txt", 512);
	struct DeviceDirectory *child = init_device_directory("c", root);
	child->files = child_file;
	root->children = child;
	struct DeviceFile *peer_file = init_device_file("z.txt", 256);
	child_file->peer = peer_file;
	struct DeviceDirectory *child_peer = init_device_directory("peer", root);
	child->peer = child_peer;
	struct DeviceFile *child_peer_file = init_device_file("m.txt", 1024);
	child_peer->files = child_peer_file;

	ASSERT_EQ_FMT((size_t)2048, device_dirsize(root, false), "%ld");

	device_free_fs(root);
	PASS();
}

TEST test_device_free_fs()
{
	/* Ensure no segfaults with a totally empty dir */
	struct DeviceDirectory *root = init_device_directory("/", NULL);
	device_free_fs(root);
	PASS();
}

TEST test_device_parse_cmd()
{
	struct DeviceCommand *cd = device_parse_cmd("$ cd butt");
	ASSERT_STR_EQ("cd", cd->executable);
	ASSERT_STR_EQ("butt", cd->argument);

	struct DeviceCommand *ls = device_parse_cmd("$ ls");
	ASSERT_STR_EQ("ls", ls->executable);
	ASSERT_EQ(NULL, ls->argument);

	device_free_cmd(cd);
	device_free_cmd(ls);
	PASS();
}

TEST test_device_execute_cd()
{
	struct DeviceDirectory *root = init_device_directory("/", NULL);
	struct DeviceDirectory *child = init_device_directory("c", root);
	root->children = child;
	struct DeviceDirectory *child_peer = init_device_directory("a", root);
	child->peer = child_peer;

	struct DeviceDirectory *pwd = root;
	device_execute_cd("a", &pwd);
	ASSERT_EQ(pwd, child_peer);

	struct DeviceDirectory *pwd2 = child;
	device_execute_cd("..", &pwd2);
	ASSERT_EQ(pwd2, root);

	device_free_fs(root);
	PASS();
}

TEST test_device_discover_directory()
{
	struct DeviceDirectory *root = init_device_directory("/", NULL);
	struct DeviceDirectory *child = init_device_directory("c", root);
	root->children = child;
	struct DeviceDirectory *child_peer = init_device_directory("a", root);
	child->peer = child_peer;

	char *line = "dir rats";

	device_discover_directory(line, child_peer);
	ASSERT_STR_EQ("rats", child_peer->children->name);

	device_discover_directory(line, root);
	ASSERT_STR_EQ("rats", root->children->name);
	ASSERT_STR_EQ("c", root->children->peer->name);

	device_free_fs(root);
	PASS();
}

TEST test_device_discover_file()
{
	char *line = "1234 butt.txt";

	struct DeviceDirectory *root = init_device_directory("/", NULL);
	device_discover_file(line, root);
	ASSERT_EQ_FMT((size_t)1234, root->files->size, "%ld");
	ASSERT_STR_EQ("butt.txt", root->files->name);

	struct DeviceDirectory *root2 = init_device_directory("/", NULL);
	struct DeviceFile *root_file = init_device_file("peer.txt", 256);
	root2->files = root_file;

	device_discover_file(line, root2);
	ASSERT_EQ_FMT((size_t)1234, root2->files->size, "%ld");
	ASSERT_STR_EQ("butt.txt", root2->files->name);
	ASSERT_STR_EQ("peer.txt", root2->files->peer->name);

	device_free_fs(root);
	device_free_fs(root2);
	PASS();
}

TEST test_device_sum_small_dirs()
{
	struct DeviceDirectory *root = init_device_directory("/", NULL);
	_device_fs_fixture(root);

	ASSERT_EQ_FMT((size_t)95437, device_sum_small_dirs(root), "%ld");

	device_free_fs(root);
	PASS();
}

SUITE(day7_suite)
{
	RUN_TEST(test_device_dirsize);
	RUN_TEST(test_device_parse_cmd);
	RUN_TEST(test_device_free_fs);
	RUN_TEST(test_device_execute_cd);
	RUN_TEST(test_device_discover_directory);
	RUN_TEST(test_device_discover_file);
	RUN_TEST(test_device_sum_small_dirs);
}
