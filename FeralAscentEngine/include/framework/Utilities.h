#ifndef UTILITIES_H
#define UTILITIES_H

constexpr float SCALE = 30.0f; // Conversion factor: 30 pixels = 1 meter

// Convert pixels to meters for Box2D
inline float PixelsToMeters(float pixels) {
    return pixels / SCALE;
}

// Convert meters to pixels for SFML
inline float MetersToPixels(float meters) {
    return meters * SCALE;
}

#endif // UTILITIES_H
