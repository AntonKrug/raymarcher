//
// Created by AntonKrug on 26/12/21.
//

#ifndef RAYMARCHER_COLOR_H
#define RAYMARCHER_COLOR_H


struct Color {
  float r, g, b;
  int cumulativeAdditionsCount = 0;

  Color(float init = 0.0f);

  Color(float rInit, float gInit, float bInit = 0.0f);

  Color operator+(Color second);

  void operator+=(Color second);

  Color operator*(float scalar);

  Color multiply(float scalar);

};


#endif //RAYMARCHER_COLOR_H
