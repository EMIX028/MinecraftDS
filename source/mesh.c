#include <nds.h>
#include "mesh.h"

void drawSpecialCube(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
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
	glNormal(NORMAL_PACK(floattov10(-1.0),0,0));
	glVertex3v16(0, 0, 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glEnd();
	
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
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
	glNormal(NORMAL_PACK(0,0,floattov10(-1.0)));
	glVertex3v16(0,0, floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glEnd();


	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
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
	glNormal(NORMAL_PACK(floattov10(1.0),0,0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), 0,0);
	glEnd();


	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(0,0,31)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face avant
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(1.0)));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0,0,0);
	glEnd();


	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
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
	glNormal(NORMAL_PACK(0,floattov10(-1.0),0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(0,0, 0);
	glEnd();


	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(31,0,31)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face dessus
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(1.0),0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0),0);
	glEnd();
}

void drawCubeTop(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(color.r,color.g,color.b)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face dessus
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(1.0),0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0),0);
	glEnd();
}

void drawCubeBottom(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(color.r,color.g,color.b)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(-1.0),0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(0,0, 0);
	glEnd();
}

void drawCubeFront(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(color.r,color.g,color.b)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face avant
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(1.0)));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0,0,0);
	glEnd();
}

void drawCubeRight(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(color.r,color.g,color.b)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face droite
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(floattov10(1.0),0,0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), 0,0);
	glEnd();
}

void drawCubeBack(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(color.r,color.g,color.b)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face arrière
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(-1.0)));
	glVertex3v16(0,0, floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glEnd();
}

void drawCubeLeft(bool cullback,rgb_t color){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(color.r,color.g,color.b)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	//face gauche
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(floattov10(-1.0),0,0));
	glVertex3v16(0, 0, 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glEnd();
}

void drawCube(bool cullback,rgb_t color){
	drawCubeFront(cullback, color);
	drawCubeBack(cullback, color);
	drawCubeLeft(cullback, color);
	drawCubeRight(cullback, color);
	drawCubeTop(cullback, color);
	drawCubeBottom(cullback, color);
}