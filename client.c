#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void perror_die(const char *m) {
  perror(m);
  exit(1);
}

int main() {
  int sock, v = 1;
  char buf[32];
  struct sockaddr_in addr;
  socklen_t size = sizeof(addr);
  struct ip_mreqn imr;

  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    perror_die("socket -1");

  addr.sin_family = AF_INET;
  addr.sin_port = htons(7777);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    perror_die("bind -1");

  imr.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
  imr.imr_address.s_addr = htonl(INADDR_ANY);
  imr.imr_ifindex = 0;

  setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &v, sizeof(v));
  recvfrom(sock, buf, 32, 0, (struct sockaddr *)&addr, &size);

  printf("%s\n", buf);
  close(sock);
  return 0;
}
