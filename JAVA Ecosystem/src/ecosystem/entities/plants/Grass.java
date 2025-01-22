package ecosystem.entities.plants;

import ecosystem.entities.Drawable;
import ecosystem.enums.TerrainType;
import ecosystem.exceptions.InvalidArgumentException;
import ecosystem.grid.Tile;

import java.awt.*;

/**
 * Most common plant in the ecosystem.
 * Grows at a moderate pace, reproduces inconsistently in tiles
 * around itself and withers fast.
 */
public class Grass extends Plant
{
    /** Default Grass constructor initializes position to (0;0).
     * See {@link #Grass(double, double)}. */
    public Grass() throws InvalidArgumentException
    {
        this(0, 0);
    }

    /**
     * Forwards to Plant constructor with lifeCycleModifier and growthTimeNeeded
     * values tied to Grass plant type. See {@link Plant#Plant(double, double, int, int, int)}
     */
    public Grass(double x, double y) throws InvalidArgumentException
    {
        super(x, y, TOTAL_GROWTH_TIME + random.nextInt(LIFETIME_MODIFIER),
                LIFETIME_MODIFIER, LIFETIME_MODIFIER);
    }

    /** See {@link Plant#getSeed()}. */
    public Plant getSeed()
    {
        return PlantGarden.getPlant(PlantGarden.PlantClass.GRASS);
    }

    /** See {@link Plant#getTerrainType()}. */
    public TerrainType getTerrainType() { return TerrainType.SOIL; }

    /** See {@link Plant#getPattern()}. */
    public int[] getPattern()
    {
        int[] pattern = new int[4];

        switch(random.nextInt(4))
        {
            case 0:
                pattern[0] = 0;
                pattern[1] = -1;
                pattern[2] = 1;
                pattern[3] = 0;
                break;
            case 1:
                pattern[0] = 1;
                pattern[1] = 0;
                pattern[2] = 0;
                pattern[3] = 1;
                break;
            case 2:
                pattern[0] = 1; //1
                pattern[1] = random.nextInt(20); //0
                pattern[2] = -1;
                pattern[3] = 0;
                break;
            case 3:
                pattern[0] = -1;
                pattern[1] = 0;
                pattern[2] = 0;
                pattern[3] = -1;
                break;
        }

        return pattern;
    }

    /** See {@link Drawable#getColor()}. */
    public Color getColor() { return new Color(154, 205, 50); }

    /** See {@link Drawable#getAdditionalColor()}. */
    public Color getAdditionalColor() { return new Color(228, 217, 111); }

    /** See {@link Drawable#getDrawWidth()}. */
    public int getDrawWidth() { return Tile.SIZE; }

    /** See {@link Drawable#getDrawHeight()}. */
    public int getDrawHeight() { return Tile.SIZE; }

    //Fields shared by Grass type plants
    private static final int TOTAL_GROWTH_TIME = 20;
    private static final int LIFETIME_MODIFIER = 60;
}
