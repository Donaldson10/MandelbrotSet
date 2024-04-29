#include "ComplexPlane.h"
#include <iostream>
#include <complex>

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
    : m_pixelWidth(pixelWidth), m_pixelHeight(pixelHeight), m_zoomCount(0), m_State(State::CALCULATING)
{
    m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
    m_plane_center = { 0.0f, 0.0f };
    m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };

    m_vArray.setPrimitiveType(sf::Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::updateRender() {
    if (m_State == State::CALCULATING) {
        for (int i = 0; i < m_pixelHeight; ++i) {
            for (int j = 0; j < m_pixelWidth; ++j) {
                m_vArray[j + i * m_pixelWidth].position = { static_cast<float>(j), static_cast<float>(i) };

                Vector2f coord = mapPixelToCoords({ j, i });
                size_t iter = countIterations(coord);

                Uint8 r, g, b;
                iterationsToRGB(iter, r, g, b);

                m_vArray[j + i * m_pixelWidth].color = Color(r, g, b);
            }
        }
        m_State = State::DISPLAYING;
    }
}

void ComplexPlane::zoomIn() {
    m_zoomCount++;
    float zoomFactor = std::pow(BASE_ZOOM, m_zoomCount);
    m_plane_size.x = BASE_WIDTH * zoomFactor;
    m_plane_size.y = BASE_HEIGHT * m_aspectRatio * zoomFactor;
    m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut() {
    if (m_zoomCount > 0) {
        m_zoomCount--;
        float zoomFactor = std::pow(BASE_ZOOM, m_zoomCount);
        m_plane_size.x = BASE_WIDTH * zoomFactor;
        m_plane_size.y = BASE_HEIGHT * m_aspectRatio * zoomFactor;
        m_State = State::CALCULATING;
    }
}

void ComplexPlane::setCenter(Vector2i mousePixel) {
    m_plane_center = mapPixelToCoords(mousePixel);
    m_State = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
    m_mouselocation = mousePixel;
}

void ComplexPlane::loadText(Text& text) {
    stringstream ss;
    ss << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << std::endl;
    ss << "Mouse Location: (" << m_mouselocation.x << ", " << m_mouselocation.y << ")" << endl;
    ss << "Left-click to Zoom in" << endl << "Right-click to Zoom out" << endl;
    text.setString(ss.str());
}

size_t ComplexPlane::countIterations(Vector2f coord) {
    complex<float> c(coord.x, coord.y);
    complex<float> z(0, 0);
    size_t itertocount = 0;

    while (abs(z) < 2.0 && itertocount < MAX_ITER) {
        z = z * z + c;
        itertocount++;
    }

    return itertocount;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
    if (count == MAX_ITER) {
        r = 0;
        g = 0;
        b = 0;
    }
    else {
        // red for proof of conc
        r = static_cast<sf::Uint8>(255 * (count / static_cast<float>(MAX_ITER)));
        g = 0;
        b = 0;
    }
}

sf::Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
    float x = ((mousePixel.x - 0) / static_cast<float>(m_pixelWidth)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);
    float y = ((mousePixel.y - m_pixelHeight) / static_cast<float>(0 - m_pixelHeight)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);
    return { x, y };
}

void ComplexPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_vArray);
}
