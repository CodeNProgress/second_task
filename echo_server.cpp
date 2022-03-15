#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    cout << "Ne udalos sozdat socket. Oshibka: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(9999);

  if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0){
    cout << "Ne udalos swyazat socket k protu 9999. Oshibka: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  if (listen(sockfd, 10) < 0){
    cout << "Ne udalos slushat socket. Oshibka: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  auto addrlen = sizeof(sockaddr);
  int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
  if (connection < 0){
    cout << "Ne udalos ustanowit soyedineniye. Oshibka: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  char buffer[100];
  auto bytesRead = read(connection, buffer, 100);

  string response = buffer;
  send(connection, response.c_str(), response.size(), 0);

  close(connection);
  close(sockfd);
}

