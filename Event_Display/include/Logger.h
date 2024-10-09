#pragma once

namespace limadou {
#define LOG_DEBUG(...)                                                         \
  do {                                                                         \
    std::printf(__VA_ARGS__);                                                  \
    std::printf("\n");                                                         \
  } while (0)

#define LOG_ERROR(...)                                                         \
  do {                                                                         \
    std::fprintf(stderr, __VA_ARGS__);                                         \
    std::fprintf(stderr, "\n");                                                \
  } while (0)
} // namespace limadou