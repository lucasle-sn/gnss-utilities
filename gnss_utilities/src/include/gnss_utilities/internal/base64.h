#ifndef GNSS_UTILITIES_INTERNAL_BASE64_H
#define GNSS_UTILITIES_INTERNAL_BASE64_H

#include <unistd.h>

namespace qle {

/**
 * @brief Encodes ASCII string into base64 format string
 *
 * @param raw Plain ASCII string
 * @param len Length of raw datastream
 * @param out Output datastream
 */
void encode_base64(const char *raw, size_t len, char *out);

}  // namespace qle

#endif  // GNSS_UTILITIES_INTERNAL_BASE64_H
