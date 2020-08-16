#include <vector>
#include <iterator>
#include <iostream>

#include "GradientPoint.h"

class Gradient {
  protected:
    std::vector<GradientPoint> points;

  public:
    Gradient() {
      
    }

    void add(
      float value,
      float position
    ) {
      GradientPoint point(
        value,
        position
      );

      this->points.push_back(point);
    }

    int length() {
      return this->points.size();
    }

    float valueAt(
      float position
    ) {
      if (this->points.empty()) {
        return 0.0f;
      }

      bool foundLeft  = false;
      bool foundRight = false;

      GradientPoint * currentPoint;
      GradientPoint * leftPoint;
      GradientPoint * rightPoint;

      GradientPoint * firstPoint = &this->points.front();
      GradientPoint * lastPoint  = &this->points.back();

      if (firstPoint->position >= position) {
        return firstPoint->value;
      }

      if (lastPoint->position <= position) {
        return lastPoint->value;
      }

      std::vector<GradientPoint>::iterator i = this->points.begin();

      while (
        !foundLeft ||
        !foundRight
      ) {
        currentPoint = &*i;

        // std::cout << "Current Point: " + std::to_string(currentPoint->position) << std::endl;

        if (currentPoint->position <= position) {
          leftPoint = currentPoint;
          foundLeft = true;
        }
        
        if (currentPoint->position >= position) {
          rightPoint = currentPoint;
          foundRight = true;
        } else {
          ++i;
        }

        if (i == this->points.end()) {
          rightPoint = leftPoint;
          foundRight = true;
        }
      }

      // std::cout << "Left:  " + std::to_string(leftPoint->position) << std::endl;
      // std::cout << "Right: " + std::to_string(rightPoint->position) << std::endl;

      return leftPoint->value + ((rightPoint->value - leftPoint->value) * ((position - leftPoint->position) / rightPoint->position));
    }
};

