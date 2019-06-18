//
// Created by starman on 17.06.19.
//

#ifndef COLORS_PALETTE_H
#define COLORS_PALETTE_H
#include <boost/filesystem.hpp>
#include <opencv2/core/mat.hpp>
#include <map>

namespace fs = boost::filesystem;

namespace palette {
  typedef std::map<unsigned int, unsigned int> HexPalette;
  typedef std::map<std::string, unsigned int> RGBPalette;
  typedef std::pair<unsigned int, unsigned int> Color;

  int getColorRating(HexPalette& colors, const fs::path& file);

  RGBPalette getPalette(const cv::Mat3b& src);

  unsigned long RGBToHex(const std::string& base);

  void reduceColor_kmeans(const cv::Mat3b& src, cv::Mat3b& dst);

  void sort(std::vector<Color>& sort_vec);

}   // namespace palette

#endif //COLORS_PALETTE_H
