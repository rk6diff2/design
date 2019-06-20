//
// Created by starman on 18.06.19.
//

#include "include/work.h"
#include <iostream>

namespace palette::work {
  bool getBest(const Color &first, const Color &second) {
    return first.second < second.second;
  }

  void usageDetails() {
    std::cout << "Usage: palette [OPTION] PATH... [OPTION]..."                         << std::endl
              << "Calculate colors rating for image or directory with images."         << std::endl
              << "Example: palette path/to/image/file.image"                           << std::endl
              << "------- Listing options -------"                                     << std::endl
              << "-d folder         Obtain RATING from DIRECTORY"                      << std::endl
              << "-k cluster_num    Set CLUSTER NUM for k-means algorithm (default 8)" << std::endl
              << "\nPalette program version 0.3   https://rowbot.dev"                  << std::endl;

  }
} // namespace palette::work
