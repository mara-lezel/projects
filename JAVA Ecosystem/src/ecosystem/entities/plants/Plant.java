package ecosystem.entities.plants;

import ecosystem.entities.Entity;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;

/**
 * <pre>
 * Plant class that represents all shared plant functionality -
 * growth and reproduction.
 *
 * Plants grow with every simulation cycle (if conditions allow it).
 *
 * Once plants are fully grown, they can reproduce and populate nearby
 * tiles with plants of the same type (which tiles are targeted depends
 * on the plant type). Plants can only attempt to reproduce once.
 *
 * If plants are not consumed, they will eventually wither, bringing
 * their nutrition (energy) value to minimum.
 *
 * The time it takes for a plant to wither is determined by life cycle
 * modifier constant - with a bigger constant, the plant will persist
 * longer.
 * </pre>
 */
public abstract class Plant extends Entity
{
    /**
     * Initial growth is always 0, how much energy the plant
     * contains depends on the time needed for the plant
     * to fully mature.
     * @param x  x coordinate on the grid (width)
     * @param y  y coordinate on the grid (height)
     * @param growthTimeNeeded  time cycles needed for a plant
     *                          to fully grow and reproduce
     * @param maxEnergyValue  amount of energy a fully mature
     *                        plant holds
     * @param lifeCycleModifier how long can plant exist without
     *                          withering (e.g. modifier 3 = 300%
     *                          lifespan)
     */
    public Plant(double x, double y, int growthTimeNeeded, int maxEnergyValue, int lifeCycleModifier)
            throws InvalidArgumentException
    {
        super(x, y, maxEnergyValue);

        if(growthTimeNeeded <= 0)
            throw new InvalidArgumentException("assigning non-positive value", "Plant", "growthTimeNeeded",
                    growthTimeNeeded);

        if(lifeCycleModifier <= 0)
            throw new InvalidArgumentException("assigning non-positive value", "Plant", "lifeCycleModifier",
                    lifeCycleModifier);

        this.growthTime = 0;
        this.growthTimeNeeded = growthTimeNeeded;
        this.lifeCycleModifier = lifeCycleModifier;
    }


    /** @return current growth percentage (100% means fully grown) */
    public int getGrowthPercentage() { return (growthTime * 100) / growthTimeNeeded; }

    /** @return time cycles already completed */
    public int getGrowthTime() { return growthTime; }

    /** @return time until plant is fully grown */
    public int getGrowthTimeNeeded() { return growthTimeNeeded; }

    /** @return time until plant withers */
    public int getLifecycleTime() { return growthTimeNeeded * lifeCycleModifier; }

    /** Resets plant's growth value.
     *  Used only during rain, otherwise should not be called. */
    public void setGrowthToZero() { growthTime = 0; }


    /** Increases plant's growth value. */
    public void grow()
    {
        ++growthTime;

        if(isWithered() && getEnergyPercentage() > 25)
            loseEnergy(1);
        if(getGrowthTime() % 7 == 0 && !isWithered())
            gainEnergy(1);
    }

    /** @return true, if plant is able to reproduce */
    public boolean canReproduce() { return growthTime == growthTimeNeeded; }

    /** @return true, if plant exceeded its life cycle
     *          false, if plant is still growing or mature */
    public boolean isWithered() { return growthTime >= growthTimeNeeded * lifeCycleModifier; }

    /** Returns a string representation of Plant. */
    public String toString()
    {
        String str = super.toString();
        str += ("Growth: " + getGrowthTime() + "/" + getGrowthTimeNeeded());
        str += (" (" + getGrowthPercentage() + "%)\n");
        str += ("Lifespan: " + lifeCycleModifier + " (becomes withered at " + lifeCycleModifier * 100 + "% growth)\n");
        return str;
    }

    /**
     * <pre>
     * Returns the reproduction pattern of a plant.
     * Pattern is an array of alternating position directions, where even
     * indexes represent [x] and odd indexes represent [y] on the tile grid.
     *
     * Position directions:
     * [x] - value representing tile count from plant's current tile on x-axis
     * [y] - value representing tile count from plant's current tile on y-axis
     *
     * @return array of alternating position directions
     * </pre>
     */
    public abstract int[] getPattern();

    /** @return terrain type required for plant to grow */
    public abstract TerrainType getTerrainType();

    /** Creates and returns a new plant of the same type.
     *  @return new plant object derived from Plant */
    public abstract Plant getSeed();


    //Fields
    private int growthTime;
    private final int growthTimeNeeded;

    private final int lifeCycleModifier;
}
