#include "renderer.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL_opengl.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL_opengl.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL_opengl.h"
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

#define PI2 (2*M_PI)
#define ELLIPSEPOINTS 128

void Renderer::SetOrigin(double x, double y) {
    glLoadIdentity();
    glTranslated(-x, -y, 0.0f);
}

void Renderer::SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
    glScissor(x, y, width, height);
}

void Renderer::SetBlendMode(int blend) {
    switch ( blend ) {
    case BLEND_SOLID:
        glBlendFunc(GL_ONE, GL_ZERO);
        break;
    case BLEND_ALPHA:
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        break;
    case BLEND_ADD:
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        break;
    case BLEND_MODULATE:
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        break;
    }
}

void Renderer::SetColor(int color) {
    glColor4ub(Renderer::Red(color), Renderer::Green(color), Renderer::Blue(color), Renderer::Alpha(color));
}

int Renderer::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    return (alpha << 24) + (red << 16) + (green << 8) + blue;
}

unsigned char Renderer::Red(int color) {
    return (color & 0x00FF0000) >> 16;
}

unsigned char Renderer::Green(int color) {
    return (color & 0x0000FF00) >> 8;
}

unsigned char Renderer::Blue(int color) {
    return (color & 0x000000FF);
}

unsigned char Renderer::Alpha(int color) {
    return (color & 0xFF000000) >> 24;
}

void Renderer::DrawPoint(double x, double y) {
    GLdouble vertices[] = {x, y};
    GLdouble texCoords[] = {0, 0};
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_POINTS, 0, 1);
}

void Renderer::DrawLine(double x1, double y1, double x2, double y2) {
    GLdouble vertices[] = {x1, y1, x2, y2};
    GLdouble texCoords[] = {0, 0, 0, 0};
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_LINES, 0, 2);
}

void Renderer::DrawRect(double x, double y, double width, double height) {
    GLdouble vertices[] = {x, y, x+width, y, x, y+height, x+width, y+height};
    GLdouble texCoords[] = {0, 0, 0, 0, 0, 0, 0, 0};
    glBindTexture(GL_TEXTURE_2D, 0);
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Renderer::DrawEllipse(double x, double y, double xrad, double yrad) {
    int i = 0;
    GLdouble vertices[ELLIPSEPOINTS*2];
    GLdouble texCoords[ELLIPSEPOINTS*2];

    for ( i = 0; i < ELLIPSEPOINTS; i++ ) {
        vertices[i*2] = x + (cos(i * PI2 / ELLIPSEPOINTS) * xrad);
        vertices[i*2+1] = y + (sin(i * PI2 / ELLIPSEPOINTS) * yrad);
    }

    memset(texCoords, 0, ELLIPSEPOINTS*2*sizeof(GLdouble));

    glBindTexture(GL_TEXTURE_2D, 0);
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSEPOINTS);
}
