#include "image.h"
#include "screen.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL_opengl.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL_opengl.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL_opengl.h"
#endif
#include <math.h>
#include <stdlib.h>
#include <string.h>

Image::Image(const Pixmap* pixmap, int hframes, int vframes) {
    _Init(pixmap, hframes, vframes);
}

Image::Image(const String& filename, int hframes, int vframes) {
    Pixmap* pixmap = new Pixmap(filename);
    _Init(pixmap, hframes, vframes);
    delete pixmap;
}

Image::~Image() {
    if ( gltex != 0 ) glDeleteTextures(1, &gltex);
}

void Image::Draw(double x, double y, int frame, double width, double height, double angle, double rectx, double recty, double rectwidth, double rectheight) {
    double u0 = 0.0;
    double v0 = 0.0;
    double u1 = 1.0;
    double v1 = 1.0;

    if ( rectx != 0.0 ) u0 = rectx / Width();
    if ( recty != 0.0 ) v0 = recty / Height();
    if ( rectwidth != 0.0 ) {
        u1 = rectwidth / Width();
        if ( width == 0.0 ) width = rectwidth;
    } else {
        if ( width == 0.0 ) width = Width();
    }
    if ( rectheight != 0.0 ) {
        v1 = rectheight / Height();
        if ( height == 0.0 ) height = rectheight;
    } else {
        if ( height == 0.0 ) height = Height();
    }

    int row = (int)frame/hframes;
    int column = frame % hframes;
    GLdouble hxscale = width / Width();
    GLdouble hyscale = height / Height();
    GLdouble ustep = lastu / hframes;
    GLdouble vstep = lastv / vframes;
    GLdouble ubegin = u0*ustep + ustep*column;
    GLdouble vbegin = v0*vstep + vstep*row;
    GLdouble uend = ubegin + ustep*u1;
    GLdouble vend = vbegin + vstep*v1;
    GLdouble x0 = -handlex*hxscale;
    GLdouble y0 = -handley*hyscale;
    GLdouble x1 = x0 + width;
    GLdouble y1 = y0 + height;
    GLdouble vertices[] = {x0, y0,  x1, y0,  x0, y1,  x1, y1};
    GLdouble texcoords[] = {ubegin, vbegin,  uend, vbegin,  ubegin, vend,  uend, vend};

    glPushMatrix();
    glTranslated(x, y, 0);
    glRotated(angle, 0, 0, -1);
    glBindTexture(GL_TEXTURE_2D, gltex);
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void Image::DrawTiled(double offsetx, double offsety, double x, double y, double width, double height) {
    GLdouble ubegin = offsetx / Width();
    GLdouble vbegin = offsety / Height();
    GLdouble uend = (offsetx+width) / Width();
    GLdouble vend = (offsety+height) / Height();
    GLdouble vertices[] = {0, 0, width, 0, 0, height, width, height};
    GLdouble texcoords[] = {ubegin, vbegin,  uend, vbegin,  ubegin, vend,  uend, vend};

    glPushMatrix();
    glTranslated(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, gltex);
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void Image::_Init(const Pixmap* pixmap, int hframes, int vframes) {
    // Create image object
    this->hframes = hframes;
    this->vframes = vframes;
    pixmap ? width = pixmap->Width() : width = 0;
    pixmap ? height = pixmap->Height() : height = 0;
    handlex = 0;
    handley = 0;
    lastu = 1.0;
    lastv = 1.0;
    gltex = 0;

    // Return if pixmap is not loaded
    if ( !pixmap ) return;
    if ( !pixmap->IsLoaded() ) return;

    // Ensure buffer is power of two
    unsigned char* buffer = (unsigned char*)pixmap->ConstBuffer();
    unsigned int w = (unsigned int)pow(2, ceil(log(width)/log(2)));
    unsigned int h = (unsigned int)pow(2, ceil(log(height)/log(2)));
    if ( width != w  ||  height != h ) {
        lastu = width*1.0 / w;
        lastv = height*1.0 / h;

        buffer = (unsigned char*)malloc(w*h*4);
        memset(buffer, 0, w*h*4);
        for ( unsigned int y = 0; y < height; y++ ) {
            for ( unsigned int x = 0; x < width; x++ ){
                buffer[4*(y*w + x) + 0] = pixmap->ConstBuffer()[4*(y*width + x) + 0];
                buffer[4*(y*w + x) + 1] = pixmap->ConstBuffer()[4*(y*width + x) + 1];
                buffer[4*(y*w + x) + 2] = pixmap->ConstBuffer()[4*(y*width + x) + 2];
                buffer[4*(y*w + x) + 3] = pixmap->ConstBuffer()[4*(y*width + x) + 3];
            }
        }
    }

    // Generate OpenGL texture
    glGenTextures(1, &gltex);
    glBindTexture(GL_TEXTURE_2D, gltex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    // If a new buffer was generated, free it
    if ( buffer != pixmap->ConstBuffer() )
        free(buffer);
}
