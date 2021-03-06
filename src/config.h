//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_CONFIG_H
#define RAYMARCHER_CONFIG_H

namespace config {
  // Render resolution
  constexpr int width  = 256*2;
  constexpr int height = 256*2;

  // Display resolution can bigger than render resolution (scaling the image)
  constexpr int displayWidth  = width  * 2;
  constexpr int displayHeight = height * 2;

  // Normal calculation offset
  constexpr float nudgeOffset = 0.04f;

  // Randomized sampler config values
  constexpr int maxSamples = 3;

  // Reflections
  constexpr int maxBounce = 3;

  // Output config SDL, Mustein, UART

  // Sphere Tracer limits
  constexpr float traceMaxDistance  = 60.0f;
  constexpr int   traceMaxSteps     = 50;
  constexpr float minObjectDistance = 0.008f;
}

#endif //RAYMARCHER_CONFIG_H
