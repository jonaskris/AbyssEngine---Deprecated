package graphics;

import com.jogamp.opengl.*;
import com.jogamp.opengl.awt.GLJPanel;
import com.jogamp.opengl.glu.GLU;
import com.jogamp.opengl.math.FloatUtil;
import com.jogamp.opengl.util.GLBuffers;
import com.jogamp.opengl.util.glsl.ShaderCode;
import com.jogamp.opengl.util.glsl.ShaderState;
import graphics.shaders.ShaderLoader;
import input.KeyboardInput;
import input.KeyboardObserver;
import input.MouseInput;
import input.MouseObserver;

import java.nio.IntBuffer;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;


import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

public class OpenGL extends GLJPanel implements GLEventListener{
    private static OpenGL instance = null;
    private ShaderState st;

    private static GL3 gl = null;
    private static GLU glu = null;

    private final String vertexShaderPath = "src/main/java/graphics/shaders/shader.vert";
    private final String fragmentShaderPath = "src/main/java/graphics/shaders/shader.frag";

    double[] testPos = new double[]{0.0d, 0.0d, 0.0d};
    double[] testPosCam = new double[]{0.0d, 500.0d, 0.0d};
    double[] testWH = new double[]{32.0d, 32.0d};
    double testSpeed = 1;

    private int shaderProgram;

    // Data
        float[] vertexData = new float[]{
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f, 1.0f, 0.0f
        };

    // Buffers
        IntBuffer buffers = IntBuffer.allocate(1);
        IntBuffer vertexArray = IntBuffer.allocate(1);
        FloatBuffer vertexBuffer = FloatBuffer.wrap(vertexData);



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
            //MouseInput.addObserver(instance, new MouseInput.type[]{MouseInput.type.CLICK, MouseInput.type.ENTER, MouseInput.type.EXIT});
            //KeyboardInput.addObserver(instance);
        }
    }

    public static OpenGL getInstance(){
        return instance;
    }

    /*
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
    */

    public void init(GLAutoDrawable glAutoDrawable) {
        gl = glAutoDrawable.getGL().getGL3();
        glu = new GLU();
        //gl.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //gl.glShadeModel(GL2.GL_SMOOTH);
        //gl.glClearDepth(1.0f);
        //gl.glEnable(GL2.GL_DEPTH_TEST);
        //gl.glDepthFunc(GL2.GL_LEQUAL);
        //gl.glHint(GL2.GL_PERSPECTIVE_CORRECTION_HINT, GL2.GL_NICEST);

        initVertexArray();
        initShaders();
        initBuffers();

        gl.glEnable(GL.GL_DEPTH_TEST);
    }
    private void initVertexArray(){
        gl.glGenVertexArrays(1, vertexArray);
        gl.glBindVertexArray(vertexArray.get(0));
    }
    private void initBuffers(){
        gl.glGenBuffers(1, buffers);
        gl.glBindBuffer(gl.GL_ARRAY_BUFFER, buffers.get(0));
        gl.glBufferData(gl.GL_ARRAY_BUFFER, 4 * 3 * 3, vertexBuffer, gl.GL_STATIC_DRAW);
    }

    private void initShaders(){
        shaderProgram = ShaderLoader.loadShaders(gl, vertexShaderPath, fragmentShaderPath);
        gl.glUseProgram(shaderProgram);
    }

    public void dispose(GLAutoDrawable glAutoDrawable) {

    }

    public void display(GLAutoDrawable glAutoDrawable) {
        // GL2
        /*if(getPressed(KeyEvent.VK_D )){
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

        gl.glPushMatrix();
        glu.gluLookAt(testPos[0] + testPosCam[0], testPos[1] + testPosCam[1], testPos[2] + testPosCam[2], testPos[0], testPos[1], testPos[2], 0, 0, -1);

        if(DevSettings.drawAxii) {
            // X axis, blue.
            gl.glColor4d(0.0d, 0.0d, 1.0d, 1.0d);
            gl.glBegin(gl.GL_LINES);
            gl.glVertex3d(0.0d, 0.0d, 0.0d);
            gl.glVertex3d(32.0d, 0.0d, 0.0d);
            gl.glEnd();

            // Y axis, green.
            gl.glColor4d(0.0d, 1.0d, 0.0d, 1.0d);
            gl.glBegin(gl.GL_LINES);
            gl.glVertex3d(0.0d, 0.0d, 0.0d);
            gl.glVertex3d(0.0d, 32.0d, 0.0d);
            gl.glEnd();

            // Z axis, red.
            gl.glColor4d(1.0d, 0.0d, 0.0d, 1.0d);
            gl.glBegin(gl.GL_LINES);
            gl.glVertex3d(0.0d, 0.0d, 0.0d);
            gl.glVertex3d(0.0d, 0.0d, 32.0d);
            gl.glEnd();
        }

        gl.glColor4d(1.0d, 1.0d, 1.0d, 1.0d);
        gl.glBegin(gl.GL_QUADS);
            gl.glVertex3d((-1/2.0d * testWH[0]) + testPos[0], 0.0d + testPos[1], (-1/2.0d * testWH[1]) + testPos[2]); //Bottom left
            gl.glVertex3d((1/2.0d * testWH[0]) + testPos[0], 0.0d + testPos[1], (-1/2.0d * testWH[1]) + testPos[2]);  //Bottom right
            gl.glVertex3d((1/2.0d * testWH[0]) + testPos[0], 0.0d + testPos[1], (1/2.0d * testWH[1]) + testPos[2]);   //Top right
            gl.glVertex3d((-1/2.0d * testWH[0]) + testPos[0], 0.0d + testPos[1], (1/2.0d * testWH[1]) + testPos[2]);  //Top left
        gl.glEnd();

        gl.glPopMatrix();
        gl.glFlush();*/


        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT); // clear color and depth buffers

        gl.glEnableVertexAttribArray(0);
        gl.glBindBuffer(gl.GL_ARRAY_BUFFER, buffers.get(0));
        gl.glVertexAttribPointer(0, 3, gl.GL_FLOAT, false, 0, 0);

        gl.glDrawArrays(gl.GL_TRIANGLES, 0, 3);
        gl.glDisableVertexAttribArray(0);

    }

    public void reshape(GLAutoDrawable glAutoDrawable, int i, int i1, int i2, int i3) {
        // GL2
        //gl.glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        /*gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        gl.glMatrixMode(GL2.GL_MODELVIEW);
        gl.glLoadIdentity();*/
        //glu.gluPerspective(45.0f, 1920.0d/1080.0d, 0.1, 10000.0);

        /*
        float[] ortho = new float[16];
        FloatUtil.makeOrtho(ortho, 0, false, -1, 1, -1, 1, 1, -1);
        for (int j = 0; j < 16; j++) {
            matBuffer.put(j, ortho[j]);
        }
        gl.glBindBuffer(gl.GL_UNIFORM_BUFFER, bufferName.get(Buffer.GLOBAL_MATRICES));
        gl.glBufferSubData(gl.GL_UNIFORM_BUFFER, 0, 16 * Float.BYTES, matBuffer);
        gl.glBindBuffer(gl.GL_UNIFORM_BUFFER, 0);

        */
        //gl.glViewport(i, i1, i2, i3);
        //glu.gluPerspective(45.0f, 1920.0d/1080.0d, 0.1, 10000.0);
    }
}


