package ecosystem.entities.animals;


import ecosystem.exceptions.InvalidArgumentException;

/**
 * <pre>
 * Combines Animal functionality and Predator behaviour.
 * Polymorphic behaviour base for predator animals.
 * </pre>
 */
public abstract class Predator extends Animal implements PredatorBehaviour
{
    /** See {@link Animal#Animal(double, double, int, double, double)}. */
    public Predator(double x, double y, int maxEnergyValue, double movementSpeed, double targetingRadius)
            throws InvalidArgumentException
    {
        super(x, y, maxEnergyValue, movementSpeed, targetingRadius);
    }
}
