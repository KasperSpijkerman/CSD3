#pragma once
#include <iostream>

class Oscillator
{
public:
  Oscillator(float frequency = 0, float amplitude = 0);
  ~Oscillator();

  // allow to set samplerate after initialization
  void setSamplerate(float samplerate);
  // return the current sample
  float getSample();

  // getters and setters
  void setFrequency(float frequency);
  void setAmplitude(float amplitude);
  float getFrequency();
  // go to next sample
  void tick();
  virtual void calculate() = 0;

protected:
  // abstract method calculate - needs to be overriden by subclasses
  float frequency;
  float amplitude;
  float phase;
  // sample contains the current sample
  float sample;
  float samplerate;
};
