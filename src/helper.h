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
    // Handy to detect the cases where accidental double would get casted to a float implicitly
    static_assert((std::is_same_v<float, Tfirst>),    "All arguments must be float");
    static_assert((std::is_same_v<float, Ts> && ...), "All arguments must be float");

    helper firstWrapped(first);
    firstWrapped >> ( helper(args) >> ...);

    return firstWrapped.value;
  }


  static float clamp(float a, float min, float max);

};


#endif //RAYMARCHER_HELPER_H
