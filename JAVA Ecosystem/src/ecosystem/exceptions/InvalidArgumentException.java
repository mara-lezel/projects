package ecosystem.exceptions;

/** Exception class for invalid values within the ecosystem. */
public class InvalidArgumentException extends SimulationException
{
    /** See {@link SimulationException#SimulationException(java.lang.String)}. */
    public InvalidArgumentException(String msg, String objName, String varName, int var)
    {
        super(msg);

        this.objName = objName;
        this.varName = varName;
        this.var = var;
    }

    public int getVar() { return var; }
    public String getVarName() { return varName; }
    public String getObjName() { return objName; }

    private final String varName;
    private final String objName;
    private final int var;
}
