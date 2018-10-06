package input;

import java.awt.event.MouseEvent;

public interface MouseObserver {
    void notify(MouseEvent e, MouseInput.type t);
}
