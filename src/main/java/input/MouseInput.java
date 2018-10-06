package input;

import javax.swing.event.MouseInputListener;
import java.awt.event.*;
import java.util.ArrayList;

public class MouseInput implements MouseInputListener, MouseMotionListener, MouseWheelListener {
    private static MouseInput instance;

    public enum type{CLICK, PRESS, RELEASE, ENTER, EXIT, WHEEL, DRAG, MOVE}
    public final int CLICK = 0;
    public final int PRESS = 1;
    public final int RELEASE = 2;
    public final int ENTER = 3;
    public final int EXIT = 4;
    public final int WHEEL = 5;
    public final int DRAG = 6;
    public final int MOVE = 7;

    static private ArrayList<MouseObserver>[] observers = new ArrayList[type.values().length];

    private MouseInput() {
        super();
    }

    public static void initSingleton(){
        if(instance == null){
            instance = new MouseInput();
            for(int i = 0; i < type.values().length; i++){
                observers[i] = new ArrayList<MouseObserver>();
            }
        }
    }

    public static MouseInput getInstance(){
        return instance;
    }

    private void notify(MouseEvent e, type t){
        int ordinal = t.ordinal();
        for(int i = 0; i < observers[ordinal].size(); i++){
            observers[ordinal].get(i).notify(e, t);
        }
    }

    public void mouseClicked(MouseEvent e) {
        notify(e, type.CLICK);
    }

    public void mousePressed(MouseEvent e) {
        notify(e, type.PRESS);
    }

    public void mouseReleased(MouseEvent e) {
        notify(e, type.RELEASE);
    }

    public void mouseEntered(MouseEvent e) {
        notify(e, type.ENTER);
    }

    public void mouseExited(MouseEvent e) {
        notify(e, type.EXIT);
    }

    public void mouseWheelMoved(MouseWheelEvent e) {
        notify(e, type.WHEEL);
    }

    public void mouseDragged(MouseEvent e) {
        notify(e, type.DRAG);
    }

    public void mouseMoved(MouseEvent e) {
        notify(e, type.MOVE);
    }

    public static void addObserver(MouseObserver o, type type){
        if(!observers[type.ordinal()].contains(o)){
            observers[type.ordinal()].add(o);
        }
    }

    public static void addObserver(MouseObserver o, type[] types){
        for(int i = 0; i < types.length; i++){
            addObserver(o, types[i]);
        }
    }

    public static void removeObserver(MouseObserver o){
        for(int i = 0; i < observers.length; i++){
            observers[i].remove(o);
        }
    }
}
