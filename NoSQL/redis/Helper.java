import redis.clients.jedis.Jedis;

import java.time.LocalDate;
import java.util.*;

public class Helper
{
    public static void generate(Jedis db)
    {
        System.out.println(db.flushAll());

        System.out.println(db.zadd("rooms", 0, "f1:01"));
        System.out.println(db.zadd("rooms", 0, "f1:02"));
        System.out.println(db.zadd("rooms", 1, "f1:03"));
        System.out.println(db.zadd("rooms", 1, "f1:04"));
        System.out.println(db.zadd("rooms", 2, "f1:06"));
        System.out.println(db.zadd("rooms", 1, "f2:01"));
        System.out.println(db.zadd("rooms", 0, "f2:02"));

        System.out.println(db.zadd("rooms", 1, "f2:03"));
        System.out.println(db.zadd("rooms", 1, "f2:04"));
        System.out.println(db.zadd("rooms", 2, "f2:05"));
        System.out.println(db.zadd("rooms", 1, "f3:01"));
        System.out.println(db.zadd("rooms", 2, "f3:02"));
        System.out.println(db.zadd("rooms", 2, "f3:03"));

        System.out.println(db.hset("studio", "price", "38 €"));
        System.out.println(db.hset("studio", "persons", "1"));
        System.out.println(db.hset("studio", "beds", "1"));

        System.out.println(db.hset("twin", "price", "45 €"));
        System.out.println(db.hset("twin", "persons", "2"));
        System.out.println(db.hset("twin", "beds", "2"));

        System.out.println(db.hset("queen", "price", "48 €"));
        System.out.println(db.hset("queen", "persons", "2"));
        System.out.println(db.hset("queen", "beds", "1"));

        System.out.println(db.zadd("room_type", 0, "studio"));
        System.out.println(db.zadd("room_type", 1, "twin"));
        System.out.println(db.zadd("room_type", 2, "queen"));
    }

    /**
     * Reads user input for details.
     *
     * @param sc scanner object
     * @return user details
     */
    public static ArrayList<String> getGuestDetails(Scanner sc)
    {
        //Get guest details
        ArrayList<String> guestDetails = new ArrayList<>();

        System.out.print("Name: ");
        String input = sc.nextLine();
        guestDetails.add(input);

        System.out.print("Surname: ");
        input = sc.nextLine();
        guestDetails.add(input);

        System.out.print("Address: ");
        input = sc.nextLine();
        guestDetails.add(input);

        return guestDetails;
    }

    /**
     * Checks for date validity and returns selected dates.
     *
     * @param sc scanner object
     * @return dates in between selected time slots
     */
    public static ArrayList<String> getDateRange(Scanner sc)
    {

        ArrayList<String> datesInRange = new ArrayList<>();

        while(true)
        {
            //Get user input
            System.out.print("\nPreferred check-in date: ");

            String dateInput = sc.nextLine();

            LocalDate today = java.time.LocalDate.now();

            LocalDate checkIn = LocalDate.parse(dateInput);


            //Check-in has to be ahead of current date, or equal
            if(today.compareTo(checkIn) <= 0)
            {
                System.out.print("Preferred check-out date: ");
                dateInput = sc.nextLine();

                LocalDate checkOut = LocalDate.parse(dateInput);

                int daysBetween = checkOut.compareTo(checkIn);

                //Time between check-in and check-out has to be at least 1 day
                if(daysBetween > 0)
                {
                    for(int i = 0; i < daysBetween; ++i)
                    {
                        LocalDate temp = checkIn.plusDays(i);
                        datesInRange.add(temp.toString());
                    }

                    break;
                }
                else
                    System.out.println("Rooms have to be reserved for at least 1 night.\n");

            }
            else
                System.out.println("Check-in is allowed from " + today + " onwards.\n");
        }

        return datesInRange;
    }

    /**
     * Displays room type data.
     *
     * @param db Redis client
     */
    public static void showRoomTypes(Jedis db)
    {
        //Get size of SORTED SET containing room type information
        long roomTypes = db.zcard("room_type");

        System.out.println("\nROOM TYPE");

        //Show all room type information
        for(int i = 0; i < roomTypes; ++i)
        {
            System.out.print((i + 1) + " ");

            //Get room type names from SORTED SET 'room_type'
            List<String> roomType = db.zrangeByScore("room_type", i, i);

            //Get first and only name on the list
            String roomTypeName = roomType.get(0);

            //Use that name to get room information from HASH 'studio', 'twin', 'queen'
            Map<String, String> typeInfo = db.hgetAll(roomTypeName);

            //Convert retrieved name to uppercase-lowercase
            roomTypeName = roomTypeName.substring(0, 1).toUpperCase() + roomTypeName.substring(1).toLowerCase();

            System.out.println(roomTypeName + " Room");
            System.out.println("---------------------------------------------");

            //Get all key-value pair data from room type HASH
            for(String entry : typeInfo.keySet())
            {
                String key = entry;
                String value = typeInfo.get(entry);

                key = key.substring(0, 1).toUpperCase() + key.substring(1).toLowerCase();
                System.out.println("+ " + key + ": " + value);
            }

            System.out.println();
        }

    }

    /**
     * Reads user input for room type and appends dates in datesInRange with given
     * room type index.
     *
     * @param sc scanner object
     * @param db Redis client
     * @param datesInRange previously specified dates of stay
     * @return room type index or
     *         -1 if selected type does not exist
     */
    public static int selectRoomType(Scanner sc, Jedis db, ArrayList<String> datesInRange)
    {
        //Select room
        System.out.print("Select preferred room type (1-3): ");
        int roomTypeInput = sc.nextInt();
        sc.nextLine();

        //If room type exists
        if(roomTypeInput > 0 && roomTypeInput <= db.zcard("room_type"))
        {
            //Append type to selected dates
            for(int i = 0; i < datesInRange.size(); ++i)
            {
                String temp = datesInRange.get(i);
                datesInRange.set(i, temp + ":" + (roomTypeInput - 1));
            }
        }
        else
        {
            System.out.println("Specified room type does not exist.");
            roomTypeInput = -1;
        }

        return roomTypeInput;
    }

    /**
     * Returns a set of rooms that are available for reservation.
     *
     * @param db Redis client
     * @param roomType room type index
     * @param datesInRange previously specified dates of stay
     * @return all rooms that are available during selected dates
     */
    public static Set<String> getAvailableRooms(Jedis db, int roomType, ArrayList<String> datesInRange)
    {
        //Get all rooms of type
        Set<String> roomSet = new HashSet<>(db.zrangeByScore("rooms", roomType - 1, roomType - 1));

        //Occupied rooms set
        Set<String> markedRooms = new HashSet<>();

        //Get rooms that are occupied during selected dates
        for(int i = 0; i < datesInRange.size(); ++i)
        {
            Set<String> temp = db.smembers(datesInRange.get(i));
            markedRooms.addAll(temp);
        }

        //Get all rooms that are available
        roomSet.removeAll(markedRooms);

        return roomSet;
    }

    /**
     * Displays available rooms.
     *
     * @param availableRooms
     */
    public static void showRooms(Set<String> availableRooms)
    {
        System.out.println("-----------------------------------------------------");
        System.out.println("| ROOMS AVAILABLE");
        System.out.println("+----------------------------------------------------");
        for(String roomNr : availableRooms)
        {
            System.out.println("| Floor: " + roomNr.charAt(1));
            System.out.println("| Room nr: " + roomNr.charAt(3) + roomNr.charAt(4));
            System.out.println("| Code: " + roomNr);
            System.out.println("-----------------------------------------------------");
        }
    }

}
