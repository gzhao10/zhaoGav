#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int random(){
  int ans[1];
  int fd = open("/dev/random", O_RDONLY);
  if (fd == -1) {
    printf("Error: %s\n", strerror(errno));
    return 0;
  }
  int check = read(fd, ans, sizeof(ans));
  if (check == -1) printf("Error: %s\n", strerror(errno));
  return *ans;
}

int main(){
  int arr [10];

  printf("Generating random numbers:\n");
  int i;
  for (i = 0; i < 10; i++){
    arr[i] = random();
    printf("     random %d: %d\n", i, arr[i]);
  }

  printf("\n");
  printf("Writing numbers to file...\n");
  int fd = open("output", O_WRONLY | O_TRUNC | O_CREAT, 0640);
  if (fd == -1) {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }
  int writecheck = write(fd, arr, sizeof(arr));
  if (writecheck == -1) {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }
  close(fd);

  printf("\n");
  int newarr [10];
  printf("Reading numbers from file...\n");
  fd = open("output", O_RDONLY);
  int readcheck = read(fd, newarr, sizeof(newarr));
  if (readcheck == -1) {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }

  printf("\n");
  printf("Verification that written values were the same:\n");
  for (i = 0; i < 10; i++){
    printf("     random %d: %d\n", i, newarr[i]);
  }
}
