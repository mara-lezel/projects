
import ecosystem.*;
import ecosystem.exceptions.NegativeDimensionsException;

/** Creates and starts ecosystem simulation.*/
public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Ecosystem simulation = new Ecosystem();
            simulation.start();
        }

        catch (NegativeDimensionsException e)
        {
            System.err.println("Error: " + e.getMessage() + " - trying to initialize " + e.getObjName() + " with " +
                    "impossible dimensions: width = " + e.getWidth() + ", height = " + e.getHeight() + ".");
            e.printStackTrace();
        }
    }
}


