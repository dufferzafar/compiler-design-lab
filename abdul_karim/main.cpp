
#include <stdlib.h>
#include <GLUT/glut.h>

GLfloat ctrlpoints[4][3] = {
    {-2.5, 4.0, 0.0}, { -2.0, 4.0, 0.0}, 
    {1.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
}

void display(void)
{
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= 30; i++) 
        glEvalCoord1f((GLfloat) i/30.0);
    glEnd();
    /* The following code displays the control points as dots. */
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 4; i++) 
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
                5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
    else
        glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
                5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

float ballX = -0.3f;
float ballY = -0.3f;
float ballZ = -1.0f;
/*
 float ballX2 = 0.3f;
 float ballY2 = 0.0f;
 float ballZ2 = -1.0f;
 */
static int flag=1;

void drawBall(void) {
    
    glColor3f(0.0, 1.0, 0.0); //set ball colour
    glTranslatef(ballX,ballY,ballZ); //moving it toward the screen a bit on creation
    glutSolidSphere (0.1, 30, 30); //create ball.
    
}

void keyPress(int key, int x, int y)
{
        if(key==GLUT_KEY_UP)
        {
            ballX += 0.01f;
            ballY+=0.01f;
    
        }
    if(key == GLUT_KEY_RIGHT)
    {
        ballX+=0.01f;
    }
    if(key==GLUT_KEY_DOWN)
    {
        ballX  += 0.01f;
        ballY -=0.01f;
    }
    
    glutPostRedisplay();
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    drawBall();

    
    glutSwapBuffers();
}

//float _angle = 30.0f;
void update(int value) {
    if(flag==1)
    {
        ballX += 0.002f;
        ballY+=0.002f;
        if(ballX>0.3)
        {
            flag=2;
        }
    }
    
    if(flag==2)
    {
        ballX +=0.002f;
        
        if(ballY==0.4)
        {
            flag=0;
        }
    }
    
    if (flag==0)
    {
        ballX += 0.002f;
        ballY-=0.002f;
        if(ballX<-0.3)
        {
            flag=1;
        }
    }  
    glutPostRedisplay(); //Tell GLUT that the display has changed
    
    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}


int main(int argc, char** argv)
{
    /*glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);

    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
  
    glutMainLoop();
     */
    
    glutInit(&argc,argv);
    
    glutInitDisplayMode(GLUT_SINGLE| GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    
    glutInitWindowSize(2000,500);
    
    glutCreateWindow("Moving Circle");
    
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyPress);
    
    glutReshapeFunc(handleResize);
    


    initRendering();
    
    glutDisplayFunc(drawScene);
    
 
    glutTimerFunc(25, update, 0);    
    glutMainLoop();
    return 0;
}