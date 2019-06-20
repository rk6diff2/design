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

  /**
   * Get colors rating for one file
   * @param {HexPalette&} colors - colors hex palette will be initialized
   * @param {fs::path&} file - path to image file
   * @param {int} cluster_num - cluster number for k-means algorithm
   * @return {int} area - image area
   */
  int getColorRating(HexPalette &colors, const fs::path &file, int cluster_num);

  /**
   * Gat palette in RGB format
   * @param {cv::Mat3b&} src - image source in matrix format
   * @return {RGBPalette} palette - RGB palette object
   */
  RGBPalette getPalette(const cv::Mat3b &src);

  /**
   * Convert RGB color to HEX format
   * @param {std::string&} base - string in hard format: R.G.B
   *                              for parsing
   * @return {unsigned long} num - num of color in hex format
   */
  unsigned long RGBToHex(const std::string &base);

  /**
   * Core project. Realize k-means algorithm, reduce colors and
   * after this clustering it. Initialize dst matrix
   * @param {const cv::Mat3b&} src - image source in matrix format
   * @param {cv::Mat3b&} dst - clustering image (colors) in matrix format
   * @param {int} cluster_num - number of clusters
   */
  void reduceColor_kmeans(const cv::Mat3b &src, cv::Mat3b &dst, int cluster_num);

  /**
   * Sort vector with colors for rating
   * @param {std::vector<Color>&} sort_vec - unsorted colors vector
   */
  void sort(std::vector<Color> &sort_vec);

  /**
   * Get the palette type the user needs
   * @param {Param} path - empty parameters will be initialize
   * @param argc - main arg count
   * @param argv - main arg vector
   * @return {enum} stat - launch status
   */
  status paletteType(Param &path, int argc, char **argv);

} // namespace palette

#endif // COLORS_PALETTE_H
