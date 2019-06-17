#include <iostream>
#include <iomanip>
#include "include/palette.h"

int main( int argc, char** argv ) {
  cv::String path_to_files("../test_data");
  if (argc > 1) {
    path_to_files = argv[1];
  }
  int64 area = 0;
  palette::HexPalette colors;
  for (const auto &entry : fs::directory_iterator(path_to_files.c_str())) {
    std::cout << entry.path() << std::endl;
    area += palette::getColorRating(colors, entry.path());
  }

  std::vector<std::pair<unsigned int, unsigned int>> sort_palette(colors.begin(), colors.end());
  palette::sort(sort_palette);
  for (const auto& color : sort_palette) {
    std::cout << "Color: #" << std::hex << std::setw(6) << std::setfill('0')
              << color.first << " \t - Area: " << 100.f * float(color.second) / float(area) << "%" << std::endl;
  }
  return 0;
}
