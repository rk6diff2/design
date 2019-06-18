#include <exception>
#include <utility>

//
// Created by starman on 16.06.19.
//

#ifndef DESIGN_ERRORS_H
#define DESIGN_ERRORS_H

namespace palette {
  enum status {
    NOT_FOUND = -3,
    UNKNOWN_FLAG,
    ERROR,
    OK,
    IS_DIR,
    IS_FILE,
  };

  class PaletteException : public std::exception {
   public:
    explicit PaletteException(char const *_params, int _type = 0) throw()
        : params_(_params), type_(_type) {}

    const char *what() const throw() override;

   private:
    const char *params_;
    int type_{};
  };
}

#endif //DESIGN_ERRORS_H
