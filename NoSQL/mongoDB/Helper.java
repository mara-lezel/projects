import com.mongodb.BasicDBObject;
import com.mongodb.DBObject;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoIterable;
import org.bson.Document;
import org.bson.types.ObjectId;

import static com.mongodb.client.model.Filters.eq;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.List;
import java.util.Map;

public class Helper
{
    public static double round(double value, int places)
    {
        if (places < 0) throw new IllegalArgumentException();

        BigDecimal bd = BigDecimal.valueOf(value);
        bd = bd.setScale(places, RoundingMode.HALF_UP);
        return bd.doubleValue();
    }

    public static String capitalize(Object s)
    {
        String str = (String)s;
        return str.substring(0, 1).toUpperCase() + str.substring(1);
    }

    public static void showMenu(MongoIterable<Document> menuItems)
    {
        System.out.println("\n\nMENU");

        System.out.println("Appetizers");
        System.out.println("+--------------------------------------------------");

        for (Document item : menuItems)
        {
            if(item.get("type").equals("appetizer"))
            {
                for (Map.Entry<String, Object> entry : item.entrySet())
                {
                    if(entry.getKey().equals("name"))
                        System.out.print("| " + entry.getValue().toString());

                    if(entry.getKey().equals("price"))
                        System.out.println(" -- " + entry.getValue().toString() + "€");
                }
            }
        }



        System.out.println("\nMain");
        System.out.println("+--------------------------------------------------");

        for (Document item : menuItems)
        {
            if(item.get("type").equals("main"))
            {
                for (Map.Entry<String, Object> entry : item.entrySet())
                {
                    if(entry.getKey().equals("name"))
                        System.out.print("| " + entry.getValue().toString());

                    if(entry.getKey().equals("price"))
                        System.out.println(" -- " + entry.getValue().toString() + "€");
                }
            }
        }


        System.out.println("\nDesserts");
        System.out.println("+--------------------------------------------------");

        for (Document item : menuItems)
        {
            if(item.get("type").equals("dessert"))
            {
                for (Map.Entry<String, Object> entry : item.entrySet())
                {
                    if(entry.getKey().equals("name"))
                        System.out.print("| " + entry.getValue().toString());

                    if(entry.getKey().equals("price"))
                        System.out.println(" -- " + entry.getValue().toString() + "€");
                }
            }
        }


        System.out.println("\nDrinks");
        System.out.println("+--------------------------------------------------");

        for (Document item : menuItems)
        {
            if(item.get("type").equals("drink"))
            {
                for (Map.Entry<String, Object> entry : item.entrySet())
                {
                    if(entry.getKey().equals("name"))
                        System.out.print("| " + entry.getValue().toString());

                    if(entry.getKey().equals("price"))
                        System.out.println(" -- " + entry.getValue().toString() + "€");
                }
            }
        }
    }

    public static void showCustomers(MongoIterable<Document> customers)
    {
        System.out.println("\n\nCUSTOMER INFO");
        int i = 0;
        for (Document customer : customers)
        {
            ++i;
            System.out.println("--+--------------------------------------------------");
            System.out.printf("%02d", i);
            for (Map.Entry<String, Object> entry : customer.entrySet())
            {
                if(entry.getKey().equals("name"))
                    System.out.print("| " + entry.getValue() + " ");

                if(entry.getKey().equals("surname"))
                    System.out.println(entry.getValue());

                if(entry.getKey().equals("address"))
                    System.out.println("  | " + entry.getValue());

            }
        }
        System.out.println("+--------------------------------------------------");
    }

    public static void showOrders(MongoDatabase db, MongoIterable<Document> orders)
    {
        System.out.println("\n\nORDER DETAILS");
        int i = 0;
        for (Document order : orders)
        {
            ++i;
            System.out.println("--+--------------------------------------------------");
            System.out.printf("%02d", i);


            for (Map.Entry<String, Object> entry : order.entrySet())
            {
                //Reference customer_id
                if(entry.getKey().equals("customer"))
                {
                    String customer_id = (String)entry.getValue();

                    Document customer = db.getCollection("customers").
                            find(eq("_id", new ObjectId(customer_id))).first();

                    System.out.print("| Customer: ");

                    for (Map.Entry<String, Object> cEntry : customer.entrySet())
                    {
                        if(cEntry.getKey().equals("name") || cEntry.getKey().equals("surname"))
                            System.out.print(cEntry.getValue() + " ");
                    }
                    System.out.println("\n  |");

                }

                //Reference menu_id array
                else if(entry.getKey().equals("items"))
                {
                    List<Document> list = (List<Document>)entry.getValue();

                    for(Document d : list)
                    {
                        for (Map.Entry<String, Object> mEntry : d.entrySet())
                        {
                            if(mEntry.getKey().equals("menu_id"))
                            {
                                String menu_id = (String)mEntry.getValue();

                                Document menu_item = db.getCollection("menu").
                                        find(eq("_id", new ObjectId(menu_id))).first();

                                for (Map.Entry<String, Object> iEntry : menu_item.entrySet())
                                {
                                    if(iEntry.getKey().equals("name"))
                                        System.out.println("  | + " + iEntry.getValue() + " ");
                                }
                            }
                            else
                            {
                                if(mEntry.getKey().equals("size"))
                                    System.out.println("  |   " + capitalize(mEntry.getValue()) + " ");

                                if(mEntry.getKey().equals("quantity"))
                                    System.out.println("  |   " + capitalize(mEntry.getKey()) + ": " +
                                            mEntry.getValue());
                            }

                        }
                        System.out.println("  |");
                    }
                }



                else if(entry.getKey().equals("payment"))
                {
                    Document payment = (Document)entry.getValue();

                    for (Map.Entry<String, Object> iEntry : payment.entrySet())
                    {
                        if(iEntry.getKey().equals("amount"))
                            System.out.println("  | Total: " + iEntry.getValue() + "€");

                        if(iEntry.getKey().equals("method"))
                            System.out.println("  | " + capitalize(iEntry.getKey()) + ": " +
                                    iEntry.getValue());

                        if(iEntry.getKey().equals("completed"))
                            System.out.println("  | " + capitalize(iEntry.getKey()) + ": " +
                                    iEntry.getValue());
                    }
                }
            }
        }

        System.out.println("--+--------------------------------------------------");
    }
}
