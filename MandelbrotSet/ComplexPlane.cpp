#include "ComplexPlane.h"
#include <iostream>	
#include <complex>

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size.x = pixelWidth;
	m_pixel_size.y = pixelHeight;
	m_aspectRatio = VideoMode::getDesktopMode().height/VideoMode::getDesktopMode().width;
	m_plane_center.x = 0;
	m_plane_center.y = 0;
	m_plane_size.x = BASE_WIDTH;
	m_plane_size.y = BASE_HEIGHT * m_aspectRatio;
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {

	target.draw(m_vArray);
}

void ComplexPlane::updateRender() {
	if (m_state == CALCULATING) {
		for (int i = 0; i < m_pixel_size.y; i++) {
			for (int j = 0; j < m_pixel_size.x; j++) {
				Vector2i temp;
				temp.x = j;
				temp.y = i;
				m_vArray[j + i * m_pixel_size.x].position = { (float)j,(float)i };
				size_t iterations = countIterations(mapPixelToCoords(temp));
				Uint8 r, g, b;
				iterationsToRGB(iterations, r, g, b);
				m_vArray[j + i * m_pixel_size.x].color = { r,g,b };
				m_state = DISPLAYING;
			}
		}
	}
}

void ComplexPlane::zoomIn() {
	m_zoomCount++;
	int x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int y = BASE_HEIGHT * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size.x = x;
	m_plane_size.y = y;
	m_state = CALCULATING;
}

void ComplexPlane::zoomOut() {
	m_zoomCount--;
	int x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int y = BASE_HEIGHT * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size.x = x;
	m_plane_size.y = y;
	m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) {

	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousPixel) {

	m_mouseLocation = mapPixelToCoords(mousPixel);
}

void ComplexPlane::loadText(Text& text) {

	stringstream saz;
	saz << "Mandelbrot Set" << endl;
	saz << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << endl;
	Vector2f mousecords = mapPixelToCoords(Mouse::getPosition());
	saz << "Cursor: (" << mousecords.x << ", " << mousecords.y << ")" << endl;
	saz << "Left-click to Zoom in" << endl << "Right-click to Zoom out";
	text.setString(saz.str());
}

size_t ComplexPlane::countIterations(Vector2f coord) {

	complex<float> c(coord.x, coord.y);
    complex<float> z(0, 0);
    size_t itertorun= 0;

    while (abs(z) < 2.0 && itertorun < MAX_ITER) {
        z = z * z + c;
        itertorun++;
    }
    return itertorun;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {

		if (count == MAX_ITER)
		{
			r = 0; g = 0; b = 0;
		}
		else {
			float coloredCount = static_cast<float>(count) / static_cast<float>(MAX_ITER);

			if (coloredCount < 0.2f)
			{ //purple 
				r = 128 + static_cast<Uint8>(127 * coloredCount / 0.2f);
				g = 0;
				b = 255 - static_cast<Uint8>(127 * coloredCount / 0.2f);
			}
			else if (coloredCount < 0.4f)
			{ // turqoised
				r = 0;
				g = 255;
				b = static_cast<Uint8>(255 * (coloredCount - 0.2f) / 0.2f);
			}
			else if (coloredCount < 0.6f)
			{ // green
				r = 0;
				g = 255 - static_cast<Uint8>(255 * (coloredCount - 0.6f) / 0.2f);
				b = 0;
			}
			else if (coloredCount < 0.8f)
			{ // yeller
				r = static_cast<Uint8>(255 * (coloredCount - 0.6f) / 0.2f);
				g = 255;
				b = 0;
			}
			else
			{ // red for higher counts
				r = 255;
				g = static_cast<Uint8>(255 * (1.0f - coloredCount) / 0.2f);
				b = 0;
			}
		}
	}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
	Vector2f plane;
	plane.x = ((mousePixel.x - 0) / (m_pixel_size.x - 0)) * (m_plane_size.y - m_plane_size.x) + (m_plane_size.x);
	plane.y = ((mousePixel.y - 0) / (m_pixel_size.y - 0)) * (m_plane_size.y - m_plane_size.x) + (m_plane_size.x);

	return plane;
}