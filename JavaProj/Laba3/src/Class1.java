import java.util.Scanner;

public class Class1{
    Class1(int n){
        int Scamer;
    };

    boolean  yes_no(int i){
        while (i > 0) {
            int digit = i % 10;
            if (digit == 0 || i % digit != 0) {
                return false;
            }
            i /= 10;
        }
        return true;
    }
    int  run(int n){
        int count = 0;
        for(int i = 1; i < n; i++){
            if(yes_no(i) == true){
                count++;
                System.out.print(String.format("%d", i));
                System.out.println(" ");

            }

        }
        return count;
    }

    public static void main(String[] args) {
        int n;
        Scanner in = new Scanner(System.in);
        n = in.nextInt();
        Class1 obj = new Class1(n);
        int count = obj.run(n);
        System.out.println("count = " + count);

    }
}