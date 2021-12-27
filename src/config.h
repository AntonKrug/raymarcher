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
  constexpr float nudgeOffset = 0.01f;

  // Randomized sampler config values
  constexpr int maxSamples = 3;

  // Output config SDL, Mustein, UART

  // Sphere Tracer limits
  constexpr float traceMaxDistance  = 40.0f;
  constexpr int   traceMaxSteps     = 40;
  constexpr float minObjectDistance = 0.03f;
}

#endif //RAYMARCHER_CONFIG_H
