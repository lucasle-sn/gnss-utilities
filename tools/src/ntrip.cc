#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <utilities/log.h>
#include <memory>

#include <gnss_utilities/ntrip_client.h>

// Signal handler function
void handle_sigint(int sig) {
  fprintf(stdout, "Caught signal %d, Ctrl + C pressed. Exiting gracefully...\n",
          sig);
  exit(0);  // Exit the program
}

int main(int argc, char **args) {
  // Set up the signal handler for SIGINT
  if (signal(SIGINT, handle_sigint) == SIG_ERR) {
    fprintf(stderr, "Unable to catch SIGINT");
    return 1;
  }

  if (argc < 5) {
    fprintf(stderr, "Missing arguments");
    return 1;
  }

  // qle::Logger::set_log_level(qle::LogLevel::DEBUG);
  const char *host = args[1];
  const char *mountpoint = args[2];
  const char *username = args[3];
  const char *password = args[4];
  auto ntrip = std::make_unique<qle::NtripClient>(host, 2101, mountpoint,
                                                  username, password);
  ntrip->init();
  ntrip->run();

  return 0;
}
