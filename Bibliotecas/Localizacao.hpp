#pragma once

class Localizacao
{
public:
    double x;
    double y;

    Localizacao() = default;
    Localizacao(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    ~Localizacao() = default;
};