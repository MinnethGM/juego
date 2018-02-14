// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <math.h>

#include <iostream>
using namespace std;
GLfloat ancho = 1024;
GLfloat alto = 768;

//Declaracion de ventana 
GLFWwindow *window;
GLfloat red, green, blue;
GLfloat ty = alto - 48;
GLfloat tx = ancho / 2;
double tiempoAnterior = 0.0;
double velocidad = 450;



GLfloat angulo = 0.0f;
GLfloat velocidadAngular = 180.0f;

GLfloat enemigoX = 0.0f;
GLfloat enemigoY = 0.8f;

GLfloat balaX = ancho / 2;
GLfloat balaY = alto / 1.7;

GLfloat balaXsp = 0.0f;
GLfloat balaYsp = 0.0f;
GLfloat balamaxsp = 250;
GLboolean disparando;

GLint nenemigos = 10;

GLfloat enemigos[100][3] = { 0 };



void checarColisiones()
{
	for (int e = 0; e < nenemigos; e++)
	{
		if (balaX > enemigos[e][0] - 32 && balaX < enemigos[e][0] + 12
			&& balaY > enemigos[e][1] - 12 && balaY < enemigos[e][1] + 48 && enemigos[e][0] != -1000)
		{
			enemigos[e][0] = -1000;
			balaYsp *= -1;
			balaXsp *= -1;
		}
	}

	if (balaX > tx - 96 && balaX < tx + 96
		&& balaY > ty - 24 && balaY < ty)
	{
		balaYsp *= -1;
		float dist = abs(balaX - tx);
		if (dist < 1)dist = 1;
		balaXsp = (balamaxsp / 30) * dist / 32;
		balaYsp = -10;
	}

	if (balaX < 0 || balaX > ancho)
	{
		balaXsp *= -1;
	}
	if (balaY < 0)
	{
		balaYsp *= -1;
	}
	if (balaY > alto + 48)
	{
		exit(0);
	}
}

void actualizar() {
	//Aqui esta bien para cambiar los valores de las variables de mi programa

	/*red += 0.001;
	green += 0.002;
	blue += 0.003;

	if (red > 1) red = 0;
	if (green > 1) green = 0;
	if (blue > 1) blue = 0;
	*/
	double tiempoActual = glfwGetTime();
	double tiempoTranscurrido = tiempoActual - tiempoAnterior;

	checarColisiones();

	balaYsp += 6 * tiempoTranscurrido;



	//DERECHA
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS)
	{
		if (tx < ancho)
			tx += velocidad * tiempoTranscurrido;

	}

	//IZQUIERDA
	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS)
	{
		if (tx > 0)
			tx -= velocidad * tiempoTranscurrido;

	}

	balaX += balaXsp * tiempoTranscurrido * 80;
	balaY += balaYsp * tiempoTranscurrido * 80;

	int estadoTeclaEspacio = glfwGetKey(window, GLFW_KEY_SPACE);
	if (estadoTeclaEspacio == GLFW_PRESS)
	{
		balaX = tx;
		balaY = ty;

		balaXsp = 0;
		balaYsp = -balamaxsp * tiempoTranscurrido;
		/*if (disparando == true)
		{
		glScalef(0.8f, 0.8f, 0.8f);
		}*/
	}

	tiempoAnterior = tiempoActual;

}
void dibujarBala()
{
	glPushMatrix();
	glTranslatef(((2 * balaX) / ancho) - 1, (((2 * balaY) / alto) - 1)*-1, 0);
	glScalef(0.08f, 0.08f, 0.08f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (float i = 0; i < 360; i++)
	{
		glVertex3f(0.2*cos(i) + 0.4, 0.2*sin(i) + 0.8, 0.0f);

	}

	glEnd();//finaliza rutina
	glPopMatrix();
}

void dibujarHeroe() {
	glPushMatrix();
	glTranslatef(((2 * tx) / ancho) - 1, (((2 * ty) / alto) - 1)*-1, 0);
	//glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	glScalef(0.08f, 0.08f, 0.08f);
	glBegin(GL_TRIANGLES);//Inicia la rutina con un modo de dibujo

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glColor3f(0.5f, 0.0f, 0.5f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);


	glEnd();//finaliza rutina
	glPopMatrix();
}


void dibujarEnemigo() {
	for (int r = 0; r < nenemigos; r++)
	{
		glPushMatrix();

		float val = enemigos[r][2];
		glColor4f(0.9 - val, 0.9 - val, 0.9 - val, 1);
		glTranslatef(((2 * enemigos[r][0]) / ancho) - 1, (((2 * enemigos[r][1]) / alto) - 1)*-1, 0);

		glScalef(32.0 / ancho, 32.0 / alto, 32.0 / alto);
		glBegin(GL_POLYGON);//Inicia la rutina con un modo de dibujo

		glColor4f(0.9 - val, 0.0 - val, 0.5 - val, 1);

		glVertex3f(-1, 1, 0);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);


		glEnd();//finaliza rutina
		glPopMatrix();
	}

}


void dibujar() {
	dibujarHeroe();
	dibujarEnemigo();
	dibujarBala();

}
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (ty < 0.9)
			ty += 0.05;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (ty > -0.9)
			ty -= 0.05f;
	}

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (tx < 0.9)
			tx += 0.05;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (tx > -0.9)
			tx -= 0.05f;
	}

	if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		dibujarBala();

	}
}

int main()
{

	//Propiedades de la ventana

	float as = 128;
	for (int e = 0; e < 8; e++)
	{
		float ypos = 0.0f;
		enemigos[nenemigos][0] = -8 * 32.0f + ancho / 2 + e * 64.0f;
		enemigos[nenemigos][1] = as + ypos * 32.0f;
		enemigos[nenemigos][2] = e / 100;
		nenemigos++;

	}
	for (int e = 0; e < 8; e++)
	{
		float ypos = 2;
		enemigos[nenemigos][0] = -8 * 32.0f + ancho / 2 + e * 64.0f;
		enemigos[nenemigos][1] = as + ypos * 32.0f;
		enemigos[nenemigos][2] = 0.15 + e / 100;
		nenemigos++;

	}
	for (int e = 0; e < 8; e++)
	{
		float ypos = 4;
		enemigos[nenemigos][0] = -8 * 32.0f + ancho / 2 + e * 64.0f;
		enemigos[nenemigos][1] = as + ypos * 32.0f;
		enemigos[nenemigos][2] = 0.3 + e / 100;
		nenemigos++;

	}

	//Inicializacion de GLFW
	if (!glfwInit()) {
		//Si no se inicio bien, terminar la ejecucion
		exit(EXIT_FAILURE);
	}

	//Inicializar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verificar si se creo bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);

	//se trae las funciones de OpenGL Moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	//Verificar que GLEW se inicializo bien
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;

	red = green = blue = 0.0f;

	//glfwSetKeyCallback(window, key_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render(Vewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia la pantalla


		glClearColor(red, green, blue, 1);

		//Limpiar pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


