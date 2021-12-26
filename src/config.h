//
// Created by AntonKrug on 26/12/21.
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
}

#endif //RAYMARCHER_CONFIG_H
