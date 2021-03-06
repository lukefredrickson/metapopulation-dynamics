#include "main.h"
#include "simulation.h"
#include "patch.h"
#include "variable_fill_circle.h"
#include "Eigen/Dense"
#include "stochastic_event.h"
using namespace std;

GLdouble width, height;
int timer_duration; // duration of one season (ms)
int wd;
bool left_mouse_pressed = false;
Simulation sim;

// CHANGE SPECIES VALUES HERE
double species_r = 0.2;
double species_emigration_prop = 0.2;
double species_migration_dist_modifier = 1.5;
double species_migrant_mortality = 0.25;
int species_probable_extinction_pop = 20;

const Species SPECIES = Species(species_r, species_emigration_prop, species_migration_dist_modifier,
                                species_migrant_mortality, species_probable_extinction_pop);

void init() {
    // WINDOW DIMENSIONS (px)
    width = 1000;
    height = 1000;
    // CHANGE SIMULATION VALUES HERE
    timer_duration = 1000;
    int generations_to_run =  50;
    double winter_harshness = 0.4; // proportion of summer carrying capacity each patch reduces to in winter
    sim = Simulation(generations_to_run, SPECIES, winter_harshness);
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
    
    // render all patches in simulation
    sim.draw();

    
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    switch(key) {
        // enter: run simulation
        case 13: {
            if(!sim.is_running()) {
                // run simulation
                sim.run();
                // begin simulation timer
                glutTimerFunc(0, sim_timer, 0);
            }
            break;
        }
        // esc: destroy window
        case 27: {
            glutDestroyWindow(wd);
            exit(0);
            break;
        }
        // del: delete last circle if the sim isn't running and left mouse isn't pressed down
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
        // up arrow increases population of most recently created patch
        case GLUT_KEY_UP: {
            if (!sim.is_running() && !left_mouse_pressed) {
                sim.increment_population_last_patch();
            }
            break;
        }
        // down arrow decreases population of most recently created patch
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
            // continuously update the radius of the last patch from that patch's center to the current coords
            // stop when left mouse released
            point2D here = point2D(static_cast<double>(x), static_cast<double>(y));
            point2D center = sim.get_ecosystem().back() -> getCenter();
            sim.update_radius_last_patch(center.distance(here));
        }
    }
    glutPostRedisplay();

}

void mouse(int button, int state, int x, int y) {
    // button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
    // state will be GLUT_UP or GLUT_DOWN
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // The left button has been pressed down
        left_mouse_pressed = true;
        // if the layout hasn't been locked in already, user is free to make new habitats.
        if (!sim.is_running()) {
            // add a patch to the ecosystem where the user clicks -- dragging to change radius handled in drag function
            Variable_Fill_Circle c = Variable_Fill_Circle(point2D(static_cast<double>(x), static_cast<double>(y)), 0,
                    0, color(1,1,1,1),color(0,0,0,1),
                    color(1,1,1,1), color(1,0,0,1));
            sim.add_patch(c);
        }
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // The left button has been released
        left_mouse_pressed = false;
    }
    glutPostRedisplay();
}

// main simulation clock, switches between simulating season and incrementing season for n generations to run.
void sim_timer(int switcher) {
    if (sim.is_running()) {
        switch(switcher) {
            case 0 : {
                sim.simulate_season();
                switcher = 1;
                break;
            }
            case 1 : {
                sim.increment_season();
                switcher = 0;
                break;
            }
            default : {
                switcher = 0;
            }
        }
        glutPostRedisplay();
    }
    if (sim.get_current_generation() > sim.get_generations_to_run()) {
        sim.stop();
    } else if (sim.is_running()) {
        glutTimerFunc(timer_duration/2, sim_timer, switcher);
    }
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
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}