package ecosystem.entities;

import java.awt.Color;

/**
 * <pre>
 * Interface for drawable entities in the simulation.
 * Entities are represented by:
 * - colour (RGB value)
 * - width (pixel value to draw on the screen)
 * - height (pixel value to draw on the screen)
 * - additional colour (for entity associated actions, RGB value)
 * </pre>
 */
public interface Drawable
{
    /** Returns the colour value of the object on the screen. */
    Color getColor();

    /** Returns the colour for object associated actions. */
    Color getAdditionalColor();

    /** Returns width of the object on the screen. */
    int getDrawWidth();

    /** Returns height of the object on the screen. */
    int getDrawHeight();
}
