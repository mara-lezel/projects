package ecosystem.entities.animals;

import ecosystem.entities.Entity;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.Tile;

/**
 * <pre>
 * Animal class implements basic animal traits - movement speed,
 * sense and action range restraints.
 *
 * Fields:
 * movementSpeed -- distance animal covers per simulation cycle;
 * targetingRadius -- target selection distance, looking for food/prey;
 * targetTile -- tile occupied by target plant or animal;
 * </pre>
 */
public abstract class Animal extends Entity implements AnimalBehaviour
{

    /**
     * Animal constructor values cannot be negative, initial target
     * is set to null.
     * @param x x coordinate (width)
     * @param y y coordinate (height)
     * @param maxEnergyValue upper energy limit
     * @param movementSpeed distance covered per cycle (in pixels)
     * @param targetingRadius target selection distance (in pixels)
     */
    public Animal(double x, double y, int maxEnergyValue, double movementSpeed, double targetingRadius)
            throws InvalidArgumentException
    {
        super(x, y, maxEnergyValue);

        setMovementSpeed(movementSpeed);
        setTargetingRadius(targetingRadius);
        setTargetTile(null);
    }


    /**
     * Updates moving speed of an animal.
     * Speed changes depending on the surface or when animal has no energy left.
     * @param movementSpeed distance that animal covers per cycle (in pixels)
     */
    public void setMovementSpeed(double movementSpeed)
    {
        if(movementSpeed > 0)
            this.movementSpeed = movementSpeed;
    }

    /**
     * Updates targeting distance of an animal.
     * Radius changes depending on weather conditions.
     * @param targetingRadius target selection distance (in pixels)
     */
    public void setTargetingRadius(double targetingRadius)
    {
        if(targetingRadius > 0)
            this.targetingRadius = targetingRadius;
    }

    /**
     * Updates target tile location on the grid.
     * Passing null forces animal to look for new target tile.
     * @param targetTile new destination on the tile grid
     */
    public void setTargetTile(Tile targetTile) { this.targetTile = targetTile; }


    /** @return current movement speed (pixels per cycle) */
    public double getMovementSpeed() { return movementSpeed; }

    /** @return tile an animal is currently trying to reach */
    public Tile getTargetTile() { return targetTile; }

    /** @return targeting distance, used for spotting food/prey (in pixels) */
    public double getTargetingRadius() { return targetingRadius; }


    /** @return true, if animal reached its target location */
    public boolean isAtTarget() { return getTargetTile().holdsEntityAt(getX(), getY()); }

    /** @return true, if animal target tile is not set (null) */
    public boolean hasNoTarget() { return getTargetTile() == null; }

    /** Returns a string representation of Animal. */
    public String toString()
    {
        String str = super.toString();
        str += ("Movement speed: " + movementSpeed + " px/cycle\n");
        str += ("Targeting radius: " + targetingRadius + " px\n");
        str += ("Target tile: " + (targetTile == null ? "null" : targetTile.toString()) + "\n");
        return str;
    }

    //Fields
    private double movementSpeed;
    private double targetingRadius;
    private Tile targetTile;
}

