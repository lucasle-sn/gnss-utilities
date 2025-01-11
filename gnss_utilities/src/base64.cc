#include <gnss_utilities/internal/base64.h>

namespace qle {

const char kBase64CodeTable[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64(const char *raw, size_t len, char *out) {
  size_t out_pos = 0;
  for (size_t i = 0; i < len; i += 3) {
    out[out_pos++] = kBase64CodeTable[(raw[i] & 0xFC) >> 2];
    if (i + 1 >= len) {
      out[out_pos++] = kBase64CodeTable[(raw[i] & 0x03) << 4];
      break;
    }
    out[out_pos++] =
        kBase64CodeTable[(raw[i] & 0x03) << 4 | (raw[i + 1] & 0xF0) >> 4];
    if (i + 2 >= len) {
      out[out_pos++] = kBase64CodeTable[(raw[i + 1] & 0x0F) << 2];
      break;
    } else {
      out[out_pos++] =
          kBase64CodeTable[(raw[i + 1] & 0x0F) << 2 | (raw[i + 2] & 0xC0) >> 6];
    }
    out[out_pos++] = kBase64CodeTable[raw[i + 2] & 0x3F];
  }
  // Padding the output to make sure it's multiple of 4 characters
  size_t padding = (out_pos % 4) ? 4 - out_pos % 4 : 0;
  for (size_t i = 0; i < padding; ++i) {
    out[out_pos++] = '=';
  }
  out[out_pos] = '\0';  // Null-terminate the output
}

}  // namespace qle
