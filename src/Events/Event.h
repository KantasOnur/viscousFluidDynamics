#pragma once

enum EventType
{
	None,
	WindowResize
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