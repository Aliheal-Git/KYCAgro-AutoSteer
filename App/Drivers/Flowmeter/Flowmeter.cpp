#include "Flowmeter.hpp"

using namespace App::Drivers;

/**
 * @brief Construct a new Flowmeter object
 * @param flowmeterFactor The flowmeter constant (K factor)
 * @param tankCapacity The capacity of the tank
 * @param outlierFilterAlpha The alpha value for the outlier filter
 * @param kalmanR The measurement noise covariance for the Kalman filter
 * @param kalmanP The estimation error covariance for the Kalman filter
 * @param kalmanQ The process noise covariance for the Kalman filter
 */
Flowmeter::Flowmeter(uint16_t flowmeterFactor, float tankCapacity, float outlierFilterAlpha, float kalmanR, float kalmanP, float kalmanQ) : flowmeterK(flowmeterFactor), tankCapacity(tankCapacity) {
    volume = tankCapacity;
    outlierFilter.alpha = outlierFilterAlpha;
    kalmanFilter.errMeasure = kalmanR;
    kalmanFilter.errEstimate = kalmanP;
    kalmanFilter.q = kalmanQ;
}

/**
 * @brief Get the current flow rate
 * @return The current flow rate
 */
float Flowmeter::getFlowRate() const {
    return flowrate;
}

/**
 * @brief Get the current volume in the tank
 * @return The current volume
 */
float Flowmeter::getVolume() const {
    return volume;
}

/**
 * @brief Handle timer overflow event
 */
void Flowmeter::onTimerOverflow(){
	overflowCount++;
    if (overflowCount > 30){
        flowrate = 0;
    }
}

/**
 * @brief Handle pulse event from flowmeter
 * @param time The captured timer value at pulse event
 */
void Flowmeter::onPulse(uint32_t time){
    calculateDuration(overflowCount*0xFFFF + time);
	calculateFlow();
    overflowCount = 0;
}

/**
 * @brief Calculate duration between pulses with outlier, moving average, and Olympic average filtering
 * @param time The current captured time
 * @result Updates pulseWidth with the filtered duration
 */
void Flowmeter::calculateDuration(uint32_t time){
    uint32_t duration = 0;
    duration = outlierFilter.filter(time - lastCaptureTime);
    duration = maFilter.filter(duration);
    duration = oaFilter.filter(duration);
    pulseWidth = duration;
    lastCaptureTime = time;
}

/**
 * @brief Calculate flow rate based on pulse width and flowmeter constant
 * @result Updates flowrate and volume   
 */
void Flowmeter::calculateFlow(){
	rawFlowrate = ((1e6 / pulseWidth) * PUSLECOUNTPERDURATION / flowmeterK) * 60.0f;
    flowrate = kalmanFilter.filter(rawFlowrate);
    volume -= 10.0f / flowmeterK;
}