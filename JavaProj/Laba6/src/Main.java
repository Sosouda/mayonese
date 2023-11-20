import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args)
    {
        try {
            File file = new File("src/stud.txt");
            Scanner sc = new Scanner(file);
            Spis spis = new Spis();

            while (sc.hasNextLine() )
            {
                String[] info = sc.nextLine().split(" ");
                spis.pushSorted(info[0], Integer.parseInt(info[1]), Float.parseFloat(info[2]));
            }
            sc.close();

            spis.print();
        }
        catch (FileNotFoundException ex){
            System.out.println(ex.getMessage());
        }



    }
}