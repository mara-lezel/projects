package ecosystem.entities.animals;


import ecosystem.exceptions.InvalidArgumentException;

/**
 * <pre>
 * Combines Animal functionality and Prey behaviour.
 * Polymorphic behaviour base for prey animals.
 * </pre>
 */
public abstract class Prey extends Animal implements PreyBehaviour
{
    /** See {@link Animal#Animal(double, double, int, double, double)}. */
    public Prey(double x, double y, int maxEnergyValue, double movementSpeed, double targetingRadius)
            throws InvalidArgumentException
    {
        super(x, y, maxEnergyValue, movementSpeed, targetingRadius);
    }

    /**
     * Changes animal status to fleeing - moving away from threat, ignoring
     * all other behaviour.
     * @param fleeing true if running away, false otherwise
     */
    public void setFleeing(boolean fleeing) { this.fleeing = fleeing; }

    /** Returns fleeing status. */
    public boolean isFleeing() { return fleeing; }

    //Fields
    private boolean fleeing;
}
