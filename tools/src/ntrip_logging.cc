#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include <utilities/log.h>

#include <gnss_utilities/ntrip_client.h>

// Signal handler function
void handle_sigint(int sig) {
  fprintf(stdout, "Caught signal %d, Ctrl + C pressed. Exiting gracefully...\n",
          sig);
  exit(EXIT_SUCCESS);
}

int main(int argc, char **args) {
  // Set up the signal handler for SIGINT
  if (signal(SIGINT, handle_sigint) == SIG_ERR) {
    fprintf(stderr, "Unable to catch SIGINT\n");
    return EXIT_FAILURE;
  }

  if (argc != 5) {
    fprintf(stderr, "Invalid arguments\n");
    fprintf(stderr,
            "Usage: ntrip-logging <host> <mountpoint> <username> <password>\n");
    return EXIT_FAILURE;
  }

  auto logger_cfg =
      std::make_unique<qle::LoggerConfigHandler>(qle::LogLevel::DEBUG);
  const char *host = args[1];
  const char *mountpoint = args[2];
  const char *username = args[3];
  const char *password = args[4];

  auto ntrip = std::make_unique<qle::NtripClient>(host, 2101, mountpoint,
                                                  username, password);

  ntrip->init();
  ntrip->run();

  return EXIT_SUCCESS;
}
