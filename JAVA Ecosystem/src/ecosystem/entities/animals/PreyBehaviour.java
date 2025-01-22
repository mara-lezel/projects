package ecosystem.entities.animals;

import ecosystem.grid.EcosystemGrid;

import java.util.ArrayList;

/**
 * <pre>
 * Interface for shared prey behaviour within the ecosystem.
 * Different prey can evolve different methods for running away
 * or selecting their destination.
 * </pre>
 */
public interface PreyBehaviour extends AnimalBehaviour
{
    /** Returns increased movement speed.
     *  Running speed scales with animal's base speed. */
    default double getRunningSpeed(double baseSpeed) { return baseSpeed * 1.5; }

    /** Forces prey to run away from a predator, if predator is
     * within line of sight. While running away prey's movement
     * speed is increased. */
    void scatter(ArrayList<Predator> predators);

    /** Scans the area on the grid within animal targeting
     * radius and sets target to the closest spotted tile.
     *
     * If target food/prey is not found within sense radius,
     * a random tile on the grid is chosen as the target
     * location. */
    void selectTarget(EcosystemGrid grid);
}

//DELEGATION