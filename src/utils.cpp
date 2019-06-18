//
// Created by starman on 18.06.19.
//
#include <unistd.h>
#include "include/work.h"
#include "include/errors.h"

namespace palette {
  status paletteType(std::string& path, int argc, char **argv) {
    int opt = 0;
    const char *optString = ".d:h?";
    status stat{};
    while (opt != -1) {
      opt = getopt(argc, argv, optString);
      switch (opt) {
      case 'd': {
        if (argc > 2) {
          stat = palette::status::IS_DIR;
          path = argv[2];
        }
        break;
      }
      case 'h':
      case '?': {
        stat = status::UNKNOWN_FLAG;
        work::usageDetails();
        break;
      }

      default: {
        if (argc > 1) {
          stat = status::IS_FILE;
          path = argv[1];
        } else {
          stat = status::ERROR;
          work::usageDetails();
        }
        break;
      }
      }
      opt = getopt(argc, argv, optString);
    }
    return stat;
  }

} // namespace: palette