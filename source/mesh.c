#include <nds.h>
#include "mesh.h"
#define TNBR0 16
#define TNBR1 16

void startingDraw(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0);//POLY_FORMAT_LIGHT0
	glColor3b(255,255,255);

	glBegin(GL_QUADS);
}

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
	glVertex3v16(0, inttov16(1), 0);
	glVertex3v16(0, inttov16(1), inttov16(-1));
	glVertex3v16(0, 0, inttov16(-1));
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
	glVertex3v16(0,0, inttov16(-1));
	glVertex3v16(0, inttov16(1), inttov16(-1));
	glVertex3v16(inttov16(1), inttov16(1), inttov16(-1));
	glVertex3v16(inttov16(1), 0, inttov16(-1));
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
	glVertex3v16(inttov16(1), 0, inttov16(-1));
	glVertex3v16(inttov16(1), inttov16(1), inttov16(-1));
	glVertex3v16(inttov16(1), inttov16(1), 0);
	glVertex3v16(inttov16(1), 0,0);
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
	glVertex3v16(inttov16(1),0, 0);
	glVertex3v16(inttov16(1), inttov16(1), 0);
	glVertex3v16(0, inttov16(1), 0);
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
	glVertex3v16(0, 0, inttov16(-1));
	glVertex3v16(inttov16(1), 0, inttov16(-1));
	glVertex3v16(inttov16(1),0, 0);
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
	glVertex3v16(inttov16(1), inttov16(1), inttov16(-1));
	glVertex3v16(0, inttov16(1), inttov16(-1));
	glVertex3v16(0, inttov16(1), 0);
	glVertex3v16(inttov16(1), inttov16(1),0);
	glEnd();
}

void drawCubeTop(vec2_8_t t){
	glNormal(NORMAL_PACK(0,floattov10(1.0),0));

		glTexCoord2t16(inttot16(1 + 18*t.y),inttot16(16*t.x)); //Texture
		glVertex3v16(inttov16(1), inttov16(1),0);

		glTexCoord2t16(inttot16(1 + 18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(0, inttov16(1), 0);

		glTexCoord2t16(inttot16(17 + 18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(0, inttov16(1), inttov16(1));

    glTexCoord2t16(inttot16(17 + 18*t.y), inttot16(16*t.x)); //Texture
		glVertex3v16(inttov16(1), inttov16(1), inttov16(1));    
}

void drawCubeBottom(vec2_8_t t){
	glNormal(NORMAL_PACK(0,floattov10(-1.0),0));

		glTexCoord2t16(inttot16(1 + 18*t.y),inttot16(16*t.x)); //Texture
		glVertex3v16(0,0, 0);

		glTexCoord2t16(inttot16(1 +18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(inttov16(1),0, 0);

		glTexCoord2t16(inttot16(17 + 18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(inttov16(1), 0, inttov16(1));

    glTexCoord2t16(inttot16(17 + 18*t.y), inttot16(16*t.x)); //Texture
		glVertex3v16(0, 0, inttov16(1));
}

void drawCubeBack(vec2_8_t t){
	glNormal(NORMAL_PACK(0,0,floattov10(-1.0)));

		glTexCoord2t16(inttot16(1 + 18*t.y),inttot16(16*t.x)); //Texture
		glVertex3v16(0,0,0);

		glTexCoord2t16(inttot16(1 +18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(0, inttov16(1), 0);

		glTexCoord2t16(inttot16(17 + 18*t.y),inttot16(16 +16*t.x)); //Texture
		glVertex3v16(inttov16(1), inttov16(1), 0);

    glTexCoord2t16(inttot16(17 + 18*t.y), inttot16(16*t.x)); //Texture
		glVertex3v16(inttov16(1),0, 0);    
}

void drawCubeRight(vec2_8_t t){
	glNormal(NORMAL_PACK(floattov10(1.0),0,0));

		glTexCoord2t16(inttot16(1 + 18*t.y),inttot16(16*t.x)); //Texture
		glVertex3v16(inttov16(1), 0,0);

		glTexCoord2t16(inttot16(1 + 18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(inttov16(1), inttov16(1), 0);

		glTexCoord2t16(inttot16(17 + 18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

    glTexCoord2t16(inttot16(17 + 18*t.y), inttot16(16*t.x)); //Texture
		glVertex3v16(inttov16(1), 0, inttov16(1));
}

void drawCubeFront(vec2_8_t t){
	glNormal(NORMAL_PACK(0,0,floattov10(1.0)));

		glTexCoord2t16(inttot16(1 + 18*t.y),inttot16(16*t.x)); //Texture
		glVertex3v16(inttov16(1), 0, inttov16(1));

		glTexCoord2t16(inttot16(1 + 18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(inttov16(1), inttov16(1), inttov16(1));

		glTexCoord2t16(inttot16(17 + 18*t.y),inttot16(16 + 16*t.x)); //Texture
		glVertex3v16(0, inttov16(1), inttov16(1));

    glTexCoord2t16(inttot16(17 + 18*t.y), inttot16( 16*t.x)); //Texture
		glVertex3v16(0,0, inttov16(1));
}

// void drawCubeLeft(vec2_8_t t){
// 		glNormal(NORMAL_PACK(floattov10(-1.0),0,0));

// 		glTexCoord2t16(inttot16(0 + TNBR0*t.y),inttot16(TNBR1 + TNBR1*t.x)); //Texture
// 		glVertex3v16(0,0,inttov16(1));

// 		glTexCoord2t16(inttot16(0 + TNBR0*t.y),inttot16(0 + TNBR0*t.x)); //Texture
// 		glVertex3v16(0,inttov16(1),inttov16(1));

// 		glTexCoord2t16(inttot16(TNBR1 + TNBR1*t.y),inttot16(0 + TNBR0*t.x)); //Texture
// 		glVertex3v16(0,inttov16(1),0);

// 		glTexCoord2t16(inttot16(TNBR1 + TNBR1*t.y), inttot16(TNBR1 + TNBR1*t.x)); //Texture
// 		glVertex3v16(0,0,0);
// }

void drawCubeLeft(vec2_8_t t)
{
    glNormal(NORMAL_PACK(floattov10(-1.0), 0, 0));

    // U = colonne (t.y), V = ligne (t.x)

    glTexCoord2t16(
        inttot16(1 + 18 * t.y),
        inttot16(16 * t.x)
    );
    glVertex3v16(0, 0, inttov16(1));

    glTexCoord2t16(
        inttot16(1 + 18 * t.y),
        inttot16(16 + 16 * t.x)
    );
    glVertex3v16(0, inttov16(1), inttov16(1));

    glTexCoord2t16(
        inttot16(17 + 18 * t.y),
        inttot16(16 + 16 * t.x)
    );
    glVertex3v16(0, inttov16(1), 0);

    glTexCoord2t16(
        inttot16(17 + 18 * t.y),
        inttot16(16 * t.x)
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