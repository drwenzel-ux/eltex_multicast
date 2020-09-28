#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void perror_die(const char *m) {
  perror(m);
  exit(1);
}

int main() {
  int sock;
  struct sockaddr_in addr;

  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    perror_die("socket -1");

  addr.sin_family = AF_INET;
  addr.sin_port = htons(7777);
  addr.sin_addr.s_addr = inet_addr("224.0.0.1");

  char buf[] = "hello from server!";
  sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
  close(sock);

  return 0;
}
