#include <stdio.h> 
#include <stdlib.h> 
#include <GLEW/glew.h> 
#include <GL/gl.h> 
#include <GLFW/glfw3.h> 
#include <math.h> 
#define CLOSE 1
#define OPEN 0

typedef struct point{
    float x;
    float y; 
} point; 

point NewPoint(float x, float y){
    point p; 
    p.x = x;
    p.y = y; 
    return p; 
} 
void PrintP(point p){
    printf("P<%0.4f, %0.4f>\n", p.x, p.y); 
}



int Draw(point* points, int numPoints, int closed){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit(); 
    if (GLEW_OK){
        fprintf(stdout, "Error: %s\n", glewGetErrorString(err)); 
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "Supported OpenGL: %s\n", glGetString(GL_VERSION));


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); 
        glBegin(GL_LINES); 

        glLineWidth(2); 
        glColor3f(1, 1, 1); 
            for(int n = 0; n<((numPoints-1+closed)*2); n++){
                glVertex2f(points[n].x, points[n].y); 
            }
        glEnd(); 

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}


point* calculateLines(point* points, int numPoints, int closed){
    point* lines = (point*)calloc(sizeof(point),(numPoints-1)*2); 
    lines[0] = points[0];
    lines[1] = points[1]; 
    for(int n = 2, m = 2; n<(numPoints-1)*2; n+=2, m++){
        printf("Loop: %d / %d\n", n, ((numPoints-1)*2)); 
        lines[n] = lines[n-1];
        lines[n+1] = points[m];
    }
    int new_size = (numPoints-1)*2; 
    if(closed){
        new_size = numPoints*2;
        lines = (point*)realloc(lines, sizeof(point)*new_size);
        lines[new_size-2] = lines[new_size-3];
        lines[new_size-1] = lines[0];
    }
    return lines; 
}

int main(){
    point points[] = {NewPoint(-0.10, -0.10), NewPoint(0.10, -0.10), NewPoint(0.0, 0.10)};
    point* lines = calculateLines(points, 3, CLOSE); 
    int err = 0; 
    err = Draw(lines, 3, CLOSE); 
    free(lines); 
    return err; 
}
