package ecosystem.entities.animals;

import java.util.ArrayList;


/**
 * <pre>
 * Interface for shared predator behaviour within the ecosystem.
 * Different predators can evolve different methods for attacking
 * opportunities or selecting their destination.
 * </pre>
 */
public interface PredatorBehaviour extends AnimalBehaviour
{
    /** Returns a radius at which animal can pounce.
     *  Pounce radius scales with animal's base targeting radius. */
    default double getPounceRadius(double baseRadius) { return baseRadius * 0.25; }

    /** Attempts to reach and consume prey in a single cycle.
     *  Pounce can only happen if animal is within pounce range.
     *  See {@link #getPounceRadius(double)}. */
    void pounce(ArrayList<Prey> prey);

    /** Scans the area on the grid within animal targeting
     * radius and sets target to the tile where prey animal
     * was last spotted.
     *
     * If target prey is not found within sense radius,
     * a random tile on the grid is chosen as the target
     * location. */
    void selectTarget(ArrayList<Prey> prey);
}
