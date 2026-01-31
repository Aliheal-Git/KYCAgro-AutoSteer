// File: IPage.hpp
// Path: App\Interfaces\IPage.hpp
// Created by Alican on 2026-01-24

#ifndef APP_INTERFACES_IPAGE_HPP_
#define APP_INTERFACES_IPAGE_HPP_

#include "IWindow.hpp"
#include "ButtonCommon.hpp"
#include <sys/types.h>

using namespace App::Interfaces;
using namespace App::Domain;

namespace App::Interfaces {
    enum class PageNavRequest : uint8_t {
        NONE = 0,
        HOME = 1,
        NEXT = 2,
        PREVIOUS = 3,
        SETTINGS = 4,
        MAIN = 5
    };

    struct PageFuncResult {
        PageNavRequest navRequest;
        uint32_t delayMs;
    };

    class IPage {
        public:
            IPage(IWindow* win) : parentWindow(win) {}
            virtual ~IPage() {}
            virtual PageFuncResult render() = 0;
            virtual PageFuncResult handleButtonInput(ButtonQueueEvent event) = 0;
            virtual PageFuncResult task(void) { return {PageNavRequest::NONE, 0xFFFFFFFF}; };
        protected:
            IWindow *parentWindow;
            uint8_t renderStep = 0;
            uint8_t taskStep = 0;
    };
}   // namespace App::Interfaces

#endif // APP_INTERFACES_IPAGE_HPP_