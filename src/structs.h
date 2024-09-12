struct vec2
{
    vec2(float x, float y) : x(x), y(y) {}

    float x;
    float y;
    vec2 operator+(const vec2 &other) const
    {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator*(float scalar) const
    {
        return vec2(x * scalar, y * scalar);
    }
    vec2 &operator+=(const vec2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
      float distanceTo(const vec2& other) const {
        float dx = other.x - x;
        float dy = other.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }
};
