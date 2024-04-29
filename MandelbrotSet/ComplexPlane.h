#ifndef COMPLEX_PLANE_H
#define COMPLEX_PLANE_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ComplexPlane : public sf::Drawable {
public:
    ComplexPlane(int pixelWidth, int pixelHeight);
    void updateRender();
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2i mousePixel);
    void setMouseLocation(Vector2i mousePixel);
    void loadText(Text& text);
    size_t countIterations(sf::Vector2f coord);
    void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
    Vector2f mapPixelToCoords(Vector2i mousePixel);

private:
    // consts and state in private to not have scope issues
    const unsigned int MAX_ITER = 64;
    const float BASE_WIDTH = 4.0;
    const float BASE_HEIGHT = 4.0;
    const float BASE_ZOOM = 0.5;
    enum class State { CALCULATING, DISPLAYING };
    State m_State;

    // data vars but also draw here with override because needed override to not cause issues in main
    Vector2f m_plane_center;
    Vector2f m_plane_size;
    float m_aspectRatio;
    int m_zoomCount;
    int m_pixelWidth;
    int m_pixelHeight;
    VertexArray m_vArray;
    Vector2i m_mouselocation;
    void draw(RenderTarget& target, RenderStates states) const override;
};
#endif // COMPLEX_PLANE_H
