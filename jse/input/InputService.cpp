#include "input/InputService.hpp"
#include "input/SDL/InputServiceSDL.hpp"

namespace jse {

	static InputServiceSDL inputServiceLocal;
	static InputService* inputService = &inputServiceLocal;

	InputService* GetInputService() { return inputService; }
}