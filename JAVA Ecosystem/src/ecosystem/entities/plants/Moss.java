package ecosystem.entities.plants;

import ecosystem.entities.Drawable;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.Tile;

import java.awt.*;

public class Moss extends Plant
{
    /** Default Moss constructor initializes position to (0;0).
     * See {@link #Moss(double, double)}. */
    public Moss() throws InvalidArgumentException
    {
        this(0, 0);
    }

    /**
     * Forwards to Plant constructor with lifeCycleModifier and growthTimeNeeded
     * values tied to Moss plant type. See {@link Plant#Plant(double, double, int, int, int)}
     */
    public Moss(double x, double y) throws InvalidArgumentException
    {
        super(x, y, TOTAL_GROWTH_TIME + random.nextInt(LIFETIME_MODIFIER),
                LIFETIME_MODIFIER, LIFETIME_MODIFIER);
    }


    /** See {@link Plant#getSeed()}. */
    public Plant getSeed()
    {
        return PlantGarden.getPlant(PlantGarden.PlantClass.MOSS);
    }

    /** See {@link Plant#getTerrainType()}. */
    public TerrainType getTerrainType() { return TerrainType.SOIL; }

    /** See {@link Plant#getPattern()}. */
    public int[] getPattern()
    {
        int[] pattern = new int[6];

        switch (random.nextInt(4))
        {
            case 0:
                pattern[0] = 0;
                pattern[1] = -3;
                pattern[2] = 1;
                pattern[3] = -3;
                pattern[4] = -1;
                pattern[5] = -3;
                break;
            case 1:
                pattern[0] = 3;
                pattern[1] = -1;
                pattern[2] = 3;
                pattern[3] = 0;
                pattern[4] = 3;
                pattern[5] = 1;
                break;
            case 2:
                pattern[0] = 1;
                pattern[1] = 3;
                pattern[2] = 0;
                pattern[3] = 3;
                pattern[4] = -1;
                pattern[5] = 3;
                break;
            case 3:
                pattern[0] = -3;
                pattern[1] = 1;
                pattern[2] = -3;
                pattern[3] = 0;
                pattern[4] = -3;
                pattern[5] = -1;
                break;
            default:
                break;
        }
        return pattern;
    }

    /** See {@link Drawable#getColor()}. */
    public Color getColor() { return new Color(162, 178, 120); }

    /** See {@link Drawable#getAdditionalColor()}. */
    public Color getAdditionalColor() { return new Color(203, 215, 179); }

    /** See {@link Drawable#getDrawWidth()}. */
    public int getDrawWidth() { return Tile.SIZE; }

    /** See {@link Drawable#getDrawHeight()}. */
    public int getDrawHeight() { return Tile.SIZE; }

    //Fields shared by Blueberry type plants
    private static final int TOTAL_GROWTH_TIME = 300;
    private static final int LIFETIME_MODIFIER = 10;
}
