//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_CONFIG_H
#define RAYMARCHER_CONFIG_H

namespace config {
  // Render resolution
  constexpr int width  = 512;
  constexpr int height = 480;

  // Display resolution can bigger than render resolution (scaling the image)
  constexpr int displayWidth  = width  * 2;
  constexpr int displayHeight = height * 2;

  // Normal calculation offset
  constexpr int nudgeOffset = 0.01f;

  // Randomized sampler config values
  constexpr int maxSamples = 32;

  // Output config SDL, Mustein, UART
}

#endif //RAYMARCHER_CONFIG_H
