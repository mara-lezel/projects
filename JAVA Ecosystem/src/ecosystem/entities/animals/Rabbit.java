package ecosystem.entities.animals;

import ecosystem.entities.Drawable;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.EcosystemGrid;
import ecosystem.grid.Tile;
import ecosystem.helper.Constants;
import ecosystem.helper.Helper;

import java.awt.*;
import java.util.ArrayList;

public class Rabbit extends Prey
{
    /**
     * Forwards to Animal constructor with movementSpeed and targetingRadius values tied to
     * Rabbit animal type. See {@link Animal#Animal(double, double, int, double, double)}.
     */
    public Rabbit(double x, double y) throws InvalidArgumentException
    {
        super(x, y, (int)(MOVEMENT_SPEED * TARGETING_RADIUS * ENERGY_MULTIPLIER), MOVEMENT_SPEED, TARGETING_RADIUS);
    }


    /** See {@link AnimalBehaviour#move()}. */
    public void move()
    {
        //Manage speed and energy
        if(isFleeing())
        {
            setMovementSpeed(getRunningSpeed(MOVEMENT_SPEED));
            loseEnergy(2);
        }
        else
        {
            setMovementSpeed(MOVEMENT_SPEED);
            loseEnergy(1);
        }


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


    /** See {@link PreyBehaviour#selectTarget(EcosystemGrid)}. */
    public void selectTarget(EcosystemGrid grid)
    {
        setFleeing(false);
        setMovementSpeed(MOVEMENT_SPEED);

        double shortestDistance = 5000;
        for(int i = 0; i < grid.getHeight(); ++i)
        {
            for(int j = 0; j < grid.getWidth(); ++j)
            {
                if(!grid.isEmptyAt(j, i))
                {
                    double distance = Helper.euclidianDistance(this, grid.getPlantAt(j, i));

                    if(distance <= getTargetingRadius())
                    {
                        if(distance < shortestDistance)
                        {
                            setTargetTile(grid.getTileAt(j, i));
                            shortestDistance = distance;
                        }
                    }
                }
            }
        }

        //IF NO TARGET IS FOUND, ROAM RANDOMLY
        if(shortestDistance == 5000)
        {
            int randomPosX = random.nextInt(grid.getWidth());
            int randomPosY = random.nextInt(grid.getHeight());
            setTargetTile(grid.getTileAt(randomPosX, randomPosY));
        }
    }

    /** See {@link PreyBehaviour#scatter(ArrayList)}. */
    public void scatter(ArrayList<Predator> predators)
    {
        for(Predator predator : predators)
        {
            if(Helper.euclidianDistance(this, predator) < getTargetingRadius() && !isFleeing())
            {
                int tileX = Helper.convertToPositionX(2 * getX() - predator.getX());
                int tileY = Helper.convertToPositionY(2 * getY() - predator.getY());
                int variance = random.nextInt(2);

                if(getY() + getTargetingRadius() > Constants.GRID_END_Y || getY() - getTargetingRadius() < 0)
                {
                    tileX = variance == 0 ? tileX - 5 : tileX + 5;
                    tileY = Helper.convertToPositionY(getY());
                }
                if(getX() + getTargetingRadius() > Constants.GRID_END_X || getX() - getTargetingRadius() < 0)
                {
                    tileY = variance == 0 ? tileY - 5 : tileY + 5;
                    tileX = Helper.convertToPositionX(getX());
                }

                setTargetTile(new Tile(tileX + variance, tileY + variance, TerrainType.SOIL));

                setFleeing(true);
            }
        }
    }

    /** See {@link Drawable#getColor()}. */
    public Color getColor() { return new Color(234, 126, 20); }

    /** See {@link Drawable#getAdditionalColor()}. */
    public Color getAdditionalColor() { return new Color(0, 150, 0); }

    /** See {@link Drawable#getDrawWidth()}. */
    public int getDrawWidth() { return Tile.SIZE; }

    /** See {@link Drawable#getDrawHeight()}. */
    public int getDrawHeight() { return Tile.SIZE; }


    //Shared fields
    private static final double MOVEMENT_SPEED = 1.7;
    private static final double TARGETING_RADIUS = 50;
    private static final double ENERGY_MULTIPLIER = 25;
}
