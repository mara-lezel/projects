package ecosystem.visual;


import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/** Implements {@link ActionListener} for all Window associated buttons. */
public class ButtonManager implements ActionListener
{

    /** See {@link ActionListener#actionPerformed(ActionEvent)}. */
    public void actionPerformed(ActionEvent e)
    {
        switch (e.getActionCommand())
        {
            case "Save":
                currentAction = 1;
                break;
            case "Load":
                currentAction = 2;
                break;
            case "Grass":
                currentAction = 3;
                break;
            case "Blueberry":
                currentAction = 4;
                break;
            case "Moss":
                currentAction = 5;
                break;
            case "Beet":
                currentAction = 6;
                break;
            case "Sunflower":
                currentAction = 7;
                break;
            case "Alyssum":
                currentAction = 8;
                break;
            case "Sheep":
                currentAction = 9;
                break;
            case "Wolf":
                currentAction = 10;
                break;
            case "Rabbit":
                currentAction = 11;
                break;
            case "Wildcat":
                currentAction = 12;
                break;
            case "Unpause":
                SwingUtilities.invokeLater(() ->
                {
                    ((JButton)e.getSource()).setIcon(new ImageIcon("assets/pause.png"));
                    ((JButton)e.getSource()).setActionCommand("Pause");
                });
                currentAction = 20;
                break;
            case "Pause":
                SwingUtilities.invokeLater(() ->
                {
                    ((JButton)e.getSource()).setIcon(new ImageIcon("assets/unpause.png"));
                    ((JButton)e.getSource()).setActionCommand("Unpause");
                });
                currentAction = 20;
                break;
            case "Reset":
                currentAction = 21;
                break;
            case "Indicator On":
                SwingUtilities.invokeLater(() ->
                {
                    ((JButton)e.getSource()).setIcon(new ImageIcon("assets/indicator_off.png"));
                    ((JButton)e.getSource()).setActionCommand("Indicator Off");
                });
                currentAction = 22;
                break;
            case "Indicator Off":
                SwingUtilities.invokeLater(() ->
                {
                    ((JButton)e.getSource()).setIcon(new ImageIcon("assets/indicator_on.png"));
                    ((JButton)e.getSource()).setActionCommand("Indicator On");
                });
                currentAction = 22;
                break;
            case "Rain On":
                SwingUtilities.invokeLater(() ->
                {
                    ((JButton)e.getSource()).setIcon(new ImageIcon("assets/rain_off.png"));
                    ((JButton)e.getSource()).setActionCommand("Rain Off");
                });
                currentAction = 23;
                break;
            case "Rain Off":
                SwingUtilities.invokeLater(() ->
                {
                    ((JButton)e.getSource()).setIcon(new ImageIcon("assets/rain_on.png"));
                    ((JButton)e.getSource()).setActionCommand("Rain On");
                });
                currentAction = 23;
                break;
            case "Locator On":
                SwingUtilities.invokeLater(() ->
                {
                    ((JButton)e.getSource()).setIcon(new ImageIcon("assets/locator_off.png"));
                    ((JButton)e.getSource()).setActionCommand("Locator Off");
                });
                currentAction = 24;
                break;
            case "Locator Off":
                SwingUtilities.invokeLater(() ->
                {
                    ((JButton)e.getSource()).setIcon(new ImageIcon("assets/locator_on.png"));
                    ((JButton)e.getSource()).setActionCommand("Locator On");
                });
                currentAction = 24;
                break;
            default:
                currentAction = 0;
                break;
        }
    }

    /**
     * <pre>
     * Action button list:
     * 0 - no action / no button pressed
     * 1 - Save button pressed
     * 2 - Load button pressed
     * 3 - Add Grass button
     * 4 - Add Blueberry button
     * 5 - Add Moss button
     * 6 - Add Beet button
     * 7 - Add Sunflower button
     * 8 - Add Alyssum button
     * 9 - Add Sheep button
     * 10 - Add Wolf button
     * 11 - Add Rabbit button
     * 12 - Add Wildcat button
     * 20 - Pause / Unpause button
     * 21 - Reset button
     * 22 - Indicators On / Off button
     * 23 - Rain On / Off button
     * 24 - Locator On / Off button
     * </pre>
     * @return value that represents a pressed button
     */
    public int getCurrentAction() { return currentAction; }

    public void update() { currentAction = 0; }

    //Fields
    int currentAction;
}
