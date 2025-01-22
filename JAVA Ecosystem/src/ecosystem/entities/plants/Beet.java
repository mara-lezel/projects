package ecosystem.entities.plants;

import ecosystem.entities.Drawable;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.Tile;

import java.awt.*;

public class Beet extends Plant
{
    /** Default Beet constructor initializes position to (0;0).
     * See {@link #Beet(double, double)}. */
    public Beet() throws InvalidArgumentException
    {
        this(0, 0);
    }

    /**
     * Forwards to Plant constructor with lifeCycleModifier and growthTimeNeeded
     * values tied to Beet plant type. See {@link Plant#Plant(double, double, int, int, int)}
     */
    public Beet(double x, double y) throws InvalidArgumentException
    {
        super(x, y, TOTAL_GROWTH_TIME + random.nextInt(TOTAL_GROWTH_TIME),
                2 * TOTAL_GROWTH_TIME, LIFETIME_MODIFIER);
    }


    /** See {@link Plant#getSeed()}. */
    public Plant getSeed()
    {
        return PlantGarden.getPlant(PlantGarden.PlantClass.BEET);
    }

    /** See {@link Plant#getTerrainType()}. */
    public TerrainType getTerrainType() { return TerrainType.SOIL; }

    /** See {@link Plant#getPattern()}. */
    public int[] getPattern()
    {
        int[] pattern = new int[4];

        pattern[0] = random.nextInt(5);
        pattern[1] = random.nextInt(5);;
        pattern[2] = random.nextInt(5);;
        pattern[3] = random.nextInt(5);

        return pattern;
    }

    /** See {@link Drawable#getColor()}. */
    public Color getColor() { return new Color(162, 57, 79); }

    /** See {@link Drawable#getAdditionalColor()}. */
    public Color getAdditionalColor() { return new Color(192, 117, 117); }

    /** See {@link Drawable#getDrawWidth()}. */
    public int getDrawWidth() { return Tile.SIZE; }

    /** See {@link Drawable#getDrawHeight()}. */
    public int getDrawHeight() { return Tile.SIZE; }

    //Fields shared by Blueberry type plants
    private static final int TOTAL_GROWTH_TIME = 150;
    private static final int LIFETIME_MODIFIER = 2;
}
