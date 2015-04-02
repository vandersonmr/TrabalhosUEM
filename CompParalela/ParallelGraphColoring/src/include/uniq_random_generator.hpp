#ifndef UNIQRANDOMGENERATOR_H
#define UNIQRANDOMGENERATOR_H
namespace {
  //Linear feedback shift register
  //http://en.wikipedia.org/wiki/Linear_feedback_shift_register
  class uniqRandomGenerator {
    private:
      static unsigned short lfsr;
      static unsigned       bit;
    public:
      static unsigned rand() {
        bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) 
                      ^ (lfsr >> 5) ) & 1;
        return lfsr =  (lfsr >> 1) | (bit << 15);
      };
  };

  unsigned short uniqRandomGenerator::lfsr = 0xACE1u;
  unsigned       uniqRandomGenerator::bit  = 0;
}
#endif
