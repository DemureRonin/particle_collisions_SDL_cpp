struct vec2
{
    vec2(float x, float y) : x(x), y(y) {}

    float x;
    float y;
    vec2 operator+(const vec2 &other) const
    {
        return vec2(x + other.x, y + other.y);
    }
    vec2 operator-(const vec2 &other) const
    {
        return vec2(x - other.x, y - other.y);
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
    vec2 &operator-=(const vec2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    float distanceTo(const vec2 &other) const
    {
        float dx = other.x - x;
        float dy = other.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }
    float magnitude() const
    {
        return std::sqrt(x * x + y * y);
    }

    vec2 normalize() const
    {
        float mag = magnitude();
        if (mag > 0)
        {
            return vec2(x / mag, y / mag);
        }
        return vec2(0, 0);
    }
    float dot(const vec2 &other) const
    {
        return x * other.x + y * other.y;
    }
};
struct color
{
    uint8_t r, g, b, a;

    color(uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    static color from_HSL(float hue, float saturation, float lightness)
    {
        float c = (1.0f - std::fabs(2.0f * lightness - 1.0f)) * saturation;
        float x = c * (1.0f - std::fabs(std::fmod(hue / 60.0f, 2) - 1.0f));
        float m = lightness - c / 2.0f;

        float rPrime = 0, gPrime = 0, bPrime = 0;
        if (0 <= hue && hue < 60)
        {
            rPrime = c;
            gPrime = x;
            bPrime = 0;
        }
        else if (60 <= hue && hue < 120)
        {
            rPrime = x;
            gPrime = c;
            bPrime = 0;
        }
        else if (120 <= hue && hue < 180)
        {
            rPrime = 0;
            gPrime = c;
            bPrime = x;
        }
        else if (180 <= hue && hue < 240)
        {
            rPrime = 0;
            gPrime = x;
            bPrime = c;
        }
        else if (240 <= hue && hue < 300)
        {
            rPrime = x;
            gPrime = 0;
            bPrime = c;
        }
        else if (300 <= hue && hue < 360)
        {
            rPrime = c;
            gPrime = 0;
            bPrime = x;
        }

        uint8_t r = static_cast<uint8_t>((rPrime + m) * 255.0f);
        uint8_t g = static_cast<uint8_t>((gPrime + m) * 255.0f);
        uint8_t b = static_cast<uint8_t>((bPrime + m) * 255.0f);

        return color(r, g, b);
    }
};