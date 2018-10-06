package graphics;

import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.awt.GLJPanel;
import com.jogamp.opengl.glu.GLU;
import input.KeyboardInput;
import input.KeyboardObserver;
import input.MouseInput;
import input.MouseObserver;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

public class OpenGL extends GLJPanel implements GLEventListener, MouseObserver, KeyboardObserver {
    private static OpenGL instance = null;

    public static GL2 gl = null;
    public static GLU glu = null;

    double[] testPos = new double[]{0.0d, 0.0d, 0.0d};
    double[] testPosCam = new double[]{0.0d, 500.0d, 0.0d};
    double[] testWH = new double[]{32.0d, 32.0d};
    double testSpeed = 1;


    private OpenGL(int VIEWPORT_WIDTH, int VIEWPORT_HEIGHT){
        setPreferredSize(new Dimension(VIEWPORT_WIDTH, VIEWPORT_HEIGHT));
        addGLEventListener(this);

        KeyboardInput.initSingleton(instance);
        KeyboardInput ki = KeyboardInput.getInstance();

        MouseInput.initSingleton();
        MouseInput mi = MouseInput.getInstance();

        addKeyListener(ki);
        addMouseListener(mi);
        addMouseMotionListener(mi);
        addMouseWheelListener(mi);
    }

    public static void initSingleton(int WINDOW_WIDTH, int WINDOW_HEIGHT){
        if(instance == null){
            instance = new OpenGL(WINDOW_WIDTH, WINDOW_HEIGHT);
            MouseInput.addObserver(instance, new MouseInput.type[]{MouseInput.type.CLICK, MouseInput.type.ENTER, MouseInput.type.EXIT});
            KeyboardInput.addObserver(instance);
        }
    }

    public static OpenGL getInstance(){
        return instance;
    }

    public void notify(MouseEvent e, MouseInput.type t) {
        switch(t){
            case CLICK:
                System.out.println("Clicked! x: " + e.getX() + ", y:" + e.getY());
                break;
            case ENTER:
                System.out.println("Entered!");
                break;
            case EXIT:
                System.out.println("Exited!");
                break;
        }
    }

    ArrayList<Integer> pressed = new ArrayList<Integer>();

    public void notify(KeyEvent e, KeyboardInput.type t) {
        switch(t){
            case PRESSED:
                pressed.add(e.getKeyCode());
                break;
            case RELEASED:
                pressed.remove((Integer)e.getKeyCode());
                break;
        }
    }

    private boolean getPressed(int keycode){
        if(pressed.contains(keycode)){
            return true;
        }
        return false;
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
            testPos[0] += testSpeed;

        } else if(getPressed(KeyEvent.VK_A)){
            testPos[0] -= testSpeed;
        }

        if(getPressed(KeyEvent.VK_W )){
            testPos[2] -= testSpeed;
        } else if(getPressed(KeyEvent.VK_S)){
            testPos[2] += testSpeed;
        }

        if(getPressed(KeyEvent.VK_RIGHT )){
            testPosCam[0] += testSpeed;
        } else if(getPressed(KeyEvent.VK_LEFT)){
            testPosCam[0] -= testSpeed;
        }

        if(getPressed(KeyEvent.VK_UP )){
            testPosCam[2] -= testSpeed;
        } else if(getPressed(KeyEvent.VK_DOWN)){
            testPosCam[2] += testSpeed;
        }

        gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT); // clear color and depth buffers
        gl.glPushMatrix();
        glu.gluLookAt(testPos[0] + testPosCam[0], testPos[1] + testPosCam[1], testPos[2] + testPosCam[2], testPos[0], testPos[1], testPos[2], 0, 0, -1);

        // X axis, blue.
        gl.glColor4d(0.0d, 0.0d,1.0d,1.0d);
        gl.glBegin(gl.GL_LINES);
            gl.glVertex3d(0.0d, 0.0d, 0.0d);
            gl.glVertex3d(32.0d, 0.0d, 0.0d);
        gl.glEnd();

        // Y axis, green.
        gl.glColor4d(0.0d, 1.0d,0.0d,1.0d);
        gl.glBegin(gl.GL_LINES);
            gl.glVertex3d(0.0d, 0.0d, 0.0d);
            gl.glVertex3d(0.0d, 32.0d, 0.0d);
        gl.glEnd();

        // Z axis, red.
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
}
