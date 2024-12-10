#ifndef GNSS_UTILITIES_INTERNAL_BASE64_H
#define GNSS_UTILITIES_INTERNAL_BASE64_H

#include <unistd.h>

namespace qle {

void encode_base64(const char *raw, size_t len, char *out);

}

#endif // GNSS_UTILITIES_INTERNAL_BASE64_H
