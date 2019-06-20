//
// Created by starman on 18.06.19.
//

#ifndef PALETTE_WORK_H
#define PALETTE_WORK_H
#include "include/palette.h"

namespace palette {
  namespace work {
    /**
     * Compare two colors by rating in percent (for sorting)
     * @param first - first color
     * @param second - second color
     * @return {bool} status - compare status
     */
    bool getBest(const Color &first, const Color &second);

    /**
     * Displays a message about usage this program to stdout
     */
    void usageDetails();
  } // namespace work
} // namespace palette

#endif // PALETTE_WORK_H
