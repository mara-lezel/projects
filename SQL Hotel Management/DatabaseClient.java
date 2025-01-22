
import java.math.BigDecimal;
import java.sql.*;
import java.sql.Date;
import java.util.*;

//SEARCH -- 5, 5.1 AND 5.2
//INSERT -- 1
//UPDATE -- 2
//DELETE -- 4

//RELATED TABLES - 2.1
//SHOW ID BEFORE INPUT -- 2
//TRANSACTION -- 2
//INJECTION -- 1

public class DatabaseClient
{
    DatabaseClient() throws ClassNotFoundException, SQLException
    {
        Class.forName("org.postgresql.Driver");

        con = DriverManager.getConnection
                ("jdbc:postgresql://pgsql2.mif/studentu", "mara4380", "ladeeDA02") ;

        methods = new ArrayList<>
                (Arrays.asList("Cash", "Credit Card", "Debit Card", "Mobile Wallet", "Virtual Payment"));
    }

    //Main loop
    public void start()
    {
        boolean running = true;
        String info = "";

        while(running)
        {
            Util.displayInterface(info);

            String action = Util.getInputOptions();

            switch(action)
            {
                case "1":
                    info = createReservation();
                    break;
                case "2":
                    info = changeReservation("all");
                    break;
                case "2.1":
                    info = changeReservation("room");
                    break;
                case "2.2":
                    info = changeReservation("arrival");
                    break;
                case "2.3":
                    info = changeReservation("departure");
                    break;
                case "2.4":
                    info = changeReservation("adults");
                    break;
                case "3":
                    info = createPayment();
                    break;
                case "4":
                    info = cancelReservation();
                    break;
                case "5":
                    info = viewAll();
                    break;
                case "5.1":
                    info = viewMadeByGuest();
                    break;
                case "5.2":
                    info = viewTimeFrame();
                    break;
                case "5.3":
                    info = viewActive();
                    break;
                case "6":
                    running = false;
                    break;
                default:
                    break;
            }
        }

        close();
    }

    //Close connection
    private void close()
    {
        try
        {
            con.close();
        }
        catch (SQLException e)
        {
             e.printStackTrace();
        }
    }


    //----------------------------------------------------  1  ---------------------------------------------------------

    /**
     * Creates a reservation, together with new guest data (optional)
     * and allows payment completion (optional).
     *
     * @return reservation and payment completion details
     */
    private String createReservation()
    {
        String info = "";
        int guestId = -1;
        int resId = -1;

        String inputs;

        Util.clearScreen();
        System.out.println("ROOM RESERVATION\n");

        System.out.print("First time guest (y/n): ");
        inputs = Util.getInputStr();

        if(inputs.equals("y"))
        {
            String result = registerGuest();

            if(!result.startsWith("4"))
                return result;

            guestId = Integer.parseInt(result);
        }
        else
        {
            Util.displayTable("SELECT * FROM Guest ORDER BY 1", 2, con);

            System.out.print("Make reservation as (ID): ");

            guestId = Util.getInputInt();

            System.out.println();
        }

        String result = reserveRoom(guestId);
        if(!result.startsWith("1"))
            return result;
        else
        {
            info = "Reservation was successfully completed!";
            resId = Integer.parseInt(result);
        }


        System.out.print("\nMake payment now (y/n): ");
        inputs = Util.getInputStr();

        if(inputs.equals("y"))
        {
            result = completePayment(resId);
            info += result;
        }

        return info;
    }


    /**
     * Adds guest data to hotel database.
     * 
     * @return guest id if operation was successful,
     *         error string otherwise
     */
    private String registerGuest()
    {
        String info = "";
        String name, surname, address, city, country, birthdate;
        
        System.out.print("Name: ");
        name = Util.getInputStr();

        System.out.print("Surname: ");
        surname = Util.getInputStr();

        System.out.print("Street address: ");
        address = Util.getInputStr();

        System.out.print("City: ");
        city = Util.getInputStr();

        System.out.print("Country: ");
        country = Util.getInputStr();

        System.out.print("Date of birth: ");
        birthdate = Util.getInputStr();

        try
        {
            String query = "INSERT INTO guest(name, surname, address, city, country, birthdate) " +
                    "VALUES(?, ?, ?, ?, ?, ?)";
            PreparedStatement statement = con.prepareStatement(query);
            
            statement.setString(1, name);
            statement.setString(2, surname);
            statement.setString(3, address);
            statement.setString(4, city);
            statement.setString(5, country);
            statement.setDate(6, java.sql.Date.valueOf(birthdate));
            statement.executeUpdate();

            statement.close();
        }

        catch (SQLException e)
        {
            info = "Guest could not be registered -- check guest information:\n" +
                    "  -- People under the age of 18 cannot be registered as guests\n" +
                    "  -- All other information should not exceed 30 letter limit";

            return info;
        }
        

        try
        {
            String query = "SELECT * FROM guest where name = '" + name + "' and surname = '" +
                    surname + "' and address = '" + address + "'";
            PreparedStatement statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();

            while(rs.next())
            {
                System.out.println("\nGUEST REGISTRATION INFO\n");

                System.out.println("GUEST ID: " + rs.getInt(1));
                System.out.println("Name: " + rs.getString(2));
                System.out.println("Surname: " + rs.getString(3));
                System.out.println("Birthdate: " + rs.getDate(7));
                System.out.println("Address: " + rs.getString(4));
                System.out.println("City: " + rs.getString(5));
                System.out.println("Country: " + rs.getString(6));

                System.out.println();

                info = "" + rs.getInt(1);
            }

            statement.close();
            rs.close();
        }

        catch (SQLException e)
        {
            info = "Guest registration info could not be displayed -- something went wrong.";

            return info;
        }
        
        return info;
    }


    /**
     * Adds reservation to hotel database.
     *
     * @param guestId guest who is making the reservation
     * @return reservation id string if operation successful,
     *         error string otherwise
     */
    private String reserveRoom(int guestId)
    {
        String info = "";
        int type = -1;

        try
        {
            java.sql.Date arrival = null;
            java.sql.Date departure = null;
            int room = -1;
            int adults = -1;
            int children = -1;

            System.out.print("Arrival date: ");
            arrival = Util.getInputDate();

            System.out.print("Departure date: ");
            departure = Util.getInputDate();

            
            Util.displayTable("SELECT DISTINCT id, title, capacity, beds, pricepernight " +
                    "FROM room, roomtype " +
                    "WHERE type = id AND " +
                    "nr NOT IN " +
                    "(SELECT room FROM reservation " +
                    "WHERE arrival <= '" + arrival + "' AND departure >= '" + departure + "') " +
                    "ORDER BY 5", 5, con);

            System.out.print("Preferred room type (ID): ");
            type = Util.getInputInt();


            //List of available rooms of selected type
            String query = "WITH " +
                    "available(nr, id, title, capacity, beds, pripernight) AS " +
                    "(SELECT distinct nr, id, title, capacity, beds, pricepernight " +
                    "FROM room, roomtype " +
                    "WHERE type = id AND " +
                    "nr NOT IN " +
                    "(SELECT room FROM reservation " +
                    "WHERE arrival >= '" + arrival + "' AND arrival <= '" + departure + "' " +
                    " OR departure >= '" + arrival + "' AND departure <= '" + departure + "') " +
                    "ORDER BY 5) " +
                    "SELECT room.nr FROM room, available " +
                    "WHERE room.nr = available.nr AND type = available.id AND id = " + type;

            PreparedStatement statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();
            rs.next();

            
            room = rs.getShort("nr");
            if(room == 0)
            {
                info = "There are no rooms available for selected time frame.\n";
                return info;
            }
            
            System.out.print("Number of adults: ");
            adults = Util.getInputInt();

            System.out.print("Number of children: ");
            children = Util.getInputInt();


            query = "INSERT INTO Reservation(ReservationDate, Arrival, Departure, Room, Guest, Adults, " +
                    "Children, Cancelled)" + " VALUES(CURRENT_DATE, ?, ?, ?, ?, ?, ?, null)";
            statement = con.prepareStatement(query);

            statement.setDate(1, arrival);
            statement.setDate(2, departure);
            statement.setShort(3, (short)room);
            statement.setInt(4, guestId);
            statement.setInt(5, adults);
            statement.setInt(6, children);
            statement.executeUpdate();

            query = "SELECT id FROM reservation WHERE arrival = '" +
                    arrival + "' and room = " + room + " and cancelled is null";

            PreparedStatement st = con.prepareStatement(query);
            ResultSet r = st.executeQuery();
            r.next();

            System.out.println("\nRESERVATION ID " + r.getInt(1));

            info += "" + r.getInt(1);
        }

        catch (SQLException e)
        {
            info = "Reservation could be not be completed -- display reservations for more info:\n" +
                    "  -- Entered arrival and departure dates might be conflicting\n" +
                    "  -- Selected room might be occupied during selected times\n" +
                    "  -- Selected room might not be suitable for the number of people entered";

            return info;
        }

        return info;
    }


    /**
     * Completes payment for specified reservation.
     *
     * @param resId reservation id associated with payment
     * @return payment information if operation successful,
     *         error string otherwise
     */
    private String completePayment(int resId)
    {
        String info = "";
        
        String inputs;
        int inputd;

        String method = "";

        try
        {
            System.out.print("\nRe-enter reservation id on screen: ");
            
            inputd = Util.getInputInt();
            
            if(inputd != resId)
            {
                info += "\nPayment could not be successfully completed -- entered guest id is invalid.";
                return info;
            }


            String query = "SELECT room, nights, totalcost FROM details WHERE id = " + resId;
            PreparedStatement statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();

            rs.next();

            System.out.println("\nReservation ID " + resId);
            System.out.println("Room: " + rs.getShort(1));
            System.out.println("Nights: " + rs.getInt(2));
            System.out.println("Price per night: " +
                    rs.getBigDecimal(3).divide(BigDecimal.valueOf(rs.getInt(2))) + "€");
            System.out.println("Total: " + rs.getBigDecimal(3) + "€");

            BigDecimal amount = rs.getBigDecimal(3);
            

            System.out.print("\nEnter amount to be paid on screen: ");
            inputs = Util.getInputStr();

            if(!inputs.equals(amount.toString()))
            {
                info += "\nPayment could not be successfully completed -- payment amounts do not match.";
                return info;
            }

            System.out.println("Accepted payment methods: Credit Card, Debit Card, Mobile Wallet, Virtual Payment");
            System.out.print("Payment method: ");
            method = Util.getInputStr();

            if(!methods.contains(method))
            {
                info = "\nPayment could not be successfully completed -- chosen payment method is not accepted.";
                return info;
            }
        }

        catch (SQLException e)
        {
            info = "\nCould not find payment details tied to reservation ID " + resId;

            return info;
        }


        try
        {
            String query = "UPDATE payment SET completed = CURRENT_DATE, method = '" +
                    method + "' WHERE reservation = " + resId;

            PreparedStatement statement = con.prepareStatement(query);
            statement.executeUpdate();

            query = "SELECT * FROM payment WHERE reservation = " + resId;
            statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();
            rs.next();

            info += "\nPayment was successfully completed!\n";

            info += "\nPayment ID: " + rs.getInt(1);
            info += "\nAmount: " + rs.getBigDecimal(2) + " €";
            info += "\nCompleted on: " + rs.getDate(3);
            info += "\nMethod: " + rs.getString(4) + "\n";
        }

        catch (SQLException e)
        {
            info += "\nCould not successfully complete payment -- unexpected error:" +
                    "  -- Reservation might have been cancelled";
            
            return info;
        }

        return info;
    }


    //----------------------------------------------------  2  ---------------------------------------------------------


    /**
     * Updates reservation details in the database.
     *
     * @return update details
     */
    private String changeReservation(String column)
    {
        Util.clearScreen();
        System.out.println("CHANGE RESERVATION DETAILS\n");

        String info = "";

        int resId = -1;


        Util.displayTable("SELECT * FROM reservation order by 1", 4, con);

        System.out.print("\nMake changes to reservation (ID): ");
        resId = Util.getInputInt();

        switch (column)
        {
            case "arrival":
                info += changeArrival(resId) + "\n";
                break;
            case "departure":
                info += changeDeparture(resId) + "\n";
                break;
            case "adults":
                info += changeOccupants(resId) + "\n";
                break;
            case "room":
                info += changeRoom(resId) + "\n";
                break;
            default:
                info += changeArrival(resId) + "\n";
                info += changeDeparture(resId) + "\n";
                info += changeOccupants(resId) + "\n";
                info += changeRoom(resId) + "\n";
                break;
        }

        return info;
    }

    //---------------------------------------------------  2.1  --------------------------------------------------------

    /**
     * Updates reservation data with new room, renews payment information
     *
     * @param resId specified reservation id
     * @return room and payment update details
     */
    private String changeRoom(int resId)
    {
        String info = "";
        String inputs;

        int type = -1;
        short room = -1;

        Date arrival = null;
        Date departure = null;

        try
        {
            String query = "SELECT * FROM reservation WHERE id = " + resId;
            PreparedStatement statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();

            rs.next();

            System.out.println("\nCURRENTLY ASSIGNED ROOM\nNr: " + rs.getShort("room"));

            query = "SELECT title, capacity, beds, pricepernight FROM room, roomtype " +
                    "WHERE type = id and nr = " + rs.getShort("room");
            statement = con.prepareStatement(query);
            rs = statement.executeQuery();
            rs.next();

            System.out.println("Title: " + rs.getString("title"));
            System.out.println("Capacity: " + rs.getInt("capacity"));
            System.out.println("Beds: " + rs.getInt("beds"));
            System.out.println("Price per night: " + rs.getBigDecimal("pricepernight"));
            System.out.println();


            System.out.print("Make changes to room (y/n): ");

            inputs = Util.getInputStr();
            if(inputs.equals("y"))
            {
                query = "SELECT arrival, departure FROM reservation " +
                        "WHERE id = " + resId;
                statement = con.prepareStatement(query);
                rs = statement.executeQuery();
                rs.next();

                arrival = rs.getDate("arrival");
                departure = rs.getDate("departure");


                Util.displayTable("SELECT distinct id, title, capacity, beds, pricepernight " +
                        "FROM room, roomtype " +
                        "WHERE type = id AND " +
                        "nr NOT IN " +
                        "(SELECT room FROM reservation " +
                        "WHERE arrival <= '" + arrival + "' AND departure >= '" + departure + "') " +
                        "ORDER BY 5", 5, con);

                System.out.print("Preferred room type (ID): ");
                type = Util.getInputInt();


                query = "WITH " +
                        "available(nr, id, title, capacity, beds, pripernight) AS " +
                        "(SELECT distinct nr, id, title, capacity, beds, pricepernight " +
                        "FROM room, roomtype " +
                        "WHERE type = id AND " +
                        "nr NOT IN " +
                        "(SELECT room FROM reservation " +
                        " WHERE arrival >= '" + arrival + "' AND arrival <= '" + departure + "' " +
                        " OR departure >= '" + arrival + "' AND departure <= '" + departure + "') " +
                        "ORDER BY 5) " +
                        "SELECT room.nr FROM room, available " +
                        "WHERE room.nr = available.nr AND type = available.id AND id = " + type;

                statement = con.prepareStatement(query);
                rs = statement.executeQuery();
                rs.next();

                room = rs.getShort("nr");

                if(room == 0)
                {
                    info = "There are no rooms available for selected time frame.\n";
                    return info;
                }

                con.setAutoCommit(false);

                statement = con.prepareStatement("UPDATE reservation SET room = " + room + " WHERE id = " + resId);
                statement.executeUpdate();

                statement = con.prepareStatement("UPDATE payment SET completed = null, method = null, " +
                        "amount = (SELECT totalcost FROM details WHERE id = " + resId + ") " +
                        "WHERE reservation = " + resId);
                statement.executeUpdate();

                con.commit();

                info = "Room details changed -- payment information renewed for reservation id " + resId;
            }
            else
            {
                return "Room details unchanged.";
            }

        }

        catch (SQLException e)
        {
            try
            {
                info = "Room details could not be changed -- reservation is closed or active.";

                con.rollback();
            }
            catch (SQLException ex)
            {
                info = "Room details could not be changed -- failed to update payment information.";
            }
        }

        finally
        {
            try
            {
                con.setAutoCommit(true);
            }
            catch (SQLException e)
            {
                info += "\nAn unexpected error occurred -- check reservation list.";
            }
        }

        return info;
    }

    //---------------------------------------------------  2.2  --------------------------------------------------------

    /**
     * Updates reservation data with new arrival date, renews payment information
     *
     * @param resId specified reservation id
     * @return arrival and payment update details
     */
    private String changeArrival(int resId)
    {
        String info = "";

        String inputs;
        Date arrival = null;

        try
        {
            String query = "SELECT * FROM reservation WHERE id = " + resId;
            PreparedStatement statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();

            rs.next();

            System.out.println("\nCurrent arrival date: " + rs.getDate("arrival"));
            System.out.print("\nMake changes to arrival date (y/n): ");

            inputs = Util.getInputStr();
            if(inputs.equals("y"))
            {
                System.out.print("Preferred new arrival date: ");
                arrival = Util.getInputDate();

                con.setAutoCommit(false);

                statement = con.prepareStatement("UPDATE reservation SET arrival = '" + arrival +
                        "' WHERE id = " + resId);
                statement.executeUpdate();

                statement = con.prepareStatement("UPDATE payment SET completed = null, method = null, " +
                        "amount = (SELECT totalcost FROM details WHERE id = " + resId + ") " +
                        "WHERE reservation = " + resId);
                statement.executeUpdate();

                con.commit();

                info = "Arrival date changed -- payment information renewed for reservation id " + resId;
            }

            else
                return "Arrival date unchanged.";
        }

        catch (SQLException e)
        {
            try
            {
                info = "Arrival date could not be changed:\n" +
                        "  -- Same room might be occupied at newly selected arrival date\n" +
                        "  -- New arrival date might conflict with reservation date\n";

                con.rollback();
            }
            catch (SQLException ex)
            {
                info = "Arrival date could not be changed -- failed to update payment information.";
            }
        }

        finally
        {
            try
            {
                con.setAutoCommit(true);
            }
            catch (SQLException e)
            {
                info += "\nAn unexpected error occurred -- check reservation list.";
            }
        }

        return info;
    }

    //---------------------------------------------------  2.3  --------------------------------------------------------

    /**
     * Updates reservation data with new departure date, renews payment information
     *
     * @param resId specified reservation id
     * @return departure and payment update details
     */
    private String changeDeparture(int resId)
    {
        String info = "";

        String inputs;
        Date departure = null;

        try
        {
            String query = "SELECT * FROM reservation WHERE id = " + resId;
            PreparedStatement statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();

            rs.next();

            System.out.println("\nCurrent departure date: " + rs.getDate("departure"));
            System.out.print("\nMake changes to departure date (y/n): ");

            inputs = Util.getInputStr();
            if(inputs.equals("y"))
            {
                System.out.print("Preferred new departure date: ");
                departure = Util.getInputDate();

                con.setAutoCommit(false);

                statement = con.prepareStatement("UPDATE reservation SET departure = '" + departure +
                        "' WHERE id = " + resId);
                statement.executeUpdate();

                statement = con.prepareStatement("UPDATE payment SET completed = null, method = null, " +
                        "amount = (SELECT totalcost FROM details WHERE id = " + resId + ") " +
                        "WHERE reservation = " + resId);
                statement.executeUpdate();

                con.commit();

                info = "Departure date changed -- payment information renewed for reservation id " + resId;
            }

            else
                return "Departure date unchanged.";
        }

        catch (SQLException e)
        {
            try
            {
                info = "Departure date could not be changed:\n" +
                        "  -- Same room might be occupied at newly selected departure date\n" +
                        "  -- New departure date might conflict with reservation date\n";

                con.rollback();
            }
            catch (SQLException ex)
            {
                info = "Departure date could not be changed -- failed to update payment information.";
            }
        }

        finally
        {
            try
            {
                con.setAutoCommit(true);
            }
            catch (SQLException e)
            {
                info += "\nAn unexpected error occurred -- check reservation list.";

            }
        }

        return info;
    }

    //---------------------------------------------------  2.4  --------------------------------------------------------

    /**
     * Updates reservation data with new number of adults and children
     *
     * @param resId specified reservation id
     * @return update details
     */
    private String changeOccupants(int resId)
    {
        String info = "";

        String inputs;

        int adults = -1;
        int children = -1;

        int oldAdults = -1;
        int oldChildren = -1;

        try
        {
            String query = "SELECT * FROM reservation WHERE id = " + resId;
            PreparedStatement statement = con.prepareStatement(query);
            ResultSet rs = statement.executeQuery();

            rs.next();

            oldAdults = rs.getInt("adults");
            oldChildren = rs.getInt("children");

            System.out.println("\nCurrent number of adults: " + rs.getInt("adults"));
            System.out.println("Current number of children: " + rs.getInt("children") + "\n");
            System.out.print("\nMake changes to number of occupants (y/n): ");

            inputs = Util.getInputStr();
            if(inputs.equals("y"))
            {
                statement = con.prepareStatement("SELECT nr, capacity FROM reservation, room, roomtype " +
                        "WHERE reservation.id = " + resId + " and room = room.nr and type = roomtype.id");
                rs = statement.executeQuery();

                rs.next();

                System.out.println("\nCurrent room nr. " + rs.getShort("nr") + " can accommodate up to " +
                        rs.getInt("capacity") + " people.\n");


                System.out.print("Updated number of adults: ");
                adults = Util.getInputInt();

                System.out.print("Updated number of children: ");
                children = Util.getInputInt();


                statement = con.prepareStatement("UPDATE reservation SET adults = " + adults +
                        ", children = " + children + " WHERE id = " + resId);
                statement.executeUpdate();

                info = "Number of occupants changed successfully!\n" +
                        "Adults " + oldAdults + " --> " + adults + "\n" +
                        "Children " + oldChildren + " --> " + children + "\n";
            }

            else
                return "Number of occupants unchanged.";
        }

        catch (SQLException e)
        {
            info = "Number of occupants could not be changed -- room cannot accommodate "
                    + (adults + children) + " people";
        }

        return info;
    }

    //----------------------------------------------------  3  ---------------------------------------------------------

    /**
     * Completes payment for specified reservation -- called from interface.
     *
     * @return payment completion details
     */
    private String createPayment()
    {
        int resId;

        Util.clearScreen();
        System.out.println("COMPLETE PAYMENT\n\n");

        Util.displayTable("SELECT * FROM payment WHERE completed is null order by 1", 3, con);

        System.out.print("Complete payment for reservation (ID): ");
        resId = Util.getInputInt();

        return completePayment(resId);
    }


    //----------------------------------------------------  4  ---------------------------------------------------------

    /**
     * Cancels any reservation specified by reservation id.
     *
     * @return cancellation details
     */
    private String cancelReservation()
    {
        Util.clearScreen();
        System.out.println("CANCEL RESERVATION\n");

        String info = "";
        String query = "DELETE FROM Reservation WHERE id = ?";

        int id = -1;

        try
        {
            Util.displayTable("SELECT * FROM reservation ORDER BY 1", 4, con);

            System.out.print("Cancel reservation (ID): ");
            id = Util.getInputInt();

            PreparedStatement statement = con.prepareStatement(query);
            statement.setInt(1, id);
            statement.executeUpdate();

            info = "Reservation was cancelled.";
        }

        catch (SQLException e)
        {
            info = "Reservation could be not be cancelled -- reservation id is invalid";
        }

        return info;
    }

    //----------------------------------------------------  5  ---------------------------------------------------------

    /**
     * Displays current reservation data as long as there is no user input.
     *
     * @return view details
     */
    private String viewAll()
    {
        Util.displayTable("SELECT * FROM reservation ORDER BY 1", 4, con);

        System.out.print("> Go back");
        Util.getInputStr();

        return "Reservation view closed.";
    }


    /**
     * Displays reservation data made by a specific guest as long as there is no
     * user input.
     *
     * @return view details
     */
    private String viewMadeByGuest()
    {
        Util.clearScreen();
        System.out.println("VIEW RESERVATIONS MADE BY GUEST\n");

        Util.displayTable("SELECT * FROM GUEST ORDER BY 1", 2, con);
        
        System.out.print("View reservations made by (ID): ");
        int guestId = Util.getInputInt();

        String query = "SELECT * FROM Reservation WHERE guest = " + guestId + " ORDER BY 1";
        Util.displayTable(query, 4, con);

        System.out.print("> Go back");
        Util.getInputStr();

        return "Reservation view closed.";
    }


    /**
     * Displays reservation data made in a specific time frame as long as there is no
     * user input.
     *
     * @return view details
     */
    private String viewTimeFrame()
    {
        Util.clearScreen();
        System.out.println("VIEW ACTIVE RESERVATIONS BETWEEN\n");

        java.sql.Date arrival = null;
        java.sql.Date departure = null;

        System.out.print("Active from: ");
        arrival = Util.getInputDate();

        System.out.print("Active until: ");
        departure = Util.getInputDate();


        String query = "SELECT * FROM Reservation WHERE arrival >= " +
                "'" + arrival + "'" + " AND arrival  <= '" +  departure + "' " +
                "OR departure >= '" + arrival + "' AND departure <= '" + departure + "' ORDER BY 1";

        Util.displayTable(query, 4, con);

        System.out.print("> Go back");
        Util.getInputStr();

        return "Reservation view closed.";
    }

    /**
     * Displays currently active reservation data as long as there is no user input.
     *
     * @return view details
     */
    private String viewActive()
    {
        System.out.println("VIEW CURRENTLY ACTIVE RESERVATIONS\n");

        String query = "SELECT * FROM active";

        Util.displayTable(query, 1, con);

        System.out.print("> Go back");
        Util.getInputStr();

        return "Reservation view closed.";
    }


    //Fields
    Connection con;
    List<String> methods;
}
