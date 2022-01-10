//
// Created by anton.krug@gmail.com on 10/01/22.
// License: MIT
//

#ifndef RAYMARCHER_LUT_H
#define RAYMARCHER_LUT_H


template<std::size_t size, typename generator>
constexpr auto lut(generator&& f){
  using return_type = decltype(f(std::size_t{0}));
  std::array<return_type, size> return_content {};

  for(std::size_t i=0; i<size; i++){
    return_content[i] = f(i);
  }

  return return_content;
}


#endif //RAYMARCHER_LUT_H
