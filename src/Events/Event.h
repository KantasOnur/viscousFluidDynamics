#pragma once
#include <glm/glm.hpp>
#include "../Core/OpenGL.h"

enum EventType
{
	None,
	WindowResize,
	MouseMove,
	WindowUpdate
};

class Event
{
public:
	virtual EventType getEventType() const { return EventType::None; };
	static EventType getStaticEventType() { return EventType::None; };
};

class WindowResizeEvent : public Event
{
public:
	const float width, height;
	WindowResizeEvent(const float& w, const float& h) : width(w), height(h) {};
	EventType getEventType() const override { return EventType::WindowResize; };
	static EventType getStaticEventType() { return EventType::WindowResize; };
};

class MouseMoveEvent : public Event
{
public:
	const glm::vec2 mousePos;
	const float width, height;
	GLFWwindow* window;
	MouseMoveEvent(const float& x, const float& y, const float& width, const float& height, GLFWwindow* window)
		: mousePos({ x, y }),
		  width(width),
		  height(height),
		  window(window)
	{};

	EventType getEventType() const override { return EventType::MouseMove; };
	static EventType getStaticEventType() { return EventType::MouseMove; };
};

class WindowUpdateEvent : public Event
{
public:
	GLFWwindow* window;
	WindowUpdateEvent(GLFWwindow* window) : window(window) {};
	EventType getEventType() const override { return EventType::WindowUpdate; };
	static EventType getStaticEventType() { return EventType::WindowUpdate; };
};