#pragma once


class Action
{
    int     m_id;
    int     m_type;
    bool    m_isActive;

public:

        Action();
        Action(int id, int type);

        const int&     getID();
        const int&     getType();
        bool&          isActive();

};