package ecosystem.entities;

import ecosystem.exceptions.InvalidArgumentException;

import java.io.Serializable;
import java.util.Random;

/**
 * <pre>
 * Base class for entities in the ecosystem.
 * Every entity has a position on the field and an energy value / limit.
 *
 * Fields:
 * x and y -- coordinates on the grid, not tied to individual tiles;
 * energyValue -- energy resource for animals (movement and actions),
 * nutritional value for plants (how much energy a specific plant restores);
 * maxEnergyValue -- upper limit for how much energy an entity can have/store;
 * random -- shared RNG between all entities, used for introducing variance
 * in different entities of the same type;
 * </pre>
 */
public abstract class Entity implements Drawable, Serializable
{

    /** Initializes energyValue to half of maxEnergyValue,
     * it cannot be negative.
     * @param x x coordinate (width)
     * @param y y coordinate (height)
     * @param maxEnergyValue upper energy limit
     */
    public Entity(double x, double y, int maxEnergyValue) throws InvalidArgumentException
    {
        if(maxEnergyValue <= 0)
            throw new InvalidArgumentException("assigning non-positive value", "Entity", "maxEnergyValue",
                                                maxEnergyValue);

        setX(x);
        setY(y);

        this.maxEnergyValue = maxEnergyValue;
        setEnergyValue(maxEnergyValue / 2);
    }


    /** @return x coordinate on the grid (width) */
    public double getX() { return x; }

    /** @return y coordinate on the grid (height) */
    public double getY() { return y; }


    /** @return current energy in percentage form */
    public int getEnergyPercentage() { return  (getEnergyValue() * 100) / getMaxEnergyValue(); }

    /** @return current energy value */
    public int getEnergyValue() { return energyValue; }

    /** @return max amount of energy entity can hold */
    public int getMaxEnergyValue() { return maxEnergyValue; }



    /** @param x x coordinate, cannot be negative (width) */
    public void setX(double x)
    {
        if(x >= 0)
            this.x = x;
    }

    /** @param y y coordinate, cannot be negative (height) */
    public void setY(double y)
    {
        if(y >= 0)
            this.y = y;
    }

    /** Sets energy value for entity.
     * Value is set to 0 if argument is negative.
     * Value is set to maxEnergyValue if it exceeds it.*/
    private void setEnergyValue(int energyValue)
    {
        this.energyValue = energyValue <= 0 ? 0 : Math.min(energyValue, getMaxEnergyValue());
    }

    /** Adds energy to entity (cannot exceed maxEnergyValue). */
    public void gainEnergy(int amount) { setEnergyValue(getEnergyValue() + amount); }

    /** Removes energy from entity (cannot go below 0). */
    public void loseEnergy(int amount) { setEnergyValue(getEnergyValue() - amount); }

    /** Returns a string representation of Entity. */
    public String toString()
    {
        String str = "";
        str += ("Coordinates: ( " + getX() + " ; " + getY() + " )\n");
        str += ("Energy: " + getEnergyValue() + "/" + getMaxEnergyValue());
        str += (" (" + getEnergyPercentage() + "%)\n");
        return str;
    }


    //Fields
    private double x;
    private double y;

    private int energyValue;
    private final int maxEnergyValue;

    protected static Random random = new Random();
}
