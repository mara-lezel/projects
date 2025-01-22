package ecosystem;

import java.awt.*;
import java.awt.image.BufferStrategy;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import ecosystem.entities.animals.*;
import ecosystem.entities.plants.PlantGarden;
import ecosystem.exceptions.NegativeDimensionsException;
import ecosystem.grid.*;
import ecosystem.entities.*;
import ecosystem.helper.Constants;
import ecosystem.helper.Helper;
import ecosystem.visual.Window;

import javax.swing.*;

/**
 * <pre>
 * Ecosystem implements internal simulation and drawing logic.
 * Simulation can be started by calling {@link Ecosystem#start()} and opens
 * associated interface window automatically.
 * </pre>
 */
public class Ecosystem
{

    public Ecosystem() throws NegativeDimensionsException
    {
        grid = new EcosystemGrid(Constants.GRID_WIDTH, Constants.GRID_HEIGHT);

        prey = new ArrayList<>();
        predators = new ArrayList<>();

        window = new Window(Constants.SCREEN_WIDTH, Constants.SCREEN_HEIGHT, "ECOSYSTEM v1");
    }

    /** Begins the ecosystem simulation. */
    public void start()
    {
        //INITIAL ACTORS
        grid.addPlantAt(5,5, PlantGarden.getPlant(PlantGarden.PlantClass.GRASS));
        grid.addPlantAt(50,50, PlantGarden.getPlant(PlantGarden.PlantClass.GRASS));
        grid.addPlantAt(5,50, PlantGarden.getPlant(PlantGarden.PlantClass.GRASS));
        grid.addPlantAt(44, 14, PlantGarden.getPlant(PlantGarden.PlantClass.BLUEBERRY));

        prey.add((Prey) AnimalDen.getAnimal(555, 155, AnimalDen.AnimalClass.SHEEP));
        prey.add((Prey) AnimalDen.getAnimal(461, 202, AnimalDen.AnimalClass.SHEEP));

        predators.add((Predator) AnimalDen.getAnimal(656, 144, AnimalDen.AnimalClass.WOLF));

        //INITIAL SYSTEM VARIABLES
        toggleIndicators = true;
        running = true;

        cycleDuration = 1;
        drawAction = 0;

        plantCount = 0;
        starveCount = 0;
        huntCount = 0;
        preyCount = 0;
        predatorCount = 0;

        loop();
    }

    /** Main event loop of the simulation. */
    private void loop()
    {
        while(running)
        {
            //USER INPUT
            input();

            //ENTITY ADDITION
            addUserEntities();

            if(!paused)
            {
                //RAIN EFFECTS
                if(toggleRain && Helper.random.nextInt(10) < 5)
                {
                    int j = Helper.random.nextInt(Constants.GRID_WIDTH);
                    int i = Helper.random.nextInt(Constants.GRID_HEIGHT);

                    if(grid.getPlantAt(j, i) == null)
                    {
                        switch (Helper.random.nextInt(10))
                        {
                            case 0:
                                grid.addPlantAt(j, i, PlantGarden.getPlant(PlantGarden.PlantClass.BLUEBERRY));
                                break;
                            case 1:
                                grid.addPlantAt(j, i, PlantGarden.getPlant(PlantGarden.PlantClass.SUNFLOWER));
                                break;
                            case 2:
                                grid.addPlantAt(j, i, PlantGarden.getPlant(PlantGarden.PlantClass.BEET));
                                break;
                            case 3:
                                grid.addPlantAt(j, i, PlantGarden.getPlant(PlantGarden.PlantClass.ALYSSUM));
                                break;
                            default:
                                grid.addPlantAt(j, i, PlantGarden.getPlant(PlantGarden.PlantClass.GRASS));
                                break;
                        }
                    }
                    else if (grid.getPlantAt(j, i).isWithered())
                        grid.getPlantAt(j, i).setGrowthToZero();
                }

                //PLANT CYCLE
                for(int i = 0; i < grid.getHeight(); ++i)
                {
                    for(int j = 0; j < grid.getWidth(); ++j)
                    {
                        if(!grid.isEmptyAt(j, i))
                        {
                            grid.getPlantAt(j, i).grow();

                            if(grid.getPlantAt(j, i).canReproduce())
                                grid.reproducePlantAt(j, i);

                            if(grid.getPlantAt(j, i).isWithered())
                                grid.removePlantAt(j, i);
                        }
                    }
                }

                //PREY CYCLE
                for(Prey preyAnimal : prey)
                {
                    preyAnimal.scatter(predators);

                    if(preyAnimal.hasNoTarget())
                        preyAnimal.selectTarget(grid);
                    else if (!preyAnimal.isAtTarget())
                        preyAnimal.move();
                    else
                    {
                        int j = preyAnimal.getTargetTile().getPosX();
                        int i = preyAnimal.getTargetTile().getPosY();

                        if(preyAnimal.isFleeing())
                        {
                            preyAnimal.setTargetTile(null);
                            preyAnimal.setFleeing(false);
                        }
                        else if (grid.isEmptyAt(j, i))
                            preyAnimal.setTargetTile(null);
                        else
                        {
                            preyAnimal.gainEnergy(2);
                            grid.getPlantAt(j, i).loseEnergy(2);

                            if(grid.getPlantAt(j, i).getEnergyValue() == 0)
                                grid.removePlantAt(j, i);
                        }
                    }
                }


                //PREDATOR CYCLE
                ArrayList<Predator> marked = new ArrayList<>();
                for(Predator predatorAnimal : predators)
                {
                    int initialEnergy = predatorAnimal.getEnergyValue();
                    predatorAnimal.selectTarget(prey);

                    if (!predatorAnimal.isAtTarget())
                    {
                        predatorAnimal.move();
                        predatorAnimal.pounce(prey);

                        if(initialEnergy <= predatorAnimal.getEnergyValue())
                            ++huntCount;
                    }
                    else
                        predatorAnimal.setTargetTile(null);

                    if(predatorAnimal.getEnergyValue() == 0)
                        marked.add(predatorAnimal);
                }
                starveCount += marked.size();
                predators.removeAll(marked);
            }

            //UPDATE COUNTERS
            plantCount = grid.getPlantCount();
            preyCount = prey.size();
            predatorCount = predators.size();

            //Render grid, all plants and animals to screen
            render();

            //ECOSYSTEM FLOW CONTROL
            delay(cycleDuration);
        }
    }

    /** Delays the ecosystem cycle execution.
     * @param ms milliseconds to delay the cycle by (1000ms ~ 1s) */
    private void delay(int ms)
    {
        try
        {
            Thread.sleep(ms);
        }

        catch(Exception e)
        {
            Thread.currentThread().interrupt();
        }
    }

    /** User input to implement later.
     *  Implement switch. */
    private void input()
    {
        //SLIDER
        cycleDuration = window.getSlider().getCustomSliderValue();
        window.updateLabelValues(plantCount, starveCount, huntCount, preyCount, predatorCount);

        //BUTTONS
        switch (window.getButtons().getCurrentAction())
        {
            case 1:
            {
                Thread t = new Thread(() ->
                {
                    writeToFile();
                    SwingUtilities.invokeLater(new Runnable()
                    {
                        public void run() { window.getFrame().setTitle("ECOSYSTEM v1      [SAVE] " + requestTime()); }
                    });
                });
                t.start();

                break;
            }
            case 2:
            {
                Thread t = new Thread(() ->
                {
                    readFromFile();
                    SwingUtilities.invokeLater(new Runnable()
                    {
                        public void run() { window.getFrame().setTitle("ECOSYSTEM v1      [LOAD] " + requestTime()); }
                    });
                });
                t.start();

                break;
            }
            case 3:
                drawAction = 1;
                break;
            case 4:
                drawAction = 2;
                break;
            case 5:
                drawAction = 3;
                break;
            case 6:
                drawAction = 4;
                break;
            case 7:
                drawAction = 5;
                break;
            case 8:
                drawAction = 6;
                break;
            case 9:
                drawAction = 7;
                break;
            case 10:
                drawAction = 8;
                break;
            case 11:
                drawAction = 9;
                break;
            case 12:
                drawAction = 10;
                break;
            case 20:
                paused = !paused;
                break;
            case 21:
                reset();
                break;
            case 22:
                toggleIndicators = !toggleIndicators;
                break;
            case 23:
                toggleRain = !toggleRain;
                break;
            case 24:
                toggleLocators = !toggleLocators;
                break;
            default:
                break;
        }
        window.getButtons().update();


        //MOUSE INPUT
        mousePressedLeft = window.getMouse().wasClickedLeft();
        mousePressedRight = window.getMouse().wasClickedRight();
        window.getMouse().update();

        if(mousePressedRight)
            drawAction = 0;
    }

    /** Renders all buffers to the screen. */
    private void render()
    {
        bs = window.getCanvas().getBufferStrategy();
        if(bs == null)
        {
            window.getCanvas().createBufferStrategy(3);
            return;
        }

        g = (Graphics2D) bs.getDrawGraphics();
        g.clearRect(0, 0, Constants.SCREEN_WIDTH, Constants.SCREEN_HEIGHT);
        g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        drawGrid();
        drawPlants();
        drawAnimals();
        drawUI();
        drawMouse();

        bs.show();
        g.dispose();
    }

    /** Draws mouse related actions. */
    private void drawMouse()
    {
        int x = window.getMouseX();
        int y = window.getMouseY();

        if(x >= Constants.GRID_OFFSET_BX && x <= Constants.SCREEN_WIDTH - 10)
        {
            if(y >= Constants.GRID_OFFSET_BY && y <= Constants.SCREEN_HEIGHT - 10)
            {
                x = (int)grid.getCoordinateXAt(Helper.convertToPositionX(x));
                y = (int)grid.getCoordinateYAt(Helper.convertToPositionY(y));

                switch (drawAction)
                {
                    case 1:
                        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.GRASS).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 2:
                        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.BLUEBERRY).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 3:
                        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.MOSS).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 4:
                        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.BEET).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 5:
                        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.SUNFLOWER).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 6:
                        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.ALYSSUM).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 7:
                        g.setColor(AnimalDen.getAnimal(0,0, AnimalDen.AnimalClass.SHEEP).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 8:
                        g.setColor(AnimalDen.getAnimal(0,0, AnimalDen.AnimalClass.WOLF).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 9:
                        g.setColor(AnimalDen.getAnimal(0,0, AnimalDen.AnimalClass.RABBIT).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    case 10:
                        g.setColor(AnimalDen.getAnimal(0,0, AnimalDen.AnimalClass.WILDCAT).getColor());
                        g.fillRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                    default:
                        g.setStroke(new BasicStroke(2));
                        g.setColor(new Color(137,207,240));
                        g.drawRect(x, y, Tile.SIZE, Tile.SIZE);
                        break;
                }
            }
        }
    }

    /** Draws panels and outlines. */
    private void drawUI()
    {
        //HIDE CANVAS INDICATORS
        //g.setColor(new Color(205, 201, 212));
        g.setColor(new Color(98, 101, 121));
        g.fillRect(0,0, Constants.SCREEN_WIDTH, 10);
        g.fillRect(Constants.SCREEN_WIDTH - 10,0, 10, Constants.SCREEN_HEIGHT);
        g.fillRect(0,Constants.SCREEN_HEIGHT - 10, Constants.SCREEN_WIDTH, 10);
        g.fillRect(Constants.GRID_OFFSET_BX - 20,0, 20, Constants.SCREEN_HEIGHT);

        //OPTION PANEL FILL
        g.setColor(new Color(236, 236, 236));
        g.fillRoundRect(10, 10, Constants.GRID_OFFSET_BX - 30, Constants.SCREEN_HEIGHT - 20,
                15, 15);

        //OPTION PANEL OUTLINE
        g.setStroke(new BasicStroke(1));
        g.setColor(new Color(137, 130, 150));
        g.drawRoundRect(10, 10, Constants.GRID_OFFSET_BX - 30, Constants.SCREEN_HEIGHT - 20,
                15, 15);

        //CANVAS OUTLINE
        g.setColor(new Color(98, 101, 121));
        g.setStroke(new BasicStroke(7));
        g.drawRoundRect(Constants.GRID_OFFSET_BX - 3, Constants.GRID_OFFSET_BY - 5,
                Constants.GRID_WIDTH * Tile.SIZE + 8, Constants.GRID_HEIGHT * Tile.SIZE + 8,
                30, 30);


        //OPTION PANEL ELEMENTS
        g.setStroke(new BasicStroke(1));
        g.setColor(new Color(20, 56, 107));
        g.drawLine(20, 184, Constants.GRID_OFFSET_BX - 30, 184);
        g.drawLine(20, 354, Constants.GRID_OFFSET_BX - 30, 354);
        g.drawLine(20, 478, Constants.GRID_OFFSET_BX - 30, 478);
        g.drawLine(20, 654, Constants.GRID_OFFSET_BX - 30, 654);

        //ENTITY COLOURS
        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.GRASS).getColor());
        g.fillRect(20, 195, 100, 2);
        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.BLUEBERRY).getColor());
        g.fillRect(140, 195, 100, 2);
        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.MOSS).getColor());
        g.fillRect(20, 240, 100, 2);
        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.BEET).getColor());
        g.fillRect(140, 240, 100, 2);
        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.SUNFLOWER).getColor());
        g.fillRect(20, 285, 100, 2);
        g.setColor(PlantGarden.getPlant(PlantGarden.PlantClass.ALYSSUM).getColor());
        g.fillRect(140, 285, 100, 2);

        g.setColor(AnimalDen.getAnimal(0,0, AnimalDen.AnimalClass.SHEEP).getColor());
        g.fillRect(20, 365, 100, 2);
        g.setColor(AnimalDen.getAnimal(0,0, AnimalDen.AnimalClass.WOLF).getColor());
        g.fillRect(140, 365, 100, 2);
        g.setColor(AnimalDen.getAnimal(0,0, AnimalDen.AnimalClass.RABBIT).getColor());
        g.fillRect(20, 410, 100, 2);
        g.setColor(AnimalDen.getAnimal(0,0, AnimalDen.AnimalClass.WILDCAT).getColor());
        g.fillRect(140, 410, 100, 2);
    }

    /** Draws the tile grid to the buffer. */
    private void drawGrid()
    {
        //BACKGROUND FILL
        //g.setColor(new Color(205, 201, 212));
        g.setColor(new Color(98, 101, 121));
        g.fillRect(0,0, Constants.SCREEN_WIDTH, Constants.SCREEN_HEIGHT);

        //CLEAR CANVAS
        g.setColor(new Color(236, 236, 236));
        for(int j = 0; j < grid.getWidth(); ++j)
            for(int i = 0; i < grid.getHeight(); ++i)
                g.fillRect((int)grid.getCoordinateXAt(j), (int)grid.getCoordinateYAt(i), Tile.SIZE, Tile.SIZE);

        //DRAW GRID
        g.setColor(new Color(211, 211, 211));
        for(int j = 0; j < grid.getWidth(); ++j)
            for(int i = 0; i < grid.getHeight(); ++i)
                g.drawRect((int)grid.getCoordinateXAt(j), (int)grid.getCoordinateYAt(i), Tile.SIZE, Tile.SIZE);
    }

    /** Draws all plants to the buffer - each plant is
     * represented by a different colour (white is empty). */
    private void drawPlants()
    {
        Drawable drawObject;

        for(int i = 0; i < grid.getHeight(); ++i)
        {
            for(int j = 0; j < grid.getWidth(); ++j)
            {
                if(!grid.isEmptyAt(j, i))
                {
                    drawObject = grid.getPlantAt(j, i);
                    g.setColor(drawObject.getColor());

                    if (grid.getPlantAt(j, i).isWithered())
                        g.setColor(drawObject.getAdditionalColor());

                    g.fillRect((int) grid.getCoordinateXAt(j), (int) grid.getCoordinateYAt(i),
                            drawObject.getDrawWidth(), drawObject.getDrawHeight());
                }
            }
        }
    }

    /** Draws all animals to the buffer. */
    private void drawAnimals()
    {
        Drawable drawObject;

        //SHEEP
        for(Prey entity : prey)
        {
            drawObject = entity;

            if(toggleLocators)
            {
                g.setColor(new Color(236, 236, 236));
                g.setStroke(new BasicStroke(3));
                g.drawOval((int)(entity.getX() + 4 - 20), (int)(entity.getY() + 4 - 20), 40, 40);
                g.setStroke(new BasicStroke(1));
            }

            g.setColor(drawObject.getColor());
            g.fillRect((int)entity.getX(), (int)entity.getY(), drawObject.getDrawWidth(), drawObject.getDrawHeight());

            g.setColor(new Color(0, 0, 0));
            g.drawRect((int)entity.getX(), (int)entity.getY(), drawObject.getDrawWidth(), drawObject.getDrawHeight());

            if(toggleIndicators)
            {
                g.setColor(drawObject.getAdditionalColor());
                if(entity.getTargetTile() != null)
                {
                    g.drawRect((int)entity.getTargetTile().getX(), (int)entity.getTargetTile().getY(),
                            drawObject.getDrawWidth(), drawObject.getDrawHeight());
                }
            }
        }


        //WOLF
        for(Predator entity : predators)
        {
            drawObject = entity;

            if(toggleLocators)
            {
                g.setColor(new Color(236, 236, 236));
                g.setStroke(new BasicStroke(3));
                g.drawOval((int)(entity.getX() + 4 - 20), (int)(entity.getY() + 4 - 20), 40, 40);
                g.setStroke(new BasicStroke(1));
            }

            g.setColor(drawObject.getColor());
            g.fillRect((int)entity.getX(), (int)entity.getY(), drawObject.getDrawWidth(), drawObject.getDrawHeight());

            g.setColor(new Color(0, 0, 0));
            g.drawRect((int)entity.getX(), (int)entity.getY(), drawObject.getDrawWidth(), drawObject.getDrawHeight());

            if(toggleIndicators)
            {
                g.setColor(drawObject.getAdditionalColor());
                if(entity.getTargetTile() != null)
                {
                    g.drawRect((int)entity.getTargetTile().getX(), (int)entity.getTargetTile().getY(),
                            drawObject.getDrawWidth(), drawObject.getDrawHeight());
                }
                g.setColor(new Color(255,0,0));
                g.drawOval((int)(entity.getX() + 2 - entity.getTargetingRadius()),
                        (int)(entity.getY() + 2 - entity.getTargetingRadius()),
                        (int)entity.getTargetingRadius() * 2,
                        (int)entity.getTargetingRadius() * 2);
            }
        }
    }

    /** Saves current ecosystem representation to file. */
    private void writeToFile()
    {
        try
        {
            FileOutputStream fileOut = new FileOutputStream("data.dat");
            ObjectOutputStream objOut = new ObjectOutputStream(fileOut);

            objOut.writeObject(grid);
            objOut.writeObject(prey);
            objOut.writeObject(predators);
            objOut.write(starveCount);
            objOut.write(huntCount);

            objOut.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /** Load ecosystem parameters from file. */
    private void readFromFile()
    {
        try
        {
            FileInputStream fileIn = new FileInputStream("data.dat");
            ObjectInputStream objIn = new ObjectInputStream(fileIn);

            grid = (EcosystemGrid) objIn.readObject();
            prey = (ArrayList<Prey>) objIn.readObject();
            predators = (ArrayList<Predator>) objIn.readObject();
            starveCount = objIn.read();
            huntCount = objIn.read();

            objIn.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /** Returns current time, used upon saving or loading. */
    private String requestTime()
    {
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
        return sdf.format(date);
    }

    /** Adds user selected entities to the ecosystem. */
    private void addUserEntities()
    {
        int x = window.getMouseX();
        int y = window.getMouseY();

        if(drawAction != 0 && mousePressedLeft)
        {
            if(x >= Constants.GRID_OFFSET_BX && x <= Constants.SCREEN_WIDTH - 10)
            {
                if(y >= Constants.GRID_OFFSET_BY && y <= Constants.SCREEN_HEIGHT - 10)
                {
                    x = (int)grid.getCoordinateXAt(Helper.convertToPositionX(x));
                    y = (int)grid.getCoordinateYAt(Helper.convertToPositionY(y));

                    switch (drawAction)
                    {
                        case 1:
                            x = Helper.convertToPositionX(x);
                            y = Helper.convertToPositionY(y);
                            grid.addPlantAt(x, y, PlantGarden.getPlant(PlantGarden.PlantClass.GRASS));
                            break;
                        case 2:
                            x = Helper.convertToPositionX(x);
                            y = Helper.convertToPositionY(y);
                            grid.addPlantAt(x, y, PlantGarden.getPlant(PlantGarden.PlantClass.BLUEBERRY));
                            break;
                        case 3:
                            x = Helper.convertToPositionX(x);
                            y = Helper.convertToPositionY(y);
                            grid.addPlantAt(x, y, PlantGarden.getPlant(PlantGarden.PlantClass.MOSS));
                            break;
                        case 4:
                            x = Helper.convertToPositionX(x);
                            y = Helper.convertToPositionY(y);
                            grid.addPlantAt(x, y, PlantGarden.getPlant(PlantGarden.PlantClass.BEET));
                            break;
                        case 5:
                            x = Helper.convertToPositionX(x);
                            y = Helper.convertToPositionY(y);
                            grid.addPlantAt(x, y, PlantGarden.getPlant(PlantGarden.PlantClass.SUNFLOWER));
                            break;
                        case 6:
                            x = Helper.convertToPositionX(x);
                            y = Helper.convertToPositionY(y);
                            grid.addPlantAt(x, y, PlantGarden.getPlant(PlantGarden.PlantClass.ALYSSUM));
                            break;
                        case 7:
                            prey.add((Prey)AnimalDen.getAnimal(x,y, AnimalDen.AnimalClass.SHEEP));
                            break;
                        case 8:
                            predators.add((Predator) AnimalDen.getAnimal(x,y, AnimalDen.AnimalClass.WOLF));
                            break;
                        case 9:
                            prey.add((Prey)AnimalDen.getAnimal(x,y, AnimalDen.AnimalClass.RABBIT));
                            break;
                        case 10:
                            predators.add((Predator) AnimalDen.getAnimal(x,y, AnimalDen.AnimalClass.WILDCAT));
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    /** Reset ecosystem - clear all entities.*/
    private void reset()
    {
        prey.clear();
        predators.clear();
        grid.removeAll();
    }

    //Fields
    EcosystemGrid grid;

    ArrayList<Prey> prey;
    ArrayList<Predator> predators;

    //Graphics and rendering
    BufferStrategy bs;
    Graphics2D g;

    Window window;

    //System variables
    boolean toggleIndicators;
    boolean toggleRain;
    boolean toggleLocators;
    boolean paused;
    boolean running;

    int drawAction;
    int cycleDuration;
    int plantCount;
    int starveCount;
    int huntCount;
    int preyCount;
    int predatorCount;

    //Input variables
    boolean mousePressedLeft;
    boolean mousePressedRight;
}
