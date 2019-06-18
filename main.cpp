//
// Created by starman on 18.06.19.
//
#include <iostream>
#include <iomanip>
#include "include/palette.h"
#include "include/utils.h"

int main(int argc, char** argv) {
  int64 area = 0;
  std::string path_to_files{};
  palette::HexPalette colors{};
  palette::status status = palette::paletteType(path_to_files, argc, argv);
  if (status < 0) {
    return status;
  }
  if (status == palette::status::IS_DIR) {
    for (const auto& entry : fs::directory_iterator(path_to_files)) {
      std::cout << entry.path() << std::endl;
      try {
        area += palette::getColorRating(colors, entry.path());
      } catch (std::exception& e){
        std::cerr << e.what() << std::endl;
        return palette::status::NOT_FOUND;
      }
    }
  } else {
    try {
      area = palette::getColorRating(colors, path_to_files);
    } catch (std::exception& e){
      std::cerr << e.what() << std::endl;
      return palette::status::NOT_FOUND;
    }
  }
  std::vector<palette::Color> sort_palette(colors.begin(), colors.end());
  palette::sort(sort_palette);
  for (const auto& color : sort_palette) {
    std::cout << "Color: #" << std::hex << std::setw(6) << std::setfill('0')
              << color.first
              << " \t - Area: " << 100.f * float(color.second) / float(area)
              << "%" << std::endl;
  }
  return 0;
}
