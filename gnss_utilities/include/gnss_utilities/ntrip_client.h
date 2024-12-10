#ifndef GNSS_UTILITIES_NTRIP_CLIENT_H
#define GNSS_UTILITIES_NTRIP_CLIENT_H

#include <cstdint>
#include <cstdio>

namespace qle {

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

  bool init() noexcept;

  void deinit() noexcept;

  void run() noexcept;

 protected:
  virtual int openfd() noexcept;

  virtual ssize_t write_data(int fd, const char *buffer,
                             size_t length) noexcept;

 private:
  int create_socket(const char *host, int port) noexcept;

  bool send_request(int sockfd, const char *host, const char *mountpoint,
                    const char *username, const char *password,
                    const char *user_agent) noexcept;

  void forward(int sockfd, int fd) noexcept;

  const char *host_{nullptr};        ///< NTRIP host
  int32_t port_{2101};               ///< Port number
  const char *mountpoint_{nullptr};  ///< NTRIP mountpoint
  const char *username_{nullptr};    ///< Username
  const char *password_{nullptr};    ///< Password
  const char *outstream_{nullptr};   ///< Output

  const char *cUserAgent_ = "NTRIP client/1.0";
  int sockfd_{};
  int fd_{};
};

}  // namespace qle

#endif  // GNSS_UTILITIES_NTRIP_CLIENT_H
