package ecosystem.entities.animals;

import ecosystem.entities.Drawable;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.Tile;
import ecosystem.helper.Constants;
import ecosystem.helper.Helper;

import java.awt.*;
import java.util.ArrayList;

public class Wolf extends Predator
{

    /**
     * Forwards to Animal constructor with movementSpeed and targetingRadius values tied to
     * Wolf animal type. See {@link Animal#Animal(double, double, int, double, double)}.
     */
    public Wolf(double x, double y) throws InvalidArgumentException
    {
        super(x, y, (int)(MOVEMENT_SPEED * TARGETING_RADIUS * ENERGY_MULTIPLIER), MOVEMENT_SPEED, TARGETING_RADIUS);
    }


    /** See {@link AnimalBehaviour#move()}. */
    public void move()
    {
        loseEnergy(1);

        double targetX = getTargetTile().getX();
        double targetY = getTargetTile().getY();

        double x = getX();
        double y = getY();

        //If entity moves diagonally, decrease speed by half (otherwise movement is 2x faster)
        int diagonal = 2;

        if(targetX > x && !getTargetTile().holdsEntityAtX(x)) //RIGHT
            setX(x + getMovementSpeed());
        else if(targetX < x && !getTargetTile().holdsEntityAtX(x)) //LEFT
            setX(x - getMovementSpeed());
        else
            diagonal = 1;

        if(targetY > y && !getTargetTile().holdsEntityAtY(y)) //DOWN
            setY(y + getMovementSpeed() / diagonal);
        else if(targetY < y && !getTargetTile().holdsEntityAtY(y)) //UP
            setY(y - getMovementSpeed() / diagonal);
    }


    /** See {@link PredatorBehaviour#selectTarget(ArrayList)}. */
    public void selectTarget(ArrayList<Prey> prey)
    {
        double shortestDistance = 5000;
        for(int i = 0; i < prey.size(); ++i)
        {
            double distance = Helper.euclidianDistance(this, prey.get(i));
            if(distance <= getTargetingRadius())
            {
                if(distance < shortestDistance)
                {
                    int posX = Helper.convertToPositionX(prey.get(i).getX());
                    int posY = Helper.convertToPositionY(prey.get(i).getY());

                    setTargetTile(new Tile(posX, posY, TerrainType.SOIL));
                    shortestDistance = distance;
                }
            }
        }

        //IF NO TARGET IS FOUND, ROAM RANDOMLY
        if(shortestDistance == 5000 && getTargetTile() == null)
        {
            if(!prey.isEmpty() && random.nextInt(100) < 10)
            {
                int posX = Helper.convertToPositionX(prey.get(0).getX());
                int posY = Helper.convertToPositionY(prey.get(0).getY());

                setTargetTile(new Tile(posX, posY, TerrainType.SOIL));
            }
            else
            {
                int randomPosX = random.nextInt(Constants.GRID_WIDTH);
                int randomPosY = random.nextInt(Constants.GRID_HEIGHT);

                setTargetTile(new Tile(randomPosX, randomPosY, TerrainType.SOIL));
            }
        }
    }

    /** See {@link PredatorBehaviour#pounce(ArrayList)}. */
    public void pounce(ArrayList<Prey> prey)
    {
        for(Prey preyAnimal : prey)
        {
            if(Helper.euclidianDistance(this, preyAnimal) < getPounceRadius(TARGETING_RADIUS))
            {
                setX(preyAnimal.getX());
                setY(preyAnimal.getY());

                gainEnergy(preyAnimal.getEnergyValue());
                prey.remove(preyAnimal);

                break;
            }
        }
    }

    /** See {@link Drawable#getColor()}. */
    public Color getColor() { return new Color(128,128,128); }

    /** See {@link Drawable#getAdditionalColor()}. */
    public Color getAdditionalColor() { return new Color(150, 0, 0); }

    /** See {@link Drawable#getDrawWidth()}. */
    public int getDrawWidth() { return Tile.SIZE; }

    /** See {@link Drawable#getDrawHeight()}. */
    public int getDrawHeight() { return Tile.SIZE; }

    //Shared fields
    private static final double MOVEMENT_SPEED = 1.6;
    private static final double TARGETING_RADIUS = 45;
    private static final double ENERGY_MULTIPLIER = 50;
}
