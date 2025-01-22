package ecosystem.helper;

import ecosystem.grid.Tile;

public class Constants
{
    public static final int GRID_WIDTH = 64;
    public static final int GRID_HEIGHT = 86;

    /** Pixels before grid area (canvas) starts on x-axis.
     * Used in rendering methods. */
    public static final int GRID_OFFSET_BX = 270;

    /** Pixels before grid area (canvas) starts on y-axis.
     * Used in rendering methods. */
    public static final int GRID_OFFSET_BY = 10;

    /** Pixels after grid area (canvas) ends on x-axis.
     * Used in rendering methods. */
    public static final int GRID_OFFSET_AX = 10;

    /** Pixels after grid area (canvas) ends on y-axis.
     * Used in rendering methods. */
    public static final int GRID_OFFSET_AY = 10;

    /** Pixel value denoting the edge of the grid area (canvas) on x-axis.
     * Used in ecosystem logic methods.*/
    public static final int GRID_END_X = GRID_OFFSET_BX + GRID_WIDTH * Tile.SIZE;

    /** Pixel value denoting the edge of the grid area (canvas) on y-axis.
     * Used in ecosystem logic methods.*/
    public static final int GRID_END_Y = GRID_OFFSET_BY + GRID_HEIGHT * Tile.SIZE;

    public static final int SCREEN_WIDTH = GRID_OFFSET_BX + GRID_WIDTH * Tile.SIZE + GRID_OFFSET_AX;
    public static final int SCREEN_HEIGHT = GRID_OFFSET_BY + GRID_HEIGHT * Tile.SIZE + GRID_OFFSET_AY;
}
