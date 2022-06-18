#include "input/InputService.hpp"
#include "input/SDL/InputServiceSDL.hpp"

namespace jse::input {

	static InputServiceSDL inputServiceLocal;
	static InputService* inputService = &inputServiceLocal;

	InputService* GetInputService() { return inputService; }
}