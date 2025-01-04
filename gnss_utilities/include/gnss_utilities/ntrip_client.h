#ifndef GNSS_UTILITIES_NTRIP_CLIENT_H
#define GNSS_UTILITIES_NTRIP_CLIENT_H

#include <cstdint>
#include <cstdio>

namespace qle {

/**
 * @brief NtripClient class
 */
class NtripClient {
 public:
  /**
   * @brief Default constructor deleted
   */
  NtripClient() = delete;

  /**
   * @brief Construct NtripClient object
   */
  NtripClient(const char *host, const char *mountpoint, const char *username,
              const char *password, const char *outstream = nullptr) noexcept;

  /**
   * @brief Construct NtripClient object
   */
  NtripClient(const char *host, int32_t port, const char *mountpoint,
              const char *username, const char *password,
              const char *outstream = nullptr) noexcept;

  /**
   * @brief Copy constructor deleted
   */
  NtripClient(const NtripClient &) = delete;

  /**
   * @brief Move constructor deleted
   */
  NtripClient(NtripClient &&) = delete;

  /**
   * @brief Copy assignment deleted
   */
  NtripClient operator=(const NtripClient &) = delete;

  /**
   * @brief Move assignment deleted
   */
  NtripClient operator=(NtripClient &&) = delete;

  /**
   * @brief Destroy NtripClient object
   */
  ~NtripClient() { deinit(); }

/**
 * @brief Initialize object
 */
  bool init() noexcept;

/**
 * @brief Deinitialize object
 */
  void deinit() noexcept;

/**
 * @brief Main process of Ntrip client
 */
  void run() noexcept;

 protected:
 /**
  * @brief Open an outstream
  */
  virtual int openfd() noexcept;

/**
 * @brief Write data to file descriptor
 * 
 * @param fd File descriptor
 * @param buffer Buffer data
 * @param length Length of buffer data
 */
  virtual ssize_t write_data(int fd, const char *buffer,
                             size_t length) noexcept;

 private:
 /**
  * @brief Create a socket to a host
  * 
  * @param host Host
  * @param port Port
  */
  int create_socket(const char *host, int port) noexcept;

/**
 * @brief Send an NTRIP request
 * 
 * @param sockfd Socket file descriptor
 * @param host Ntrip host
 * @param mountpoint Ntrip mountpoint
 * @param username Ntrip username
 * @param password Ntrip password
 * @param user_agent User agent
 */
  bool send_request(int sockfd, const char *host, const char *mountpoint,
                    const char *username, const char *password,
                    const char *user_agent) noexcept;

/**
 * @brief Forward data from socket file descriptor to a file descriptor
 * 
 * @param sockfd Socket file descriptor
 * @param fd Output file descriptor
 */
  void forward(int sockfd, int fd) noexcept;

  const char *host_{nullptr};        ///< NTRIP host
  int32_t port_{2101};               ///< Port number
  const char *mountpoint_{nullptr};  ///< NTRIP mountpoint
  const char *username_{nullptr};    ///< Username
  const char *password_{nullptr};    ///< Password
  const char *outstream_{nullptr};   ///< Output

  const char *cUserAgent_ = "NTRIP client/1.0"; ///< User agent
  int sockfd_{}; ///< Socket file descriptor
  int fd_{}; ///< Outpur file descriptor
};

}  // namespace qle

#endif  // GNSS_UTILITIES_NTRIP_CLIENT_H
