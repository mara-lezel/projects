package ecosystem.entities.animals;

import ecosystem.exceptions.InvalidArgumentException;

/**
 * <pre>
 * Animal object factory - animal den.
 * Produces any animal specified by AnimalClass.
 *
 * Handles exceptions related to bad initialization values
 * (non-positive values in fields that are final).
 * </pre>
 */
public class AnimalDen
{
    /** Contains all available animals in the simulation. */
    public enum AnimalClass
    {
        SHEEP,
        WOLF,
        RABBIT,
        WILDCAT
    }

    /**
     * Creates and returns specified animal class.
     * @param animalClass animal name enum --AnimalDen.AnimalClass
     * @return new animal object, derived from Animal
     */
    public static Animal getAnimal(int x, int y, AnimalClass animalClass)
    {
        Animal animal = null;

        try
        {
            switch (animalClass)
            {
                case SHEEP:
                    animal = new Sheep(x, y);
                    break;
                case WOLF:
                    animal = new Wolf(x, y);
                    break;
                case RABBIT:
                    animal = new Rabbit(x, y);
                    break;
                case WILDCAT:
                    animal = new Wildcat(x, y);
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

        return animal;
    }
}
