#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    Position(int x = 0, int y = 0);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

private:
    int x;
    int y;
};

#endif // POSITION_H
