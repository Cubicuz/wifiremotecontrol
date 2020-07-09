#include <functional>
#include "Rotary.h"

class RotaryWrapper{
  public:
    RotaryWrapper(char _pin1, char _pin2);
    RotaryWrapper(char _pin1, char _pin2, std::function<void (void)> f_cw, std::function<void (void)> f_ccw);
    RotaryWrapper(char _pin1, char _pin2, std::function<void (unsigned char)> f);
    
    unsigned char process();
    void setFunction(std::function<void (unsigned char)> f);
    void setFunctionCW(std::function<void (void)> f_cw);
    void setFunctionCCW(std::function<void (void)> f_ccw);


  private:
    Rotary rotary;
    std::function<void (void)> f_cw;
    std::function<void (void)> f_ccw;
    std::function<void (unsigned char)> f;


  
};