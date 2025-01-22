package ecosystem.grid;

import ecosystem.enums.TerrainType;
import ecosystem.exceptions.NegativeDimensionsException;
import ecosystem.containers.Array2D;

import java.io.Serializable;

/**
 * <pre>
 * Class representing the positional layout of the ecosystem
 * as 2D tile grid.
 *
 * Responsible for changing the state of individual tiles in
 * the grid.
 * </pre>
 */
public class Grid implements Serializable
{
    /**
     * Grid dimensions are set to the smallest width and height
     * when parameters are negative (or incorrect).
     * @param width  columns of the grid (from 0 to width - 1)
     * @param height  rows of the grid (from 0 to height - 1)
     */
    public Grid(int width, int height) throws NegativeDimensionsException
    {
        if(width <= 0 || height <= 0)
            throw new NegativeDimensionsException("assigning non-positive dimension values", "Grid", width, height);

        this.width = width;
        this.height = height;

        initGrid();
    }

    /**
     * Helper method for the Grid constructor.
     * Creates all tile objects in the grid and initializes
     * their position and type.
     */
    private void initGrid()
    {
        Tile[][] grid = new Tile[width][height];

        for(int i = 0; i < width; ++i)
            for(int j = 0; j < height; ++j)
                grid[i][j] = new Tile(i, j, TerrainType.SOIL);

        this.grid = new Array2D<>(grid);
    }


    /**
     * Get terrain type at grid position [x][y].
     * @param x  x position on the grid (column)
     * @param y  y position on the grid (row)
     * @return terrain type of the tile, if it exists;
     *         null otherwise
     */
    public TerrainType getTypeAt(int x, int y)
    {
        return exists(x, y) ? grid.get(x, y).getType() : null;
    }

    /**
     * Get tile at grid position [x][y].
     * @param x  x position on the grid (column)
     * @param y  y position on the grid (row)
     * @return selected tile on the grid
     */
    public Tile getTileAt(int x, int y)
    {
        return exists(x, y) ? grid.get(x, y) : null;
    }


    /** @return height of the grid (row count) */
    public int getHeight() { return height; }

    /** @return width of the grid (column count) */
    public int getWidth()  { return width; }

    /** @return column coordinate of the tile */
    public double getCoordinateXAt(int x) { return grid.get(x, 0).getX(); }

    /** @return row coordinate of the tile */
    public double getCoordinateYAt(int y) { return grid.get(0, y).getY(); }

    //CHECK LATER
    /** @return column position of selected coordinates */
    public int getPositionXAt(double x) { return (int)x / Tile.SIZE; }

    /** @return row position of selected coordinates */
    public int getPositionYAt(double y) { return (int)y / Tile.SIZE; }


    /**
     * Changes terrain type of the tile, if it exists.
     * @param x  x position on the grid (column)
     * @param y  y position on the grid (row)
     * @param type terrain type of the tile
     */
    public void setTypeAt(int x, int y, TerrainType type)
    {
        if(exists(x, y))
            grid.get(x, y).setType(type);
    }

    /**
     * Checks whether a requested tile belongs to the grid.
     * @param x  x position on the grid (column)
     * @param y  y position on the grid (row)
     * @return true if tile is valid, false otherwise
     */
    public final boolean exists(int x, int y)
    {
        return (x >= 0 && x < width) && (y >= 0 && y < height);
    }


    //Private fields
    private final int width;
    private final int height;

    private Array2D<Tile> grid;
}
