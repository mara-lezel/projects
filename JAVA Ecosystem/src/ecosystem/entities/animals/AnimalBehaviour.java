package ecosystem.entities.animals;

/**
 * Interface for shared animal behaviour within the ecosystem.
 *
 * Movement can have speed and direction variations.
 */
public interface AnimalBehaviour
{
    /** Method for moving around the grid. */
    void move();
}