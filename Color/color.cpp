//
// Created by Hà Tường Nguyên on 12/29/23.
//

#include "color.h"

namespace color {

    std::string getColorConstant(int index) {
        switch (index) {
            case 7:
            case 6:
                return color::RED;
            case 5:
                return color::YELLOW;
            case 4:
                return color::GREEN;
            case 3:
                return color::BLUE;
            case 2:
                return color::CYAN;
            case 1:
                return color::MAGENTA;
            default:
                return "";
        }
    }

} // color