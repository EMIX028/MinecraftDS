#include "mesh.h"
#include <stdint.h>
#define TNBR0 16
#define TNBR1 16


void startingDraw(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0);
    glMaterialf(
        GL_AMBIENT,
        RGB15(25,25,25)
    );
	glBegin(GL_QUADS);
}

void drawCubeTop(vec2_t t,uint8_t angle){

	glNormal(NORMAL_PACK(0,floattov10(1.0),0));

    int u0 = 1  + 18 * t.z;
    int u1 = 17 + 18 * t.z;

    int v0 = 1  + 18 * t.x;
    int v1 = 17 + 18 * t.x;

    switch(angle){
        case 0:
        default:
	        glTexCoord2t16(inttot16(u1),inttot16(v1));
	        glVertex3v16(inttov16(1), inttov16(1),0);

	        glTexCoord2t16(inttot16(u1),inttot16(v0));
	        glVertex3v16(0, inttov16(1), 0);

	        glTexCoord2t16(inttot16(u0),inttot16(v0));
	        glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u0),inttot16(v1));
	        glVertex3v16(inttov16(1), inttov16(1), inttov16(1));
            break;

        case 90:
            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(inttov16(1), inttov16(1),0);

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(0, inttov16(1), 0);

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(inttov16(1), inttov16(1), inttov16(1));
            break;

        case 180:
            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(inttov16(1), inttov16(1),0);

            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(0, inttov16(1), 0);

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(inttov16(1), inttov16(1), inttov16(1));
            break;
    }
}

void drawCubeBottom(vec2_t t, uint8_t angle){

	glNormal(NORMAL_PACK(0,floattov10(-1.0),0));

    int u0 = 1  + 18 * t.z;
    int u1 = 17 + 18 * t.z;

    int v0 = 1  + 18 * t.x;
    int v1 = 17 + 18 * t.x;

    switch(angle){
        case 0:
        default:
	        glTexCoord2t16(inttot16(u1),inttot16(v1));
	        glVertex3v16(0,0, 0);

	        glTexCoord2t16(inttot16(u1),inttot16(v0));
	        glVertex3v16(inttov16(1),0, 0);

	        glTexCoord2t16(inttot16(u0),inttot16(v0));
	        glVertex3v16(inttov16(1), 0, inttov16(1));

            glTexCoord2t16(inttot16(u0),inttot16(v1));
	        glVertex3v16(0, 0, inttov16(1));
            break;

        case 90:
            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(0,0, 0);

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(inttov16(1),0, 0);

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(inttov16(1), 0, inttov16(1));

            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(0, 0, inttov16(1));
            break;

        case 180:
            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(0,0, 0);

            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(inttov16(1),0, 0);

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(inttov16(1), 0, inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(0, 0, inttov16(1));
            break;
    }
}

void drawCubeBack(vec2_t t,uint8_t angle){
	
    glNormal(NORMAL_PACK(0,0,floattov10(-1.0)));

    int u0 = 1  + 18 * t.z;
    int u1 = 17 + 18 * t.z;

    int v0 = 1  + 18 * t.x;
    int v1 = 17 + 18 * t.x;

    switch(angle){
        case 0:
        default:
	        glTexCoord2t16(inttot16(u1),inttot16(v1));
	        glVertex3v16(0,0,0);

	        glTexCoord2t16(inttot16(u1),inttot16(v0));
	        glVertex3v16(0, inttov16(1), 0);

	        glTexCoord2t16(inttot16(u0),inttot16(v0));
	        glVertex3v16(inttov16(1), inttov16(1), 0);

            glTexCoord2t16(inttot16(u0),inttot16(v1));
	        glVertex3v16(inttov16(1),0, 0);
            break;

        case 90:
            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(0,0,0);

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(0, inttov16(1), 0);

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(inttov16(1), inttov16(1), 0);

            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(inttov16(1),0, 0);
            break;

        case 180:
            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(0,0,0);

            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(0, inttov16(1), 0);

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(inttov16(1), inttov16(1), 0);

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(inttov16(1),0, 0);
            break;
    }
}

void drawCubeRight(vec2_t t, uint8_t angle){
	
    glNormal(NORMAL_PACK(floattov10(1.0),0,0));

    int u0 = 1  + 18 * t.z;
    int u1 = 17 + 18 * t.z;

    int v0 = 1  + 18 * t.x;
    int v1 = 17 + 18 * t.x;

    switch(angle){
        case 0:
        default:
	        glTexCoord2t16(inttot16(u1),inttot16(v1));
	        glVertex3v16(inttov16(1), 0,0);

	        glTexCoord2t16(inttot16(u1),inttot16(v0));
	        glVertex3v16(inttov16(1), inttov16(1), 0);

	        glTexCoord2t16(inttot16(u0),inttot16(v0));
	        glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u0),inttot16(v1));
	        glVertex3v16(inttov16(1), 0, inttov16(1));
            break;
        
        case 90:
            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(inttov16(1), 0,0);

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(inttov16(1), inttov16(1), 0);

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(inttov16(1), 0, inttov16(1));
            break;

        case 180:
            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(inttov16(1), 0,0);

            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(inttov16(1), inttov16(1), 0);

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(inttov16(1), 0, inttov16(1));
            break;
    }
}

void drawCubeFront(vec2_t t, uint8_t angle){

    glNormal(NORMAL_PACK(0,0,floattov10(1.0)));

    int u0 = 1  + 18 * t.z;
    int u1 = 17 + 18 * t.z;

    int v0 = 1  + 18 * t.x;
    int v1 = 17 + 18 * t.x;

    switch(angle){
        case 0:
        default:
            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(inttov16(1), 0, inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(0, 0, inttov16(1));
            break;

        case 90:
            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(inttov16(1), 0, inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(0, 0, inttov16(1));
            break;

        case 180:
            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(inttov16(1), 0, inttov16(1));

            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(0, 0, inttov16(1));
            break;
    }
}

void drawCubeLeft(vec2_t t,uint8_t angle){

    glNormal(NORMAL_PACK(floattov10(-1.0), 0, 0));

    int u0 = 1  + 18 * t.z;
    int u1 = 17 + 18 * t.z;

    int v0 = 1  + 18 * t.x;
    int v1 = 17 + 18 * t.x;

    switch(angle){
        case 0:
        default:
	        glTexCoord2t16(inttot16(u1),inttot16(v1));
            glVertex3v16(0, 0, inttov16(1));

	        glTexCoord2t16(inttot16(u1),inttot16(v0));
            glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u0),inttot16(v0));
            glVertex3v16(0, inttov16(1), 0);

            glTexCoord2t16(inttot16(u0),inttot16(v1));
            glVertex3v16(0, 0, 0);
            break;

        case 90:
            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(0, 0, inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(0, inttov16(1), 0);

            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(0, 0, 0);
            break;

        case 180:
            glTexCoord2t16(inttot16(u0), inttot16(v0));
            glVertex3v16(0, 0, inttov16(1));

            glTexCoord2t16(inttot16(u0), inttot16(v1));
            glVertex3v16(0, inttov16(1), inttov16(1));

            glTexCoord2t16(inttot16(u1), inttot16(v1));
            glVertex3v16(0, inttov16(1), 0);

            glTexCoord2t16(inttot16(u1), inttot16(v0));
            glVertex3v16(0, 0, 0);
            break;
    }
}

void drawCube(bool cullback, vec2_t t){
	startingDraw(cullback);
	drawCubeLeft(t,0);
    drawCubeFront(t, 0);
	drawCubeBack(t,0);
	drawCubeRight(t,0);
	drawCubeTop(t,0);
	drawCubeBottom(t,0);
	glEnd();
}

// glMaterialf(
//         GL_AMBIENT,
//         RGB15((int)(color.r*AMBIENT_RATIO),(int)(color.g*AMBIENT_RATIO),(int)(color.b*AMBIENT_RATIO))
//     );

//     glMaterialf(
//         GL_DIFFUSE,
//         RGB15(color.r,color.g,color.b) // Influe sur la couleur de la texture
//     );

//     glMaterialf(
//         GL_SPECULAR,
//         RGB15(15,15,15)
//     );

static void drawBar(v16 minX, v16 minY, v16 minZ,v16 maxX, v16 maxY, v16 maxZ){
    glBegin(GL_QUADS);

    // Avant
    glVertex3v16(minX, minY, maxZ);
    glVertex3v16(maxX, minY, maxZ);
    glVertex3v16(maxX, maxY, maxZ);
    glVertex3v16(minX, maxY, maxZ);

    // Arrière
    glVertex3v16(maxX, minY, minZ);
    glVertex3v16(minX, minY, minZ);
    glVertex3v16(minX, maxY, minZ);
    glVertex3v16(maxX, maxY, minZ);

    // Gauche
    glVertex3v16(minX, minY, minZ);
    glVertex3v16(minX, minY, maxZ);
    glVertex3v16(minX, maxY, maxZ);
    glVertex3v16(minX, maxY, minZ);

    // Droite
    glVertex3v16(maxX, minY, maxZ);
    glVertex3v16(maxX, minY, minZ);
    glVertex3v16(maxX, maxY, minZ);
    glVertex3v16(maxX, maxY, maxZ);

    // Haut
    glVertex3v16(minX, maxY, maxZ);
    glVertex3v16(maxX, maxY, maxZ);
    glVertex3v16(maxX, maxY, minZ);
    glVertex3v16(minX, maxY, minZ);

    // Bas
    glVertex3v16(minX, minY, minZ);
    glVertex3v16(maxX, minY, minZ);
    glVertex3v16(maxX, minY, maxZ);
    glVertex3v16(minX, minY, maxZ);

    glEnd();
}



void drawBlockOutline(int x, int y, int z){
    glPushMatrix();
    glTranslatef32(inttof32(x),inttof32(y),inttof32(z));
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE );
    glColor(RGB15(0,0,0));

    // Bas avant
    drawBar(
        MIN, MIN, MIN,
        MAX, OUTLINE_SIZE, OUTLINE_SIZE
    );

    // Bas arrière
    drawBar(
        MIN, MIN, MAX - OUTLINE_SIZE,
        MAX, OUTLINE_SIZE, MAX
    );

    // Haut avant
    drawBar(
        MIN, MAX - OUTLINE_SIZE, MIN,
        MAX, MAX, OUTLINE_SIZE
    );

    // Haut arrière
    drawBar(
        MIN, MAX - OUTLINE_SIZE, MAX - OUTLINE_SIZE,
        MAX, MAX, MAX
    );

    // Avant gauche
    drawBar(
        MIN, MIN, MIN,
        OUTLINE_SIZE, MAX, OUTLINE_SIZE
    );

    // Avant droite
    drawBar(
        MAX - OUTLINE_SIZE, MIN, MIN,
        MAX, MAX, OUTLINE_SIZE
    );

    // Arrière gauche
    drawBar(
        MIN, MIN, MAX - OUTLINE_SIZE,
        OUTLINE_SIZE, MAX, MAX
    );

    // Arrière droite
    drawBar(
        MAX - OUTLINE_SIZE, MIN, MAX - OUTLINE_SIZE,
        MAX, MAX, MAX
    );

    // Bas gauche
    drawBar(
        MIN, MIN, MIN,
        OUTLINE_SIZE, OUTLINE_SIZE, MAX
    );

    // Bas droite
    drawBar(
        MAX - OUTLINE_SIZE, MIN, MIN,
        MAX, OUTLINE_SIZE, MAX
    );

    // Haut gauche
    drawBar(
        MIN, MAX - OUTLINE_SIZE, MIN,
        OUTLINE_SIZE, MAX, MAX
    );

    // Haut droite
    drawBar(
        MAX - OUTLINE_SIZE, MAX - OUTLINE_SIZE, MIN,
        MAX, MAX, MAX
    );

    glPopMatrix(1);
}