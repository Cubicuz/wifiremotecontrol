#include "RotaryWrapper.h"

RotaryWrapper::RotaryWrapper(char _pin1, char _pin2)
  : rotary(_pin1, _pin2)
{

}
RotaryWrapper::RotaryWrapper(char _pin1, char _pin2, std::function<void (void)> f_cw, std::function<void (void)> f_ccw)
  : RotaryWrapper(_pin1, _pin2)
{
  this->f_cw = f_cw;
  this->f_ccw = f_ccw;
}
RotaryWrapper::RotaryWrapper(char _pin1, char _pin2, std::function<void (unsigned char)> f)
  : RotaryWrapper(_pin1, _pin2)
{
  this->f = f;
}

void RotaryWrapper::setFunction(std::function<void (unsigned char)> f){
  this->f = f;
}
void RotaryWrapper::setFunctionCW(std::function<void (void)> f_cw){
  this->f_cw = f_cw;
}
void RotaryWrapper::setFunctionCCW(std::function<void (void)> f_ccw){
  this->f_ccw = f_ccw;
}

unsigned char RotaryWrapper::process(){
  unsigned char ret = rotary.process();
  switch (ret)
  {
  case DIR_CW:
    if (f_cw){
      f_cw();
    }
    if (f) {
      f(DIR_CW);
    }
    break;
  case DIR_CCW:
    if (f_ccw){
      f_ccw();
    }
    if (f){
      f(DIR_CCW);
    }
    break;
  default:
    break;
  }
  return ret;
}
