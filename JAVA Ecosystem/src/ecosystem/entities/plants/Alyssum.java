package ecosystem.entities.plants;

import ecosystem.entities.Drawable;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.Tile;

import java.awt.*;

public class Alyssum extends Plant
{
    /** Default Alyssum constructor initializes position to (0;0).
     * See {@link #Alyssum(double, double)}. */
    public Alyssum() throws InvalidArgumentException
    {
        this(0, 0);
    }

    /**
     * Forwards to Plant constructor with lifeCycleModifier and growthTimeNeeded
     * values tied to Alyssum plant type. See {@link Plant#Plant(double, double, int, int, int)}
     */
    public Alyssum(double x, double y) throws InvalidArgumentException
    {
        super(x, y, TOTAL_GROWTH_TIME + random.nextInt(TOTAL_GROWTH_TIME),
                TOTAL_GROWTH_TIME + random.nextInt(TOTAL_GROWTH_TIME), LIFETIME_MODIFIER);
    }


    /** See {@link Plant#getSeed()}. */
    public Plant getSeed()
    {
        return PlantGarden.getPlant(PlantGarden.PlantClass.ALYSSUM);
    }

    /** See {@link Plant#getTerrainType()}. */
    public TerrainType getTerrainType() { return TerrainType.SOIL; }

    /** See {@link Plant#getPattern()}. */
    public int[] getPattern()
    {
        int[] pattern = new int[6];

        switch (random.nextInt(2))
        {
            case 0:
                pattern[0] = 1;
                pattern[1] = 0;
                pattern[2] = -1;
                pattern[3] = 0;
                pattern[4] = 0;
                pattern[5] = -1;
                break;
            case 1:
                pattern[0] = 1;
                pattern[1] = 0;
                pattern[2] = -1;
                pattern[3] = 0;
                pattern[4] = 0;
                pattern[5] = 0;
                break;
            default:
                break;
        }

        return pattern;
    }

    /** See {@link Drawable#getColor()}. */
    public Color getColor() { return new Color(179, 120, 211); }

    /** See {@link Drawable#getAdditionalColor()}. */
    public Color getAdditionalColor() { return new Color(205, 167, 229); }

    /** See {@link Drawable#getDrawWidth()}. */
    public int getDrawWidth() { return Tile.SIZE; }

    /** See {@link Drawable#getDrawHeight()}. */
    public int getDrawHeight() { return Tile.SIZE; }

    //Fields shared by Blueberry type plants
    private static final int TOTAL_GROWTH_TIME = 200;
    private static final int LIFETIME_MODIFIER = 5;
}
