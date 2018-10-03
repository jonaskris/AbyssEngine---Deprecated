package graphics;

import com.jogamp.opengl.GL;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.awt.GLJPanel;
import com.jogamp.opengl.glu.GLU;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class OpenGL extends GLJPanel implements GLEventListener, KeyListener {
    public static GL2 gl = null;
    public static GLU glu = null;

    private static int WINDOW_WIDTH;
    private static int WINDOW_HEIGHT;


    double[] testPos = new double[]{0.0d, 0.0d, 0.0d};
    double speed = 0.1;


    public OpenGL(int WINDOW_WIDTH, int WINDOW_HEIGHT){
        //setPreferredSize(new Dimension(WINDOW_HEIGHT, WINDOW_WIDTH));
        addGLEventListener(this);
        addKeyListener(this);

        this.WINDOW_WIDTH = WINDOW_WIDTH;
        this.WINDOW_HEIGHT = WINDOW_HEIGHT;
    }

    public void init(GLAutoDrawable glAutoDrawable) {
        gl = glAutoDrawable.getGL().getGL2();
        glu = new GLU();
        gl.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //gl.glShadeModel(GL2.GL_SMOOTH);
        //gl.glClearDepth(1.0f);
        gl.glEnable(GL2.GL_DEPTH_TEST);
        //gl.glDepthFunc(GL2.GL_LEQUAL);
        gl.glHint(GL2.GL_PERSPECTIVE_CORRECTION_HINT, GL2.GL_NICEST);
    }

    public void dispose(GLAutoDrawable glAutoDrawable) {

    }

    public void display(GLAutoDrawable glAutoDrawable) {
        gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT); // clear color and depth buffers
        gl.glLoadIdentity();
        gl.glColor3d(1.0f ,1.0f, 1.0f); //White

        glu.gluLookAt(0, 0, 0, testPos[0], testPos[1], testPos[2], 0, 1, 0);
        gl.glPushMatrix();
        //gl.glTranslated(-1.0d, -1.0d, 0.0d);
        //gl.glScaled(1920.0d, 1080.0d, 0.0d);
        //gl.glTranslated(-1920.0d/2, -1080.0d/2, 0.0d);
            gl.glBegin(gl.GL_LINES);
               //gl.glVertex3d(0.0d, 0.0d, 0.0d);
               //gl.glVertex3d(1920.0d, 1080.0d, 0.0d);
                gl.glVertex3d(-1.0d, -1.0d, 0.0d);
                gl.glVertex3d(1.0d, 1.0d, 0.0d);
            gl.glEnd();

            gl.glBegin(gl.GL_TRIANGLES);
                gl.glVertex3d(-1.0d + testPos[0], -1.0d + testPos[1], 0.0d + testPos[2]);
                gl.glVertex3d(0.0d + testPos[0], 1.0d + testPos[1], 0.0d + testPos[2]);
                gl.glVertex3d(1.0d + testPos[0], -1.0d + testPos[1], 0.0d + testPos[2]);
                gl.glEnd();


        gl.glPopMatrix();
        gl.glFlush();

    }

    public void reshape(GLAutoDrawable glAutoDrawable, int i, int i1, int i2, int i3) {
        //gl.glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        glu.gluPerspective( 45.0f, 1920.0d/1080.0d, 0.1, 100.0 );
        gl.glMatrixMode(GL2.GL_MODELVIEW);
        gl.glLoadIdentity();

    }

    public void keyTyped(KeyEvent e) {

    }

    public void keyPressed(KeyEvent e) {
        System.out.println(e.getKeyChar());

        switch(e.getKeyChar()){
            case 'q':
                testPos[0] += speed;
                break;
            case 'a':
                testPos[0] -= speed;
                break;
            case 'w':
                testPos[1] += speed;
                break;
            case 's':
                testPos[1] -= speed;
                break;
            case 'e':
                testPos[2] += speed;
                break;
            case 'd':
                testPos[2] -= speed;
                break;
        }

    }

    public void keyReleased(KeyEvent e) {

    }
}
