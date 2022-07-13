#ifndef _INCLUDE_LOOP_HPP_
#define _INCLUDE_LOOP_HPP_

class Loop {
  public:
    Loop();
    ~Loop();

    bool IsRunning();

  private:
    bool running;
};

Loop::Loop() {

}

Loop::~Loop() {

}

bool Loop::IsRunning() {
  return running;
}

#endif
