// lab2_sam.cpp : 定义控制台应用程序的入口点。
//

#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include<string>
#include<vector>
#include <sstream>
#include <iostream>
#include <fstream>
#define random(x) (rand()%x)


// Windows include files 

#ifdef _WIN32
#include <windows.h>
#endif



// OpenGL include files 

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "opencv2/highgui/highgui.hpp"

using namespace std;

typedef struct Vertex
{
	float x,y,z;
}Vertex;

typedef struct Facep
{
	int num;
	int order[3];
}Facep;
static char *filename="chair_0001.off";

Vertex ver[10000];
Facep fap[20000];
int i,j,k,n_node,n_face,n_edge;
float scale=25.4,spin=0;
static int window_height = 480;
static int window_width = 640;
static double r = 500;


double angle[3] = { 0 };
// x = r*cos(angle[1])*cos(angle[0]);
// y = r*cos(angle[1])*sin(angle[0]);
// z = r*sin(angle[1]);
int times = 1;
int times_pitch = 1;
int times_r = 1;
int label = 1;
GLint modelview_loc;
GLint projection_loc;
void* frame_data = 0;
ofstream file_label;
cv::Mat frame;

cv::Mat channels[3], temp, frame_16u;
std::vector<cv::Mat> channels_vec;

std::stringstream stream;
std::string name_pic;

int readoff(const char* filename)
{
	FILE *fp;
	
	if(!(fp=fopen(filename,"r")))
	{
		fprintf(stderr,"Open fail");
		return 0;
	}
    char buffer[1024];
	if(fgets(buffer,1023,fp))
	{
		if(!strstr(buffer,"OFF"))
			{
				printf("It's not a OFF FILE");
				return 0;
		}
		
		if(fgets(buffer,1023,fp))
		{
			sscanf(buffer,"%d %d %d",&n_node,&n_face,&n_edge);
			
			for(i=0;i<n_node;i++)
			{
				fgets(buffer,1023,fp);
				sscanf(buffer,"%f%f%f",&ver[i].x,&ver[i].y,&ver[i].z);
			}
			for(i=0;i<n_face;i++)
			{
				fgets(buffer,1023,fp);
				int temp;
				sscanf(buffer,"%d%d%d%d",&fap[i].num,&fap[i].order[0],&fap[i].order[1],&fap[i].order[2]);
			}
		}

    }
}
void redraw(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(/*45.0*/48.6, window_height/(double)window_width, 100, 10000);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*for(int j = 0;j<20;j++)
	{
		printf("random number is %d\n",random(100));
	}*/
	if(times_r == 1)
		r = 1000;
	else if(times_r == 2)
		r =  1100 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 3)
		r =  1200 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 4)
		r = 1300 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 5)
		r = 1400 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 6)
		r = 1500 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 7)
		r = 1600 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 8)
		r =  1700 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 9)
		r =  1800 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 10)
		r = 1900 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 11)
		r = 2000 + ((double)rand() / RAND_MAX)*(100-50)+50;

	else if(times_r == 12)
		r = 2050 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 13)
		r = 2100 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 14)
		r =  2150 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 15)
		r =  2200 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 16)
		r = 2250 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 17)
		r = 2300 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 18)
		r = 2350 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 19)
		r = 2400 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 20)
		r =  2450 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 21)
		r =  2500 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 22)
		r = 2550 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 23)
		r = 2600 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 24)
		r = 2650 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 25)
		r = 2700 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 26)
		r =  2750 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 27)
		r =  2800 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 28)
		r = 2850 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 29)
		r = 2900 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 30)
		r = 2950 + ((double)rand() / RAND_MAX)*(50-25)+25;
	else if(times_r == 31)
		r = 3000 + ((double)rand() / RAND_MAX)*(50-25)+25;

	else if(times_r == 32)
		r =  3100 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 33)
		r =  3200 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 34)
		r = 3300 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 35)
		r = 3400 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 36)
		r = 3500 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 37)
		r = 3600 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 38)
		r =  3700 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 39)
		r =  3800 + ((double)rand() / RAND_MAX)*(100-50)+50;
	else if(times_r == 40)
		r = 4000 + ((double)rand() / RAND_MAX)*(100-50)+50;
	
	
	
	double pos[3] = { r*cos(angle[1])*sin(angle[0]), r*sin(angle[1]),  r*cos(angle[1])*cos(angle[0]) };
	printf("the r is %lf\n",r);	
	//r +=  ((double)rand() / RAND_MAX)*(600-400)+400;
	
	gluLookAt(pos[0], pos[1], pos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(-90,1.0,0.0,0.0);
	glScalef(scale,scale,scale);

	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

	float projection[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projection);


	glUniformMatrix4fv(modelview_loc, 1, GL_FALSE, modelview);
	glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection);


	//gluLookAt(0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_TRIANGLES);
	for(i=0;i<n_face;i++)
	{
		int count=fap[i].order[0];
		glVertex3f(ver[count].x,ver[count].y,ver[count].z);
		count=fap[i].order[1];
		glVertex3f(ver[count].x,ver[count].y,ver[count].z);
		count=fap[i].order[2];
		glVertex3f(ver[count].x,ver[count].y,ver[count].z);
	}
	glEnd();
	/*
	if(times_pitch == 1)
		angle[1] = 0;
	else if(times_pitch == 2)
		angle[1] = (5.0/180.0)*3.1415925;
	else if(times_pitch == 3)
		angle[1] = (10.0/180.0)*3.1415925;
	else if(times_pitch == 4)
		angle[1] = (15.0/180.0)*3.1415925;
	else if(times_pitch == 5)
		angle[1] = (20.0/180.0)*3.1415925;
	else if(times_pitch == 6)
		angle[1] = (25.0/180.0)*3.1415925;
	else if(times_pitch == 7)
		angle[1] = (30.0/180.0)*3.1415925;
	else if(times_pitch == 8)
		angle[1] = (35.0/180.0)*3.1415925;*/
	
	
	if(times_pitch == 1)
		angle[1] = 0;
	else if(times_pitch == 2)
		angle[1] = (1.0/180.0)*3.1415925;
	else if(times_pitch == 3)
		angle[1] = (2.0/180.0)*3.1415925;
	else if(times_pitch == 4)
		angle[1] = (3.0/180.0)*3.1415925;
	else if(times_pitch == 5)
		angle[1] = (4.0/180.0)*3.1415925;
	else if(times_pitch == 6)
		angle[1] = (5.0/180.0)*3.1415925;
	else if(times_pitch == 7)
		angle[1] = (6.0/180.0)*3.1415925;
	else if(times_pitch == 8)
		angle[1] = (7.0/180.0)*3.1415925;
	else if(times_pitch == 9)
		angle[1] = (8.0/180.0)*3.1415925;
	else if(times_pitch == 10)
		angle[1] = (9.0/180.0)*3.1415925;
	else if(times_pitch == 11)
		angle[1] = (10.0/180.0)*3.1415925;
	else if(times_pitch == 12)
		angle[1] = (11.0/180.0)*3.1415925;
	else if(times_pitch == 13)
		angle[1] = (12.0/180.0)*3.1415925;
	else if(times_pitch == 14)
		angle[1] = (13.0/180.0)*3.1415925;
	else if(times_pitch == 15)
		angle[1] = (14.0/180.0)*3.1415925;
	else if(times_pitch == 16)
		angle[1] = (15.0/180.0)*3.1415925;
	else if(times_pitch == 17)
		angle[1] = (16.0/180.0)*3.1415925;
	else if(times_pitch == 18)
		angle[1] = (17.0/180.0)*3.1415925;
	else if(times_pitch == 19)
		angle[1] = (18.0/180.0)*3.1415925;
	else if(times_pitch == 20)
		angle[1] = (19.0/180.0)*3.1415925;
	else if(times_pitch == 21)
		angle[1] = (20.0/180.0)*3.1415925;
	else if(times_pitch == 22)
		angle[1] = (21.0/180.0)*3.1415925;
	else if(times_pitch == 23)
		angle[1] = (22.0/180.0)*3.1415925;
	else if(times_pitch == 24)
		angle[1] = (23.0/180.0)*3.1415925;
	else if(times_pitch == 25)
		angle[1] = (24.0/180.0)*3.1415925;
	else if(times_pitch == 26)
		angle[1] = (25.0/180.0)*3.1415925;
	else if(times_pitch == 27)
		angle[1] = (26.0/180.0)*3.1415925;
	else if(times_pitch == 28)
		angle[1] = (27.0/180.0)*3.1415925;
	else if(times_pitch == 29)
		angle[1] = (28.0/180.0)*3.1415925;
	else if(times_pitch == 30)
		angle[1] = (29.0/180.0)*3.1415925;
	else if(times_pitch == 31)
		angle[1] = (30.0/180.0)*3.1415925;
	else if(times_pitch == 32)
		angle[1] = (31.0/180.0)*3.1415925;
	else if(times_pitch == 33)
		angle[1] = (32.0/180.0)*3.1415925;
	else if(times_pitch == 34)
		angle[1] = (33.0/180.0)*3.1415925;
	else if(times_pitch == 35)
		angle[1] = (34.0/180.0)*3.1415925;
	else if(times_pitch == 36)
		angle[1] = (35.0/180.0)*3.1415925;
	else if(times_pitch == 37)
		angle[1] = (36.0/180.0)*3.1415925;
	else if(times_pitch == 38)
		angle[1] = (37.0/180.0)*3.1415925;
	else if(times_pitch == 39)
		angle[1] = (38.0/180.0)*3.1415925;
	else if(times_pitch == 40)
		angle[1] = (39.0/180.0)*3.1415925;
	
	

	
	//angle[1] += (5.0/180.0)*3.1415925;
	//if(times > 19)
	//	angle[0] = (0/180.0)*3.1415925;
	//else

	angle[0] += (18.0/180.0)*3.1415925;
	
	
	glReadPixels(0, 0, window_width, window_height, GL_RGB, GL_UNSIGNED_BYTE, frame_data);
	frame = cv::Mat(window_height, window_width, CV_8UC3, frame_data);
	cv::split(frame, channels);
	channels_vec.clear();
	channels_vec.push_back(channels[2]);
	channels_vec.push_back(channels[1]);
	cv::merge(channels_vec, temp);
	frame_16u = cv::Mat(window_height, window_width, CV_16U, temp.data);
	cv::flip(frame_16u,frame_16u,0);
	stream.clear();	
	stream << times;
	stream >> name_pic;
	std::cout<<name_pic<<std::endl;
	string name1 = name_pic.append(".png");
	string path = "/media/zf/22D6BB82D6BB552F/depth_image/";
	string name = path.append(name1);
	std::cout << name << std::endl;
	cv::imwrite("/media/zf/22D6BB82D6BB552F/depth_image/" + name1, frame_16u);
	//cv::imwrite("/home/zf/abc.png", frame_16u);
	//fprintf(file_label,"%s %d\n",name,times_pitch+1);
	//fprintf(file_label,"%s\n",name);
	
	/*
	if(label == 21)
	{	
		
		label = 1;
		file_label << name << " " << label <<endl;
	}
	else
	{
		file_label << name << " " << label <<endl;
		label = label + 1;
	}*/
	printf("hello %s\n", (char*)frame_data);
	printf("times = %d\n",times);
	printf("times_pitch = %d\n",times_pitch);
	printf("times_r = %d\n",times_r);
	glEnable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
	//sleep(1);
	if(times < (20*40*40+1)) {
		glutPostRedisplay();

		
		times_pitch = (times/20)%40 + 1;
		times_r = (times/800)%40 + 1;
		label = (times-1)%20;
		file_label << name << " " << label <<endl;
		times++;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'p':glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);glutPostRedisplay();break;
		case 'l':glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);glutPostRedisplay();break;
		case 'f':glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);glutPostRedisplay();break;
		case '1':angle[0] += (10.0/180.0)*3.1415925; glutPostRedisplay();break;
		case '2':angle[1] += (10.0/180.0)*3.1415925; glutPostRedisplay();break;
		case 't':
			for (int i = 0; i < 20; i++)
			 {
				angle[0] += (18.0/180.0)*3.1415925;
				glutPostRedisplay();			
				printf("%d\n", i);
				sleep(1);
		}
		break;
		case 'r':
			glReadPixels(0, 0, window_width, window_height, GL_RGB, GL_UNSIGNED_BYTE, frame_data);
			frame = cv::Mat(window_width, window_width, CV_8UC3, frame_data);


			cv::split(frame, channels);
			channels_vec.clear();
			channels_vec.push_back(channels[2]);
			channels_vec.push_back(channels[1]);
			cv::merge(channels_vec, temp);
			frame_16u = cv::Mat(window_height, window_width, CV_16U, temp.data);
			cv::imwrite("/home/zf/abc.png", frame_16u);
			printf("hello %s\n", (char*)frame_data);
		break;
		case 'q':exit(1);
	}
}
void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		scale*=1.1;
		glutPostRedisplay();
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		
		for(i=0;i<10;i++)
		{
			spin=spin+1;
		    glutPostRedisplay();
			glFlush();
		}
	}
}
void init(int *argc, char **argv)
{

	// Open window 
	glutInit(argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(window_width, window_height);

	

	glutCreateWindow("OFF MADE BY SAM JJX");

	// Initialize GLUT callback functions 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glutReshapeFunc(GLUTResize);
	glutDisplayFunc(redraw);
		
	glutKeyboardFunc(keyboard);
	//glutKeyboardFunc(mouse);
	glutMouseFunc(mouse);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	//glutMotionFunc(motion);
	glutIdleFunc(0);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "error: '%s'\n", glewGetErrorString(res));
		return;
	}

	GLuint program = LoadShaders("triangles.vert", "triangles.frag");
	glValidateProgram(program);
	glUseProgram(program);

	modelview_loc = glGetUniformLocation(program, "modelview");
	projection_loc = glGetUniformLocation(program, "projection");
	


}
int main(int argc, char** argv)
{
	srand((int)time(0));
	init(&argc,argv);
	readoff(filename);
	
	frame_data = malloc( window_width * window_height * 3);
	file_label.open("/home/zf/off_label.txt",ios::app);
	glutMainLoop();

	free(frame_data);
	file_label.close();
	return 0;
}

