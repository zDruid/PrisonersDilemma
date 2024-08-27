#include "Utils.h"

#include <random>
using namespace std;

static unsigned int _seed = 3278;
// static unsigned int _seed = random_device{}();
static mt19937 _generator{_seed};

int GetRandom(int min, int max) {
  uniform_int_distribution<int> uniform(min, max-1);
  return uniform(_generator);
}