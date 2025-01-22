package ecosystem.entities.plants;


import ecosystem.entities.Drawable;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.Tile;

import java.awt.*;

/**
 * Grows at a slow rate, reproduces consistently in a large
 * radius around itself and withers at a moderate pace.
 */
public class Blueberry extends Plant
{

    /** Default Blueberry constructor initializes position to (0;0).
     * See {@link #Blueberry(double, double)}. */
    public Blueberry() throws InvalidArgumentException
    {
        this(0, 0);
    }

    /**
     * Forwards to Plant constructor with lifeCycleModifier and growthTimeNeeded
     * values tied to Blueberry plant type. See {@link Plant#Plant(double, double, int, int, int)}
     */
    public Blueberry(double x, double y) throws InvalidArgumentException
    {
        super(x, y, TOTAL_GROWTH_TIME + random.nextInt(LIFETIME_MODIFIER),
                2 * LIFETIME_MODIFIER + random.nextInt(TOTAL_GROWTH_TIME), LIFETIME_MODIFIER);
    }


    /** See {@link Plant#getSeed()}. */
    public Plant getSeed()
    {
        return PlantGarden.getPlant(PlantGarden.PlantClass.BLUEBERRY);
    }

    /** See {@link Plant#getTerrainType()}. */
    public TerrainType getTerrainType() { return TerrainType.SOIL; }

    /** See {@link Plant#getPattern()}. */
    public int[] getPattern()
    {
        int[] pattern = new int[8];

        pattern[0] = 2;
        pattern[1] = -2;

        pattern[2] = -2;
        pattern[3] = -2;

        pattern[4] = 2;
        pattern[5] = 2;

        pattern[6] = -2;
        pattern[7] = 2;

        return pattern;
    }

    /** See {@link Drawable#getColor()}. */
    public Color getColor() { return new Color(30, 144, 255); }

    /** See {@link Drawable#getAdditionalColor()}. */
    public Color getAdditionalColor() { return new Color(173,216,230); }

    /** See {@link Drawable#getDrawWidth()}. */
    public int getDrawWidth() { return Tile.SIZE; }

    /** See {@link Drawable#getDrawHeight()}. */
    public int getDrawHeight() { return Tile.SIZE; }

    //Fields shared by Blueberry type plants
    private static final int TOTAL_GROWTH_TIME = 270;
    private static final int LIFETIME_MODIFIER = 10;
}
