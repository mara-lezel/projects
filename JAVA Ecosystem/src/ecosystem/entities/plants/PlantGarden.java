package ecosystem.entities.plants;

import ecosystem.exceptions.InvalidArgumentException;

/**
 * <pre>
 * Plant object factory - plant garden.
 * Produces any plant specified by PlantClass.
 *
 * Handles exceptions related to bad initialization values
 * (non-positive values in fields that are final).
 * </pre>
 */
public class PlantGarden
{
    /** Contains all available plants in the simulation. */
    public enum PlantClass
    {
        GRASS,
        BLUEBERRY,
        MOSS,
        BEET,
        SUNFLOWER,
        ALYSSUM
    }

    /**
     * Creates and returns specified plant class.
     * @param plantClass plant name enum --PlantGarden.PlantClass
     * @return new plant object, derived from Plant
     */
    public static Plant getPlant(PlantClass plantClass)
    {
        Plant plant = null;

        try
        {
            switch (plantClass)
            {
                case GRASS:
                    plant = new Grass();
                    break;
                case BLUEBERRY:
                    plant = new Blueberry();
                    break;
                case MOSS:
                    plant = new Moss();
                    break;
                case BEET:
                    plant = new Beet();
                    break;
                case SUNFLOWER:
                    plant = new Sunflower();
                    break;
                case ALYSSUM:
                    plant = new Alyssum();
                    break;
                default:
                    break;
            }
        }

        catch (InvalidArgumentException e)
        {
            System.err.println("Error: " + e.getMessage() + " - trying to initialize " + e.getObjName() + " with "
                    + e.getVarName() + " value of " + e.getVar() + ".");
            e.printStackTrace();
        }

        return plant;
    }
}
