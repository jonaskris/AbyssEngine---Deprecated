package graphics;

import com.jogamp.opengl.awt.GLJPanel;

/*import entities.Entity;
import entities.components.GComponent.GComponent;
import entities.components.GComponent.GSComponent;
import entities.components.GComponent.GSSComponent;
import entities.components.PComponent;
*/

import javax.swing.*;
import java.awt.*;


import static com.jogamp.nativewindow.WindowClosingProtocol.WindowClosingMode.DISPOSE_ON_CLOSE;


public class Renderer {

    public static final String[] SPRITESHEETPATHS = {
            "graphics/spritesheets/testSheet.png"
    };
    //public static final Spritesheet[] SPRITESHEETS = new Spritesheet[SPRITESHEETPATHS.length];

    public static final String[] SPRITEPATHS = {
            "graphics/sprites/testSprite.png"
    };
    //public static final Sprite[] SPRITES = new Sprite[SPRITEPATHS.length];


    public static final int SPRITE_SIZE = 32;
    private static final float ASPECT = 16/9f;
    private static final int WINDOW_WIDTH = 1920/2;
    private static final int WINDOW_HEIGHT = (int)((1/ASPECT) * WINDOW_WIDTH);

    final static private String TITLE = "Abysswalker";

    private static JFrame window;
    private static GLJPanel content;

    public static void init(){
        OpenGL.initSingleton(WINDOW_WIDTH, WINDOW_HEIGHT);

        window = new JFrame(TITLE);
        content = OpenGL.getInstance();
        window.setLayout(new BorderLayout());
        window.add(content, BorderLayout.CENTER);
        window.setContentPane(content);
        window.setSize(new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT));
        window.setResizable(false);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
        content.requestFocusInWindow();

        content.setFocusable(true);

        createSpritesheets();
        createSprites();
    }

    public static void render(){ //Problem: render - drawSprite - bindSprite/bindSpritesheet prøver å binde teksturer før init i openGL kjøres
        content.display();
    }

    private static void createSpritesheets(){
        /*for(int i = 0; i < SPRITESHEETPATHS.length; i++){
            SPRITESHEETS[i] = new Spritesheet(SPRITESHEETPATHS[i], SPRITE_SIZE);
        }*/
    }

    private static void createSprites(){
        /*for(int i = 0; i < SPRITEPATHS.length; i++){
            SPRITES[i] = new Sprite(SPRITEPATHS[i]);
        }*/
    }
}
