#include<windows.h>
#include<GL/glut.h>
#include<gl/glaux.h>
#   pragma comment (lib, "glaux.lib")    /* link with Win32 GLUT lib */

#include<iostream>
#include"ObjModel.h"

using namespace std;
ObjModel model;
unsigned int id;

void CreateTexture(UINT &texture, LPCSTR strFileName)
{
	AUX_RGBImageRec *pBitmap = NULL;
	if (!strFileName)									// Return from the function if no file name was passed in
		return;
	pBitmap = auxDIBImageLoad(strFileName);				// Load the bitmap and store the data
	if (pBitmap == NULL)									// If we can't load the file, quit!
		exit(0);

	glGenTextures(1, &texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (pBitmap)										// If we loaded the bitmap
	{
		if (pBitmap->data)								// If there is texture data
		{
			free(pBitmap->data);						// Free the texture data, we don't need it anymore
		}

		free(pBitmap);									// Free the bitmap structure
	}
}

void charKey(unsigned char k, int x, int y)
{
	glutPostRedisplay();
	switch (k)
	{
	case 27:
		exit(0);
		break;

	}
}

float angle = 0;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	angle += 0.1;
	glTranslatef(0, 0, -80);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(-90, 1, 0, 0);
	glRotatef(angle, 0, 1, 1);

	if (model.hasTextureCoord())
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glEnable(GL_TEXTURE_2D);
	}
	glBegin(GL_TRIANGLES);
	{
		for (int i = 0; i<model.vectorOfFace.size(); i++)
		{

			if (model.hasNormalCoord())
				glNormal3d(model.vectorOfNormal[model.vectorOfFace[i].firstVertex[2]].xn,
					model.vectorOfNormal[model.vectorOfFace[i].firstVertex[2]].yn,
					model.vectorOfNormal[model.vectorOfFace[i].firstVertex[2]].zn);
			if (model.hasTextureCoord())
				glTexCoord2f(model.vectorOfTexture[model.vectorOfFace[i].firstVertex[1]].s,
					model.vectorOfTexture[model.vectorOfFace[i].firstVertex[1]].t);
			glVertex3f(model.vectorOfVertex[model.vectorOfFace[i].firstVertex[0]].x,
				model.vectorOfVertex[model.vectorOfFace[i].firstVertex[0]].y,
				model.vectorOfVertex[model.vectorOfFace[i].firstVertex[0]].z);
			if (model.hasNormalCoord())
				glNormal3d(model.vectorOfNormal[model.vectorOfFace[i].secondVertex[2]].xn,
					model.vectorOfNormal[model.vectorOfFace[i].secondVertex[2]].yn,
					model.vectorOfNormal[model.vectorOfFace[i].secondVertex[2]].zn);
			if (model.hasTextureCoord())
				glTexCoord2f(model.vectorOfTexture[model.vectorOfFace[i].secondVertex[1]].s,
					model.vectorOfTexture[model.vectorOfFace[i].secondVertex[1]].t);
			glVertex3f(model.vectorOfVertex[model.vectorOfFace[i].secondVertex[0]].x,
				model.vectorOfVertex[model.vectorOfFace[i].secondVertex[0]].y,
				model.vectorOfVertex[model.vectorOfFace[i].secondVertex[0]].z);

			if (model.hasNormalCoord())
				glNormal3d(model.vectorOfNormal[model.vectorOfFace[i].thirdVertex[2]].xn,
					model.vectorOfNormal[model.vectorOfFace[i].thirdVertex[2]].yn,
					model.vectorOfNormal[model.vectorOfFace[i].thirdVertex[2]].zn);

			if (model.hasTextureCoord())
				glTexCoord2f(model.vectorOfTexture[model.vectorOfFace[i].thirdVertex[1]].s,
					model.vectorOfTexture[model.vectorOfFace[i].thirdVertex[1]].t);
			glVertex3f(model.vectorOfVertex[model.vectorOfFace[i].thirdVertex[0]].x,
				model.vectorOfVertex[model.vectorOfFace[i].thirdVertex[0]].y,
				model.vectorOfVertex[model.vectorOfFace[i].thirdVertex[0]].z);
		}
	}
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0,w,0,h);
	gluPerspective(65, 1, .1, -100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);

	
	
	glutCreateWindow("wavefront file loader ");
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);

	GLfloat amb_light[] = { 0.91, 0.91, 0.91, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);




	glColor3f(1, 1, 1);
	glClearColor(0, 0, 0, 1);
	model.load("spaceship.obj");
	CreateTexture(id, "spaceship.bmp");
	glutDisplayFunc(display);

	glutReshapeFunc(reshape);
	glutIgnoreKeyRepeat(0);
	glutKeyboardFunc(charKey);


	glutMainLoop();
	return 0;
}
