package ecosystem.visual;

import javax.swing.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/** Implements See {@link MouseListener} for all mouse related actions. */
public class MouseManager implements MouseListener
{
    /** See {@link MouseListener#mouseClicked(MouseEvent)}. */
    public void mouseClicked(MouseEvent e)
    {
        if(SwingUtilities.isLeftMouseButton(e))
            clickedLeft = true;
        else if (SwingUtilities.isRightMouseButton(e))
            clickedRight = true;
    }

    public void mousePressed(MouseEvent e) {}
    public void mouseReleased(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}

    /** Update mouse states to not pressed. */
    public void update()
    {
        clickedLeft = false;
        clickedRight = false;
    }

    public boolean wasClickedLeft() { return clickedLeft; }
    public boolean wasClickedRight() { return clickedRight; }

    //Fields
    boolean clickedLeft;
    boolean clickedRight;
}
