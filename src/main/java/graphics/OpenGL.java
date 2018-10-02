package graphics;

import com.jogamp.opengl.GL;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.awt.GLJPanel;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class OpenGL extends GLJPanel implements GLEventListener, KeyListener {
    public static GL2 gl = null;


    public OpenGL(){
        //setPreferredSize(new Dimension(WINDOW_HEIGHT, WINDOW_WIDTH));
        addGLEventListener(this);
        addKeyListener(this);
    }

    public void init(GLAutoDrawable glAutoDrawable) {
        gl = glAutoDrawable.getGL().getGL2();
        gl.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    }

    public void dispose(GLAutoDrawable glAutoDrawable) {

    }

    public void display(GLAutoDrawable glAutoDrawable) {
        gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT); // clear color and depth buffers
        gl.glColor3d(1.0f ,1.0f, 1.0f); //White
        //gl.glTranslated(-1.0d, -1.0d, -5.0d);

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
        gl.glPopMatrix();
        gl.glFlush();

    }

    public void reshape(GLAutoDrawable glAutoDrawable, int i, int i1, int i2, int i3) {

    }

    public void keyTyped(KeyEvent e) {

    }

    public void keyPressed(KeyEvent e) {

    }

    public void keyReleased(KeyEvent e) {

    }
}
