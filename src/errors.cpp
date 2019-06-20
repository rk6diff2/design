//
// Created by starman on 18.06.19.
//

#include "include/errors.h"

namespace palette {
  const char *PaletteException::what() const throw() {
    switch (type_) {
    case 1:
      return params_;
    default:
      return "Error";
    }
  }
} // namespace palette
