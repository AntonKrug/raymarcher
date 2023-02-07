//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_HELPER_H
#define RAYMARCHER_HELPER_H

#include <type_traits>

class helper {
private:
  float value;

  explicit helper(float valueInit);

  helper operator<<(helper second);
  helper operator>>(helper second);

  static float minf2(float a, float b);
  static float maxf2(float a, float b);

public:

  // https://stackoverflow.com/questions/614233/undefined-reference-to-function-template-when-used-with-string-gcc
  // http://www.parashift.com/c++-faq-lite/separate-template-class-defn-from-decl.html
  template<typename Tfirst, typename ...Ts>
  static float minf(Tfirst first, Ts ...args) {
    // Handy to detect the cases where accidental double would get casted to a float implicitly
    static_assert((std::is_same_v<float, Tfirst>),    "All arguments must be float");
    static_assert((std::is_same_v<float, Ts> && ...), "All arguments must be float");

    helper firstWrapped(first);
    firstWrapped << ( helper(args) << ...);

    return firstWrapped.value;
  }


  // https://stackoverflow.com/questions/614233/undefined-reference-to-function-template-when-used-with-string-gcc
  // http://www.parashift.com/c++-faq-lite/separate-template-class-defn-from-decl.html
  template<typename Tfirst, typename ...Ts>
  static float maxf(Tfirst first, Ts... args) {
    // Handy to detect the cases where accidental double would get cast to a float implicitly
    static_assert((std::is_same_v<float, Tfirst>),    "All arguments must be float");
    static_assert((std::is_same_v<float, Ts> && ...), "All arguments must be float");

    helper firstWrapped(first);
    firstWrapped >> ( helper(args) >> ...);

    return firstWrapped.value;
  }


  template<float smooth>
  static float smoothMin(float a, float b) {
    // https://www.iquilezles.org/www/articles/smin/smin.htm

    constexpr float inverseSmooth = 0.5f/smooth;
    const float ab = a - b;

    const float progress = clamp(0.5f + ab * inverseSmooth, 0.0f, 1.0f);
    return mix(a, b, progress) - (smooth * progress * (1.0f - progress));
  }

  static float mix(float a, float b, float progress);

  static float clamp(float a, float min, float max);

};


#endif //RAYMARCHER_HELPER_H
