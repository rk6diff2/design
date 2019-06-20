//
// Created by starman on 17.06.19.
//

#ifndef COLORS_PALETTE_H
#define COLORS_PALETTE_H

#include "include/errors.h"
#include <boost/filesystem.hpp>
#include <map>
#include <opencv2/core/mat.hpp>

#define DEFAULT_K 8
#define OPT_KEYS ".d:k:h?"

namespace fs = boost::filesystem;

namespace palette {
  typedef std::map<unsigned int, unsigned int> HexPalette;
  typedef std::map<std::string, unsigned int> RGBPalette;
  typedef std::pair<unsigned int, unsigned int> Color;
  typedef std::pair<std::string, int> Param;

  int getColorRating(HexPalette &colors, const fs::path &file, int cluster_num);

  RGBPalette getPalette(const cv::Mat3b &src);

  unsigned long RGBToHex(const std::string &base);

  void reduceColor_kmeans(const cv::Mat3b &src, cv::Mat3b &dst, int cluster_num);

  void sort(std::vector<Color> &sort_vec);
  status paletteType(Param &path, int argc, char **argv);

} // namespace palette

#endif // COLORS_PALETTE_H
