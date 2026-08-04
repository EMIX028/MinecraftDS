#include <nds.h>
#include "mesh.h"

void drawSpecialCube(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(7,7,7)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(31,31,31)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face gauche
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(inttov10(-1),0,0));
	glVertex3v16(0, 0, 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glEnd();
	
	glMaterialf(
        GL_AMBIENT,
        RGB15(7,7,7)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(31,0,0)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face arrière
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,inttov10(-1)));
	glVertex3v16(0,0, floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glEnd();


	glMaterialf(
        GL_AMBIENT,
        RGB15(7,7,7)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(0,31,0)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face droite
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(inttov10(1),0,0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), 0,0);
	glEnd();


	glMaterialf(
        GL_AMBIENT,
        RGB15(0,0,(int)(31*AMBIENT_RATIO))
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(0,0,31)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(0,0,0)
    );
	//face avant
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,inttov10(1)));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0,0,0);
	glEnd();


	glMaterialf(
        GL_AMBIENT,
        RGB15(7,7,7)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(31,20,0)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face dessous
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,inttov10(-1),0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(0,0, 0);
	glEnd();


	glMaterialf(
        GL_AMBIENT,
        RGB15(4,4,4)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(0,0,31)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(0,0,0)
    );
	//face dessus
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,inttov10(1),0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0),0);
	glEnd();
}

void drawCubeTop(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0);//POLY_FORMAT_LIGHT0
	glColor3b(255,255,255);

	//face dessus
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(1.0),0));

    glTexCoord2t16(inttot16(16), inttot16(16));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));

    glTexCoord2t16(inttot16(16),0);
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));

    glTexCoord2t16(0,0);
	glVertex3v16(0, floattov16(1.0), 0);

    glTexCoord2t16(0,inttot16(16));
	glVertex3v16(floattov16(1.0), floattov16(1.0),0);
	glEnd();
}

void drawCubeBottom(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0); //| POLY_FORMAT_LIGHT0
	glColor3b(255,255,255);

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(-1.0),0));

    glTexCoord2t16(inttot16(16), inttot16(16));
	glVertex3v16(0, 0, floattov16(-1.0));

    glTexCoord2t16(inttot16(16),0);
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));

    glTexCoord2t16(0,0);
	glVertex3v16(floattov16(1.0),0, 0);

    glTexCoord2t16(0,inttot16(16));
	glVertex3v16(0,0, 0);
	glEnd();
}

void drawCubeFront(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0); //POLY_FORMAT_LIGHT0
	glColor3b(255,255,255);
    
	//face avant
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(1.0)));

    glTexCoord2t16(inttot16(16), inttot16(16));
	glVertex3v16(floattov16(1.0),0, 0);

    glTexCoord2t16(inttot16(16),0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);

    glTexCoord2t16(0,0);
	glVertex3v16(0, floattov16(1.0), 0);

    glTexCoord2t16(0,inttot16(16));
	glVertex3v16(0,0,0);
	glEnd();
}

void drawCubeRight(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0); //POLY_FORMAT_LIGHT0
	glColor3b(255,255,255);
	//face droite
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(floattov10(1.0),0,0));

    glTexCoord2t16(inttot16(16), inttot16(16));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));

    glTexCoord2t16(inttot16(16),0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));

    glTexCoord2t16(0,0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);

    glTexCoord2t16(0,inttot16(16));
	glVertex3v16(floattov16(1.0), 0,0);
	glEnd();
}

void drawCubeBack(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0); //POLY_FORMAT_LIGHT0
	glColor3b(255,255,255);
	//face arrière
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(-1.0)));

    glTexCoord2t16(inttot16(16), inttot16(16));
	glVertex3v16(0,0, floattov16(-1.0));

    glTexCoord2t16(inttot16(16),0);
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));

    glTexCoord2t16(0,0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));

    glTexCoord2t16(0,inttot16(16));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glEnd();
}

void drawCubeLeft(bool cullback,rgb_t color){
    glPolyFmt(
        POLY_ALPHA(31) |
        (cullback ? POLY_CULL_BACK : POLY_CULL_NONE) |
        POLY_FORMAT_LIGHT0
    );

    glColor3b(255,255,255);

    glBegin(GL_QUADS);

glBegin(GL_QUADS);
glNormal(NORMAL_PACK(floattov10(-1.0),0,0));

glTexCoord2t16(inttot16(16), inttot16(16));
glVertex3v16(0,0,0);

glTexCoord2t16(inttot16(16),0);
glVertex3v16(0,inttov16(1),0);

glTexCoord2t16(0,0);
glVertex3v16(0,inttov16(1),inttov16(-1));

glTexCoord2t16(0,inttot16(16));
glVertex3v16(0,0,inttov16(-1));

glEnd();
}

void drawCube(bool cullback,rgb_t color){
	drawCubeLeft(cullback, color);
    drawCubeFront(cullback, color);
	drawCubeBack(cullback, color);
	drawCubeRight(cullback, color);
	drawCubeTop(cullback, color);
	drawCubeBottom(cullback, color);
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