#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <memory>
#include <string>

#include <utilities/log.h>

#include <gnss_utilities/internal/base64.h>
#include <gnss_utilities/ntrip_client.h>

namespace qle {

auto logger = std::make_unique<qle::Logger>("NtripClient");

NtripClient::NtripClient(const char *host, const char *mountpoint,
                         const char *username, const char *password,
                         const char *outstream) noexcept
    : host_(host),
      mountpoint_(mountpoint),
      username_(username),
      password_(password),
      outstream_(outstream) {}

NtripClient::NtripClient(const char *host, int32_t port, const char *mountpoint,
                         const char *username, const char *password,
                         const char *outstream) noexcept
    : host_(host),
      port_(port),
      mountpoint_(mountpoint),
      username_(username),
      password_(password),
      outstream_(outstream) {}

bool NtripClient::init() noexcept {
  sockfd_ = open_socket(host_, port_);
  if (sockfd_ < 0) {
    logger->error("Fail to create socket");
    return false;
  }

  outfd_ = open_outstream();
  if (outfd_ < 0) {
    logger->error("Fail to open output stream");
    return false;
  }
  return true;
}

void NtripClient::deinit() noexcept {
  close(sockfd_);
  close(outfd_);
}

void NtripClient::run() noexcept {
  if (send_request(sockfd_, host_, mountpoint_, username_, password_)) {
    logger->debug("Connected to NTrip server");
    forward(sockfd_, outfd_);
  }
}

int NtripClient::open_outstream() noexcept {
  if (outstream_ == nullptr) {
    return STDOUT_FILENO;
  }
  return open(outstream_, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

ssize_t NtripClient::write_data(int fd, const char *buffer,
                                size_t length) noexcept {
  if (fd < 0) {
    logger->error("Invalid file descriptor for writing");
    return -1;
  }
  return write(fd, buffer, length);
}

int NtripClient::open_socket(const char *host, int port) noexcept {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    logger->error("Opening socket failed");
    return -1;
  }

  struct hostent *server = gethostbyname(host);
  if (server == nullptr) {
    logger->error("Host not found");
    return -1;
  }

  struct sockaddr_in server_addr {};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr = *(struct in_addr *)server->h_addr;
  server_addr.sin_port = htons(port);

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    logger->error("Error connecting");
    close(sockfd);
    return -1;
  }

  logger->debug("Connected to NtripCaster[%s:%d]", host, port);
  return sockfd;
}

bool NtripClient::send_request(int sockfd, const char *host,
                               const char *mountpoint, const char *username,
                               const char *password) noexcept {
  char credential[1024]{};
  snprintf(credential, sizeof(credential), "%s:%s", username, password);

  char credential_base64[1024]{};
  encode_base64(credential, strlen(credential), credential_base64);

  char request[4096]{};
  auto request_len = snprintf(request, sizeof(request),
                              "GET /%s HTTP/1.1\r\n"
                              "Host: %s\r\n"
                              "Ntrip-Version: Ntrip/2.0\r\n"
                              "User-Agent: NTRIP client/1.0\r\n"
                              "Authorization: Basic %s\r\n"
                              "\r\n",
                              mountpoint, host, credential_base64);
  logger->debug("%s", request);

  if (send(sockfd, request, request_len, 0) < 0) {
    logger->error("Error sending request");
    return false;
  }

  char buf[1024]{};
  auto received_len = read(sockfd, buf, sizeof(buf));
  std::string buf_str = std::string(buf, received_len);
  logger->debug("Request response:\n%s", buf);

  bool validResponse{false};

  if ((buf_str.find("ICY 200 OK\r\n")) != std::string::npos) {
    validResponse = true;  // Non standard HTTP response
    ;
  } else if (((buf_str.find("HTTP/1.1 200 OK")) != std::string::npos) &&
             ((buf_str.find("\r\n\r\n")) != std::string::npos)) {
    validResponse = true;
  }

  if (!validResponse ||
      (buf_str.find("Transfer-Encoding: chunked") == std::string::npos)) {
    return false;
  }

  return true;
}

void NtripClient::forward(int sockfd, int outfd) noexcept {
  char buffer[4096]{};
  ssize_t bytes_received = 0;

  while ((bytes_received = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
    write_data(outfd, buffer, bytes_received);
  }

  if (bytes_received < 0) {
    logger->error("Error reading from socket");
  }
}

}  // namespace qle
