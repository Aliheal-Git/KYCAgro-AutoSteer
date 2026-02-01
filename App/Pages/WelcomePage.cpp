#include "Page.hpp"

#include <cstdint>

using namespace App::Domain;
using namespace App::Pages;

PageFuncResult WelcomePage::render(){
	constexpr uint8_t iterationCount = 8;
	this->parentWindow->clearWindow();
	for (; renderStep < iterationCount; renderStep++) {
		this->parentWindow->writeCustomCharacter(customCharIndex::leftTriangleIndex, 2, renderStep+1);
		this->parentWindow->writeCustomCharacter(customCharIndex::rightTriangleIndex, 2, MAX_COLUMNS-3-renderStep);
		return {PageNavRequest::NONE, 400};
	};
	if (renderStep == iterationCount) {
		this->parentWindow->writeCustomCharacter(customCharIndex::heartIndex, 2, 9);
		return {PageNavRequest::NONE, 400};
		renderStep++;
	}

	return {PageNavRequest::HOME, 0};
}
