package input;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;

public class KeyboardInput implements KeyListener {
    private static KeyboardInput instance;

    public enum type{PRESSED, RELEASED}

    private static ArrayList<KeyboardObserver> observers = new ArrayList<KeyboardObserver>();

    private static ArrayList<Integer> pressed = new ArrayList<Integer>();

    private static Component keyEventSource;

    private KeyboardInput(Component keyEventSource){
        super();
        this.keyEventSource = keyEventSource;
    }

    public static void initSingleton(Component keyEventSource){
        if(instance == null){
            instance = new KeyboardInput(keyEventSource);
        }
    }

    public static KeyboardInput getInstance(){
        return instance;
    }

    public void notify(KeyEvent e, type t){
        for(int i = 0; i < observers.size(); i++){
            observers.get(i).notify(e, t);
        }
    }

    public void keyTyped(KeyEvent e) {
        // Do nothing
    }

    public void keyPressed(KeyEvent e) {
        if(!pressed.contains(e.getKeyCode())){
            pressed.add(e.getKeyCode());
            notify(e, type.PRESSED);
        }
    }

    public void keyReleased(KeyEvent e) {
        if(pressed.contains(e.getKeyCode())){
            pressed.remove((Integer)e.getKeyCode());
            notify(e, type.RELEASED);
        }
    }

    public static void addObserver(KeyboardObserver o){
        if(!observers.contains(o)){
            observers.add(o);
            for(int i = 0; i < pressed.size(); i++){
                o.notify(createFakeKeyEventPressed(pressed.get(i)), type.PRESSED);
            }
        }
    }

    private static KeyEvent createFakeKeyEventPressed(int keyCode){
        return new KeyEvent(keyEventSource, KeyEvent.KEY_PRESSED, 0, 0, keyCode, KeyEvent.CHAR_UNDEFINED);
    }
}
