//
// Created by starman on 18.06.19.
//

#include "include/work.h"
#include <iostream>

namespace palette::work {
  bool getBest(const Color &first,
               const Color &second) {
    return first.second < second.second;
  }

  void usageDetails() {
    std::cout << "Usage:" << std::endl
              << "./palette -d path/to/images/dir " << std::endl
              << "or" << std::endl
              << "./palette path/to/image/file.image" << std::endl;
  }

} // namespace palette::work

