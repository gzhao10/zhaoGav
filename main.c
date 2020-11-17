#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int random(){
  int ans[1];
  int fd = open("/dev/random", O_RDONLY);
  if (fd == -1) printf("Error: %s\n", strerror(errno));
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
  int out = open("output", O_RDWR | O_CREAT, 0764);
  if (out == -1) printf("Error: %s\n", strerror(errno));
  int writecheck = write(out, arr, sizeof(arr));
  if (writecheck == -1) printf("Error: %s\n", strerror(errno));


  printf("\n");
  int newarr [10];
  printf("Reading numbers from file...\n");
  int readcheck = read(out, newarr, sizeof(newarr));
  if (readcheck == -1) printf("Error: %s\n", strerror(errno));

  printf("\n");
  printf("Verification that written values were the same:\n");
  for (i = 0; i < 10; i++){
    printf("     random %d: %d\n", i, newarr[i]);
  }
  //not sure what went wrong
}
