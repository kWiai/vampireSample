#pragma once

class GameObject;

enum class EventType
{
    None,

    Damage,
    Death,

    Attack,

    Interact,

    ButtonPressed,

    DialogueStarted,
    DialogueFinished
};

struct Event
{
    EventType Type = EventType::None;

    GameObject* Sender = nullptr;
    GameObject* Target = nullptr;

    float Value = 0.0f;
};