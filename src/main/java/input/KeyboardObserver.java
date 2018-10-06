package input;

import java.awt.event.KeyEvent;

public interface KeyboardObserver {
    void notify(KeyEvent e, KeyboardInput.type t);
}
