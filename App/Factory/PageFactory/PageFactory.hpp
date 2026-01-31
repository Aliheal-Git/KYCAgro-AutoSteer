// File: PageFactory.hpp
// Path: App\Factory\PageFactory\PageFactory.hpp
// Created by Alican on 2026-01-24

#ifndef APP_FACTORY_PAGEFACTORY_PAGEFACTORY_HPP_
#define APP_FACTORY_PAGEFACTORY_PAGEFACTORY_HPP_

namespace App::Factory::PageFactory {
    class PageFactory {
    public:
        static IPage* createPage(uint8_t pageId, IWindow* parentWindow);
    };
} // namespace App::Factory::PageFactory

#endif // APP_FACTORY_PAGEFACTORY_PAGEFACTORY_HPP_