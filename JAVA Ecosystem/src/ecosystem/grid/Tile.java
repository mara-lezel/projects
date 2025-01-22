package ecosystem.grid;

import ecosystem.enums.TerrainType;
import ecosystem.helper.Constants;
import ecosystem.helper.Helper;

import java.io.Serializable;

/**
 * <pre>
 * Class representing a tile - unit, that is used to build the entire
 * ecosystem grid.
 *
 * Fields:
 * x and y -- position / coordinates - [x][y] or (x * SIZE ; y * SIZE);
 * type -- {@link TerrainType};
 * SIZE -- tile dimensions shared by all Tile objects;
 *
 * Coordinates and position are not the same.
 * Position only accounts for tiles in the grid.
 * Coordinates also track entity's position within a tile.
 *
 * E.g. if a tile is 8px and entity's coordinates
 * are (5;3) then entity's position is going to be the very
 * first tile [0][0] and not [5][3].
 *
 * Position is used for ecosystem's internal logic, coordinates are used
 * mainly for graphical representation (drawing).
 * </pre>
 */
public class Tile implements Serializable
{

    /** Default constructor -- initializes tile coordinates to (0;0)
     * and sets terrain type to SOIL.*/
    public Tile() { this(0, 0, TerrainType.SOIL); }

    /**
     * Tile constructor for initializing tiles by position.
     * Format: [x][y] -- [column][row]
     * @param x x position on the grid (column number)
     * @param y y position on the grid (row number)
     * @param type terrain type of the tile (SOIL, ROCK, WATER)
     */
    public Tile(int x, int y, TerrainType type)
    {
        setPosX(x);
        setPosY(y);
        setType(type);
    }


    /** @return top-left x coordinate of the tile */
    public double getX() { return Helper.convertToCoordinateX(x); }

    /** @return top-left y coordinate of the tile */
    public double getY() { return Helper.convertToCoordinateY(y); }

    /** @return x position on the grid (column number) */
    public int getPosX() { return x; }

    /** @return y position on the grid (row number) */
    public int getPosY() { return y; }

    /** @return current TerrainType of the tile */
    public TerrainType getType() { return type; }

    /** @param type terrain type of the tile (SOIL, ROCK, WATER) */
    public void setType(TerrainType type) { this.type = type; }


    /** EXCEPTION CASE FOR X */
    private void setPosX(int x)
    {
        if(x >= 0 && x < Constants.GRID_WIDTH)
            this.x = x;

        //else if (x > Constants.GRID_WIDTH)
        //    this.x = Constants.GRID_WIDTH - 1;
    }

    /** EXCEPTION CASE FOR Y */
    private void setPosY(int y)
    {
        if(y >= 0 && y < Constants.GRID_HEIGHT)
            this.y = y;

        //else if (y > Constants.GRID_HEIGHT)
        //    this.y = Constants.GRID_HEIGHT - 1;
    }


    /**
     * Checks if given entity coordinates are within tile area.
     * @param x first coordinate of Entity object
     * @param y second coordinate of Entity object
     * @return true, if entity is inside the tile area;
     *         false, otherwise
     */
    public boolean holdsEntityAt(double x, double y)
    {
        return holdsEntityAtX(x) && holdsEntityAtY(y);
    }

    /** x-axis version of {@link #holdsEntityAt(double, double)}. */
    public boolean holdsEntityAtX(double x)
    {
        return (x >= getX() && x < getX() + Tile.SIZE);
    }

    /** y-axis version of {@link #holdsEntityAt(double, double)}. */
    public boolean holdsEntityAtY(double y)
    {
        return (y >= getY() && y < getY() + Tile.SIZE);
    }

    /** Returns a string representation of Tile. */
    public String toString()
    {
        return "[" + getPosX() + "][" + getPosY() + "] / (" + getX() + ";" + getY() + ") " + type;
    }


    //Shared field
    public static final int SIZE = 8;

    //Fields
    private int x;
    private int y;
    private TerrainType type;
}
