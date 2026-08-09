#pragma once

#include <vector>

#include "Event.h"

class EventManager
{
public:

    EventManager();
    ~EventManager();

    void Send(
        const Event& event);

    void Update();

    const std::vector<Event>&
        GetEvents() const;

    void Clear();

private:

    void Dispatch(
        const Event& event);

private:

    std::vector<Event> m_Events;
};