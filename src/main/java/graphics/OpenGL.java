package graphics;

import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.awt.GLJPanel;
import com.jogamp.opengl.glu.GLU;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;

public class OpenGL extends GLJPanel implements GLEventListener, KeyListener {
    public static GL2 gl = null;
    public static GLU glu = null;

    private static int WINDOW_WIDTH;
    private static int WINDOW_HEIGHT;


    double[] testPos = new double[]{0.0d, 0.0d, 0.0d};
    double[] testPosCam = new double[]{0.0d, 500.0d, 0.0d};
    double[] testWH = new double[]{32.0d, 32.0d};
    double speed = 1;


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
        //gl.glHint(GL2.GL_PERSPECTIVE_CORRECTION_HINT, GL2.GL_NICEST);
    }

    public void dispose(GLAutoDrawable glAutoDrawable) {

    }

    public void display(GLAutoDrawable glAutoDrawable) {



        if(getPressed(KeyEvent.VK_D )){
            testPos[0] += speed;

        } else if(getPressed(KeyEvent.VK_A)){
            testPos[0] -= speed;

        }

        if(getPressed(KeyEvent.VK_W )){
            testPos[2] += speed;
        } else if(getPressed(KeyEvent.VK_S)){
            testPos[2] -= speed;
        }

        if(getPressed(KeyEvent.VK_RIGHT )){
            testPosCam[0] += speed;
        } else if(getPressed(KeyEvent.VK_LEFT)){
            testPosCam[0] -= speed;
        }

        if(getPressed(KeyEvent.VK_UP )){
            testPosCam[2] += speed;
        } else if(getPressed(KeyEvent.VK_DOWN)){
            testPosCam[2] -= speed;
        }

        gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT); // clear color and depth buffers
        gl.glPushMatrix();

        //glu.gluLookAt(0, 10, 0, 0, 0, 0, 1, 0, 0);
        gl.glScaled(-1.0d, 1.0d, 1.0d);
        glu.gluLookAt(testPos[0] + testPosCam[0], testPos[1] + testPosCam[1], testPos[2] + testPosCam[2], testPos[0], testPos[1], testPos[2], 0, 0, 1);

        //gl.glScaled(1920.0d, 1080.0d, 0.0d);


        // X, blue.
        gl.glColor4d(0.0d, 0.0d,1.0d,1.0d);
        gl.glBegin(gl.GL_LINES);
        gl.glVertex3d(0.0d, 0.0d, 0.0d);
        gl.glVertex3d(32.0d, 0.0d, 0.0d);
        gl.glEnd();

        // Y, green.
        gl.glColor4d(0.0d, 1.0d,0.0d,1.0d);
        gl.glBegin(gl.GL_LINES);
        gl.glVertex3d(0.0d, 0.0d, 0.0d);
        gl.glVertex3d(0.0d, 32.0d, 0.0d);
        gl.glEnd();

        // Z, red.
        gl.glColor4d(1.0d, 0.0d,0.0d,1.0d);
        gl.glBegin(gl.GL_LINES);
        gl.glVertex3d(0.0d, 0.0d, 0.0d);
        gl.glVertex3d(0.0d, 0.0d, 32.0d);
        gl.glEnd();

        gl.glColor4d(1.0d, 1.0d, 1.0d, 1.0d);
        gl.glBegin(gl.GL_QUADS);
        gl.glVertex3d((-1/2.0d * testWH[0]) + testPos[0], 0.0d + testPos[1], (-1/2.0d * testWH[1]) + testPos[2]); //Bottom left
        gl.glVertex3d((1/2.0d * testWH[0]) + testPos[0], 0.0d + testPos[1], (-1/2.0d * testWH[1]) + testPos[2]);  //Bottom right
        gl.glVertex3d((1/2.0d * testWH[0]) + testPos[0], 0.0d + testPos[1], (1/2.0d * testWH[1]) + testPos[2]);   //Top right
        gl.glVertex3d((-1/2.0d * testWH[0]) + testPos[0], 0.0d + testPos[1], (1/2.0d * testWH[1]) + testPos[2]);  //Top left
        gl.glEnd();

        gl.glPopMatrix();

        gl.glFlush();
    }

    public void reshape(GLAutoDrawable glAutoDrawable, int i, int i1, int i2, int i3) {
        //gl.glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        glu.gluPerspective(45.0f, 1920.0d/1080.0d, 0.1, 10000.0);
        gl.glMatrixMode(GL2.GL_MODELVIEW);
        gl.glLoadIdentity();

    }

    ArrayList<Integer> pressedKeys = new ArrayList<Integer>();

    public void keyTyped(KeyEvent e) {

    }

    public void keyPressed(KeyEvent e) {
        //System.out.println(e.getKeyCode());

        if(!pressedKeys.contains(e.getKeyCode())){
            pressedKeys.add(e.getKeyCode());
        }
    }

    public void keyReleased(KeyEvent e) {
        pressedKeys.remove((Integer)e.getKeyCode());
    }

    public boolean getPressed(Integer k){
        if(pressedKeys.contains(k)){
            return true;
        }
        return false;
    }
}
