#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
	int input_fd, output_fd;
	unsigned char art[65536];
	off_t file_size_bytes;
	unsigned int file_size_kbs, file_size_mbs;
	if(argc != 3)
	{
		printf("uasge:\n\t%s input.bin output.bin\n", argv[0]);
		exit(0);
	}
	
	/*get art data*/
	input_fd = open(argv[1], O_RDONLY);
	if(input_fd < 0)
	{
		printf("open %s failed!\n", argv[1]);
		exit(0);
	}
	file_size_bytes = lseek(input_fd, 0, SEEK_END);/*get file size*/
	file_size_kbs = file_size_bytes / 1024;
	file_size_mbs = file_size_kbs / 1024;
	printf("%s size is %db\t%dkb\t%dmb\n", argv[1], (unsigned int)file_size_bytes, file_size_kbs, file_size_mbs);
	if(file_size_mbs == 0 || file_size_bytes % 1024 != 0 || file_size_kbs % 1024 != 0)
	{
		printf("%s is not a programmer firmware\n", argv[1]);
		exit(0);
	}
	memset(&art[0], 0xff, 65536);
	if(file_size_mbs == 1)
	{
		lseek(input_fd, -(16*1024), SEEK_END);
		read(input_fd, &art[0x1000], 65536);
	}
	else
	{
		lseek(input_fd, -(64*1024), SEEK_END);
		read(input_fd, &art[0], 64*1024);
	}
	close(input_fd);
	/*get art data end*/
	
	/*output art data*/
	output_fd = open(argv[2], O_WRONLY | O_CREAT, 00666);
	if(output_fd < 0)
	{
		printf("open %s failed!\n", argv[2]);
		exit(0);
	}
	printf("output art to %s\n", argv[2]);
	lseek(output_fd, 0, SEEK_SET);
	write(output_fd, &art[0], 65536);
	close(output_fd);
	/*output art data*/
	return 0;
}