#include <nds.h>
#include "mesh.h"

void drawCube(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(0,20,0)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(floattov10(-1.0),0,0));
	glVertex3v16(0, 0, 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(-1.0)));
	glVertex3v16(0,0, floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(floattov10(1.0),0,0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), 0,0);
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(1.0)));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0,0,0);
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(-1.0),0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(0,0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(1.0),0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0),0);
	glEnd();
}

void drawPierre(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)|POLY_FORMAT_LIGHT0);
	glMaterialf(
        GL_AMBIENT,
        RGB15(3,3,3)
    );

    glMaterialf(
        GL_DIFFUSE,
        RGB15(15,15,15)
    );

    glMaterialf(
        GL_SPECULAR,
        RGB15(15,15,15)
    );
	
	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(floattov10(-1.0),0,0));
	glVertex3v16(0, 0, 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(-1.0)));
	glVertex3v16(0,0, floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(floattov10(1.0),0,0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), 0,0);
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,0,floattov10(1.0)));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0), 0);
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(0,0,0);
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(-1.0),0));
	glVertex3v16(0, 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0), 0, floattov16(-1.0));
	glVertex3v16(floattov16(1.0),0, 0);
	glVertex3v16(0,0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glNormal(NORMAL_PACK(0,floattov10(1.0),0));
	glVertex3v16(floattov16(1.0), floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), floattov16(-1.0));
	glVertex3v16(0, floattov16(1.0), 0);
	glVertex3v16(floattov16(1.0), floattov16(1.0),0);
	glEnd();
}