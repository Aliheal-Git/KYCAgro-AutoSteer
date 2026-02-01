// File: FilterCommon.hpp
// Path: App\Domain\FilterCommon.hpp
// Created by Alican on 2026-01-24

#ifndef APP_DOMAIN_FILTERCOMMON_HPP_
#define APP_DOMAIN_FILTERCOMMON_HPP_

#include <math.h>

namespace App::Domain {

    /**
     * @brief Structure for Olympic Average Filter.
     */
    struct OlympicAverageFilter {
        const uint8_t windowSize = 5;
        uint32_t max = 0;
        uint32_t min = 0xFFFFFFFF;
        uint64_t sum = 0;
        uint32_t average = 0;
        uint8_t count = 0;

        uint32_t filter(float sample) {
            sum += sample;
            if (sample > max) max = sample;
            if (sample < min) min = sample;
            if (++count >= windowSize){
                average = (sum - max - min) / (count - 2);
                reset();
            }
            return average;
        }   

        void reset() {
            max = 0;
            min = 0xFFFFFFFF;
            sum = 0;
            count = 0;
        }
    } oaFilter;

    /**
     * @brief Structure for Moving Average Filter.
     */
    struct MovingAverageFilter {
        static const int size = 16;
        uint32_t samples[size] = {0};
        uint64_t sum = 0;
        uint8_t index = 0;

        uint32_t filter(uint32_t sample) {
            sum -= samples[index];
            sum += sample;
            samples[index] = sample;
            if (++index >= size)
                index = 0;
            return sum / size;
        }
    } maFilter; 

    /**
     * @brief Structure for Outlier Filter.
     * alpha: Sensitivity factor for outlier detection.
     */
    struct OutlierFilter {
        float alpha = 2.5f;
        uint32_t prevSample = 0;

        uint32_t filter(uint32_t sample) {
            if (sample > (alpha*((prevSample + sample) / 2.0f)))
                return  (0.5*sample + 0.5*((prevSample + sample) / 2.0f));
            return sample;
        }

    };

    /**
     * @brief Structure for Kalman Filter.
     * errMeasure: Measurement error.
     * errEstimate: Estimate error.
     * q: Process noise covariance.
     */
    struct KalmanFilter {
        float errMeasure = 0;
        float errEstimate = 0;
        float q = 0;
        float currentEstimate = 0;
        float lastEstimate = 0;
        float kalmanGain = 0;

        float filter(float sample) {
            kalmanGain = errEstimate / (errEstimate + errMeasure);
            currentEstimate = lastEstimate + kalmanGain * (sample - lastEstimate);
            errEstimate = (1.0f - kalmanGain) * errEstimate + fabsf(lastEstimate - currentEstimate) * q;
            lastEstimate = currentEstimate;
            return currentEstimate;
        }
        
    };

} // namespace App::Domain

#endif // APP_DOMAIN_FILTERCOMMON_HPP_