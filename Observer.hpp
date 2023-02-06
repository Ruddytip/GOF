#pragma once

// Клиент
class IObserver{
public:
    virtual void HandleInsideCheck() = 0;
};

// Сервер
class IObservable{
public:
    virtual void addObserver(IObserver* obs) = 0;
    virtual void eraseObserver(IObserver* obs) = 0;
    virtual void update() = 0;
};

