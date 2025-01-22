package ecosystem.grid;

import ecosystem.entities.plants.Plant;
import ecosystem.exceptions.NegativeDimensionsException;
import ecosystem.containers.Array2D;

import java.io.Serializable;
import java.util.Iterator;

/**
 * <pre>
 * Combines two layers - positional grid and plant grid.
 * This way plants are tied to grid and easier to manage.
 * One tile can only have one plant.
 * </pre>
 */
public class EcosystemGrid extends Grid implements Serializable
{
    /**
     * Initializes plant 2D array alongside {@link ecosystem.grid.Grid}.
     * @param width columns in the grid
     * @param height rows in the grid
     */
    public EcosystemGrid(int width, int height) throws NegativeDimensionsException
    {
        super(width, height);
        flora = new Array2D<>(new Plant[width][height]);
    }

    /**
     * Returns specified tile content.
     * @param x column position in the grid
     * @param y row position in the grid
     * @return plant at specified tile (null if it does not exist)
     */
    public Plant getPlantAt(int x, int y)
    {
        return exists(x, y) ? flora.get(x, y) : null;
    }


    /**
     * Adds plant to specified tile in the grid.
     * Tile has to be empty and the have the
     * correct terrain for the plant to grow.
     * @param x column position in the grid
     * @param y row position in the grid
     * @param newPlant plant to be added at specified tile
     */
    public void addPlantAt(int x, int y, Plant newPlant)
    {
        if(isEmptyAt(x, y) && newPlant != null && sameTypeAt(x, y, newPlant))
        {
            newPlant.setX(getCoordinateXAt(x) + (Tile.SIZE / 2.0));
            newPlant.setY(getCoordinateYAt(y) + (Tile.SIZE / 2.0));
            flora.set(x, y, newPlant);
        }
    }

    /**
     * Checks if specified plant can grow in provided
     * tile - their terrain types have to match.
     * @param x column position in the grid
     * @param y row position in the grid
     * @param plant plant in question
     * @return true, if terrain and plant types match
     */
    public boolean sameTypeAt(int x, int y, Plant plant)
    {
        return getTypeAt(x, y) == plant.getTerrainType();
    }

    /**
     * Removes plant from a specified tile
     * (or at least disassociates plant from tile).
     * @param x column position in the grid
     * @param y row position in the grid
     */
    public void removePlantAt(int x, int y)
    {
        if(exists(x, y))
            flora.set(x, y, null);
    }

    /**
     * Checks if tile is available for planting.
     * @param x column position in the grid
     * @param y row position in the grid
     * @return true, if specified tile is empty
     *         false, if occupied or does not exist
     */
    public boolean isEmptyAt(int x, int y)
    {
        return exists(x, y) && flora.get(x, y) == null;
    }


    /**
     * Reproduces plant at specified tile. Which tiles it
     * reproduces to are dependent on plant type.
     * @param x column position in the grid
     * @param y row position in the grid
     */
    public void reproducePlantAt(int x, int y)
    {
        Plant plant = getPlantAt(x, y);
        int[] pattern = plant.getPattern();

        int posX = 0;
        int posY = 0;
        for(int i = 0; i < pattern.length; ++i)
        {
            if(i % 2 == 0)
                posX = x + pattern[i];
            else
            {
                posY = y + pattern[i];

                addPlantAt(posX, posY, plant.getSeed());
            }
        }
    }

    /** Returns current plant count in the ecosystem. */
    public int getPlantCount()
    {
        int count = 0;
        for(Plant plant : flora)
        {
            if(plant != null)
                ++count;
        }
        return count;
    }

    /** Removes all plants from the grid. */
    public void removeAll()
    {
        for (Iterator<Plant> it = flora.iterator(); it.hasNext(); )
            it.remove();
    }

    //2D Plant grid
    private Array2D<Plant> flora;
}
