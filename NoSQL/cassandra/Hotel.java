
import com.datastax.driver.core.*;

import java.util.Date;
import java.util.Scanner;

import java.time.LocalDate;

public class Hotel
{

    public static void main(String[] args)
    {
        CassandraConnector client = new CassandraConnector();
        client.connect("127.0.0.1", 9042);

        boolean running = true;
        ResultSet rs;
        int input;
        Scanner sc = new Scanner(System.in);



        while(running)
        {
            System.out.println("\nConnected to Hotel Reservations System.\n");
            System.out.println("1. Display reservations");
            System.out.println("2. Display guest list");
            System.out.println("3. Display room type information");
            System.out.println("4. Display room list");

            System.out.println("\n5. Search/filter reservations");
            System.out.println("6. Update arrival dates");
            System.out.println("\n0. Exit");

            System.out.print(">> ");

            input = sc.nextInt();
            sc.nextLine();

            switch (input)
            {
                case 1:
                    rs = client.getSession().execute("select * from hotel.reservations;");
                    showReservations(rs);

                    System.out.print("\n>> ");
                    sc.nextLine();
                    break;
                case 2:
                    rs = client.getSession().execute("select * from hotel.guests;");
                    showGuests(rs);

                    System.out.print("\n>> ");
                    sc.nextLine();
                    break;
                case 3:
                    rs = client.getSession().execute("select * from hotel.roomtypes;");
                    showTypes(rs);

                    System.out.print("\n>> ");
                    sc.nextLine();
                    break;
                case 4:
                    rs = client.getSession().execute("select * from hotel.rooms;");
                    showRooms(rs);

                    System.out.print("\n>> ");
                    sc.nextLine();
                    break;
                case 5:
                    System.out.println("1. Search for reservations by guest_id");
                    System.out.println("2. Search for reservations by arrival date");

                    System.out.print("\n>> ");

                    int inp = sc.nextInt();
                    sc.nextLine();

                    if(inp == 1)
                    {
                        rs = client.getSession().execute("select * from hotel.guests;");
                        showGuests(rs);

                        System.out.print("\nSearch by guest last name: ");
                        String surname = sc.nextLine();

                        rs = client.getSession().execute(
                                "select id,name from hotel.guests where surname='" + surname + "';");

                        Row r = rs.one();
                        int id = r.getInt(0);
                        String name = r.getString(1);

                        System.out.println("\nReservations made by " + name + " " + surname);
                        rs = client.getSession().execute(
                                "select * from hotel.reservations where guest_id=" + id + ";");

                        showReservations(rs);

                        System.out.print("\n>> ");
                        sc.nextLine();
                    }
                    else if (inp == 2)
                    {
                        System.out.print("Search by arrival date: ");
                        String date = sc.nextLine();

                        rs = client.getSession().execute(
                                "select * from hotel.reservations where arrival='" + date + "';");

                        showReservations(rs);

                        System.out.print("\n>> ");
                        sc.nextLine();
                    }

                    break;
                case 6:

                    String currentDate = LocalDate.now().toString();

                    rs = client.getSession().execute("select * from hotel.reservations;");
                    showReservations(rs);

                    System.out.print("Make changes to reservation id: ");
                    int id = sc.nextInt();
                    sc.nextLine();

                    rs = client.getSession().execute("select arrival from hotel.reservations where id=" + id + ";");
                    String date = rs.one().getDate(0).toString();

                    System.out.println(date);
                    System.out.println(currentDate);


                    if(currentDate.compareTo(date) >= 0)
                    {
                        System.out.println("Cannot change arrival date after the fact.");
                    }
                    else
                    {
                        System.out.print("Change arrival time from " + date + " to: ");
                        String newDate = sc.nextLine();



                        rs = client.getSession().execute(
                                "update hotel.reservations" +
                                        "set arrival = '" + newDate + "' where id=" + id +
                                        " if departure > '" + newDate + "';");

                        //update reservations set arrival='2022-11-25' where id=100100 if departure>'2022-11-25';

                        System.out.println("Arrival date changed from " + date + " to " + newDate);
                    }
                    
                    break;
                case 0:
                    running = false;
                    break;
            }

        }

        client.close();
    }

    public static void showRooms(ResultSet rs)
    {
        System.out.printf("\n  %-2s | %8s %5s \n",
                rs.getColumnDefinitions().getName(0), rs.getColumnDefinitions().getName(1), "");

        System.out.println("-----+----------------");
        for(Row row  : rs)
        {
            short id = row.getShort(0);
            String type = row.getString(1);

            System.out.printf("  %-2d | %14s \n", id, type);
            //System.out.println("+----+---------------+");
        }
    }

    public static void showGuests(ResultSet rs)
    {

        System.out.println("    id   |        address        |  country  |   name   |  surname   ");
        System.out.println("---------+-----------------------+-----------+----------+------------");
        for(Row row  : rs)
        {
            int id = row.getInt(0);
            String address = row.getString(1);
            String country = row.getString(2);
            String name = row.getString(3);
            String surname = row.getString(4);

            System.out.printf("  %-2d | %22s| %10s| %9s| %10s \n", id, address, country, name, surname);
           // System.out.println("---------+-----------------------+-----------+----------+------------");
        }
    }

    public static void showTypes(ResultSet rs)
    {

        System.out.println("      title    | beds | people |  price   ");
        System.out.println("---------------+------+--------+----------");
        for(Row row  : rs)
        {
            String title = row.getString(0);
            float price = row.getFloat(3);
            short beds = row.getShort(1);
            short people = row.getShort(2);

            System.out.printf("  %-12s | %5d| %7d| %8.2f \n", title, beds, people, price);
            //System.out.println("---------------+------+--------+----------");
        }
    }

    public static void showReservations(ResultSet rs)
    {

        System.out.println("     id    |  arrival  | departure | guest_id | room_nr ");
        System.out.println("-----------+-----------+-----------+----------+---------");
        for(Row row  : rs)
        {
            int id = row.getInt(0);
            com.datastax.driver.core.LocalDate arrival = row.getDate(1);
            com.datastax.driver.core.LocalDate departure = row.getDate(2);
            int guest = row.getInt(3);
            short room = row.getShort(4);


            System.out.printf("  %8d | %s| %s| %9d| %7d \n", id, arrival, departure, guest, room);
            //System.out.println("-----------+-----------+---------+-----------+--------");
        }
    }
}

