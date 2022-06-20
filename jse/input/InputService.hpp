#ifndef JSE_INPUT_SERVICE_H
#define JSE_INPUT_SERVICE_H

#include "input/InputTypes.hpp"
#include "core/math/Vector.hpp"

namespace jse::input {


	class InputService
	{
	public:
		virtual ~InputService() {};

		virtual void Update() = 0;
		virtual bool IsKeyDown(const Key aKey) = 0;

		virtual bool IsButtonDown(const MouseButton aButton) const = 0;
		virtual KeyPress GetKeyPressed() = 0;
		virtual KeyPress GetKeyReleased() = 0;
		virtual bool IsKeyPressed() = 0;
		virtual bool IsKeyReleased() = 0;

		virtual math::ivec2 GetMousePosition() const = 0;

		virtual void SetRelativeMouseMode(const bool a0) = 0;
		virtual math::ivec2 GetRelativeMousePosition() const = 0;

		virtual bool IsWheelUpMoved() const = 0;
		virtual bool IsWheelDownMoved() const = 0;

		bool IsMouseInputHandled() const { return isMouseInputHandled; }
		void SetMouseInputHandled(const bool a0) { isMouseInputHandled = a0; }
		bool IsKeyboardInputHandled() const { return isKeyboardInputHandled; }
		void SetKeyboardInputHandled(const bool a0) { isKeyboardInputHandled = a0; }

		float GetMouseSensitivity() const { return mouseSensitivity; }
		void SetMouseSensitivity(const float aX) { mouseSensitivity = aX; }

	private:
		bool isMouseInputHandled;
		bool isKeyboardInputHandled;
		float mouseSensitivity;
	};

	extern InputService* GetInputService();
}
#endif
