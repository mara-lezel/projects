
import java.sql.*;


public class Client
{
    public static void main(String[] args)
    {
        try
        {
            DatabaseClient dbc = new DatabaseClient();
            dbc.start();
        }

        catch (SQLException e)
        {
            System.err.println("Error: connection to database 'studentu' failed.");
            e.printStackTrace();
        }

        catch (ClassNotFoundException e)
        {
            System.err.println("Error: could not find driver class.");
            e.printStackTrace();
        }
    }
}
