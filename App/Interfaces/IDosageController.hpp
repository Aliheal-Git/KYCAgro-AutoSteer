// File: IDosageController.hpp
// Path: App\Interfaces\IDosageController.hpp
// Created by Alican on 2026-01-31

#ifndef APP_INTERFACES_IDOSAGECONTROLLER_HPP_
#define APP_INTERFACES_IDOSAGECONTROLLER_HPP_

namespace App::Interfaces {
    struct DosageControllerTaskResult {
        bool success;
        uint32_t delayMs;
    };

    class IDosageController {
        public:
            virtual ~IDosageController() {}
            virtual void enable() = 0;
            virtual void disable() = 0;
            virtual DosageControllerTaskResult tick() = 0;
            virtual void setTargetDosage(float dosage) = 0;
            virtual float getTargetDosage() const = 0;
    };

} // namespace App::Interfaces

#endif // APP_INTERFACES_IDOSAGECONTROLLER_HPP_