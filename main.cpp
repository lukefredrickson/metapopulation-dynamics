#include "main.h"
#include "simulation.h"
#include "patch.h"
#include "variable_fill_circle.h"
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
bool left_mouse_pressed = false;
bool layout_locked = false;
Simulation sim;
const Species SPECIES = Species();

void init() {
    width = 1000;
    height = 500;
    int gens =  100;
    sim = Simulation(gens, SPECIES);
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE
    
    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE
    
    /* render circles */
    sim.draw();

    
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    switch(key) {
        // enter: lock layout
        case 13: {
            sim.run();
            // run simulation
            break;
        }
        // esc: destroy window
        case 27: {
            glutDestroyWindow(wd);
            exit(0);
            break;
        }
        // del: delete last circle if layout isn't locked, mouse isn't pressed down, and there is a circle to delete
        case 127: {
            if(!sim.is_running() && !left_mouse_pressed) {
                sim.delete_last_patch();
            }
            break;
        }
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP: {
            if (!sim.is_running() && !left_mouse_pressed) {
                sim.increment_population_last_patch();
            }
            break;
        }
        case GLUT_KEY_DOWN: {
            if (!sim.is_running() && !left_mouse_pressed) {
                sim.decrement_population_last_patch();
            }
            break;
        }
    }
    
    glutPostRedisplay();
}

void drag(int x, int y) {

    if (!sim.is_running()) {
        if (left_mouse_pressed) {
            point2D here = point2D(static_cast<double>(x), static_cast<double>(y));
            point2D center = sim.get_ecosystem().back() -> getCenter();
            sim.update_radius_last_patch(center.distance(here));
        }
    }
    glutPostRedisplay();

}




// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // The left button has been pressed down
        left_mouse_pressed = true;
        // if the layout hasn't been locked in already, user is free to make new habitats.
        if (!sim.is_running()) {
            Variable_Fill_Circle c = Variable_Fill_Circle(color(1,1,1,1),
                    point2D(x,y), 0, color(0,0,0,1), 0);
            sim.add_patch(c);
        }

    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // The left button has been released
        left_mouse_pressed = false;
    }
    
    glutPostRedisplay();
}

void timer(int dummy) {
    
//    glutPostRedisplay();
//    glutTimerFunc(30, timer, dummy);
}


void resize(int w, int h) {
    // ignore params, snap window back to previous size
    glutReshapeWindow( width, height);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(250, 180); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Metapopulation Dynamics Simulation - Luke Fredrickson (May 2020)" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles click and drag movement
    glutMotionFunc(drag);
    
    // handles mouse click
    glutMouseFunc(mouse);

    // handles window resizing
    glutReshapeFunc(resize);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
