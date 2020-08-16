#include <iostream>
#include "Gradient.h"

using namespace std;

Gradient test = Gradient();

int main()
{
  test.add(255, 0);
  test.add(120, 0.5);
  test.add(200, 1);

  for (float i = 0.0f; i <= 1.1f; i += 0.1f) {
    cout << test.valueAt(i) << endl;
  }

  return 0;
}

