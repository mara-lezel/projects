package ecosystem.exceptions;

/** Custom exception class for simulation related errors. */
public class SimulationException extends Exception
{
    /**
     * Constructs a new exception with specified message.
     * @param msg message about detected error in the simulation
     */
    public SimulationException(String msg)
    {
        super(msg);
    }
}
