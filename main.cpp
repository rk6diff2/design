//
// Created by starman on 18.06.19.
//

#include "include/palette.h"
#include <iomanip>
#include <iostream>

int main(int argc, char **argv) {
  palette::Param param{};
  palette::status status = palette::paletteType(param, argc, argv);
  if (status < 0) {
    return status;
  }
  palette::HexPalette colors{};
  int64 area = 0;

  if (status == palette::status::IS_DIR) {
    for (const auto &entry : fs::directory_iterator(param.first)) {
      std::cout << entry.path() << std::endl;
      try {
        area += palette::getColorRating(colors, entry.path(), param.second);
      } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return palette::status::NOT_FOUND;
      }
    }
  } else {
    try {
      area = palette::getColorRating(colors, param.first, param.second);
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
      return palette::status::NOT_FOUND;
    }
  }

  std::vector<palette::Color> sort_palette(colors.begin(), colors.end());
  palette::sort(sort_palette);
  for (const auto &color : sort_palette) {
    std::cout << "Color: #" << std::hex << std::setw(6) << std::setfill('0')
              << color.first
              << " \t - Area: " << 100.f * float(color.second) / float(area)
              << "%" << std::endl;
  }
  return 0;
}
