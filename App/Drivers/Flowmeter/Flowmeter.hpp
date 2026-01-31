#ifndef FLOWMETER_HPP
#define FLOWMETER_HPP

#include <cstdint>
#include "IFlowmeter.hpp"
#include "FilterCommon.hpp"

#define PUSLECOUNTPERDURATION 10

using namespace App::Interfaces::FlowmeterInterface;
using namespace App::Domain::FilterCommon;

namespace App::Drivers {

class Flowmeter : public IFlowmeter {
public:
    Flowmeter(uint16_t flowmeterFactor, float tankCapacity, float outlierFilterAlpha, float kalmanR, float kalmanP, float kalmanQ);
    float getFlowRate() const override;
    float getVolume() const override; 
    void onTimerOverflow() override;
    void onPulse(uint32_t time) override;
    
    void calculateDuration(uint32_t time);
    void calculateFrequency(uint32_t time);
    void calculateFlow();

private:
    volatile uint32_t pulseWidth = 0;
    volatile uint16_t overflowCount = 0;
    volatile uint32_t lastCaptureTime = 0;
    volatile float rawFlowrate = 0.0f;
    volatile float flowrate = 0.0f;
    volatile float volume = 0.0f;

    uint16_t flowmeterK;
    float tankCapacity;
    
    OutlierFilter outlierFilter;
    MovingAverageFilter maFilter;
    OlympicAverageFilter oaFilter;
    KalmanFilter kalmanFilter;
};

} // namespace App::Drivers

#endif // FLOWMETER_HPP
