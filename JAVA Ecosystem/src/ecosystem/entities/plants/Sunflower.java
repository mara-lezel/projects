package ecosystem.entities.plants;

import ecosystem.entities.Drawable;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.Tile;
import ecosystem.helper.Constants;

import java.awt.*;

public class Sunflower extends Plant
{
    /** Default Sunflower constructor initializes position to (0;0).
     * See {@link #Sunflower(double, double)}. */
    public Sunflower() throws InvalidArgumentException
    {
        this(0, 0);
    }

    /**
     * Forwards to Plant constructor with lifeCycleModifier and growthTimeNeeded
     * values tied to Sunflower plant type. See {@link Plant#Plant(double, double, int, int, int)}
     */
    public Sunflower(double x, double y) throws InvalidArgumentException
    {
        super(x, y, TOTAL_GROWTH_TIME + random.nextInt(LIFETIME_MODIFIER),
                10 * LIFETIME_MODIFIER + random.nextInt(TOTAL_GROWTH_TIME), LIFETIME_MODIFIER);
    }


    /** See {@link Plant#getSeed()}. */
    public Plant getSeed()
    {
        return PlantGarden.getPlant(PlantGarden.PlantClass.SUNFLOWER);
    }

    /** See {@link Plant#getTerrainType()}. */
    public TerrainType getTerrainType() { return TerrainType.SOIL; }

    /** See {@link Plant#getPattern()}. */
    public int[] getPattern()
    {
        int[] pattern = new int[2];

        pattern[0] = random.nextInt(3) - 4;
        pattern[1] = random.nextInt(10);

        return pattern;
    }

    /** See {@link Drawable#getColor()}. */
    public Color getColor() { return new Color(235, 179, 43); }

    /** See {@link Drawable#getAdditionalColor()}. */
    public Color getAdditionalColor() { return new Color(156,125,34); }

    /** See {@link Drawable#getDrawWidth()}. */
    public int getDrawWidth() { return Tile.SIZE; }

    /** See {@link Drawable#getDrawHeight()}. */
    public int getDrawHeight() { return Tile.SIZE; }

    //Fields shared by Blueberry type plants
    private static final int TOTAL_GROWTH_TIME = 50;
    private static final int LIFETIME_MODIFIER = 20;
}
