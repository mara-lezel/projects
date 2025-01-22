import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class Util
{
    //Clear screen (non-windows)
    public static void clearScreen()
    {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    //Hotel Database Interface
    public static void displayInterface(String info)
    {
        Util.clearScreen();
        System.out.println("HOTEL RESERVATION SYSTEM\n");

        System.out.println(info + "\n");

        System.out.println("1 -- Reserve a Room");
        System.out.println("2 -- Make Changes to Reservation");
        System.out.println("  2.1 -- Change Room");
        System.out.println("  2.2 -- Change Arrival Date");
        System.out.println("  2.3 -- Change Departure Date");
        System.out.println("  2.4 -- Change Number of Occupants");
        System.out.println("3 -- Complete Payment");
        System.out.println("4 -- Cancel Reservation");
        System.out.println("\n5 -- Display Reservations");
        System.out.println("  5.1 -- Made by Guest");
        System.out.println("  5.2 -- Active During Specific Time Frame");
        System.out.println("  5.3 -- Active Now");
        System.out.println("6 -- Exit\n");
    }

    //Interface input
    public static String getInputOptions()
    {
        Scanner in = new Scanner(System.in);
        String action;

        while(true)
        {
            System.out.print("> ");
            action = in.nextLine();
            if(options.contains(action))
                break;
        }

        return action;
    }

    //User input - Date
    public static java.sql.Date getInputDate()
    {
        Scanner in = new Scanner(System.in);
        java.sql.Date date = null;

        try
        {
            String inputDate = in.nextLine();
            date = java.sql.Date.valueOf(inputDate);
        }

        catch (IllegalArgumentException e)
        {
            System.err.println("\nEntered value does not represent a valid date.\n");
        }

        return date;
    }


    //User input - int
    public static int getInputInt()
    {
        Scanner in = new Scanner(System.in);
        int input = -1;

        try
        {
            input = in.nextInt();
            in.nextLine();
        }

        catch (InputMismatchException e)
        {
            System.err.println("\nEntered value does not represent a valid number.\n");
        }

        return input;
    }


    //User input - String
    public static String getInputStr()
    {
        Scanner in = new Scanner(System.in);
        String input = "";

        try
        {
            input = in.nextLine();
        }

        catch (InputMismatchException e)
        {
            System.err.println("\nEntered value does not represent a string.\n");
        }

        return input;
    }


    /**
     * Displays table information.
     *
     * @param query query for the database
     * @param format display format
     */
    public static void displayTable(String query, int format, Connection con)
    {
        try
        {
            PreparedStatement statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();


            //Active
            if(format == 1)
            {
                System.out.printf("\n %-7s | %-15s | %-15s | %-4s | %-10s | %-10s \n",
                        "id", "name", "surname", "room", "arrival", "departure");
                System.out.print("---------+-----------------+-----------------+------+------------+------------\n");

                while(rs.next())
                    System.out.printf(" %d | %-15s | %-15s | %-4d | %tY-%<tm-%<td | %tY-%<tm-%<td \n",
                            rs.getInt("id"), rs.getString("name"),
                            rs.getString("surname"), rs.getShort("room"),
                            rs.getDate("arrival"), rs.getDate("departure"));

                System.out.print("------------------------------------------------------------------------------\n");
            }


            //Guest
            if(format == 2)
            {
                System.out.printf("\n %-6s | %-10s | %-10s | %-30s | %-15s | %-15s | %-10s \n",
                        "id", "name", "surname", "address", "city", "country", "birthdate");
                System.out.print("--------+------------+------------+--------------------------------+" +
                        "-----------------+-----------------+------------\n");

                while(rs.next())
                    System.out.printf(" %d | %-10s | %-10s | %-30s | %-15s | %-15s | %tY-%<tm-%<td\n",
                            rs.getInt("id"), rs.getString("name"),
                            rs.getString("surname"), rs.getString("address"),
                            rs.getString("city"), rs.getString("country"),
                            rs.getDate("birthdate"));

                System.out.print("--------------------------------------------------------------------" +
                        "------------------------------------------------\n");
            }


            //Payment
            if(format == 3)
            {
                System.out.printf("\n %-11s | %-6s | %-10s | %-15s \n",
                        "reservation", "amount", "completed", "method");
                System.out.print("-------------+--------+------------+-----------------\n");

                while(rs.next())
                    System.out.printf(" %-11d | %-4.0f € |            |  \n",
                            rs.getInt("reservation"), rs.getBigDecimal("amount"));

                System.out.print("-----------------------------------------------------\n");
            }


            //Reservation
            if(format == 4)
            {
                System.out.printf("\n %-7s | %-10s | %-10s | %-10s | %-4s | %-6s | %-6s | %-8s | %-10s\n",
                        "id", "resdate", "arrival", "departure", "room", "guest", "adults", "children", "cancelled");
                System.out.print("---------+------------+------------+------------+------+--------+--------+" +
                        "----------+------------\n");

                while(rs.next())
                {
                    System.out.printf(" %d | %tY-%<tm-%<td | %tY-%<tm-%<td | %tY-%<tm-%<td | %-4d | %-6d | %-6d | %-8d |",
                            rs.getInt("id"), rs.getDate("reservationdate"),
                            rs.getDate("arrival"), rs.getDate("departure"),
                            rs.getShort("room"), rs.getInt("guest"),
                            rs.getInt("adults"), rs.getInt("children"));

                    if(rs.getDate("cancelled") != null)
                        System.out.printf(" %tY-%<tm-%<td \n", rs.getDate("cancelled"));
                    else
                        System.out.println();
                }

                System.out.print("--------------------------------------------------------------------------" +
                        "-----------------------\n");
            }

            //Room Type
            if(format == 5)
            {
                System.out.printf("\n %-4s | %-18s | %-8s | %-4s | price per night \n",
                        "id", "title", "capacity", "beds");
                System.out.print("------+--------------------+----------+------+-----------------\n");

                while(rs.next())
                    System.out.printf(" %d | %-18s | %-8d | %-4d | %-3d €\n",
                            rs.getInt("id"), rs.getString("title"),
                            rs.getInt("capacity"), rs.getInt("beds"),
                            rs.getInt("pricepernight"));

                System.out.print("---------------------------------------------------------------\n");
            }

            statement.close();
            rs.close();
        }

        catch (SQLException e)
        {
            System.err.println("Column not found -- something went wrong.");
        }
    }


    //Fields
    public static List<String> options = new ArrayList<>
            (Arrays.asList("1", "2", "2.1", "2.2", "2.3", "2.4", "3", "4", "5", "5.1", "5.2", "5.3", "6"));
}
