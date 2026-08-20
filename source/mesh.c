#include <nds.h>
#include "mesh.h"
#include "nds/arm9/videoGL.h"
#define TNBR0 16
#define TNBR1 16


void startingDraw(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0);//POLY_FORMAT_LIGHT0
	glColor3b(255,255,255);

	glBegin(GL_QUADS);
}

void drawCubeTop(vec2_8_t t){
	glNormal(NORMAL_PACK(0,floattov10(1.0),0));

	glTexCoord2t16(
		inttot16(1  + 18*t.y),
		inttot16(1 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), inttov16(1),0);

	glTexCoord2t16(
		inttot16(1 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(0, inttov16(1), 0);

	glTexCoord2t16(
		inttot16(17 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(0, inttov16(1), inttov16(1));

    glTexCoord2t16(
		inttot16(17 + 18*t.y), 
		inttot16(1  + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), inttov16(1), inttov16(1));    
}

void drawCubeBottom(vec2_8_t t){
	glNormal(NORMAL_PACK(0,floattov10(-1.0),0));

	glTexCoord2t16(
		inttot16(1  + 18*t.y),
		inttot16(1 + 18*t.x)
	); //Texture
	glVertex3v16(0,0, 0);

	glTexCoord2t16(
		inttot16(1 +18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1),0, 0);

	glTexCoord2t16(
		inttot16(17 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), 0, inttov16(1));

    glTexCoord2t16(
		inttot16(17 + 18*t.y), 
		inttot16(1  + 18*t.x)
	); //Texture
	glVertex3v16(0, 0, inttov16(1));
}

void drawCubeBack(vec2_8_t t){
	glNormal(NORMAL_PACK(0,0,floattov10(-1.0)));

	glTexCoord2t16(
		inttot16(1  + 18*t.y),
		inttot16(1 + 18*t.x)
	); //Texture
	glVertex3v16(0,0,0);

	glTexCoord2t16(
		inttot16(1 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(0, inttov16(1), 0);

	glTexCoord2t16(
		inttot16(17 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), inttov16(1), 0);

    glTexCoord2t16(
		inttot16(17 + 18*t.y), 
		inttot16(1  + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1),0, 0);    
}

void drawCubeRight(vec2_8_t t){
	glNormal(NORMAL_PACK(floattov10(1.0),0,0));

	glTexCoord2t16(
		inttot16(1  + 18*t.y),
		inttot16(1 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), 0,0);

	glTexCoord2t16(
		inttot16(1 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), inttov16(1), 0);

	glTexCoord2t16(
		inttot16(17 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

    glTexCoord2t16(
		inttot16(17 + 18*t.y), 
		inttot16(1  + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), 0, inttov16(1));
}

void drawCubeFront(vec2_8_t t){
	glNormal(NORMAL_PACK(0,0,floattov10(1.0)));

	glTexCoord2t16(
		inttot16(1 + 18*t.y),
		inttot16(1 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), 0, inttov16(1));

	glTexCoord2t16(
		inttot16(1 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

	glTexCoord2t16(
		inttot16(17 + 18*t.y),
		inttot16(17 + 18*t.x)
	); //Texture
	glVertex3v16(0, inttov16(1), inttov16(1));

    glTexCoord2t16(
		inttot16(17 + 18*t.y), 
		inttot16(1  + 18*t.x)
	); //Texture
	glVertex3v16(0,0, inttov16(1));
}

void drawCubeLeft(vec2_8_t t){
    glNormal(NORMAL_PACK(floattov10(-1.0), 0, 0));

    glTexCoord2t16(
        inttot16(1  + 18 * t.y),
        inttot16(1 + 18 * t.x)
    );
    glVertex3v16(0, 0, inttov16(1));

    glTexCoord2t16(
        inttot16(1 + 18 * t.y),
        inttot16(17 + 18 * t.x)
    );
    glVertex3v16(0, inttov16(1), inttov16(1));

    glTexCoord2t16(
        inttot16(17 + 18 * t.y),
        inttot16(17 + 18 * t.x)
    );
    glVertex3v16(0, inttov16(1), 0);

    glTexCoord2t16(
        inttot16(17 + 18 * t.y),
        inttot16(1  + 18 * t.x)
    );
    glVertex3v16(0, 0, 0);
}

void drawCube(bool cullback, vec2_8_t t){
	startingDraw(cullback);
	drawCubeLeft( t);
  	drawCubeFront( t);
	drawCubeBack( t);
	drawCubeRight( t);
	drawCubeTop( t);
	drawCubeBottom(t);
	glEnd();
}

void drawBlockOutline(int x, int y, int z)
{
    glPushMatrix();

    glTranslatef32(
        inttof32(x),
        inttof32(y),
        inttof32(z)
    );

    glPolyFmt(
        POLY_ALPHA(31) |
        POLY_CULL_NONE |
        POLY_ID(0)
    );

    glColor(RGB15(0, 0, 0));

    glBegin(GL_QUADS);

        // Face avant
        glVertex3v16(inttov16(1), 0, inttov16(1));
        glVertex3v16(inttov16(1), inttov16(1), inttov16(1));
        glVertex3v16(0, inttov16(1), inttov16(1));
        glVertex3v16(0, 0, inttov16(1));

        // Face arrière
        glVertex3v16(0, 0, 0);
        glVertex3v16(0, inttov16(1), 0);
        glVertex3v16(inttov16(1), inttov16(1), 0);
        glVertex3v16(inttov16(1), 0, 0);

        // Face gauche
        glVertex3v16(0, 0, inttov16(1));
        glVertex3v16(0, inttov16(1), inttov16(1));
        glVertex3v16(0, inttov16(1), 0);
        glVertex3v16(0, 0, 0);

        // Face droite
        glVertex3v16(inttov16(1), 0, 0);
        glVertex3v16(inttov16(1), inttov16(1), 0);
        glVertex3v16(inttov16(1), inttov16(1), inttov16(1));
        glVertex3v16(inttov16(1), 0, inttov16(1));

        // Haut
        glVertex3v16(0, inttov16(1), 0);
        glVertex3v16(inttov16(1), inttov16(1), 0);
        glVertex3v16(inttov16(1), inttov16(1), inttov16(1));
        glVertex3v16(0, inttov16(1), inttov16(1));

        // Bas
        glVertex3v16(0, 0, 0);
        glVertex3v16(0, 0, inttov16(1));
        glVertex3v16(inttov16(1), 0, inttov16(1));
        glVertex3v16(inttov16(1), 0, 0);

    glEnd();

    glPopMatrix(1);
}

// glMaterialf(
//         GL_AMBIENT,
//         RGB15((int)(color.r*AMBIENT_RATIO),(int)(color.g*AMBIENT_RATIO),(int)(color.b*AMBIENT_RATIO))
//     );

//     glMaterialf(
//         GL_DIFFUSE,
//         RGB15(color.r,color.g,color.b)
//     );

//     glMaterialf(
//         GL_SPECULAR,
//         RGB15(15,15,15)
//     );