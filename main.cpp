#include <array>

#include <gsl/gsl>

#include "raylib-cpp.hpp"

template<int N>
int BinaryToDecimal(const std::array<bool, N> &p_digits)
{
    int sum{ 0 };
    
    int i{ 0 };
    for (auto it{ p_digits.rbegin() }; it != p_digits.rend(); ++it)
    {
        sum += (*it) * std::pow(2, i);
        ++i;
    }

    return sum;
}

int main()
{
    constexpr int numberOfRects{ 8 };
    constexpr int frameSize{ 100 };

    rl::Window window{ frameSize * numberOfRects, frameSize + 50, "BinToDec" };
    std::array<rl::Rectangle, numberOfRects> rects;
    std::array<bool, numberOfRects> digits;

    const std::string subText{ "Decimal is " };
    std::string decimal{ "0" };

    for (gsl::index i{ 0 }; auto &rect : rects)
    {
        rect.SetSize(frameSize - 20, frameSize - 20);
        rect.SetX(10 + frameSize * i);
        rect.SetY(10);
        digits[i] = 0;
        ++i;
    }

    rl::Rectangle frame{ 0.f, 0.f, frameSize * 1.f, frameSize * 1.f };

    while (!window.ShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_LEFT) && frame.GetX() > 0)
        {
            frame.SetX(frame.GetX() - 100);
        }
        else if (IsKeyPressed(KEY_RIGHT) && frame.GetX() < window.GetWidth() - 100)
        {
            frame.SetX(frame.GetX() + 100);
        }
        else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN))
        {
            digits[frame.GetX() / 100] = !digits[frame.GetX() / 100];
            decimal = std::to_string(BinaryToDecimal<numberOfRects>(digits));
        }

        // Draw
        window.BeginDrawing();

            window.ClearBackground();

            frame.Draw(rl::Color::Red());

            for (gsl::index i{ 0 }; auto &rect : rects)
            {
                const std::string digit{ digits[i] ? "1" : "0" };
                rect.Draw(rl::Color::RayWhite());
                rl::DrawText(
                    digit, rect.GetX() + (rect.GetWidth() - rl::MeasureText(digit, 50)) / 2, rect.GetY() + (rect.GetHeight() - 50) / 2, 50, 
                    rl::Color::Black()
                );
                ++i;
            }

            rl::DrawText(subText + decimal, (window.GetWidth() - rl::MeasureText(subText + decimal, 50)) / 2, frameSize, 50, rl::Color::RayWhite());

        window.EndDrawing();
    }

    return 0;
}
