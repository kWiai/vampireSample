#pragma once

class Tile
{
public:

    Tile()
    {
        m_Id = -1;
        m_Solid = false;
        m_Visible = true;
    }

    explicit Tile(int id)
    {
        m_Id = id;
        m_Solid = false;
        m_Visible = true;
    }

    void SetId(int id)
    {
        m_Id = id;
    }

    int GetId() const
    {
        return m_Id;
    }

    void SetSolid(bool solid)
    {
        m_Solid = solid;
    }

    bool IsSolid() const
    {
        return m_Solid;
    }

    void SetVisible(bool visible)
    {
        m_Visible = visible;
    }

    bool IsVisible() const
    {
        return m_Visible;
    }

private:

    int m_Id;

    bool m_Solid;

    bool m_Visible;
};