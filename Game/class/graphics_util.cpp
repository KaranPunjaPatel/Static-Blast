#include "../header/graphics_util.hpp"


bool Vector2Equal(Vector2 first, Vector2 second) {
    return (first.x == second.x && first.y == second.y);
}

void getTime(double timeInSeconds, char timeStr[6]) {
    int minutes = static_cast<int>(timeInSeconds) / 60;
    int seconds = static_cast<int>(timeInSeconds) % 60;

    sprintf(timeStr, "%02d:%02d", minutes, seconds); // "MM:SS\0"
}

int normalizeAngle(int angle) {
    angle = std::fmod(angle, 360);
    if (angle > 180)
        angle -= 360;
    else if (angle <= -180)
        angle += 360;
    return angle;
}