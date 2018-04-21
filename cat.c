#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

// cat < input.txt 
// 在 fork 后 exec 前，通过文件描述符来进行 IO 重定向
// char *argv[2];
// argv[0] = "cat";
// ### argv[1] = 0;
// if(fork() == 0) {
//     close(0);
//     open("input.txt", O_RDONLY);
//     exec("cat", argv);
// }

void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);
  }
  exit();
}
