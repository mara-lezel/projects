package ecosystem.helper;

import ecosystem.entities.Entity;
import ecosystem.grid.Tile;

import java.util.Random;

/** Class providing utility methods for ecosystem logic. */
public class Helper
{
    /** Returns distance between two entities. */
    public static double euclidianDistance(Entity e1, Entity e2)
    {
        double deltaX = e1.getX() - e2.getX();
        double deltaY = e1.getY() - e2.getY();

        return Math.sqrt(deltaX * deltaX + deltaY * deltaY);
    }

    /** Returns x coordinate value from given position. */
    public static double convertToCoordinateX(int positionX)
    {
        return Constants.GRID_OFFSET_BX + (positionX * Tile.SIZE);
    }

    /** Returns y coordinate value from given position. */
    public static double convertToCoordinateY(int positionY)
    {
        return Constants.GRID_OFFSET_BY + (positionY * Tile.SIZE);
    }

    /** Returns position on the grid from given x coordinate. */
    public static int convertToPositionX(double x)
    {
        int pos = (int)(x - Constants.GRID_OFFSET_BX) / Tile.SIZE;
        return pos >= 0 ? pos < Constants.GRID_WIDTH ? pos : Constants.GRID_WIDTH - 1 : 0;
    }

    /** Returns position on the grid from given y coordinate. */
    public static int convertToPositionY(double y)
    {
        int pos = (int)(y - Constants.GRID_OFFSET_BY) / Tile.SIZE;
        return pos >= 0 ? pos < Constants.GRID_HEIGHT ? pos : Constants.GRID_HEIGHT - 1 : 0;
    }

    /** Returns random number generator. */
    public static Random random = new Random();
}
