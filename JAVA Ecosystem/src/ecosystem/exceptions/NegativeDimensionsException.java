package ecosystem.exceptions;

/** Exception class for objects which hold dimensions with negative values. */
public class NegativeDimensionsException extends SimulationException
{
    /** See {@link SimulationException#SimulationException(java.lang.String)}. */
    public NegativeDimensionsException(String msg, String objName, int width, int height)
    {
        super(msg);

        this.objName = objName;
        this.width = width;
        this.height = height;
    }

    public int getWidth() { return width; }
    public int getHeight() { return height; }
    public String getObjName() { return objName; }

    private int width;
    private int height;
    private String objName;
}
