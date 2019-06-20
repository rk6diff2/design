//
// Created by starman on 17.06.19.
//

#include "include/palette.h"
#include "include/errors.h"
#include "include/work.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <unistd.h>

namespace palette {
  RGBPalette getPalette(const cv::Mat3b &src) {
    RGBPalette palette{};
    for (int r = 0; r < src.rows; ++r) {
      for (int c = 0; c < src.cols; ++c) {
        cv::Vec3b color = src(r, c);
        std::string str{};
        for (unsigned char i : color.val) {
          str += std::to_string(i) + ".";
        }
        palette[str] = palette.count(str) == 0 ? 1 : palette[str] + 1;
      }
    }
    return palette;
  }

  int getColorRating(HexPalette &colors, const fs::path &file, int cluster_num) {
    cv::Mat3d img = imread(file.string(), cv::IMREAD_COLOR); // Read the file
    if (!img.data) {
      std::cout << "No image data: " << file << std::endl;
      throw PaletteException("No image data");
    }

    cv::Mat3b src{};
    reduceColor_kmeans(img, src, cluster_num);
    auto palette = getPalette(src);
    int area = img.rows * img.cols;
    for (const auto &color : palette) {
      colors[RGBToHex(color.first)] += color.second;
    }
    return area;
  }

  unsigned long RGBToHex(const std::string &base) {
    std::vector<std::string> split{};
    boost::split(split, base, boost::is_any_of("."));
    unsigned int arr[3]{};
    uint8_t i = 0;
    char *end = nullptr;
    for (const auto &item : split) {
      if (i < 3) {
        arr[i] = std::strtol(item.c_str(), &end, 10);
        ++i;
      }
    }
    return ((arr[2] & 0xff) << 16) + ((arr[1] & 0xff) << 8) + (arr[0] & 0xff);
  }

  void reduceColor_kmeans(const cv::Mat3b &src, cv::Mat3b &dst,
                          int cluster_num = 8) {
    int n = src.rows * src.cols;
    cv::Mat data = src.reshape(1, n);
    data.convertTo(data, CV_32F);

    cv::Mat labels{};
    cv::Mat1f colors{};
    kmeans(data, cluster_num, labels, cv::TermCriteria(), 1,
           cv::KMEANS_PP_CENTERS, colors);

    for (int i = 0; i < n; ++i) {
      data.at<float>(i, 0) = colors(labels.at<int>(i), 0);
      data.at<float>(i, 1) = colors(labels.at<int>(i), 1);
      data.at<float>(i, 2) = colors(labels.at<int>(i), 2);
    }

    cv::Mat reduced = data.reshape(3, src.rows);
    reduced.convertTo(dst, CV_8U);
  }

  void sort(std::vector<std::pair<unsigned, unsigned>> &sort_vec) {
    std::sort(sort_vec.begin(), sort_vec.end(), work::getBest);
  }

  status paletteType(Param &param, int argc, char **argv) {
    param = {"", DEFAULT_K};
    int opt = 0;
    int k_ind = 0;
    status stat = status::OK;
    opt = getopt(argc, argv, OPT_KEYS);
    while (opt != -1 && stat != status::ERROR) {
      switch (opt) {
      case 'd': {
        if (argc > 2) {
          stat = palette::status::IS_DIR;
          param.first = optarg;
        }
        break;
      }

      case 'k': {
        if (argc > 3) {
          if (optarg) {
            char *end = nullptr;
            param.second = std::strtol(optarg, &end, 10);
            k_ind = optind;
          }
        } else {
          stat = status::ERROR;
        }
        break;
      }

      case 'h':
      case '?': {
        stat = status::UNKNOWN_FLAG;
        work::usageDetails();
        break;
      }

      default: {
        if (argc > 1) {
          stat = status::IS_FILE;
          param.first = argv[optind];
        } else {
          stat = status::ERROR;
        }
        break;
      }
      }
      opt = getopt(argc, argv, OPT_KEYS);
    }
    if (stat == status::ERROR) {
      work::usageDetails();
      return stat;
    }

    if (stat == status::OK) {
      stat = status::IS_FILE;
      if (k_ind) {
        param.first = argv[3];
      } else {
        param.first = argv[1];
      }
    }
    return stat;
  }
} // namespace palette
