package ecosystem.visual;

import ecosystem.Ecosystem;

import java.awt.*;
import javax.swing.*;

/**
 * <pre>
 * Interactive and graphical user interface component.
 * Combines usual interface tools - JFrame, Canvas, JButtons, JLabels,
 * JSlider - and custom Listener classes.
 *
 * Interactive component values can be retrieved by calling get *component name*().
 * Mouse input is separated into Mouse Listener, which records and updates current
 * mouse states, and two methods returning Mouse coordinates on the screen (X and Y
 * coordinates respectively).
 *
 * Label values have to be updated manually by calling {@link #updateLabelValues(int, int, int, int, int)}.
 *
 * Drawing is done by {@link Ecosystem} class by passing Canvas to rendering buffer.
 * </pre>
 */
public class Window
{
    /**
     * Window is not directly tied to Ecosystem grid.
     * @param width screen width
     * @param height screen height
     * @param title window title
     */
    public Window(int width, int height, String title)
    {
        this.width = width;
        this.height = height;
        this.title = title;

        initWindow();
    }

    /** Sets graphical interface window parameters. */
    private void initWindow()
    {
        frame = new JFrame(title);
        frame.setSize(width, height);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

        initButtons();
        initSlider();
        initLabels();
        initCanvas();
        initMouse();

        frame.pack();
    }

    /** Initializes buttons on the screen and their parameters, enables button functionality. */
    private void initButtons()
    {
        buttonManager = new ButtonManager();

        //SAVE
        JButton buttonSave = new JButton();
        buttonSave.setVisible(true);
        buttonSave.setFocusPainted(false);
        buttonSave.setContentAreaFilled(false);
        buttonSave.setText("Save");
        buttonSave.setActionCommand("Save");
        buttonSave.setBounds(20, 20, 100, 30);
        buttonSave.addActionListener(buttonManager);

        //LOAD
        JButton buttonLoad = new JButton();
        buttonLoad.setVisible(true);
        buttonLoad.setFocusPainted(false);
        buttonLoad.setContentAreaFilled(false);
        buttonLoad.setText("Load");
        buttonLoad.setActionCommand("Load");
        buttonLoad.setBounds(140, 20, 100, 30);
        buttonLoad.addActionListener(buttonManager);

        //RESET
        JButton buttonReset = new JButton();
        buttonReset.setVisible(true);
        buttonReset.setFocusPainted(false);
        buttonReset.setContentAreaFilled(false);
        buttonReset.setText("Clear");
        buttonReset.setActionCommand("Reset");
        buttonReset.setBounds(20, 130, 100, 30);
        buttonReset.addActionListener(buttonManager);

        //PAUSE / UNPAUSE
        JButton buttonPause = new JButton(new ImageIcon("assets/pause.png"));
        buttonPause.setVisible(true);
        buttonPause.setFocusPainted(false);
        buttonPause.setContentAreaFilled(false);
        buttonPause.setBorderPainted(false);
        buttonPause.setActionCommand("Pause");
        buttonPause.setBounds(210, 130, 25, 28);
        buttonPause.addActionListener(buttonManager);

        //INDICATOR
        JButton buttonIndicator = new JButton(new ImageIcon("assets/indicator_on.png"));
        buttonIndicator.setVisible(true);
        buttonIndicator.setFocusPainted(false);
        buttonIndicator.setContentAreaFilled(false);
        buttonIndicator.setBorderPainted(false);
        buttonIndicator.setActionCommand("Indicator On");
        buttonIndicator.setBounds(140, 130, 28, 28);
        buttonIndicator.addActionListener(buttonManager);


        //ADD GRASS
        JButton buttonGrass = new JButton();
        buttonGrass.setVisible(true);
        buttonGrass.setFocusPainted(false);
        buttonGrass.setContentAreaFilled(false);
        buttonGrass.setText("Grass");
        buttonGrass.setActionCommand("Grass");
        buttonGrass.setBounds(20, 200, 100, 30);
        buttonGrass.addActionListener(buttonManager);

        //ADD BLUEBERRY
        JButton buttonBlueberry = new JButton();
        buttonBlueberry.setVisible(true);
        buttonBlueberry.setFocusPainted(false);
        buttonBlueberry.setContentAreaFilled(false);
        buttonBlueberry.setText("Blueberry");
        buttonBlueberry.setActionCommand("Blueberry");
        buttonBlueberry.setBounds(140, 200, 100, 30);
        buttonBlueberry.addActionListener(buttonManager);

        //ADD MOSS
        JButton buttonMoss = new JButton();
        buttonMoss.setVisible(true);
        buttonMoss.setFocusPainted(false);
        buttonMoss.setContentAreaFilled(false);
        buttonMoss.setText("Moss");
        buttonMoss.setActionCommand("Moss");
        buttonMoss.setBounds(20, 245, 100, 30);
        buttonMoss.addActionListener(buttonManager);

        //ADD BEET
        JButton buttonBeet = new JButton();
        buttonBeet.setVisible(true);
        buttonBeet.setFocusPainted(false);
        buttonBeet.setContentAreaFilled(false);
        buttonBeet.setText("Beet");
        buttonBeet.setActionCommand("Beet");
        buttonBeet.setBounds(140, 245, 100, 30);
        buttonBeet.addActionListener(buttonManager);

        //ADD SUNFLOWER
        JButton buttonSun = new JButton();
        buttonSun.setVisible(true);
        buttonSun.setFocusPainted(false);
        buttonSun.setContentAreaFilled(false);
        buttonSun.setText("Sunflower");
        buttonSun.setActionCommand("Sunflower");
        buttonSun.setBounds(20, 290, 100, 30);
        buttonSun.addActionListener(buttonManager);

        //ADD ALYSSUM
        JButton buttonAlyssum = new JButton();
        buttonAlyssum.setVisible(true);
        buttonAlyssum.setFocusPainted(false);
        buttonAlyssum.setContentAreaFilled(false);
        buttonAlyssum.setText("Alyssum");
        buttonAlyssum.setActionCommand("Alyssum");
        buttonAlyssum.setBounds(140, 290, 100, 30);
        buttonAlyssum.addActionListener(buttonManager);


        //ADD SHEEP
        JButton buttonSheep = new JButton();
        buttonSheep.setVisible(true);
        buttonSheep.setFocusPainted(false);
        buttonSheep.setContentAreaFilled(false);
        buttonSheep.setText("Sheep");
        buttonSheep.setActionCommand("Sheep");
        buttonSheep.setBounds(20, 370, 100, 30);
        buttonSheep.addActionListener(buttonManager);

        //ADD WOLF
        JButton buttonWolf = new JButton();
        buttonWolf.setVisible(true);
        buttonWolf.setFocusPainted(false);
        buttonWolf.setContentAreaFilled(false);
        buttonWolf.setText("Wolf");
        buttonWolf.setActionCommand("Wolf");
        buttonWolf.setBounds(140, 370, 100, 30);
        buttonWolf.addActionListener(buttonManager);

        //ADD RABBIT
        JButton buttonRabbit = new JButton();
        buttonRabbit.setVisible(true);
        buttonRabbit.setFocusPainted(false);
        buttonRabbit.setContentAreaFilled(false);
        buttonRabbit.setText("Rabbit");
        buttonRabbit.setActionCommand("Rabbit");
        buttonRabbit.setBounds(20, 415, 100, 30);
        buttonRabbit.addActionListener(buttonManager);

        //ADD WILDCAT
        JButton buttonWild = new JButton();
        buttonWild.setVisible(true);
        buttonWild.setFocusPainted(false);
        buttonWild.setContentAreaFilled(false);
        buttonWild.setText("Wildcat");
        buttonWild.setActionCommand("Wildcat");
        buttonWild.setBounds(140, 415, 100, 30);
        buttonWild.addActionListener(buttonManager);

        //RAIN
        JButton buttonRain = new JButton(new ImageIcon("assets/rain_off.png"));
        buttonRain.setVisible(true);
        buttonRain.setFocusPainted(false);
        buttonRain.setContentAreaFilled(false);
        buttonRain.setBorderPainted(false);
        buttonRain.setActionCommand("Rain Off");
        buttonRain.setBounds(20, 660, 28, 28);
        buttonRain.addActionListener(buttonManager);

        //LOCATOR
        JButton buttonLocator = new JButton(new ImageIcon("assets/locator_off.png"));
        buttonLocator.setVisible(true);
        buttonLocator.setFocusPainted(false);
        buttonLocator.setContentAreaFilled(false);
        buttonLocator.setBorderPainted(false);
        buttonLocator.setActionCommand("Locator Off");
        buttonLocator.setBounds(60, 660, 28, 28);
        buttonLocator.addActionListener(buttonManager);


        frame.add(buttonSave);
        frame.add(buttonLoad);
        frame.add(buttonReset);
        frame.add(buttonIndicator);
        frame.add(buttonPause);

        frame.add(buttonGrass);
        frame.add(buttonBlueberry);
        frame.add(buttonMoss);
        frame.add(buttonBeet);
        frame.add(buttonSun);
        frame.add(buttonAlyssum);

        frame.add(buttonSheep);
        frame.add(buttonWolf);
        frame.add(buttonRabbit);
        frame.add(buttonWild);

        frame.add(buttonRain);
        frame.add(buttonLocator);
    }

    /** Initializes slider and its parameters, enables slider functionality. */
    private void initSlider()
    {
        sliderManager = new SliderManager();

        JSlider slider = new JSlider();
        slider.setVisible(true);
        slider.setBackground(new Color(236, 236, 236));
        slider.setBounds(20, 87, 220, 30);
        slider.setUI(new CustomSliderUI(slider));
        slider.addChangeListener(sliderManager);
        slider.setMinimum(1);
        slider.setMaximum(41);
        slider.setValue(32);

        //slider.setMajorTickSpacing(4);
        //slider.setMinorTickSpacing(4);
        //slider.setPaintTicks(true);

        frame.add(slider);
    }

    /** Places labels on fixed window positions. */
    private void initLabels()
    {
        JLabel label1 = new JLabel("Cycle Speed:");
        label1.setOpaque(true);
        label1.setBackground(new Color(236, 236, 236));
        label1.setBounds(20, 70, 75,20);
        label1.setFocusable(true);

        speedLabel = new JLabel();
        speedLabel.setOpaque(true);
        speedLabel.setBackground(new Color(236, 236, 236));
        speedLabel.setBounds(100, 70, 100,20);
        speedLabel.setFocusable(true);

        JLabel label2 = new JLabel("Add Plant:");
        label2.setOpaque(true);
        label2.setBackground(new Color(236, 236, 236));
        label2.setBounds(20, 170, 65,20);
        label2.setFocusable(true);

        JLabel label3 = new JLabel("Add Animal:");
        label3.setOpaque(true);
        label3.setBackground(new Color(236, 236, 236));
        label3.setBounds(20, 340, 75,20);
        label3.setFocusable(true);

        JLabel label4 = new JLabel("Ecosystem State:");
        label4.setOpaque(true);
        label4.setBackground(new Color(236, 236, 236));
        label4.setBounds(20, 464, 108,20);
        label4.setFocusable(true);

        plantLabel = new JLabel("Current plant count: ");
        plantLabel.setOpaque(true);
        plantLabel.setBackground(new Color(236, 236, 236));
        plantLabel.setBounds(20, 490, 180,15);
        plantLabel.setFocusable(true);

        starveLabel = new JLabel("Predators starved: ");
        starveLabel.setOpaque(true);
        starveLabel.setBackground(new Color(236, 236, 236));
        starveLabel.setBounds(20, 610, 180,15);
        starveLabel.setFocusable(true);

        huntLabel = new JLabel("Successful hunts: ");
        huntLabel.setOpaque(true);
        huntLabel.setBackground(new Color(236, 236, 236));
        huntLabel.setBounds(20, 586, 180,15);
        huntLabel.setFocusable(true);

        preyLabel = new JLabel("Prey population: ");
        preyLabel.setOpaque(true);
        preyLabel.setBackground(new Color(236, 236, 236));
        preyLabel.setBounds(20, 514, 180,15);
        preyLabel.setFocusable(true);

        predatorLabel = new JLabel("Predator population: ");
        predatorLabel.setOpaque(true);
        predatorLabel.setBackground(new Color(236, 236, 236));
        predatorLabel.setBounds(20, 538, 180,15);
        predatorLabel.setFocusable(true);

        JLabel label5 = new JLabel("Other:");
        label5.setOpaque(true);
        label5.setBackground(new Color(236, 236, 236));
        label5.setBounds(20, 640, 40,20);
        label5.setFocusable(true);

        frame.add(label1);
        frame.add(speedLabel);
        frame.add(label2);
        frame.add(label3);
        frame.add(label4);
        frame.add(plantLabel);
        frame.add(starveLabel);
        frame.add(huntLabel);
        frame.add(preyLabel);
        frame.add(predatorLabel);
        frame.add(label5);
    }

    /** Sets canvas parameters. */
    private void initCanvas()
    {
        canvas = new Canvas();
        canvas.setFocusable(false);
        canvas.setPreferredSize(new Dimension(width, height));

        frame.add(canvas);
    }

    /** Links mouse component with relevant panels. */
    private void initMouse()
    {
        mouseManager = new MouseManager();
        frame.addMouseListener(mouseManager);
        canvas.addMouseListener(mouseManager);
    }


    /** @return drawing area associated with window */
    public Canvas getCanvas() { return canvas; }

    /** @return graphical representation of window */
    public JFrame getFrame() { return frame; }

    /** @return window component holding button information */
    public ButtonManager getButtons() { return buttonManager; }

    /** @return window component holding slider information */
    public SliderManager getSlider() { return sliderManager; }

    /** @return window component holding mouse information */
    public MouseManager getMouse() { return mouseManager; }

    /** Returns mouse location coordinate x relative to canvas. */
    public int getMouseX()
    {
        Point temp = MouseInfo.getPointerInfo().getLocation();
        SwingUtilities.convertPointFromScreen(temp, canvas);
        return (int)temp.getX();
    }

    /** Returns mouse location coordinate y relative to canvas. */
    public int getMouseY()
    {
        Point temp = MouseInfo.getPointerInfo().getLocation();
        SwingUtilities.convertPointFromScreen(temp, canvas);
        return (int)temp.getY();
    }

    /** Updates window with current settings and numbers. */
    public void updateLabelValues(int plantCount, int starveCount, int huntCount, int preyCount, int predatorCount)
    {
        double relativeValue = Math.round(1200.0 / sliderManager.getCustomSliderValue()) / 100.0;
        SwingUtilities.invokeLater(() -> speedLabel.setText("x" + relativeValue));

        SwingUtilities.invokeLater(() -> plantLabel.setText("》Current plant count: " + plantCount));
        SwingUtilities.invokeLater(() -> starveLabel.setText("》Predators starved: " + starveCount));
        SwingUtilities.invokeLater(() -> huntLabel.setText("》Successful hunts: " + huntCount));
        SwingUtilities.invokeLater(() -> preyLabel.setText("》Prey population: " + preyCount));
        SwingUtilities.invokeLater(() -> predatorLabel.setText("》Predator population: " + predatorCount));
    }


    //Graphic components
    private JFrame frame;
    private Canvas canvas;

    //Action elements
    private ButtonManager buttonManager;
    private SliderManager sliderManager;
    private MouseManager mouseManager;

    //Mutable labels
    private JLabel speedLabel;
    private JLabel plantLabel;
    private JLabel starveLabel;
    private JLabel huntLabel;
    private JLabel preyLabel;
    private JLabel predatorLabel;

    //Window parameters
    private int width;
    private int height;
    private String title;
}
