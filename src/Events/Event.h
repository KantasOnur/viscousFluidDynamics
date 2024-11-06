#pragma once
#include <glm/glm.hpp>

enum EventType
{
	None,
	WindowResize,
	MouseMove
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
	const glm::vec2 position;
	MouseMoveEvent(const float& x, const float& y) : position({x, y}) {};
	EventType getEventType() const override { return EventType::MouseMove; };
	static EventType getStaticEventType() { return EventType::MouseMove; };
};